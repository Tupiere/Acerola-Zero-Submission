#include"main.h"

int main(int argc, char* argv[]){
    program_init();
    while(program.run){
        switch(program.state){
        case PRGM_MENU:
            program_menu();
            break;
        case PRGM_GAME:
            program_game();
            break;
        case PRGM_PAUSE:
            program_pause();
        }
    }
    program_quit();
    return 0;
}
