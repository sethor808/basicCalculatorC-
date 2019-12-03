//////////////////////////////////////////////////////////////////
//This is a simple calculator meant to practice making full applications for the user
//Created by: Seth Orr Robinson
//Created: 11/29/2019
//Last worked on: 12/2/2019
//Sources: 
//https://cal-linux.com/tutorials/strings.html - used to reinforce that I can use std::string the same in C++ as I did in C
//http://www.cplusplus.com/reference/cctype/isdigit/ - reference on how to use isdigit and isalpha from <cctype>
//////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

float convertToNum(std::string, int); //Converts user inputted numbers from string to floats
void printFunctions(); //Prints the functionality list of the calculator
void runCalculations(float[], char[], int, int); //Handles all calculations after user input occurs
void reorder(float[], char[], int, int, int, int); //Used to reorder the arrays as calculations run through

bool running = true; //Main loop control
bool error = false; //Error flag to avoid crashes

const int MAX_TERMS = 50; //TODO: Convert this into a dynamic array or a list of some sort

int main() {

	//Initial greeting of the user
	std::cout << "Welcome to Seth O.R.'s calculator, to see the list of supported math functions, please input 'f' for functions." << std::endl
		<< "To exit the application, please enter 'q' for quit." << std::endl
		<< "Otherwise, please begin by entering your equations." << std::endl
		<< ">";

	//Main application loop
	while (running) {
		
		float equation[MAX_TERMS] = { 0 }; //This will hold all user inputted terms
		int totalTerms = 0; //Keeps track of how many elements are in the equation array
		char operators[MAX_TERMS]; //This will hold all operators inputted
		int operatorsIndex = 0; //Keeps track of many elements are in the operator array
		int previousIndex = 0; //Bookmarking value for the application to remember the last element visited
		std::string input; //All input goes into this string

		error = false;

		std::getline(std::cin, input);

		//If the user inputs 'q' the application should exit the loop immediately
		if (input == "q") {
			std::cout << "Quitting application now." << std::endl;
			running = false;
		}

		//If the user inputs 'f' the application should print all the funcionality of the application and continue with the loop
		else if(input == "f"){
			printFunctions();
		}

		//If no other specified command is stated, the application runs through through the following code, the bulk of the processing
		else {
			//Checks each char in the string individually
			for (int i = 0; i <= input.length(); i++) {

				//If any of the char in the string is not a digit, it assumes that is an operator and makes every char 
				//before it up to the previous index as a number. If any char is a letter, this loop is left.
				//TODO: Add proper error handling for when a non-operator is inputted, such as '@' and ','
				if (!isdigit(input[i]) || input[i] == '\0') {
					std::string temp = ""; //Throw away string to help with the conversion process

					//Exits the loop if a letter is inputted, skipping the calculations and avoiding any bugs.
					if (isalpha(input[i])) {
						std::cout << "Error, please input numeric values only. This feature may become available at another time." << std::endl;
						error = true;
						exit;
					}

					//Creates a string (temp) that is a copy of all the numbers from one operator to the next
					for (int j = previousIndex; j < i; j++) {
						temp = temp + input[j];
					}

					operators[operatorsIndex] = input[i]; //Stores the operator
					previousIndex = i + 1; //Keeps track of the last operator stopped at
					equation[totalTerms] = convertToNum(temp, temp.length()); //Converts temp and stores it
					operatorsIndex++; 
					totalTerms++;
				}
			}

			if (!error) {
				//Once all the numbers have been sifted out and the operators stored, runCalculations crunches the numbers
				runCalculations(equation, operators, totalTerms, operatorsIndex);

				//Prints out the answer
				std::cout << "> = " <<
					equation[0] << std::endl;

				//Sets up the next input
				std::cout << ">";
			}
		}
	}

	std::cout << "Thank you for using Seth O.R.'s Calculator." << std::endl;
	return 0;

}

float convertToNum(std::string input, int length) {
	
	int x = 0;
	
	for (size_t i = 0; i < length; i++)
	{
		int y = input[i] - '0';
		x = x + y * (pow(10, length - i - 1));
		
	}

	return x;

}

void runCalculations(float numbers[], char operators[], int totalNumbers, int totalOperators) {

	for (size_t i = 0; i < totalOperators; i++)
	{
		if(operators[i] == '*') {
			numbers[i] = numbers[i] * numbers[i + 1];
			reorder(numbers, operators, totalNumbers, totalOperators, i+1, i);
			totalNumbers--;
			totalOperators--;
			i = -1;
		}
		else if (operators[i] == '/') {
			numbers[i] = numbers[i] / numbers[i + 1];
			reorder(numbers, operators, totalNumbers, totalOperators, i + 1, i);
			totalNumbers--;
			totalOperators--;
			i = -1;
		}
	}

	for (size_t i = 0; i < totalOperators; i++)
	{
		if (operators[i] == '+') {
			numbers[i] = numbers[i] + numbers[i + 1];
			reorder(numbers, operators, totalNumbers, totalOperators, i + 1, i);
			totalNumbers--;
			totalOperators--;
			i = -1;
		}
		else if (operators[i] == '-') {
			numbers[i] = numbers[i] - numbers[i+1];
			reorder(numbers, operators, totalNumbers, totalOperators, i + 1, i);
			totalNumbers--;
			totalOperators--;
			i = -1;
		}
	}

}

void reorder(float numbers[], char operators[], int numberMax, int operatorMax, int numberToDelete, int operatorToRemove) {

	//Simple loop to run through and remove an element that is no longer neeeded

	for (int i = numberToDelete; i < numberMax; i++)
	{
		numbers[i] = numbers[i + 1];
	}
	numbers[numberMax - 1] = 0;

	for (int i = operatorToRemove; i < operatorMax; i++)
	{
		operators[i] = operators[i + 1];
	}
	operators[operatorMax - 1] = NULL;

}

void printFunctions() {
	
	std::string currentFunctionality =
		"Current supported functions:\n\tAdd, subtract, divide, multiply.\nNext to be added:\n\tExponent support, parantheses support, decimal number input, negative number input.";

	std::cout << currentFunctionality << "\n>";

}