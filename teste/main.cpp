#include <iostream>
#include "../classes/GameManager.h"
#include "../classes/Ia.h"
#include "../classes/Maze.h"
#include "../classes/Snake.h"

int main(int argc, const char *argv[]){
    GameManager God;
      
    if(God.prepareBigBang(argc, argv)){
        God.welcomeToParadise();
        God.BigBang();
    }

    return 0;
}