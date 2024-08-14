#ifndef WINDOW_H
#define WINDOW_H
#include <SDL2/SDL.h>

class Window{
    private:
        SDL_Window* global_window = NULL;
        SDL_Surface* global_s_surface = NULL;
        

    public:
        SDL_Renderer* global_renderer = NULL;
        Window();
        bool init();
        bool load();
        void close();
        void update();

        bool open();
        bool input_event();
        bool updateRender(unsigned char pixels[]);
};

#endif