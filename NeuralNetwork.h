#pragma once
#include <cmath>
#include <random>
#include "Matrix.h"
#include "Vector.h"
#include "Data.h"
#include "Timer.h"

void Sigmoid(float& value);
void Sigmoid_Prime(float& value);
void NormalDistribution(float& value);

static const float LEARNING_RATE = 0.005f;
static const float MOMENTUM = 0.8f;

template<unsigned int _Inputs, unsigned int _Outputs, unsigned int _Layers, unsigned int _Neurons>
class NeuralNetwork
{
private:
	Matrix<float, _Inputs, _Neurons>*	_inputMatrixWeights;
	Vector<float, _Neurons>*			_inputBiases;
	Matrix<float, _Neurons, _Outputs>*	_outputMatrixWeights;
	Vector<float, _Outputs>*			_outputBiases;
	Matrix<float, _Neurons, _Neurons>*	_layersMatrixWeights;
	Matrix<float, _Neurons, _Layers>*	_layersBiases;

	Matrix<float, _Neurons, _Layers + 1>* _aValues;
	Matrix<float, _Neurons, _Layers + 1>* _oZPrimeValues;

	Matrix<float, _Neurons, _Layers + 1>* _aErrors;
	 
	float* _inputData;
	float* _outputData;
	unsigned int _sampleCount;
	unsigned int _sampleBatch;
public:
	NeuralNetwork()
	{
		static_assert(
			_Inputs  > 0 ||
			_Outputs > 0 ||
			_Neurons > 0 ||
			_Layers  > 0,
			"Invalid Network Creation"
			);

		srand(std::chrono::system_clock::now().time_since_epoch().count());
		_inputMatrixWeights = new Matrix<float, _Inputs, _Neurons>;
		_inputBiases = new Vector<float, _Neurons>;
		_outputMatrixWeights = new Matrix<float, _Neurons, _Outputs>;
		_outputBiases = new Vector<float, _Outputs>;
		_layersMatrixWeights = new Matrix<float, _Neurons, _Neurons>[_Layers];
		_layersBiases = new Matrix<float, _Neurons, _Layers>;

		_inputMatrixWeights->ApplyToMatrix(NormalDistribution);
		_inputBiases->ApplyToVector(NormalDistribution);
		for (int i = 0; i < _Layers; i++)
			_layersMatrixWeights[i].ApplyToMatrix(NormalDistribution);
		_layersBiases->ApplyToMatrix(NormalDistribution);
		_outputMatrixWeights->ApplyToMatrix(NormalDistribution);
		_outputBiases->ApplyToVector(NormalDistribution);

		(*_inputMatrixWeights) = *_inputMatrixWeights / sqrtf(_Inputs);
		(*_inputBiases) = *_inputBiases / sqrtf(_Inputs);
		for (int i = 0; i < _Layers; i++)
			_layersMatrixWeights[i] = _layersMatrixWeights[i] / sqrtf(_Neurons);
		(*_layersBiases) = *_layersBiases / sqrtf(_Neurons);
		(*_outputMatrixWeights) = *_outputMatrixWeights / sqrtf(_Neurons);
		(*_outputBiases) = *_outputBiases / sqrtf(_Neurons);

		_aValues = new Matrix<float, _Neurons, _Layers + 1>;
		_oZPrimeValues = new Matrix<float, _Neurons, _Layers + 1>;
		_aErrors = new Matrix<float, _Neurons, _Layers + 1>;

	}

	void SetTrainingConfig(float*& inputData, float*& outputData, const unsigned int& sampleCount, const unsigned int& sampleBatch = 1)
	{
		_inputData = inputData;
		_outputData = outputData;
		_sampleCount = sampleCount;
		_sampleBatch = sampleBatch;
		/*
		inputData = nullptr;
		outputData = nullptr;
		*/
	}

	Vector<float, _Outputs> TestSample(const unsigned int& id)
	{
		auto sample = GetSampleInputData(id);
		Vector<float, _Neurons> vec = (*_inputBiases) + ((*_inputMatrixWeights) * sample);
		vec.ApplyToVector(Sigmoid);
		for (unsigned int i = 0; i < _Layers; i++)
		{
			vec = _layersBiases->GetRowVector(i) + (_layersMatrixWeights[i] * vec);
			vec.ApplyToVector(Sigmoid);
		}
		Vector<float, _Outputs> out = (*_outputBiases) + ((*_outputMatrixWeights) * vec);
		out.ApplyToVector(Sigmoid);
		return out;
	}

	void StartTraining()
	{
		Timer t;
		t.Start();
		for (unsigned int j = 0; j < _sampleCount / _sampleBatch; j++)
		{
			Vector<float, _Outputs> gradient;
			Vector<float, _Outputs> outputData;
			Vector<float, _Outputs> expectedOutputData;
			for (unsigned int i = 0; i < _sampleBatch; i++)
			{
				outputData = ProcessSample(GetSampleInputData(j * _sampleBatch + i)); 
				expectedOutputData = GetSampleOutputData(j * _sampleBatch + i);
				auto cost = outputData - expectedOutputData;
				gradient = gradient + cost;
			}
			AdjustNetwork(gradient, GetSampleInputData(j), outputData);
		}
		t.Stop();
		std::cout << "Time Elapsed: " << t.GetCount(t.SECONDS) << std::endl;
	}

	void AdjustNetwork(const Vector<float, _Outputs>& gradient, const Vector<float, _Inputs>& sample, const Vector<float, _Outputs>& output)
	{
		Matrix<float, _Neurons, _Outputs> output_layer_w_error;
		Vector<float, _Outputs> output_layer_b_error = gradient * output * (Vector<float, _Outputs>(1.0f) - output);
		//^ Equivalent to (a-y) * o'(z)

		for (unsigned int i = 0; i < _Outputs; i++)
			output_layer_w_error.SetRowVector(i, _aValues->GetRowVector(_Layers) * output_layer_b_error[i]);
		_aErrors->SetRowVector(_Layers, (_oZPrimeValues->GetRowVector(_Layers) * (_outputMatrixWeights->Transpose() * output_layer_b_error)) * MOMENTUM);
		(*_outputMatrixWeights) = (*_outputMatrixWeights) - (output_layer_w_error.Multiply(LEARNING_RATE));
		(*_outputBiases) = (*_outputBiases) - (output_layer_b_error * LEARNING_RATE);

		for (unsigned int i = 0; i < _Layers; i++)
		{
			Matrix<float, _Neurons, _Neurons> layers_w_error;
			Vector<float, _Neurons> layers_b_error = _aErrors->GetRowVector(_Layers - 1 - i + 1);

			for (unsigned int j = 0; j < _Neurons; j++)
				layers_w_error.SetRowVector(j, _aValues->GetRowVector(_Layers - 1 - i) * layers_b_error[j]);
			_aErrors->SetRowVector(_Layers - 1 - i, (_oZPrimeValues->GetRowVector(_Layers - 1 - i) * (_layersMatrixWeights[_Layers - 1 - i].Transpose() * layers_b_error)) * MOMENTUM);
			_layersMatrixWeights[_Layers - 1 - i] = _layersMatrixWeights[_Layers - 1 - i] - layers_w_error.Multiply(LEARNING_RATE);
			_layersBiases->SetRowVector(_Layers - 1 - i, _layersBiases->GetRowVector(_Layers - 1 - i) - (layers_b_error * LEARNING_RATE));
		}

		Matrix<float, _Inputs, _Neurons> input_layer_w_error;
		Vector<float, _Neurons> input_layer_b_error = _aErrors->GetRowVector(0);

		for (unsigned int i = 0; i < _Neurons; i++)
			input_layer_w_error.SetRowVector(i, sample * input_layer_b_error[i]);

		(*_inputMatrixWeights) = (*_inputMatrixWeights) - input_layer_w_error.Multiply(LEARNING_RATE);
		(*_inputBiases) = (*_inputBiases) - (input_layer_b_error * LEARNING_RATE);
	}

	Vector<float, _Outputs> ProcessSample(const Vector<float, _Inputs>& sample) const
	{
		//Input Layer
		Vector<float, _Neurons> vec = (*_inputBiases) + ((*_inputMatrixWeights) * sample);
		_oZPrimeValues->SetRowVector(0, vec);
		_oZPrimeValues->ApplyToMatrixRow(0, Sigmoid_Prime);
		vec.ApplyToVector(Sigmoid);
		_aValues->SetRowVector(0, vec);

		//Hidden Layers
		for (unsigned int i = 0; i < _Layers; i++)
		{
			vec = _layersBiases->GetRowVector(i) + (_layersMatrixWeights[i] * vec);
			_oZPrimeValues->SetRowVector(i + 1, vec);
			_oZPrimeValues->ApplyToMatrixRow(i + 1, Sigmoid_Prime);
			vec.ApplyToVector(Sigmoid);
			_aValues->SetRowVector(i + 1, vec);
		}

		//Output Layer
		Vector<float, _Outputs> out = (*_outputBiases) + ((*_outputMatrixWeights) * vec);
		out.ApplyToVector(Sigmoid);
		return out;
	}

	float GetTestSampleError(const unsigned int& sampleId)
	{
		auto ans = TestSample(sampleId);
		auto error = ans - GetSampleOutputData(sampleId);
		return error.Magnitude();
	}
	
	inline Vector<float, _Inputs> GetSampleInputData(const unsigned int& sampleId) const { return Vector<float, _Inputs>(&_inputData[sampleId * _Inputs]); }
	inline Vector<float, _Outputs> GetSampleOutputData(const unsigned int& sampleId) const { return Vector<float, _Outputs>(&_outputData[sampleId * _Outputs]); }

	void Serialize() const
	{
		std::ofstream file;
		file.open("data.txt");

		file << "Network Data\n";
		file << "From Left to Right column then Top to Bottom row\n\n";

		file << "InputWeights\n";
		for (unsigned int i = 0; i < _Inputs * _Neurons; i++)
			file << (*_inputMatrixWeights)[0][i] << "\n";

		file << "\nInputBiases\n";
		for (unsigned int i = 0; i < _Neurons; i++)
			file << (*_inputBiases)[i] << "\n";

		file << "\nHiddenWeights\n";
		for (unsigned int j = 0; j < _Layers; j++)
			for (unsigned int i = 0; i < _Neurons * _Neurons; i++)
				file << _layersMatrixWeights[j][0][i] << "\n";

		file << "\nHiddenBiases\n";
		for (unsigned int i = 0; i < _Neurons * _Layers; i++)
			file << (*_layersBiases)[0][i] << "\n";

		file << "\nOutputWeights\n";
		for (unsigned int i = 0; i < _Neurons * _Outputs; i++)
			file << (*_outputMatrixWeights)[0][i] << "\n";

		file << "\nOutputBiases\n";
		for (unsigned int i = 0; i < _Outputs; i++)
			file << (*_outputBiases)[i] << "\n";

		file.close();
	}
	
	~NeuralNetwork()
	{
		delete _inputMatrixWeights;
		delete _inputBiases;
		delete _outputMatrixWeights;
		delete _outputBiases;
		delete _layersBiases;
		delete _aValues;
		delete _oZPrimeValues;
		delete _aErrors;
		delete[] _inputData;
		delete[] _outputData;

		if (_Layers > 1)
			delete[] _layersMatrixWeights;
		else
			delete _layersMatrixWeights;
	}
};

inline void Sigmoid(float& value)
{
	value = 1.0f / (1.0f + exp(-value));
}

void Sigmoid_Prime(float& value)
{
	float temp = value;
	Sigmoid(temp);
	value = temp * (1.0f - temp);
}

void NormalDistribution(float& value)
{
	static std::normal_distribution<float> distribution;
	static std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	value = distribution(generator);
}