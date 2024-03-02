#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include<math.h>
#include<string.h>
#include<time.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#define min(a, b) ((a < b)? a: b)
#define max(a, b) ((a > b)? a: b)

#define button_max 256

extern const float PI, PI_2, PI_4, TAU, RAD, DEG, SQRT2, SQRT2_2;

enum program_state{
    PRGM_MENU,
    PRGM_GAME,
    PRGM_PAUSE
};

enum menu_screen{
    MENU_MAIN,
    MENU_OPTNS
};

enum pause_screen{
    PAUSE_MAIN,
    PAUSE_OPTNS
};

enum button_state{
    BUTTON_NEUTRAL = 0,
    BUTTON_HIGHLIGHT,
    BUTTON_PRESSED
};

struct{
    bool run;
    int state;
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;
}program;

struct{
    int screen;
}menu;

struct{
    SDL_Surface* surface;
}game;

struct{

}pause;

struct{
    long start;
    float time, minimum;
}frame;

struct{
    int x, y;
}mouse;

struct{
    int width, height;
}screen;

struct{
    float x, y, zoom;
}camera;

struct{
    float x, y, dx, dy, width, height, speed, jump;
}player;

typedef struct{
    float x, y, size;
    char* message;
    int state;
    void (*on_click)();
}button;

int button_counter;
button* buttons[button_max];

SDL_Texture* font_tileset;
SDL_Texture* button_tileset;

void program_init();
void program_menu();
void program_game();
void program_pause();
void program_quit();

void menu_init();
void menu_input();
void menu_update();
void menu_render();
void menu_framerate();
void menu_quit();

void game_init();
void game_input();
void game_update();
void game_render();
void game_framerate();
void game_quit();

void pause_init();
void pause_input();
void pause_update();
void pause_render();
void pause_framerate();
void pause_quit();

SDL_Texture* load_img(const char* file);
void render_texture(SDL_Texture* texture, float x, float y, float w, float h);

void create_button(float x, float y, float size, const char* message);
void destroy_button(int id);
void update_button(int id);
void render_button(int id);

bool in_range(float d, float x1, float x2);
