#include "window.h"
#include <iostream>
#include <SDL2/SDL.h>

Window::Window(){
    
}


void Window::close(){

    SDL_DestroyWindow(global_window);
    global_window = NULL;

    SDL_Quit();
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
        
        if (pixels[i] ==1){
            SDL_Rect pixel;
            pixel.x=i%64;
            pixel.y=(int)(i/64);
            pixel.h=1;
            pixel.w=1;
            SDL_RenderFillRect(global_renderer, &pixel);
        }
    }
    SDL_RenderPresent(global_renderer);
}
