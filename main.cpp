#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isNumeric(const std::string& str) {
	bool hasDecimalPoint = false;
	int start = 0;

	if (str[0] == '-') {
		start = 1;
		if (str.length() == 1) {
			return false;
		}
	}
	for (int i = start; i < str.length(); ++i) {
		if (str[i] == '.') {
			if (hasDecimalPoint) {
				return false;
			}
			hasDecimalPoint = true;
		}
		else if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool isInteger(const std::string& str) {
	int start = 0;

	if (str[0] == '-') {
		start = 1;
		if (str.length() == 1) {
			return false;
		}
	}
	for (int i = start; i < str.length(); ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

bool isValidInput(const std::string& input) {
	return input.length() == 1 && (input[0] == 'f' || input[0] == 'k');
}
bool isValidChoice(const std::string& input) {
	return input.length() == 1 && (input[0] == 'y' || input[0] == 'n');
}

int main()
{
	string input;
	do {
		double a = 0, b = 0, step = 0;
		int n = 0;
		bool validInput_1 = false;
		bool validInput_2 = false;
		bool validInput_3 = false;

		while (!validInput_1) {
			std::cout << "You want to load data from file or input from keyboard? (f = file; k = keyboard): ";
			getline(cin, input);

			if (isValidInput(input)) {
				validInput_1 = true;
			}
			else {
				std::cout << "You need to enter only one character ('f' or 'k'). Try again." << std::endl;
			}
		}

		if (input == "f")
		{
			std::cout << "You chose to load data from file." << std::endl;
			std::cout << "Important! To enter floating point data, use '.'" << std::endl;
			ifstream inputFile("input.txt");
			if (!inputFile.is_open())
			{
				std::cout << "Create input.txt, in directory with this code-file, and add 4 separated numbers in txt. The numbers order: a, b, step, n." << endl;
				return 1;
			}
			if (!(inputFile >> a >> b >> step >> n))
			{
				std::cout << "Error: File input.txt is empty or does not contain enough data, not correct data. Make sure it has 4 numbers (a, b, step, n)." << endl;
				return 1;
			}
			if (b < a)
			{
				std::cout << "The b (end of the range) have to be bigger than a (start of the range). Check your file, second number is b and try again." << endl;
			}
			if (step <= 0)
			{
				std::cout << "The step have to be bigger than zero. Check your file, third number is step and try again." << endl;
			};
			if (n <= 1)
			{
				std::cout << "Integer n have to be bigger than 1! Check your file, fourth number is n and try again." << endl;
				return 1;
			}
			else
			{
				inputFile.close();
				std::cout << "Data from file are loaded" << endl;
				std::cout << "a = " << a << ", b = " << b << ", step = " << step << ", n = " << n << endl;
				while (!validInput_2) {
					std::cout << "Is your data correct? Type y - if yes, n - if no: ";
					getline(cin, input);
					if (isValidChoice(input)) {
						validInput_2 = true;
					}
					else {
						std::cout << "You need to enter only one character ('y' or 'n'). Try again." << std::endl;
					}
					if (input == "n")
					{
						std::cout << "Change your data in the file and try again. Closing program...";
						return 1;
					}
				}
			}
		}
		else if (input == "k")
		{
			std::cout << "You chose to input data from keyboard." << std::endl;
			std::cout << "Important! To enter floating point data, use '.'" << std::endl; 
			do {
				do {
					std::cout << "Input a (start of the range): ";
					cin >> input;
					if (!isNumeric(input)) {
						std::cout << "Invalid input. Please enter a numeric value." << std::endl;
					}
					else {
						a = stod(input);
						break;
					}
				} while (true);
				do {
					std::cout << "Input b (end of the range): ";
					cin >> input;
					if (!isNumeric(input) || stod(input) <= a) {
						std::cout << "Invalid input. Please enter a numeric value and b must be greater than a." << std::endl;
					}
					else {
						b = stod(input);
						break;
					}
				} while (!isNumeric(input) || b < a);
				do {
					std::cout << "Input step: ";
					cin >> input;
					if (!isNumeric(input) || stod(input) <= 0) {
						std::cout << "Invalid input. Please enter a numeric value greater than 0." << std::endl;
					}
					else {
						step = stod(input);
						break;
					}
				} while (true);

				do
				{
					std::cout << "Input n (n > 1): ";
					cin >> input;
					if (!isInteger(input) || stoi(input) <= 1) {
						std::cout << "Invalid input. Please enter an INTEGER value greater than 1." << std::endl;
					}
					else {
						n = stoi(input);
						break;
					}
				} while (true);

				std::cout << "a = " << a << ", b = " << b << ", step = " << step << ", n = " << n << endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				while (!validInput_2)
				{
					std::cout << "Is your data correct? Type y - if yes, n - if no: ";
					getline(cin, input);
					if (isValidChoice(input)) {
						validInput_2 = true;
					}
					else {
						std::cout << "You need to enter only one character ('y' or 'n'). Try again." << std::endl;
					}
				}
				if (input == "n")
				{
					std::cout << "You choose input your data again." << endl;
				}
			} while (input == "n");
		}

		std::cout << "Detailed calculation: " << endl;

		ofstream outputFile("output.txt");
		if (!outputFile.is_open())
		{
			std::cerr << "Error: Could not create output.txt. Check permissions or directory." << endl;
			return 1;
		}

		std::cout << "--------------------------------------" << endl;
		std::cout << "|   x    	  | y		     |" << endl;
		std::cout << "--------------------------------------" << endl;

		outputFile << "--------------------------------------" << endl;
		outputFile << "|   x   	  | y		     |" << endl;
		outputFile << "--------------------------------------" << endl;

		for (double x = a; x <= b; x += step)
		{
			double result = 0;
			if (x < 0)
			{
				double y = 0;
				for (int i = 0; i <= n; i++)
				{
					double p = 1;

					for (double j = 0; j <= n + 1; j++)
					{
						p *= (i - j / 2.0);
						std::cout << "i = " << i << ", j = " << j << ", p = " << p << endl;
					}
					y += p;
					std::cout << "y after i = " << i << " equals " << y << endl;
				}
				result = y;
			}
			else
			{
				double y = 1;

				for (int j = 1; j <= n; j++)
				{
					y *= (j / (x + 3 * j));
					std::cout << "j = " << j << ", y after dividing = " << y << endl;
				}
				result = y + x;
			}
			int i_plus = 1;
			std::cout << "--------------------------------------" << endl;
			std::cout << "|   x_" << i_plus << " = " << x << "       |   y_" << i_plus << " = " << result << "       |" << endl;
			outputFile << "|   x_" << i_plus << " = " << x << "      |   y_" << i_plus << " = " << result << "       |" << endl;
			std::cout << "--------------------------------------" << endl;
			i_plus++;
		}
		outputFile << "--------------------------------------" << endl;
		outputFile.close();
		std::cout << " \nDone! Your result in output.txt. I hope and pray that you enjoyed of all this calculations, because i hate this" << endl;

		while (!validInput_3) {
			std::cout << "Would you like to run the program again? (y - yes, n - no): ";
			getline(cin, input);
			if (isValidChoice(input)) {
				validInput_3 = true;
			}
			else {
				std::cout << "You need to enter only one character ('y' or 'n'). Try again." << std::endl;
			}
		}
	} while (input == "y");
	
	std::cout << "Thank you for using the program. I hope we won't see each other anymore!" << std::endl;
	return 0;
}
