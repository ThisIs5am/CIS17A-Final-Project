#pragma once
#include <iostream>
#include <random>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class GameState
{
private:
	int randomNumGenerator;
	int playerWinningNumbers;
	int counterForPlay = 0;
	int timesHit = 0;
	int limitCount = 0;
	int betAmnt = 0;
	int balance = 100; // edit this
	string randomGen1;
	string randomGen2;
	bool betCont = false;
	bool playGame = false;

public:
	bool pressedButton[80] = { false };
	bool colorChange[80] = { false };

	void showBalance(int balance);
	int *randomNumGen();
	int playerNumCompare(int player[], int temp[]);
	void winningBetCalc();

	void play();
	void clear();
	void bet();
	void betDecrease();
	void betIncrease();
	void buttonSelect(int i);

	string getRandomGen1();
	string getRandomGen2();
	int getBetAmnt();
	int getBalance();
};
