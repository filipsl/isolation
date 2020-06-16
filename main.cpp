#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {

    std::ios::sync_with_stdio(false);
    int w, h, l, k;

    scanf("%d %d %d %d", &w, &h, &l, &k);

    char string[256];
    scanf("%s", string);


    vector<vector<char> > board(h+2, vector<char>(w + 2, '.'));

    char c;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf(" %c", &c);
            board[i + 1][j + 1] = c;
        }
    }

    for (int i = 0; i < h+2; i++) {

        for (int j = 0; j < w+2; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
