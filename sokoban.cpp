#include "sokoban.h"

void Sokoban::printMap(){
    // cout << "\033[2J\033[1;1H"; //清空終端機
    // cout << end << endl;
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            //cout << map[i][j];
            if (map[i][j] == '0')
                cout << "☺";
            else if (map[i][j] == '1')
                cout << "□";
            else if (map[i][j] == '/')
                cout << "𝄪";
            else if (map[i][j] == '2')
                cout << "☆";
            else if (map[i][j] == '-')
                cout << " ";
        }
        cout << endl;
    }
    cout << "A: left" << endl << "D: right" << endl << "W: up" << endl << "S: down" << endl << "R: reset" << endl << "Q: quit"<< endl;
}

void Sokoban::setMap(){
    fstream f;
    //int x, y;
    win = 0;
    end = 0;
    f.open("mission3.txt", ios::in);
    f >> x >> y;

//開map的記憶體
    map.resize(x);
    for(int i = 0; i < x; i++)
        map[i].resize(y);
    
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            f >> map[i][j];
            if(map[i][j] == '0'){  //判斷玩家位置
                px = i;
                py = j;
            }
            if(map[i][j] == '2'){  //判斷終點的位置
                destination[end].first = i;
                destination[end].second = j;
                end++;
            }
        }
    }
    f.close();

    printMap();
}

void Sokoban::Game(){
    int quit = 0;
    while(1 && quit != 1){
        //偵測鍵盤
        system("stty -icanon");
        int move = getchar();
        int x_move = 0, y_move = 0;
        switch (move)
        {
        case 'a': case 'A':
            y_move -= 1;
            break;
        case 's': case 'S':
            x_move += 1;
            break;
        case 'w': case 'W':
            x_move -= 1;
            break;
        case 'd': case 'D':
            y_move += 1;
            break;
        case 'r': case 'R':
            setMap();
            break;
        case 'q': case 'Q':
            quit = 1;
            break;
        default:
            break;
        }

        int next_x = px + x_move;
        int next_y = py + y_move;
        int next_next_x = next_x + x_move;
        int next_next_y = next_y + y_move;

        if(map[next_x][next_y] == '-' || map[next_x][next_y] == '2'){  //前面沒有推箱子
            for(int i = 0; i < end; i++){
                if(px == destination[i].first && py == destination[i].second){
                    map[px][py] = '2';
                    break;
                }
                else
                    map[px][py] = '-';
            }

            map[next_x][next_y] = '0';
            px = next_x;
            py = next_y;
        }
        if(map[next_x][next_y] == '1' && (map[next_next_x][next_next_y] == '2' || map[next_next_x][next_next_y] == '-')){  //前面有箱子
            for(int i = 0; i < end; i++){
                if(px == destination[i].first && py == destination[i].second){
                    map[px][py] = '2';
                    break;
                }
                else
                    map[px][py] = '-';
            }
            for(int i = 0; i < end; i++){
                if(next_next_x == destination[i].first && next_next_y == destination[i].second)
                    win++;
                else if(next_x == destination[i].first && next_y == destination[i].second)
                    win--;
            }
            map[next_x][next_y] = '0';
            map[next_next_x][next_next_y] = '1';
            px = next_x;
            py = next_y;
        }
        printMap();
        
        if(win == end){
            cout << "You win!" << endl;
            break;
        }
    }
}