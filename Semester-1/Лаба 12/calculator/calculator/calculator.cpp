#include <iostream>
#include <string>
#include <algorithm>;
#include <stack>

class Calculator {
private:
	std::stack <char> operators;
	std::string mathLine, polishNote = " ";
	void infixToRPN() {
		std::getline(std::cin, mathLine);
		mathLine = " " + mathLine;
		for (int i = 0; i < mathLine.length(); i++) {
			if (mathLine[i] >= '0' && mathLine[i] <= '9') {
				polishNote = polishNote + " ";
				do {
					polishNote = polishNote + mathLine[i];
					i++;
					if (i == mathLine.length()) {
						break;
					}
				} while (mathLine[i] >= '0' && mathLine[i] <= '9');
				i--;
			}
			else if (mathLine[i] == '-' && (mathLine[i - 1] == ' ' || mathLine[i-1] == '(') && mathLine[i + 1] >= '0' && mathLine[i + 1] <= '9') {   //unary minus
				polishNote = polishNote + " ";
				do {
					polishNote = polishNote + mathLine[i];
					i++;
					if (i == mathLine.length()) {
						break;
					}
				} while (mathLine[i] >= '0' && mathLine[i] <= '9');
				i--;
			}
			else if (mathLine[i] != ' ') {
				if (operators.empty()) {
					operators.push(mathLine[i]);
				}
				else if (mathLine[i] == '(') {
					operators.push(mathLine[i]);
				}
				else if (mathLine[i] == ')') {
					while (operators.top() != '(') {
						polishNote = polishNote + " " + operators.top();
						operators.pop();
					}
					operators.pop();
				}
				else if (mathLine[i] == '+' || mathLine[i] == '-') {
					if (operators.top() == '(') {
						operators.push(mathLine[i]);
					}
					else {
						polishNote = polishNote + " " + operators.top();
						operators.pop();
						operators.push(mathLine[i]);
					}
				}
				else if (mathLine[i] == '*' || mathLine[i] == '/') {
					if (operators.top() == '(' || operators.top() == '+' || operators.top() == '-') {
						operators.push(mathLine[i]);
					}
					else {
						polishNote = polishNote + " " + operators.top();
						operators.pop();
						operators.push(mathLine[i]);
					}
				}
				else if (mathLine[i] == '^') {
					if (operators.top() == '(' || operators.top() == '+' || operators.top() == '-' || operators.top() == '*' || operators.top() == '/') {
						operators.push(mathLine[i]);
					}
					else {
						polishNote = polishNote + " " + operators.top();
						operators.pop();
						operators.push(mathLine[i]);
					}
				}
			}
		}
		while (!operators.empty()) {
			polishNote = polishNote + " " + operators.top();
			operators.pop();
		}
	}
public:
	void calculate() {
		infixToRPN();
		std::stack<long long> numbers;
		std::string number;
		for (int i = 0; i < polishNote.length(); i++) {
			if (polishNote[i] >= '0' && polishNote[i] <= '9') {
				number = "";
				do {
					number = number + polishNote[i];
					i++;
				} while (polishNote[i] >= '0' && polishNote[i] <= '9');
				i--;
				numbers.push(std::atoi(number.c_str()));
			}
			else if (polishNote[i] == '-' && polishNote[i + 1] >= '0' && polishNote[i + 1] <= '9') {
				number = "";
				i++;
				do {
					number = number + polishNote[i];
					i++;
				} while (polishNote[i] >= '0' && polishNote[i] <= '9');
				i--;
				numbers.push(-1 * std::atoi(number.c_str()));
			}
			else if (polishNote[i] != ' ') {
				long long temp;
				switch (polishNote[i]) {
				case '+':
					temp = numbers.top();
					numbers.pop();
					temp = numbers.top() + temp;
					numbers.pop();
					numbers.push(temp);
					break;
				case'-':
					temp = numbers.top();
					numbers.pop();
					temp = numbers.top() - temp;
					numbers.pop();
					numbers.push(temp);
					break;
				case'*':
					temp = numbers.top();
					numbers.pop();
					temp = numbers.top() * temp;
					numbers.pop();
					numbers.push(temp);
					break;
				case'/':
					temp = numbers.top();
					numbers.pop();
					temp = numbers.top() / temp;
					numbers.pop();
					numbers.push(temp);
					break;
				case'^':
					temp = numbers.top();
					numbers.pop();
					temp = std::pow(numbers.top(), temp);
					numbers.pop();
					numbers.push(temp);
					break;
				default:
					break;
				}
			}
		}
		std::cout << numbers.top() << "\n";
	}
	void showRPN() {
		infixToRPN();
		std::cout << polishNote << "\n";
	}
};

 
int main() {
	Calculator a1;
	a1.showRPN();
	a1.calculate();
	a1.calculate();
	return 0;
}