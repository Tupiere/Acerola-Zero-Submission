#include"main.h"

const float PI = acos(-1);
const float PI_2 = PI/2;
const float PI_4 = PI/4;
const float TAU = 2*PI;
const float RAD = PI/180;
const float DEG = 180/PI;

const float SQRT2 = sqrt(2);
const float SQRT1_2 = sqrt(2)/2;

void program_init(){
    program.run = true;
    program.state = PRGM_MENU;
    SDL_Init(SDL_INIT_EVERYTHING);
    program.window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN_DESKTOP);
    program.renderer = SDL_CreateRenderer(program.window, -1, SDL_RENDERER_ACCELERATED);
    SDL_GetWindowSize(program.window, &screen.width, &screen.height);
    frame.minimum = 1./60;
    font_tileset = load_img("assets/font_tileset.png");
    button_tileset = load_img("assets/button_tileset.png");
}

void program_menu(){
    menu_init();
    while(program.state == PRGM_MENU && program.run){
        menu_input();
        menu_update();
        menu_render();
        menu_framerate();
    }
}

void program_game(){
    game_init();
    while(program.state == PRGM_GAME && program.run){
        game_input();
        game_update();
        game_render();
        game_framerate();
    }
    game_quit();
}

void program_pause(){
    pause_init();
    while(program.state == PRGM_PAUSE && program.run){
        pause_input();
        pause_update();
        pause_render();
        pause_framerate();
    }
    pause_quit();
}

void program_quit(){
    SDL_Quit();
}

SDL_Texture* load_img(const char* file){
    SDL_Surface* surface = IMG_Load(file);
    if(surface == NULL){
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(program.renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void render_texture(SDL_Texture* texture, float x, float y, float w, float h){
    SDL_Rect rectangle = {x - camera.x, y - camera.y, w*camera.zoom, h*camera.zoom};
    SDL_RenderCopy(program.renderer, texture, NULL, &rectangle);
}

void create_button(float x, float y, float size, const char* message){
    if(button_counter >= button_max) return;
    int message_length = strlen(message);
    buttons[button_counter] = (button*)malloc(sizeof(button));
    buttons[button_counter]->x = x;
    buttons[button_counter]->y = y;
    buttons[button_counter]->size = size;
    buttons[button_counter]->message = malloc(message_length + 1);
    strcpy(buttons[button_counter]->message, message);
    button_counter++;
}

void destroy_button(int id){
    if(buttons[id] == NULL || id < 0) return;
    free(buttons[id]);
    for(int i = id; i < button_counter; ++i){
        buttons[i] = buttons[i+1];
    }
    button_counter--;
}

void render_button(int id){
    button* object = buttons[id];
    SDL_Rect button_src, button_dst, font_src, font_dst;
    struct{
        float x, y, size;
    }texture;
    texture.x = camera.zoom*(object->x - camera.x) + screen.width/2;
    texture.y = camera.zoom*(object->y - camera.y) + screen.height/2;
    texture.size = object->size*camera.zoom;
    button_src.x = 0;
    button_src.y = object->state*12;
    button_src.w = 2;
    button_src.h = 12;
    button_dst.x = texture.x;
    button_dst.y = texture.y;
    button_dst.w = texture.size*2;
    button_dst.h = texture.size*12;
    SDL_RenderCopy(program.renderer, button_tileset, &button_src, &button_dst);
    font_src.w = 8;
    font_src.h = 8;
    font_dst.y = (object->state == BUTTON_PRESSED)? texture.y + texture.size*3:
                                                    texture.y + texture.size*2;
    font_dst.w = texture.size*8;
    font_dst.h = texture.size*8;
    button_src.x = 2;
    button_src.w = 8;
    button_dst.w = texture.size*8 + 2;
    int i;
    for(i = 0; object->message[i] != '\0'; ++i){
        button_dst.x = texture.x + texture.size*(i*8 + 2) - 1;
        font_src.x = (object->message[i]%8)*8;
        font_src.y = (object->message[i] < 96)? (object->message[i]/8 - 4)%8*8:
                                                object->message[i]/8%8*8;
        font_dst.x = (object->state == BUTTON_PRESSED)? texture.x + texture.size*(i*8 + 3):
                                                        texture.x + texture.size*(i*8 + 2);
        SDL_RenderCopy(program.renderer, button_tileset, &button_src, &button_dst);
        SDL_RenderCopy(program.renderer, font_tileset, &font_src, &font_dst);
    }
    button_src.x = 10;
    button_src.w = 2;
    button_dst.x = texture.x + texture.size*(i*8 + 2);
    button_dst.w = texture.size*2;
    SDL_RenderCopy(program.renderer, button_tileset, &button_src, &button_dst);
}

void update_button(int id){
    button* object = buttons[id];
    struct{
        float x, y, size;
    }texture;
    texture.x = camera.zoom*(object->x - camera.x) + screen.width/2;
    texture.y = camera.zoom*(object->y - camera.y) + screen.height/2;
    texture.size = object->size*camera.zoom;
    if(in_range(mouse.x, texture.x, texture.x + texture.size*(strlen(object->message)*8 + 4)) &&
       in_range(mouse.y, texture.y, texture.y + texture.size*12)){
        if(SDL_GetMouseState(NULL, NULL) == 1){
            object->state = BUTTON_PRESSED;
            return;
        }
        object->state = BUTTON_HIGHLIGHT;
        return;
    }
    object->state = BUTTON_NEUTRAL;
}

bool in_range(float d, float x1, float x2){
    return d > min(x1, x2) && d < max(x1, x2);
}
