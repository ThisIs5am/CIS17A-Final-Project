#pragma once

#include "GameState.h"

SDL_Event event;

class UI
{
private:
	SDL_Rect* numButton[80];

	SDL_Surface* temp;
	SDL_Texture* backLayer;
	SDL_Texture* numLayer;
	SDL_Texture* redButtonLayer;
	SDL_Texture* yellowButtonLayer;

	SDL_Rect* randomNumArea1;
	SDL_Rect* randomNumArea2;
	SDL_Rect* betTextArea;
	SDL_Rect* balanceTextArea;
	SDL_Rect* playButton;
	SDL_Rect* clearButton;
	SDL_Rect* betButton;
	SDL_Rect* betIncreaseButton;
	SDL_Rect* betDecreaseButton;

	TTF_Font* font;
	SDL_Color white;
	SDL_Texture* text;

public:
	UI(SDL_Renderer* renderer)
	{
		createTextures(renderer);
		createButtons();
		font = TTF_OpenFont("blowbrush.ttf", 75);
		white = { 255, 255, 255 };
	}

	void createTextures(SDL_Renderer* renderer)
	{
		// Background layer texture
		temp = IMG_Load("Keno_Background.png");
		backLayer = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_FreeSurface(temp);

		// Number layer texture for the buttons
		temp = IMG_Load("Keno_Numbers.png");
		numLayer = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_FreeSurface(temp);

		// Red Button color layer texture
		temp = IMG_Load("Red_Selected_Button.png");
		redButtonLayer = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_FreeSurface(temp);

		// Yellow Button color layer texture
		temp = IMG_Load("Yellow_Won_Button.png");
		yellowButtonLayer = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_FreeSurface(temp);
	}

	void createButtons()
	{
		// Create the 1-80 Number Button mouse click areas
		for (int i = 0; i < 10; i++)
		{
			int x = 406;
			for (int j = i * 8; j < (i + 1) * 8; j++)
			{
				numButton[j] = new SDL_Rect;
				numButton[j]->h = 75;
				numButton[j]->w = 75;
				numButton[j]->x = x;
				numButton[j]->y = 4 + (i * 76);

				x += 77;
			}
		}

		// Text area for the first half of the random generated numbers
		randomNumArea1 = new SDL_Rect;
		randomNumArea1->h = 35;
		randomNumArea1->w = 200;
		randomNumArea1->x = 90;
		randomNumArea1->y = 153;

		// Text area for the second half of the random generated numbers
		randomNumArea2 = new SDL_Rect;
		randomNumArea2->h = 35;
		randomNumArea2->w = 200;
		randomNumArea2->x = 90;
		randomNumArea2->y = 194;

		// Text area for the bet amount
		betTextArea = new SDL_Rect;
		betTextArea->h = 35;
		betTextArea->w = 75;
		betTextArea->x = 260;
		betTextArea->y = 348;

		// Text area for the balance amount
		balanceTextArea = new SDL_Rect;
		balanceTextArea->h = 40;
		balanceTextArea->w = 150;
		balanceTextArea->x = 208;
		balanceTextArea->y = 425;

		// Play Button mouse click area
		playButton = new SDL_Rect;
		playButton->h = 72;
		playButton->w = 173;
		playButton->x = 24;
		playButton->y = 249;

		// Clear Button mouse click area;
		clearButton = new SDL_Rect;
		clearButton->h = 72;
		clearButton->w = 173;
		clearButton->x = 212;
		clearButton->y = 249;

		// Bet Button mouse click area
		betButton = new SDL_Rect;
		betButton->h = 72;
		betButton->w = 173;
		betButton->x = 24;
		betButton->y = 329;

		// Bet increase button mouse click area
		betDecreaseButton = new SDL_Rect;
		betDecreaseButton->h = 40;
		betDecreaseButton->w = 30;
		betDecreaseButton->x = 222;
		betDecreaseButton->y = 346;

		// Bet increase button mouse click area
		betIncreaseButton = new SDL_Rect;
		betIncreaseButton->h = 40;
		betIncreaseButton->w = 30;
		betIncreaseButton->x = 346;
		betIncreaseButton->y = 346;
	}

	void display(SDL_Renderer* renderer, GameState* game)
	{
		//SDL_RenderClear(renderer);

		// Renders the background layer
		SDL_RenderCopy(renderer, backLayer, NULL, NULL);

		// Example text for the random generated numbers
		// I have it split into 2 parts
		// This is the first half
		temp = TTF_RenderText_Solid(font, game->getRandomGen1().c_str(), white);
		text = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_RenderCopy(renderer, text, NULL, randomNumArea1);
		SDL_FreeSurface(temp);

		// This is the second half
		temp = TTF_RenderText_Solid(font, game->getRandomGen2().c_str(), white);
		text = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_RenderCopy(renderer, text, NULL, randomNumArea2);
		SDL_FreeSurface(temp);

		// Text for the bet amount
		temp = TTF_RenderText_Solid(font, to_string(game->getBetAmnt()).insert(0, "$").c_str(), white);
		text = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_RenderCopy(renderer, text, NULL, betTextArea);
		SDL_FreeSurface(temp);

		// Text for the balance
		temp = TTF_RenderText_Solid(font, to_string(game->getBalance()).insert(0, "$").c_str(), white);
		text = SDL_CreateTextureFromSurface(renderer, temp);
		SDL_RenderCopy(renderer, text, NULL, balanceTextArea);
		SDL_FreeSurface(temp);

		// Render number button color changes
		for (int i = 0; i < 80; i++)
		{
			if (game->pressedButton[i] == true)
			{
				if (game->colorChange[i] == false)
					SDL_RenderCopy(renderer, redButtonLayer, NULL, numButton[i]);
				else if (game->colorChange[i] == true)
					SDL_RenderCopy(renderer, yellowButtonLayer, NULL, numButton[i]);
			}
		}
		SDL_RenderCopy(renderer, numLayer, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	void handle_events(int x, int y, GameState* game)
	{
		if ((x > playButton->x) && (x < playButton->x + 173) && (y > playButton->y) && (y < playButton->y + 72))
			game->play();
		else if ((x > clearButton->x) && (x < clearButton->x + 173) && (y > clearButton->y) && (y < clearButton->y + 72))
			game->clear();
		else if ((x > betButton->x) && (x < betButton->x + 173) && (y > betButton->y) && (y < betButton->y + 72))
				game->bet();
		else if ((x > betDecreaseButton->x) && (x < betDecreaseButton->x + 30) && (y > betDecreaseButton->y) && (y < betDecreaseButton->y + 40))
			game->betDecrease();
		else if ((x > betIncreaseButton->x) && (x < betIncreaseButton->x + 30) && (y > betIncreaseButton->y) && (y < betIncreaseButton->y + 40))
			game->betIncrease();
		else
		{
			for (int i = 0; i < 80; i++)
			{
				if ((x > numButton[i]->x) && (x < numButton[i]->x + 75) && (y > numButton[i]->y) && (y < numButton[i]->y + 75))
					game->buttonSelect(i);
			}
		}
	}
};