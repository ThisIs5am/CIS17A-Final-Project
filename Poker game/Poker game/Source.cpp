#include <iostream>
#include <random>
using namespace std;

int playerInput(string questionNum) {
	int playerInput = 0;
	do {
		cout << "Enter the " << questionNum << " number : ";//Player number entry
		cin >> playerInput;
		if (playerInput > 80 || playerInput < 0) {
			printf("\nEnter a valid number. Please try again\n"); // Question validator
		}
	} while (playerInput > 80 || playerInput < 0);

	return playerInput;
}
bool playerNextInput() {
	//Variables
	int playerAns = 0;
	bool playerCheck = {};
	//User new # entry question
	do {
		cout << "Would you like to enter another number? {1 = yes, 0 = no}\n";
		cin >> playerAns;
		if (playerAns > 1 || playerAns < 0) {
			printf("\nEnter a valid number. Please try again\n");
		}
		else if (playerAns == 0) {
			playerCheck = true;
		}
	} while (playerAns > 1 || playerAns < 0);

	return playerCheck;
}
int* randomNumberGenerator() {
	//Variables
	int* numTemp = new int[10];
	random_device rand;
	mt19937 gen(rand()); //Mersenne Twister pseudo-random number generator
	uniform_int_distribution<> dis(1, 20); // Generate pseudo-random numbers

	for (int i = 0; i < 10; i++) { // Generate ten pseudo-random numbers
		int randomX;
		bool check;
		do {
			randomX = dis(gen);
			check = true;
			for (int j = 0; j < 10; j++) {//If random number was already made new it makes a new one
				if (randomX == numTemp[j]) {
					check = false;
					break;
				}
			}
		} while (!check);
		numTemp[i] = randomX;
		cout << "\nWinning number " << i + 1 << " : " << randomX;
	}
	return numTemp;
}
void playerNumCompare(int player[], int temp[]) {
	int counter = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (player[i] == temp[j]) {
				cout << "\nNumber Hit : " << player[i]; // If numbers match, show matching number
				counter++;
			}
			else if (i == 9 && j == 9 && counter == 0) {//If no matches then no results
				printf("\nResults\nNo Matches\n");
			}
		}
	}
}


int main() {

	//Variables
	int playerNums[10];
	bool playerCheck = {};
	int playerAns = NULL;
	int counter = 0;
	string questionNum[10] = { "1st","2nd","3rd","4th","5th", "6th", "7th", "8th", "9th", "10th" };

	//User input
	printf("Player pick you're numbers please\n");
	do {
		playerNums[counter] = playerInput(questionNum[counter]);
		playerCheck = playerNextInput();
		counter++;
	} while (!playerCheck || counter > 10);


	//Random number generator
	int* randTemp = randomNumberGenerator();
	cout << endl;

	//Compare numbers
	playerNumCompare(playerNums, randTemp);

	return 0;
}