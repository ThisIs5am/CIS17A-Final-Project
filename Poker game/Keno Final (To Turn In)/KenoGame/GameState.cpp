#include "GameState.h"

int *GameState::randomNumGen() {
	int* numTemp = new int[10];
	random_device rand;
	mt19937 gen(rand()); //Mersenne Twister pseudo-random number generator
	uniform_int_distribution<> dis(1, 80); // Generate pseudo-random numbers you forgot to put it in bwtn 1-80

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
};
int GameState::playerNumCompare(int player[], int temp[]) {
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
void GameState::winningBetCalc()
{
	switch (timesHit) { // Bet multiplies by 2 and adds 3 for every nth winning number
	case 1:
		//betAmnt = betAmnt * 2;
		balance = balance + (betAmnt * 2);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 2:
		//betAmnt = betAmnt * 5;
		balance = balance + (betAmnt * 5);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 3:
		//betAmnt = betAmnt * 8;
		balance = balance + (betAmnt * 8);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 4:
		//betAmnt = betAmnt * 11;
		balance = balance + (betAmnt * 11);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 5:
		//betAmnt = betAmnt * 14;
		balance = balance + (betAmnt * 14);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 6:
		//betAmnt = betAmnt * 17;
		balance = balance + (betAmnt * 17);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 7:
		//betAmnt = betAmnt * 20;
		balance = balance + (betAmnt * 20);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 8:
		//betAmnt = betAmnt * 23;
		balance = balance + (betAmnt * 23);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 9:
		//betAmnt = betAmnt * 26;
		balance = balance + (betAmnt * 26);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	case 10:
		//betAmnt = betAmnt * 29;
		balance = balance + (betAmnt * 29);
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	default:
		cout << "\nPlayer balance :\t$" << balance << endl;
		break;
	}
};


void GameState::play()
{
	int *temp = randomNumGen();
	playGame = true;
	timesHit = 0;

	if (counterForPlay > 0) {
		randomGen1.clear();
		randomGen2.clear();
		for (int i = 0; i < 80; i++)
		{
			colorChange[i] = false;
		}
	}
	cout << counterForPlay << " <- is the counter for play\n";
	for (int i = 0; i < 10; i++)
	{
		if (i < 5)

			randomGen1.append((to_string(temp[i])) + ", ");
		else
			randomGen2.append((to_string(temp[i])) + ",");
	}
	for (int i = 0; i < 80; i++) {
		if (pressedButton[i] == true) {
			for (int j = 0; j < 10; j++) {
				if (temp[j] == i + 1) {
					colorChange[i] = true;
					timesHit++;
				}
			}
		}
	}
	counterForPlay++;
	winningBetCalc();
}

void GameState::clear()
{
	betAmnt = 0;
	for (int i = 0; i < 80; i++)
	{
		pressedButton[i] = false;
		colorChange[i] = false;
	}

	cout << "\nThe board has been cleared\n";

	timesHit = 0;
	limitCount = 0;
	playGame = false; // fixed clear
	betCont = false;
	randomGen1.clear();
	randomGen2.clear();
}

void GameState::bet()
{
	if (betCont == false) 
	{
		balance -= betAmnt;

		betCont = true;

		cout << "\nThe total bet is " << getBetAmnt() << endl;
	}
}

void GameState::betDecrease()
{
	if (betAmnt > 0 && betCont == false)
	betAmnt -= 10;
	cout << "\nDecrease the the bet amount by 10\n";
}

void GameState::betIncrease()
{
	if (betCont == false && betAmnt < balance)
		betAmnt += 10;
	cout << "\nIncrease the bet amount by 10\n";
}

void GameState::buttonSelect(int i)
{
	if (betCont == true && playGame == false)
	{
		if (pressedButton[i] == true)
		{
			cout << "\nThe number " << i + 1 << " has been pressed" << endl;
			pressedButton[i] = false;
			limitCount--;
		}
		else if (limitCount < 10)
		{
			pressedButton[i] = true;
			limitCount++;
		}
	}
}

string GameState::getRandomGen1() { return randomGen1; }
string GameState::getRandomGen2() { return randomGen2; }
int GameState::getBetAmnt() { return betAmnt; }
int GameState::getBalance() { return balance; }