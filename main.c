#define W 800
#define H 600

#define DEBUG 1

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "chip8.h"

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Texture* texture;

void
c8_initGfx()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Chip8", 
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            800,
                                            600,
                                            SDL_WINDOW_ALLOW_HIGHDPI);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 128, 64);

}

Chip8 c8;

void c8_init();

void c8_run(Chip8* c8, const char* file);

void delay_timer();
void sound_timer();

void
c8_init(Chip8* c8)
{
    // basically we just want to zero out *everything*, have a clean slate for the program
    // uhhh... except keys and all that. we want that
    c8->opcode = 0x200;
    c8->sp &= 0;
    c8->I = 0;

    memset(c8->gfx, 0, sizeof(c8->gfx));
    memset(c8->stack, 0, sizeof(c8->stack));
    memset(c8->V, 0, sizeof(c8->V));

    // uhhh what the hell do i do after this?
    // are we all good? im gonna have to read
    // the thing again

    c8->delay_timer = 0;
    c8->sound_timer = 0;

    // the start of most chip8 programs is 0x200, therefore...
    c8->pc = 0x200;

    // this can be like, the end i think. 
}

void 
c8_run(Chip8* c8, const char* file) 
{

    c8->rom = fopen(file, "rb");
    if(c8->rom == NULL) {
        printf("c8_run: rom cannot be opened!\n");
        exit(1);
    }

    fseek(c8->rom, 0, SEEK_END);
    int fLen = ftell(c8->rom);
    fseek(c8->rom, 0, SEEK_SET);

    fread(c8->memory + 0x200, fLen, 1, c8->rom);
    fclose(c8->rom);

}

int 
main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("usage: ez8 <rom>\n"); 
        return 1;
    }
    
    c8_run(&c8, argv[1]);
    c8_init(&c8);

    srand(time(NULL));

    c8_initGfx();

    return 0;
}
