#include <iostream>
#include <vector>
#include <curses.h>
#include "sokoban.h"
using namespace std;
int main(){
    Sokoban sokoban;
    sokoban.setMap();
    sokoban.Game();
    return 0;
}