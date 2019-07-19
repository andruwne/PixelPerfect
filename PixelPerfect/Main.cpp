#include "include.h"
#include "pixel.h"
#include "line.h"

#define LANGUAGE CPP

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;
const int FLAGS = SDL_WINDOW_SHOWN;

int errnum;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Surface* bmp;
SDL_Event event;

int pixel_test ();
int image_test ();
int line_test ();
int setup ();
int input ();

int main (int argc, char* argv[]) {
    errnum == 0;
    char* test;
    char* arg_check; memcpy (arg_check, argv[1], 8);
    if (argc < 1 || strcmp (arg_check, "--test=") != 0) {
        test = argv[1];
    } else {
        perror ("At least one test must be specified using --test=");
        errnum == -1;
    }

    errnum == setup ();
    if (errnum != 0) {
        return exit () || errnum;
    }

    if (strcmp (test, "--test=line") == 0) {
        line_test ();
    } else {
        perror ("Not using line test");
    }

    if (strcmp (test, "--test=image") == 0) {
        image_test ();
        perror ("Not using image test");
    } else {

    }

    if (strcmp (test, "--test=pixel") == 0) {
        pixel_test ();
    } else {
        perror ("Valid test not found");
        return exit () || errnum;
    }

    while (true) {
        errnum == input ();
        if (errnum != 0) {
            return exit () || errnum;
        }
        errnum == SDL_RenderClear (renderer);
        if (errnum != 0) {
            return exit () || errnum;
        }
        errnum == SDL_RenderCopy (renderer, texture, NULL, NULL);
        if (errnum != 0) {
            return exit () || errnum;
        }
        errnum == SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
        if (errnum != 0) {
            return exit () || errnum;
        }
        errnum == SDL_RenderDrawLine (renderer, 0, 0, WIDTH, HEIGHT);
        if (errnum != 0) {
            return exit () || errnum;
        }
        SDL_RenderPresent (renderer);
        SDL_Delay (1000);
    }

    return exit () || errnum;
}


int input () {
    while (SDL_PollEvent (&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_q:
                        return -1;
                    default:
                        break;
                }
        }
    }
    return 0;
}

int setup () {
    if (SDL_Init (SDL_INIT_VIDEO) != 0) {
        fprintf (stderr, "Video initialization failed: %s\n",
                 SDL_GetError ());
        SDL_Quit ();
        return 1;
    }

    SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow ("PixelPerfect", 100, 100, WIDTH, HEIGHT, FLAGS);
    if (window == nullptr) {
        fprintf (stderr, "Video mode set failed: %s\n",
                 SDL_GetError ());
        SDL_Quit ();
        return 1;
    }

    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow (window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError () << std::endl;
        SDL_Quit ();
        return 1;
    }

    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);

    return 0;
}

int exit () {
    SDL_DestroyTexture (texture);
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit ();
    return 0;
}

int line_test () {
    return 0;
}

int pixel_test () {
    pixel p1;
    p1.init (0, 0, 0, 255);
    printf ("INIT\n");
    printf ("red: %u\n", p1.r);
    printf ("green: %u\n", p1.g);
    printf ("blue: %u\n", p1.b);
    printf ("alpha: %u\n", p1.a);

    pixel p2;
    p2.init (0, 0, 0, 255);
    p2.set (0xFF0000FF);
    printf ("SET RED\n");
    printf ("red: %u\n", p2.r);
    printf ("green: %u\n", p2.g);
    printf ("blue: %u\n", p2.b);
    printf ("alpha: %u\n", p2.a);

    BYTE* byte_arr = p1.pack ();
    printf ("PACKED\n");
    printf ("red: %u\n", byte_arr[2]);
    printf ("green: %u\n", byte_arr[1]);
    printf ("blue: %u\n", byte_arr[0]);
    printf ("alpha: %u\n", byte_arr[3]);

    printf ("SHIFT\n");
    int hex_value = 0xFFFFFF;
    printf ("%d >> 8 = %d", hex_value, hex_value >> 8);
    return 0;
}

int image_test () {
    std::string imagePath = "image.bmp";
    bmp = SDL_LoadBMP (imagePath.c_str ());
    if (bmp == nullptr) {
        SDL_DestroyRenderer (renderer);
        SDL_DestroyWindow (window);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError () << std::endl;
        SDL_Quit ();
        return 1;
    }

    texture = SDL_CreateTextureFromSurface (renderer, bmp);
    SDL_FreeSurface (bmp);
    if (texture == nullptr) {
        SDL_DestroyRenderer (renderer);
        SDL_DestroyWindow (window);
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError () << std::endl;
        SDL_Quit ();
        return 1;
    }

    return 0;
}