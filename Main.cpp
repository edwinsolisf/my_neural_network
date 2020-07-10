#include <iostream>
#include <chrono>
#include "Timer.h"
#include "Bitmap.h"
#include "IMAGE_FILE.h"
#include "LABEL_FILE.h"
#include <vector>
#include "NeuralNetwork.h"
#include <thread>

void ActualTime();
void BitmapImage();
void flip_vertically(unsigned char* ptr, const unsigned int& width, const unsigned int& height);
void flip_horizontally(unsigned char* ptr, const unsigned int& width, const unsigned int& height);
void NetworkTest();
inline float Process(const float& val)
{
	return (3.0f * val) + 5.0f;
}
//[m=1,name!="edwinlsf"]
template<unsigned int n>
void Print(const Vector<float, n>& vec)
{
	std::cout << "[ ";
	for (unsigned int i = 0; i < n - 1; i++)
		std::cout << vec[i] << " , ";
	std::cout << vec[n - 1] << " ]" << "\n";
}

int main()
{
	std::cout << "Hello World!" << std::endl;
	//NetworkTest();

	/*
	float* input = new float[8]{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	float* output = new float[4]{
		0.0f, 1.0f, 1.0f, 0.0f
	};

	NeuralNetwork<2, 1, 2, 16> n;
	n.SetTrainingConfig(input, output, 4);
	Print(n.TestSample(0));
	for (int i = 0; i < 20000; i++)
	{
		n.StartTraining();
		float er = n.GetTestSampleError(0);
		er += n.GetTestSampleError(1);
		er += n.GetTestSampleError(2);
		er += n.GetTestSampleError(3);

		std::cout << er << "\n";

		if (er < 0.05f)
		{
			std::cout << i + 1 << "\n";
			break;
		}
	}

	Print(n.TestSample(0));
	Print(n.TestSample(1));
	Print(n.TestSample(2));
	Print(n.TestSample(3));
	*/
	/*int temp = 2;
	std::cout << std::endl;
	std::cout << (float)input[temp] << " " << (float)output[temp] << std::endl;
	*/
	
	std::cin.get();
	return 0;
}

void NetworkTest()
{
	IMAGE_FILE file("data/train-images.idx3-ubyte");
	LABEL_FILE label("data/train-labels.idx1-ubyte");

	Bitmap img("data.bmp", file.GetImageWidth(), file.GetImageHeight(), 24);
	unsigned char* buffer = new unsigned char[file.GetSize() * 3];
	auto temp = file.GetImageData(4);
	flip_vertically(temp, file.GetImageWidth(), file.GetImageHeight());

	for (int i = 0; i < file.GetSize() * 3; i += 3)
	{
		buffer[i] = temp[i / 3];
		buffer[i + 1] = temp[i / 3];
		buffer[i + 2] = temp[i / 3];
	}
	img.WriteImage(buffer);
	img.CreateImage();
	std::cout << (char)(*label.GetItemData(3) + 48) << std::endl;

	Data data;
	data.LoadData(50000, file.GetData(), file.GetSize(), label.GetData(), 10);
	file.FreeData();

	NeuralNetwork<784, 10, 2, 16> network;

	int t = 0;

	std::cout << (char)(*label.GetItemData(t) + 48) << std::endl;
	network.SetTrainingConfig(data._inputData, data._outputData, 50000);
	auto before = network.TestSample(t);
	for (int i = 0; i < 1000; i++)
	{
		network.SetTrainingConfig(data._inputData, data._outputData, 50 * (i + 1));
		network.StartTraining();
		Print(network.TestSample(t));
		std::cout << network.GetTestSampleError(t) << "\n";
	}
	Print(before);
	Print(network.GetSampleOutputData(t));
	Print(network.TestSample(t));

	std::cout << "-------------------------------\n";
	for (int i = 0; i < 20; i++)
	{
		Print(network.GetSampleOutputData(i));
		Print(network.TestSample(i));
		std::cout << "-------------------------------\n";
	}

	network.Serialize();

	std::cin.get();

}

void BitmapImage()
{
	unsigned char* buffer = new unsigned char[255 * 255 * 3]{};
	for (int i = 0; i < 255; i++)
	{
		for (int j = 0; j < 255; j++)
		{
			buffer[3 * (i * 255 + j)] = (i*j) % 255;//b
			buffer[3 * (i * 255 + j) + 1] = j % 255;//g
			buffer[3 * (i * 255 + j) + 2] = i % 255;//r
		}
	}
	
	Bitmap image("image.bmp", 255, 255);
	image.WriteImage(buffer);
	if (image.CreateImage())
		std::cout << "Success!" << std::endl;

	Bitmap img2("image.bmp");
	img2.Read();
	std::shared_ptr<unsigned char> data = img2.GetImageData();
	Bitmap img3("img2.bmp", img2.GetImageWidth(), img2.GetImageHeight());
	img3.WriteImage(&(*data));
	img3.CreateImage();
	img3.FreeImageData();

	delete[] buffer;
}
void ActualTime()
{
	using namespace std::chrono_literals;

	auto time = 5s;
	auto thistime = std::chrono::system_clock::now().time_since_epoch().count();

	Timer timer;
	
	for (int i = 0; i < 5; i++)
	{
		/*timer.Reset();
		timer.Start();*/
		auto past = std::chrono::high_resolution_clock::now();
		for (int j = 0; j < 10; j++)
			std::this_thread::sleep_for(1ms);
		auto present = std::chrono::high_resolution_clock::now();

		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(present - past).count() << " us " << std::endl;
		/*timer.Stop();*/
		
		/*std::cout << timer.GetCount(Timer::MILI_SECONDS) << " ms" << std::endl;*/
	}

	std::cin.get();
}


void flip_vertically(unsigned char* ptr, const unsigned int& width, const unsigned int& height)
{
	for (unsigned int i = 0; i < height / 2; i++)
	{
		if (i != height - 1 - i)
		{
			unsigned char temp = 0;
			for (unsigned int j = 0; j < width; j++)
			{
				temp = ptr[(height - 1 - i)*width + j];
				ptr[(height - 1 - i)*width + j] = ptr[i*width + j];
				ptr[i* width + j] = temp;
			}
		}
	}
}

void flip_horizontally(unsigned char* ptr, const unsigned int& width, const unsigned int& height)
{
	for (unsigned int i = 0; i < height; i++)
	{
		unsigned char temp = 0;
		for (unsigned int j = 0; j < width/2; j++)
		{
			if (i != width - i - 1)
			{
				temp = ptr[(i + 1)*width - j - 1];
				ptr[(i + 1)*width - j - 1] = ptr[i*width + j];
				ptr[i* width + j] = temp;
			}
		}
	}
}
