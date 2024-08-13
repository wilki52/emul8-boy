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

        

            bool quit = false;
            SDL_Event e;

            while (!quit){
                while(SDL_PollEvent(&e)!=0){
                    if (e.type==SDL_QUIT){
                        quit = true;
                    }

                }

                SDL_FillRect(global_s_surface, NULL, SDL_MapRGB( global_s_surface->format, 0xFF, 0xFF, 0xFF ) );
                SDL_UpdateWindowSurface( global_window );



            
        }

    }
    close();
}

bool Window::open(){
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) >=0){
        std::cout << "window opened" << std::endl;
        SDL_CreateWindowAndRenderer(640, 320, 0, &global_window, &global_renderer);
        SDL_RenderSetScale(global_renderer, 10, 10);
        SDL_SetRenderDrawColor(global_renderer, 255, 255, 255, 255);
        //SDL_RenderClear(global_renderer);

        
        SDL_RenderPresent(global_renderer);
         return success;
    }
    std::cout << "failed to open" << std::endl;
    return false;
   

}

bool Window::updateRender(unsigned char pixels[]){
    SDL_SetRenderDrawColor(global_renderer, 0, 0, 0, 255);
    SDL_RenderClear(global_renderer);
    SDL_SetRenderDrawColor(global_renderer, 255, 255, 255, 255);
    for (int i=0; i < 64*32; i++){
        
        //SDL_SetRenderDrawColor(global_renderer, 0, 0, 0, 255);
        //SDL_RenderClear(global_renderer);
        if (pixels[i] ==1){
            SDL_Rect pixel;
            pixel.x=i%64;
            pixel.y=(int)floor(i/64);
            pixel.h=1;
            pixel.w=1;
            SDL_RenderFillRect(global_renderer, &pixel);
        }
    }
    SDL_RenderPresent(global_renderer);
    
    //SDL_FillRect(global_s_surface, NULL, SDL_MapRGB( global_s_surface->format, 0xFF, 0xFF, 0xFF ) );
    //SDL_UpdateWindowSurface( global_window );

}

bool Window::input_event(){


}