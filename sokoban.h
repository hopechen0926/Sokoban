#include <iostream>
#include <fstream>
#include <vector>
#include <curses.h>
#include <utility>
//#include <cstdlib>
#include <unistd.h>
using namespace std;
class Sokoban{
private:
    int x, y;
    int px, py;  //玩家當下位置
    vector < vector<char> > map;
    pair <int, int> destination[10];  //存終點的xy座標
    int end;  //終點有幾個
    int win;  //判斷輸贏
public:
    void setMap();  //設置地圖
    void printMap();  //畫地圖
    void Game();  //遊戲過程
};
