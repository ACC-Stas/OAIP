#include <iostream>
#include <algorithm>

int main()
{
	int t;
	std::cin >> t;
	int n, k;
	int* a;
	int* b;
	int* result;
	std::pair <double, int>* ab;

	
	for (int i = 0; i < t; i++) {
		std::cin >> n >> k;
		a = new int[n];
		b = new int[n];
		result = new int[k];
		ab = new std::pair <double, int>[n];
		for (int j = 0; j < n; j++) {
			std::cin >> a[j];
		}
		for (int j = 0; j < n; j++) {
			std::cin >> b[j];
		}
		double maxResult, hypothesis;
		double left = 0, right = 1000000;
		do {
			hypothesis = (left + right) / 2;
			for (int j = 0; j < n; j++) {
				ab[j].first = a[j] - hypothesis * b[j];
				ab[j].second = j + 1;
			}
			maxResult = 0;
			std::sort(ab, ab + n);
			std::reverse(ab, ab + n);
			for (int j = 0; j < k; j++) {
				maxResult += ab[j].first;
			}
			if (maxResult > 0) {
				left = (left + right) / 2;
			}
			else {
				right = (left + right) / 2;
			}
		} while (maxResult < -0.000001 || maxResult > 0.000001);
		for (int j = 0; j < k - 1; j++) {
			result[j] = ab[j].second;
		}
		result[k-1] = ab[k - 1].second;
		std::sort(result, result + k);
		for (int j = 0; j < k - 1; j++) {
			std::cout << result[j] << " ";
		}
		std::cout << result[k - 1] << "\n";
		delete[] a;
		delete[] b;
		delete[] ab;
		delete[] result;
	}
}