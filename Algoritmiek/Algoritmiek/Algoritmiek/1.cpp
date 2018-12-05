
#include <iostream>
#include <algorithm>
#include <array>
#include <stdio.h> 
#include <cstdlib>
#include <chrono>

using namespace std ::chrono;

// Driver program to test above functions 
int main()
{
	const int length = 10000;
	int arr[length];
	char yn;
	int count = 0;
	int times[10];

	do
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = rand();
			//std::cout << arr[i] << std::endl;
		}

		auto start = high_resolution_clock::now();

		size_t size = sizeof(arr) / sizeof(arr[0]);
		std::sort(arr, arr + size);
		for (size_t i = 0; i < size; ++i) {
			std::cout << arr[i] << ' ';
		}

		auto stop = high_resolution_clock::now();

		auto duration = duration_cast<microseconds>(stop - start);

		times[count] = duration.count();

		std::cout << std::endl << std::endl << duration.count() * 0.000001 << "  seconds" << std::endl << std::endl;

		count++;
	} while (count < 10);
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << times[i] * 0.000001 << std::endl;
	}

	return 0;
}
