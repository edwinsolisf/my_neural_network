#pragma once

class Data
{
public:
	float* _inputData;
	float* _outputData;

	unsigned int _inputsPerSample;
	unsigned int _outputsPerSample;
	unsigned int _samples;
public:
	Data()
		:_samples(0), _inputData(nullptr), _inputsPerSample(0), _outputData(nullptr), _outputsPerSample(0)
	{
	}

	void LoadData(const unsigned int& samples, void* inputData, const unsigned int& inputsPerSample, void* outputData, const unsigned int& outputsPerSample)
	{
		_samples = samples;
		_inputData = new float[samples * inputsPerSample];
		_inputsPerSample = inputsPerSample;
		_outputData = new float[samples * outputsPerSample]{};
		_outputsPerSample = outputsPerSample;
		for (unsigned int i = 0; i < samples * inputsPerSample; i++)
		{
			int temp = 0;
			char* c = (char*)&temp;
			*c = ((char*)inputData)[i];
			_inputData[i] = temp;
		}

		for (unsigned int i = 0; i < samples; i++)
		{
			int temp = 0;
			char* c = (char*)&temp;
			*c = ((char*)outputData)[i];
			_outputData[i * outputsPerSample + temp] = 1.0f;
		}
	}

	~Data()
	{
		delete[] _inputData;
		delete[] _outputData;

		_inputData = nullptr;
		_outputData = nullptr;
	}

};