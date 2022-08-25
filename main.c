#include <stdbool.h>
#include <stdio.h>

#include <math.h>

#include <SDL2/SDL.h>

#define FPS                   60
#define DELTA_TIME           (1.0f / FPS)
#define LOGO_IMAGE_SCALE      1.5
#define LOGO_IMAGE_HEIGHT    (53 * LOGO_IMAGE_SCALE)
#define LOGO_IMAGE_WIDTH     (118 * LOGO_IMAGE_SCALE)
#define WIDTH                 640
#define HEIGHT                420
#define LOGO_DEFAULT_VELOCITY 3

void* scp(void* ptr)
{
    if (ptr == NULL) {
        fprintf(stderr, "SDL Pooped itself: %s\n", SDL_GetError());
        exit(1);
    }

    return ptr;
}

void scc(int code)
{
    if (code < 0) {
        fprintf(stderr, "SDL Pooped itself: %s\n", SDL_GetError());
        exit(code);
    }
}

int main(void)
{
    scc(SDL_Init(SDL_INIT_EVERYTHING));
    scc(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"));
    scc(SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"));

    SDL_Window* window = scp(SDL_CreateWindow(
                                 "DVD Logo",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 WIDTH, HEIGHT, 0));
    SDL_Renderer* renderer = scp(SDL_CreateRenderer(window, -1, 0));

    SDL_Surface* dvd_logo_surface = scp(SDL_LoadBMP("dvd.bmp"));
    SDL_Texture* dvd_logo_texture = scp(SDL_CreateTextureFromSurface(renderer, dvd_logo_surface));
    SDL_Rect dvd_logo_rect = {
        .x = 0,
        .y = 0,
        .w = LOGO_IMAGE_WIDTH,
        .h = LOGO_IMAGE_HEIGHT,
    };
    int dvd_logo_x_velocity = LOGO_DEFAULT_VELOCITY;
    int dvd_logo_y_velocity = LOGO_DEFAULT_VELOCITY;

    SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);

        { // Update
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            }


            if (((dvd_logo_rect.x + LOGO_IMAGE_WIDTH) > WIDTH) || (dvd_logo_rect.x < 0)) {
                dvd_logo_x_velocity = -dvd_logo_x_velocity;
            }

            if (((dvd_logo_rect.y + LOGO_IMAGE_HEIGHT) > HEIGHT) || (dvd_logo_rect.y < 0)) {
                dvd_logo_y_velocity = -dvd_logo_y_velocity;
            }

            dvd_logo_rect.x += dvd_logo_x_velocity;
            dvd_logo_rect.y += dvd_logo_y_velocity;
        }

        scc(SDL_RenderCopy(renderer, dvd_logo_texture, NULL, &dvd_logo_rect));

        SDL_RenderPresent(renderer);
        scc(SDL_RenderClear(renderer));

        SDL_Delay((int) floorf(DELTA_TIME * 1000.0f));
    }

    SDL_FreeSurface(dvd_logo_surface);
    SDL_DestroyTexture(dvd_logo_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
