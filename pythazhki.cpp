#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

class RussianFlag {
private:
    static const int SIZE = 4;
    int board[SIZE][SIZE];
    int emptyRow, emptyCol;
    int movescount;
    void setColor(int c) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        switch(c) {
            case 1: SetConsoleTextAttribute(h, 15); break;
            case 2: SetConsoleTextAttribute(h, 9); break;
            case 3: SetConsoleTextAttribute(h, 12); break;
            default: SetConsoleTextAttribute(h, 0);
        }
    }
    void resetColor() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    
public:
    RussianFlag() : movescount(0) {
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(i == 0) {
                    board[i][j] = 1;
                }
                else if(i == 1) {
                    board[i][j] = 2;
                }
                else if(i == 2) {
                    board[i][j] = 3;
                }
                else {
                    board[i][j] = 0;
                }
            }
        }
        emptyRow = 3; emptyCol = 0;
        srand(time(0));
        for(int k = 0; k < 200; k++) {
            int dir = rand() % 4;
            int r = emptyRow, c = emptyCol;
            if (dir == 0 && r > 0) {
                r--;
            }
            else if(dir == 1 && r < SIZE-1) {
                r++;
            }
            else if(dir == 2 && c > 0) {
                c--;
            }
            else if(dir == 3 && c < SIZE-1) {
                c++;
            }
            if (r != emptyRow || c != emptyCol) {
                board[emptyRow][emptyCol] = board[r][c];
                board[r][c] = 0;
                emptyRow = r; emptyCol = c;
            }
        }
    }
    
    void show() {
        system("cls");
        resetColor();
        cout << "SOBERI ROSSIYSKIY FLAG!\n";
        cout << "Hodov: " << movescount << "\n\n";
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                if(board[i][j] == 0) {
                    cout << "[ ] ";
                } else {
                    setColor(board[i][j]);
                    cout << "██ ";
                    resetColor();
                }
            }
            cout << endl;
        }
        cout << "\nUpravlenie: WASD (dvigat pustuyu kletku)\n";
        cout << "Q - vyhod\n> ";
    }
    
    bool move(char cmd) {
        cmd = tolower(cmd);
        int r = emptyRow, c = emptyCol;
        if(cmd == 'w' && r < SIZE-1) {
            r++;
        }
        else if(cmd == 's' && r > 0) {
            r--;
        }
        else if(cmd == 'a' && c < SIZE-1) {
            c++;
        }
        else if(cmd == 'd' && c > 0) {
            c--;
        }
        else if(cmd == 'q') {
            return false;
        }
        else {
            return true;
        }
        if(r != emptyRow || c != emptyCol) {
            board[emptyRow][emptyCol] = board[r][c];
            board[r][c] = 0;
            emptyRow = r; emptyCol = c;
            movescount++;
        }
        return true;
    }
    
    bool checkWin() {
        for(int i = 0; i < SIZE; i++) {
            for(int j = 0; j < SIZE; j++) {
                int correct = 0;
                if(i == 0) {
                    correct = 1;
                }
                else if(i == 1) {
                    correct = 2;
                }
                else if(i == 2) {
                    correct = 3;
                }
                if(board[i][j] != correct) {
                    return false;
                }
            }
        }
        return true;
    }
    
    void play() {
        while(true) {
            show();
            if(checkWin()) {
                cout << "\nPOBEDA! Flag sobran!\n";
                system("pause");
                break;
            }
            char cmd = _getch();
            if(!move(cmd)) {
                break;
            }
        }
    }
};

int main() {
    RussianFlag game;
    game.play();
    return 0;
}