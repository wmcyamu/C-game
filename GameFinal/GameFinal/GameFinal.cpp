#include "window.h"
#include "player.h"
//#include "Log.h"
#include "menu.h"
#include "enemy.h"
//#include "collision.h"
#include "timer.h"


Window window("Cube Survival, CGP2011M-2-1819, Oskar Sobon, 16608908", 1080, 760);
player _player(window, 60, 60, 100, 100, 0, 0, 200, 255);
enemy _enemy(window, 60, 60, 100, 100, 139, 0, 0, 255);

bool AABB(const SDL_Rect & recA, const SDL_Rect & recB)
{

	/*printf("recA.h %i - recA.w %i \n", recA.h, recA.w);
	printf("recA.x %i - recA.y %i \n", recA.x, recA.y);

	printf("---");
	printf("recB.h %i - recB.w %i \n", recB.h, recB.w);
	printf("recB.x %i - recB.y %i \n", recB.x, recB.y);*/

	if (
		recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y + recA.h >= recB.y &&
		recB.y + recB.h >= recA.y
		)
	{
		return true;

	}

	return false;
}


void pollEvents(Window &window, player &_player, enemy &_enemy, Menu &_menu)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		_menu.pollevent(event);
		_player.pollEvents(event);
		window.pollEvents(event);
		_enemy.pollEvents(event);
	}
}


void onWindowResize_callback()
{
	std::cout << "windwo resized\n" << std::endl;
	WindowSize size = window.getWindowSize();
	_player.setpos(size.width / 2, size.height / 2);
	_enemy.setpos(size.width / 2, size.height / 2);
}

//void TimeFunc()
//{
//	std::cout << EngineUtils::Timer::Instance()->DeltaTime() << std::endl;
//}

int main(int argc, char* argv[])
{
	EngineUtils::Timer * timer = EngineUtils::Timer::Instance();
	printf("timer init sucess\n");
	//Log log;

	window.setWindowResizeCallback(onWindowResize_callback);
	onWindowResize_callback();

	Menu _menu(window._renderer);
	printf("menu loaded successfuly\n");


	std::vector<enemy*> enemies;


	//for (int i = 0; i < 1; i++)
	//{
	//	WindowSize size = window.getWindowSize();

	//	int x = rand() % size.width;
	//	int y = 0;//rand() % size.height;

	//	enemy* badguy = new enemy(window, 100, 100, x, y, 137, 0, 0, 255);
	//	enemies.push_back(badguy);
	//}

	int lastTicks = 0;
	int ticks = 0;
	float elapsedTime = 0.0f;
	int frames = 0;
	int sec;
	sec = 0;



	while (!window.isClosed())
	{

		//_player.pollEvents();
		pollEvents(window, _player, _enemy, _menu);
		window.clear();
		//window.pollEvents();


		if (_menu.menuActive == true)
		{

			_menu.Render(window._window, window._renderer);
			_menu.Menufunc();
		}


		else
		{

			timer->Tick();
			//timer->Reset();
			elapsedTime += timer->DeltaTime();
			//frames++;
			//if (elapsedTime >= 1.0f)
			//{
			//	std::cout << "time: " << elapsedTime << std::endl;
			//	//TimeFunc();
			//	elapsedTime = 0.0f;
			//	//frames = 0;
			//}
			if (elapsedTime > 2000)
			{
				sec++;
				elapsedTime = 0;
				std::cout << "time: " << sec << std::endl;
			}

			if (sec >= 60)
			{
				std::cout << "game fin" << std::endl;
				std::cout << "you survived gz" << std::endl;
				SDL_Delay(1500);
				exit(0);
			}

			int diff = SDL_GetTicks() - lastTicks;

			ticks += diff;

			if (ticks > 200)
			{
				printf("spawn an enemy!!\n");

				WindowSize size = window.getWindowSize();

				int x = rand() % size.width;
				int y = 0;//rand() % size.height;

				enemy* badguy = new enemy(window, 60, 60, x, y, 137, 0, 0, 255);
				enemies.push_back(badguy);

				ticks = 0;
			}


			int mtime = 0;

			mtime += timer->DeltaTime();

			_player.draw();



			//_enemy.draw();

			for (int i = 0; i < enemies.size(); i++)
				enemies[i]->draw();


			bool collide = AABB(_player.mccollider, _enemy.encollider);

			//printf("There's a collision: %d \n", collide);

			if (mtime<500)
			{
				mtime = 0;
				_enemy.move();
				for (int i = 0; i < enemies.size(); i++)
					enemies[i]->move();
			}

			//printf("pos %i", _enemy.__x);
			//_enemy.DEBUG_getpos();
		}
		EngineUtils::Timer::Release;

		lastTicks = SDL_GetTicks();

		window.present();


	}

	return 0;
}