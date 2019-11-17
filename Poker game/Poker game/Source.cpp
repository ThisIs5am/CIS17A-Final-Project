//Basic Keno Logic
//Added betting in game
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
bool playerNextInput(int balance, int bet) {
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
		else if (balance < bet) { // Check if invalid balance
			cout << "\n\nInvalid Bet. Low Balance. Procceding with game.\n\n";
			playerCheck = true;
		}
		else if (playerAns == 0) { // Check if user does not want another # 
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
int playerNumCompare(int player[], int temp[]) {
	int counter = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (player[i] == temp[j]) {
				cout << "\nNumber Hit : \t#" << player[i]; // If numbers match, show matching number
				counter++;
			}
			else if (i == 9 && j == 9 && counter == 0) {//If no matches then no results
				printf("\nResults\nNo Matches\n");
			}
		}
	}
	return counter;
}


int main() {

	//Variables
	int playerNums[10];
	bool playerCheck = {};
	int playerAns = NULL;
	int playerBetAns = NULL;
	int counter = 0;
	string questionNum[10] = { "1st","2nd","3rd","4th","5th", "6th", "7th", "8th", "9th", "10th" };
	bool betCheck = false;
	int playerBalance = 100;
	int playerBet = 0;

	//User bet input
	do {
		cout << "Player Balance :\t$" << playerBalance << endl;
		cout << "Player Bet :\t\t$" << playerBet << endl;
		cout << "Enter you're bet\n1 = Increase\n2 = Decrease\n3 = Enter)\n";
		cin >> playerBetAns;
		switch (playerBetAns) {
		case 1:
			if (playerBalance < 5) {
				system("cls");
				cout << "Balance insufficient\n\n";
			}
			else {
				playerBet = playerBet + 5;
				playerBalance = playerBalance - 5;
				system("cls");
			}
			break;
		case 2:
			if (playerBet < 5) {
				system("cls");
				cout << "Player bet is $0\n Enter again\n\n";
			}
			else {
				playerBet = playerBet - 5;
				playerBalance = playerBalance + 5;
				system("cls");
			}
			break;
		case 3:
			betCheck = true;
			break;
		}

	} while (!betCheck);

	//User # input
	printf("Player pick you're numbers please\n");
	do {
		playerNums[counter] = playerInput(questionNum[counter]); // Ask user #input
		if (counter != 0) { // If 1st question then it does not subtract bet from balance, it already happened
			playerBalance = playerBalance - playerBet;
		}
		cout << "\nBalance:\t$" << playerBalance << endl;
		cout << "Player Bet\t$" << playerBet << endl;
		playerCheck = playerNextInput(playerBalance, playerBet); //Ask if user wants another # input or not
		counter++; // Loop # increases
	} while (!playerCheck || counter > 9);

	//Random number generator
	int* randTemp = randomNumberGenerator();
	cout << endl;

	//Compare numbers
	int winningNums = playerNumCompare(playerNums, randTemp);

	//Winning bet calculation
	switch (winningNums) { // Bet multiplies by 2 and adds 2 for every nth winning number
	case 1:
		playerBet = playerBet * 2;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 2:
		playerBet = playerBet * 4;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 3:
		playerBet = playerBet * 6;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 4:
		playerBet = playerBet * 8;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 5:
		playerBet = playerBet * 10;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 6:
		playerBet = playerBet * 12;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 7:
		playerBet = playerBet * 14;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 8:
		playerBet = playerBet * 16;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 9:
		playerBet = playerBet * 18;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	case 10:
		playerBet = playerBet * 20;
		playerBalance = playerBalance + playerBet;
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	default:
		cout << "\nPlayer balance :\t$" << playerBalance << endl;
		break;
	}

	return 0;
}