#include<iostream>
#include<map>
#include<string>
void reset(char board[3][3]);
bool checkmove(char m, int r, int c, bool turn, char board[3][3],bool verbose);
bool move(char m, int r, int c, bool turn, char board[3][3]);
void reset(char board[3][3]);
void print(char board[3][3]);
bool crow(char board[3][3]);
bool ccol(char board[3][3]);
bool chor(char board[3][3]);
bool fin(char board[3][3]);
bool gameEnds(char m, bool turn, char board[3][3], int winningMoves);

    int main() {
        char board[3][3];
        reset(board);
        bool game = true;
        bool turn = 1; //1 for 'O';
        std::cout<<"Play tictactoe\n";
        std::cout<<"To move, input a 3 char string: char1 turn = O or X, char2 row = (0,1,2), char3 col = (0,1,2)\n";
        while (game==true){
            std::cout<<"move: \n";
            std::string input;
            std::getline(std::cin, input);
            char m = input[0];
            int r = input[1]-'0';
            int c = input[2]-'0';
            if (input.size()!=3 ||
                    (m!='O' && m!='X') ||
                    (r<0 || r>2) ||
                    (c<0 || c>2)) {
                std::cout<<"Invalid input try again\n";
                continue;
            }
            if (move(m,r,c,turn,board)==false){ continue; }
            print(board);
            char nextplayer;
            if (m == 'O') nextplayer = 'X';
            if (m == 'X') nextplayer = 'O';
            if (gameEnds(nextplayer,(turn+1)%2, board,1)){ std::cout<<nextplayer<<" won the game\n";break;}
            if (gameEnds(m,turn, board,2)){ std::cout<<m<<" won the game\n";break;}
            turn=(turn+1)%2;
        }
        return 0;
    }

    bool gameEnds(char m, bool turn, char board[3][3], int winningMoves){
        if(fin(board)==true) return true;
        int saved_moves = 0;
        for(int i=0; i<3; i++){ 
            for(int j=0; j<3; j++){ 
                if (checkmove(m,i,j,turn,board,false) == true){
                    board[i][j] = m;
                    if(fin(board) == true){ saved_moves++;}
                    board[i][j] = '.';
                }
            }
        }
        if (saved_moves >= winningMoves) { return true;}
        return false;
    }
    bool checkmove(char m, int r, int c, bool turn, char board[3][3], bool verbose){
        if (m=='O' && turn != true) {if(verbose) std::cout<<"Moved failed, it is X turn to play\n";return false;}
        if (m=='X' && turn != false) {if (verbose) std::cout<<"Moved failed, is is O turn to play\n";return false;}
        if (board[r][c] != '.') {if (verbose) std::cout<<"Moved failed, spot is filled please try again\n";return false;}
        return true;
    }
    bool move(char m, int r, int c, bool turn, char board[3][3]){
        if(checkmove(m,r,c,turn,board, true)==false){ return false;}
        board[r][c]=m;
        return true;
    }
    void reset(char board[3][3]){
        for(int i=0; i<3; i++){ 
            for(int j=0; j<3; j++){ 
                board[i][j] = '.';
            }
        }
    }
    void print(char board[3][3]){
        std::cout<<"-------\n";
        for(int i=0; i<3; i++){ 
            std::cout<<"|";
            for(int j=0; j<3; j++){ 
                std::cout<<board[i][j]<<"|";
            }
            std::cout<<"\n-------\n";
        }
    }
    bool crow(char board[3][3]){
        for(int i=0; i<3; i++){ 
            if(board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
                return true;
            }
        }
        return false;
    }
    bool ccol(char board[3][3]){
        for(int i=0; i<3; i++){ 
            if(board[0][i] != '.' && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
                return true;
            }
        }
        return false;
    }
    bool chor(char board[3][3]){
        if(board[0][0] != '.' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){ return true;}
        if(board[0][2] != '.' && board[0][2] == board[1][1] && board[1][1] == board[2][0]){ return true;}
        return false;
    }
    bool fin(char board[3][3]){
        return (crow(board) || ccol(board) || chor(board));
    }
