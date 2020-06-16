#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int W, H, L, K;

vector<vector<char> > read_board();

void print_board(vector<vector<char> > &board);


int main() {

    std::ios::sync_with_stdio(false);

    scanf("%d %d %d %d", &W, &H, &L, &K);

    char string[256];
    scanf("%s", string);

    vector<vector<char> > board = read_board();
    print_board(board);

    return 0;
}

vector<vector<char> > read_board() {
    vector<vector<char> > board(H + 2, vector<char>(W + 2, '.'));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            scanf(" %c", &board[i + 1][j + 1]);
        }
    }
    return board;
}

void print_board(vector<vector<char>> &board) {
    for (int i = 0; i < H + 2; i++) {
        for (int j = 0; j < W + 2; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}