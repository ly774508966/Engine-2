#include "Engine.h"
#include <iostream>

Engine::Engine(int width, int height, Game *game)
{
  sdl_manager = new SDLManager(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  glew_manager = new GLEWManager();

  gl_manager = new GLManager(width, height);

  this->game = game;

  quit = false;
}

Engine::~Engine(void)
{
  delete sdl_manager;
  delete glew_manager;
  delete gl_manager;
}

void Engine::start(void)
{
  game->init();

  while (!quit)
  {
    sdl_manager->tick();
    Uint32 delta_time = sdl_manager->getDeltaTime();

    SDL_Event event;
    while (sdl_manager->poll_event(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
          keyHandler.handleEvent(event.key);
          break;
        case SDL_QUIT:
          quit = true;
          break;
      }
    }

    game->update(delta_time, &keyHandler);

    game->render(gl_manager);

    sdl_manager->swapBuffer();
  }
}