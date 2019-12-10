#include "UI.h"
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(0));
	bool isRunning = true;
	GameState* game = new GameState;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Final Keno", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, false);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	UI* gameUI = new UI(renderer);

	gameUI->display(renderer, game);

	while (isRunning)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_RenderClear(renderer);
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				gameUI->handle_events(event.motion.x, event.motion.y, game);
				gameUI->display(renderer, game);
			}
			else
				break;
			SDL_Delay(300);
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}