// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <iostream>

#include "Game.h"
#include "GFX/Graphics.h"
#include "Controls/Keyboard.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(int argc, char **argv)
{
    Keyboard keyboard;

    Game game(keyboard);

#ifdef TEST_SDL_LOCK_OPTS
    EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

    float t = 0.0f;
    bool close = false;
    while (!close)
    {        
        SDL_Event event;
        /* Poll for events. SDL_PollEvent() returns 0 when there are no  */
        /* more events on the event queue, our while loop will exit when */
        /* that occurs.                                                  */
        while (SDL_PollEvent(&event))
        {
            /* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
            switch (event.type)
            {
            case SDL_KEYDOWN:
                keyboard.KeyDownEvent(event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    close = true;
                }
                break;

            case SDL_KEYUP:
                keyboard.KeyUpEvent(event.key.keysym.sym);
                break;
            default:
                break;
            }
        }

        game.Tick();
    }

    return 0;
}