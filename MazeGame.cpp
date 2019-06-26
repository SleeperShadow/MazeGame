// MazeGame.cpp : Defines the entry point for the application.
//

#include "ECS.h"
#include "Game.h"
#include "MazeBuilder.h"
#include "SDL.h"
#include <iostream>

using namespace std;

int
main(int argc, char** argv)
{
  (void)argc;
  (void)argv;

  Game& game = Game::instance();

  auto m = std::make_unique<Manager>();

  game.init("Maze",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1000,
            800,
            false,
            m.get());

  MazeBuilder builder(1);
  builder.buildMaze();
  builder.getMaze().enter();

  const int FPS = 64;
  const int frameDelay = 1000 / FPS;

  uint32_t frameStart;
  int frameTime;

  while (game.running()) {
    frameStart = SDL_GetTicks(); // ticks since SDL init

    game.handleEvents();
    game.update();
    game.render();

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  return 0;
}
