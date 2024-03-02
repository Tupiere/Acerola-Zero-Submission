#include"main.h"

void menu_parse_events(){
    SDL_Event event;
    while(SDL_PollEvent(&event) > 0){
        switch(event.type){
        case SDL_QUIT:
            program.run = false;
        break;
        }
    }
}

void menu_parse_keys(){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if(keystate[SDL_SCANCODE_ESCAPE]){
        program.run = false;
    }
    if(keystate[SDL_SCANCODE_D]){
        camera.x += 10;
    }
    if(keystate[SDL_SCANCODE_A]){
        camera.x -= 10;
    }
    if(keystate[SDL_SCANCODE_S]){
        camera.y += 10;
    }
    if(keystate[SDL_SCANCODE_W]){
        camera.y -= 10;
    }
    if(keystate[SDL_SCANCODE_EQUALS]){
        camera.zoom += .005;
    }
    if(keystate[SDL_SCANCODE_MINUS]){
        camera.zoom -= .005;
    }
    if(keystate[SDL_SCANCODE_R]){
        camera.x = 0;
        camera.y = 0;
        camera.zoom = 1;
    }
}

void menu_init(){
    camera.x = screen.width/2;
    camera.y = screen.height/2;
    camera.zoom = 1;
    create_button(64, 64, 4, "BUTTON");
    create_button(512, 128, 1, "lowercase text");
    create_button(128, 512, 6, "Hello, world!");
    create_button(700, 600, 5, "wheeeeee :3");
}

void menu_input(){
    frame.start = clock();
    menu_parse_events();
    menu_parse_keys();
    SDL_GetMouseState(&mouse.x, &mouse.y);
}

void menu_update(){
    int i;
    for(i = 0; i < button_counter; ++i){
        update_button(i);
    }
}

void menu_render(){
    SDL_SetRenderDrawColor(program.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(program.renderer);
    int i;
    for(i = 0; i < button_counter; ++i){
        render_button(i);
    }
    SDL_RenderPresent(program.renderer);
}

void menu_framerate(){
    frame.time = (clock() - frame.start)/CLOCKS_PER_SEC;
    if(frame.time < frame.minimum){
        SDL_Delay((frame.minimum - frame.time)*1000);
    }
}

void menu_quit(){

}
