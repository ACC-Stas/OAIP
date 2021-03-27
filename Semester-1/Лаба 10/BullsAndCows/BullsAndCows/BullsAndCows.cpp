#include <iostream>
#include <string>
#include <fstream>


class game {
private:
	bool sieve[10000] = { false };
	void analyse(std::string Number, int bulls, int cows) {
		std::string supposedNumber, currentNumber;
		currentNumber = Number;
		int supposedBulls, supposedCows;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					for (int f = 0; f < 10; f++) {
						if (f != k && f != j && f != i && k != j && k != i && j != i) {
							supposedNumber = std::to_string(i * 1000 + j * 100 + k * 10 + f);
							supposedBulls = 0; supposedCows = 0;
							for (int x = 0; x < 4; x++) {
								for (int y = 0; y < 4; y++) {
									if (currentNumber[x] == supposedNumber[y] && x == y) {
										supposedBulls++;
									}
									else if (currentNumber[x] == supposedNumber[y] && x != y) {
										supposedCows++;
									}
								}
							}
							if (supposedBulls != bulls || supposedCows != cows) {
								sieve[i * 1000 + j * 100 + k * 10 + f] = false;
							}
						}
					}
				}
			}
		}
	}
public:
	void play() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					for (int f = 0; f < 10; f++) {
						if (f != k && f != j && f != i && k != j && k != i && j != i) {
							sieve[i * 1000 + j * 100 + k * 10 + f] = true;
						}
					}
				}
			}
		}
		int cows = 0, bulls = 0, counter = 0;
		std::string currentNumber;
		do {
			counter++;
			for (int i = 0; i < 10000; i++) {
				if (sieve[i]) {
					if (i < 1000) {
						std::cout << "0" << i << "\n";
						currentNumber = "0" + std::to_string(i);
						sieve[i] = false;
						break;
					}
					std::cout << i << "\n";
					currentNumber = std::to_string(i);
					sieve[i] = false;
					break;
				}
			}
			std::cin >> bulls >> cows;
			analyse(currentNumber, bulls, cows);
		} while (bulls != 4);
		std::cout << "Game over with " << counter;
	}
};

int main() {
	game number1;
	number1.play();
	return 0;
}