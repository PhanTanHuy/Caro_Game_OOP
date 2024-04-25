#include <iostream>
#include <vector>
#include <stdexcept>
#include <stdlib.h>  // system("clear")

// Ð?nh nghia các h?ng s? màu s?c
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

using namespace std;

class Board {
private:
    vector<char> board;

public:
    Board() {
        board = vector<char>(9, ' '); // Kh?i t?o b?ng tr?ng
    }
    //chinh mau vien
    void printBoard() const {
    // In ra vi?n trên cùng
    cout << YELLOW<< "-------------" << RESET << endl;

    for (int i = 0; i < 9; i += 3) {
        // In ra vi?n bên trái
        cout <<YELLOW << "| " << RESET;

        // In ra t?ng ô và màu c?a nó
        for (int j = 0; j < 3; ++j) {
            cout << getColor(board[i + j]) << board[i + j] << RESET << YELLOW<< " | " << RESET;
        }
        cout << endl;

        // In ra dòng ngan cách gi?a các hàng
        if (i < 6) {
            cout << YELLOW << "-------------" << RESET << endl;
        }
    }
    // In ra vi?n du?i cùng
    cout << YELLOW << "-------------" << RESET << endl;
}


    bool isFull() const {
        for (char cell : board) {
            if (cell == ' ') return false;
        }
        return true;
    }

    void placeMark(int position, char mark) {
        if (position < 0 || position >= 9) {
            throw out_of_range("Invalid!");
        }
        if (board[position] != ' ') {
            throw invalid_argument("Valid!");
        }
        board[position] = mark;
    }

    char checkWinner() const {
        // Ki?m tra hàng ngang
        for (int i = 0; i < 9; i += 3) {
            if (board[i] != ' ' && board[i] == board[i + 1] && board[i] == board[i + 2]) {
                return board[i];
            }
        }
        // Ki?m tra hàng d?c
        for (int i = 0; i < 3; ++i) {
            if (board[i] != ' ' && board[i] == board[i + 3] && board[i] == board[i + 6]) {
                return board[i];
            }
        }
        // Ki?m tra du?ng chéo chính
        if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
            return board[0];
        }
        // Ki?m tra du?ng chéo ph?
        if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
            return board[2];
        }
        return ' ';
    }

private:
    string getColor(char cell) const {
        if (cell == 'X') return GREEN;
        else if (cell == 'O') return RED;
        else return RESET;
    }
};

class Player {
private:
    char mark;

public:
    Player(char m) : mark(m) {}

    virtual int makeMove(const Board& board) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(char m) : Player(m) {}

    int makeMove(const Board& board) override {
        int position;
        //nhap cach di
        cin >> position;
        return position - 1; 
    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(char m) : Player(m) {}

    int makeMove(const Board& board) override {
        // Gi? s? máy tính ch?n v? trí ng?u nhiên
        return rand() % 9;
    }
};

class Game {
private:
    Board board;
    Player* player1;
    Player* player2;

public:
    Game(Player* p1, Player* p2) : player1(p1), player2(p2) {}

    void play() {
        Player* currentPlayer = player1;
        char currentMark = 'X';
        while (true) {
            system("clear"); // Xóa màn hình
            
            board.printBoard();
            int move = currentPlayer->makeMove(board);
            try {
                board.placeMark(move, currentMark);
            } catch (const exception& e) {
                cerr << e.what() << endl;
                continue; // L?p l?i lu?t di n?u có l?i
            }
            char winner = board.checkWinner();
            if (winner != ' ') {
                system("clear"); // Xóa màn hình 
               
                board.printBoard();
                cout << "Player " << currentMark << " Thang!" << endl;
                break;
            } else if (board.isFull()) {
                system("clear"); // Xóa màn hình 
               
                cout << "It's draw" << endl;
                break;
            }
            currentMark = (currentMark == 'X') ? 'O' : 'X';
            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }
    }
    void start() {
        cout << "Welcome to Tic-tac-toe!" << endl;
        cout << "Play mode: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            player1 = new HumanPlayer('X');
            player2 = new ComputerPlayer('O');
        } else if (choice == 2) {
            player1 = new HumanPlayer('X');
            player2 = new HumanPlayer('O');
        } else {
            player1 = new ComputerPlayer('X');
            player2 = new ComputerPlayer('O');
        }

        play();

        delete player1;
        delete player2;
    }
};

int main() {
    Game game(nullptr, nullptr);
    game.start();

    return 0;
}





