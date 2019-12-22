#include <iostream>
#include <unistd.h>
#include <curses.h>

class Game 
{
    public:
    int dim;
    char **state;
    int pos [2] = {0, 0};
    char player;

    // constructor
    // set initial game state as a
    // dim * dim array. Values can be _ (blank), 
    // X, or O
    // also set initial move to 'X'
    Game (int d) : dim(d), state(new char*[d]) {
        for (int i = 0; i < dim; i++) {
            state[i] = new char[dim];
            for (int j = 0; j < dim; j++) {
                state[i][j] = '_';
            }
        }
        player = 'X';
    }

    // update the current cursor position
    void updatePos(int x, int y) {
        if (x > -1 && x < dim && y > -1 && y < dim) {
            pos[0] = x;
            pos[1] = y;
        }
    }

    void makeMove() {
        if (state[pos[0]][pos[1]] == '_') {
            state[pos[0]][pos[1]] = player;
            player = (player == 'X') ? 'O' : 'X';
        }
    }

    bool gameWon() {
        int i;
        int j;

        // check rows and columns
        for (i = 0; i < dim; i++) {
            // take i as row index, walk columns
            // basically check if each column is same as prev
            // and isn't blank (_)
            // if j gets to the end, then it's a valid row
            for (j = 1; j < dim; j++) {
                if (state[i][j] != state[i][j - 1] || state[i][j] == '_') {
                    break;
                }
            }
            if (j == dim) {
                return true;
            }

            // same except take i as column index
            for (j = 1; j < dim; j++) {
                if (state[j][i] != state[j - 1][i] || state[j][i] == '_') {
                    break;
                }
            }
            if (j == dim) {
                return true;
            }
        }

        // TODO - check diagonals
        for (i = 1; i < dim; i++) {
            if (state[i][i] != state[i - 1][i - 1] || state[i][i] == '_') {
                break;
            }
        }
        if (i == dim) {
            return true;
        }
        for (i = 1; i < dim; i++) {
            if (state[i][dim - 1 - i] != state[i - 1][dim - i] || state[i][dim - 1 - i] == '_') {
                break;
            }
        }
        if (i == dim) {
            return true;
        }

        return false;
    }

    // redraw the game's current state
    void redraw(WINDOW *win) {
        // get rid of what's on the screen
        erase();

        // helper hint
        printw("Press enter to move: %c\n", player);

        // go through state and print either _, X, O
        // to show current cursor pos we demarcate ._.
        for (int i = 0; i < dim; i++) {
            printw("|");
            for (int j = 0; j < dim; j++) {
                if (i == pos[0] && j == pos[1]) {
                    printw(".%c.", state[i][j]);
                }
                else {
                    printw(" %c ", state[i][j]);
                }
                printw("|");
            }
            printw("\n");
        }

        // won't print anything new  to terminal 
        // until we call refresh
        wrefresh(win);
    }
};

int main() {

    // ncurses setup
    WINDOW *win = initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // get game dimension
    printw("Enter dimension of tictactoe grid, from 3 to 9: ");
    int dim;
    while (1) {
        dim = getch();
        // 3 is charcode 50, 9 is 57
        if (dim > 50 && dim < 58) {
            break;
        }
    }

    // instantiate game
    Game g(dim - 48);
    g.redraw(win);

    // keep getting characters via getch
    // could be either arrow keys, or enter
    while(!g.gameWon()) {
        int ch = getch();

        // key pressed, draw
        if (ch == KEY_RIGHT) {
            g.updatePos(g.pos[0], g.pos[1] + 1);
        }
        else if (ch == KEY_LEFT) {
            g.updatePos(g.pos[0], g.pos[1] - 1);
        }
        else if (ch == KEY_UP) {
            g.updatePos(g.pos[0] - 1, g.pos[1]);
        }
        else if (ch == KEY_DOWN) {
            g.updatePos(g.pos[0] + 1, g.pos[1]);
        }
        // enter key
        else if (ch == 10) {
            g.makeMove();
        }
        g.redraw(win);
    }

    // whoever moved last must have won
    printw("Game won by %c!\nPress ENTER to exit.", (g.player == 'X') ? 'O' : 'X');
    while (getch() != 10) {}
    endwin();
}
