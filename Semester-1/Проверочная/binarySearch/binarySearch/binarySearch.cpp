#include <iostream>


int main() {
	int n;
	std::cin >> n;
	int* numbers = new int[n+1];
	for (int i = 0; i < n; i++) {
		std::cin >> numbers[i];
	}
	int k;
	std::cin >> k;
	int request, b, l, r, left, right, mid;
	for (int i = 0; i < k; i++) {
		std::cin >> request;
		numbers[n] = numbers[n - 1] + request + 1;
		b = 0;
		l = -1;
		r = -1;
		if (request < numbers[0]) {
			l = 0;
			r = 0;
		}
		else if (request > numbers[n - 1]) {
			l = n;
			r = n;
		}
		else {
			left = 0;
			right = n;
			while (left < right) {
				mid = (left + right) / 2;
				if (request <= numbers[mid]) {
					right = mid;
				}
				else {
					left = mid + 1;
				}
			}
			l = left;
			if (request == numbers[l]) {
				b = 1;
			}
			left = 0;
			right = n;
			while (left < right) {
				mid = (left + right) / 2;
				if (request >= numbers[mid]) {
					left = mid + 1;
				}
				else {
					right = mid;
				}
			}
			r = left;
		}
		std::cout << b << " " << l << " " << r << "\n";
	}
}