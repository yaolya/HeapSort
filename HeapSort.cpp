#include <iostream> 
#include <chrono>
#include <algorithm>


void printArray(int arr[], int n)
{
	for (int i = 1; i < n + 1; ++i)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

void MaxHeapify(int A[], int n, int i) {
	int l = 2 * i;
	int r = 2 * i + 1;
	int largest = i;
	if (l <= n && A[l] > A[i]) largest = l;
	else largest = i;
	if (r <= n && A[r] > A[largest]) largest = r;
	if (largest != i) {
		std::swap(A[i], A[largest]);
		MaxHeapify(A, n, largest);
	}
}

void BuildMaxHeap(int A[], int n) {

	for (int i = n / 2; i > 0; i--) {
		MaxHeapify(A, n, i);
	}
}

void HeapSort(int A[], int n)
{
	BuildMaxHeap(A, n);

	for (int i = n; i >= 1; i--)
	{
		std::swap(A[1], A[i]);
		MaxHeapify(A, i - 1, 1);
	}
}

int* generateArray(int n, int min, int max) {
	srand(time(NULL));
	int* array = new int[n+1];
	for (int i = 1; i <= n; i++) {
		array[i] = min + rand() % (max - min + 1);
	}
	return array;
}


int main()
{
	int min, max, num_of_iterations;
	std::cout << "input min, max, number of iterations: ";
	std::cin >> min >> max >> num_of_iterations;
	for (int n = 10; n < 10000; n+=10) {
		int* ar = generateArray(n, min, max);
		printArray(ar, n);
		double sum = 0;
		for (int j = 0; j < num_of_iterations; j++) {
			auto start_time = std::chrono::steady_clock::now();
			HeapSort(ar, n);
			auto end_time = std::chrono::steady_clock::now();
			auto sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
			sum += sort_time.count();
		}
		double average_time_for_iteration = sum / num_of_iterations;
		printArray(ar, n);
		std::cout << "iteration: " << n/10 << " time: " << average_time_for_iteration << std::endl;
		delete[] ar;
	}

	return 0;
}