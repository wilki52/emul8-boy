#include "window.h"
#include <iostream>
#include <SDL2/SDL.h>

Window::Window(){
    
}

bool Window::init(){
    bool success = true;

    //initialize
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error:  "<< SDL_GetError() << std::endl;
        success = false;
    }
    else{
        //create window
        global_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 64, 32, SDL_WINDOW_SHOWN);
        if (global_window == NULL)
        {
            std::cout << "SDL could not initialize! SDL_Error: " << std::endl;
            success = false;
        }
        else{
            //get window surface of window.
            global_s_surface = SDL_GetWindowSurface(global_window);
            
            //SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; }}
        }
    }
    
    return success;
}

bool Window::load(){
    bool success = true;

    SDL_Surface* hello_world;
    if (hello_world == NULL){
        std::cout << "goodbye world" << std::endl;
        //success = false;
    }
    else{
        SDL_BlitSurface( hello_world, NULL, global_s_surface, NULL );
    }

    return success;
    
}

void Window::close(){

    SDL_DestroyWindow(global_window);
    global_window = NULL;

    SDL_Quit();
}

void Window::update(){

    if (init()){

        if (load()){

            bool quit = false;
            SDL_Event e;

            while(!quit){
                while(SDL_PollEvent(&e)!=0){
                    if (e.type==SDL_QUIT){
                        quit = true;
                    }

                }

                SDL_FillRect(global_s_surface, NULL, SDL_MapRGB( global_s_surface->format, 0xFF, 0xFF, 0xFF ) );
                SDL_UpdateWindowSurface( global_window );



            }
        }

    }
    close();
}