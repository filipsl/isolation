#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_set>

int W, H, L, K;

struct bfs_node {
    int id;
    int depth;
};

struct cell_coords {
    int x;
    int y;
};

std::vector<std::vector<char> > read_board();

void print_board(std::vector<std::vector<char> > &board);

std::vector<std::vector<int> > get_ranges(std::vector<std::vector<char>> &board);

std::unordered_set<int> visit_cells(std::vector<std::vector<char>> &board, const int x, const int y);

int get_cell_range(std::vector<std::vector<char>> &board, int x, int y);

int get_id(int x, int y);

int get_id(cell_coords coords);

cell_coords shift_back(cell_coords coords);

std::vector<int> get_neighbors(std::vector<std::vector<char>> &board, int id);

void print_ranges(std::vector<std::vector<int>> &ranges);


int main() {

    std::ios::sync_with_stdio(false);

    scanf("%d %d %d %d", &W, &H, &L, &K);

    char string[256];
    scanf("%s", string);

    std::vector<std::vector<char> > board = read_board();
    print_board(board);
    std::vector<std::vector<int> > ranges = get_ranges(board);
    print_ranges(ranges);

    return 0;
}

std::vector<std::vector<char> > read_board() {
    std::vector<std::vector<char> > board(H + 2, std::vector<char>(W + 2, '.'));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            scanf(" %c", &board[i + 1][j + 1]);
        }
    }
    return board;
}

void print_board(std::vector<std::vector<char>> &board) {
    for (int i = 0; i < H + 2; i++) {
        for (int j = 0; j < W + 2; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

std::vector<std::vector<int> > get_ranges(std::vector<std::vector<char>> &board) {
    std::vector<std::vector<int> > ranges(H, std::vector<int>(W, 0));

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ranges[i][j] = get_cell_range(board, i, j);
        }
    }
    return ranges;
}

std::unordered_set<int> visit_cells(std::vector<std::vector<char>> &board, const int x, const int y) {

    std::queue<bfs_node> cells_queue;
    std::unordered_set<int> visited_cells;

    bfs_node node{get_id(x, y), L};
    cells_queue.push(node);

    while (!cells_queue.empty()) {
        bfs_node current_node = cells_queue.front();
        cells_queue.pop();
        visited_cells.insert(current_node.id);
        std::vector<int> neighbors = get_neighbors(board, current_node.id);
        for (auto neighbor : neighbors) {
            if (visited_cells.find(neighbor) == visited_cells.end() && current_node.depth - 1 >= 0) {
                bfs_node new_node{neighbor, current_node.depth - 1};
                cells_queue.push(new_node);
            }
        }
    }
    return visited_cells;
}

int get_cell_range(std::vector<std::vector<char>> &board, const int x, const int y) {
    if (board[x + 1][y + 1] == '.')
        return 0;
    return visit_cells(board, x, y).size();
}

int get_id(const int x, const int y) {
    return x * W + y;
}

int get_id(const cell_coords coords) {
    return coords.x * W + coords.y;
}

cell_coords get_coords(const int id) {
    return cell_coords{id / W, id % W};
}

std::vector<int> get_neighbors(std::vector<std::vector<char>> &board, const int id) {
    cell_coords cellCoords = get_coords(id);
    int x = cellCoords.x + 1;
    int y = cellCoords.y + 1;
    cell_coords cellCoordsUp = cell_coords{x - 1, y};
    cell_coords cellCoordsDown = cell_coords{x + 1, y};
    cell_coords cellCoordsLeft = cell_coords{x, y - 1};
    cell_coords cellCoordsRight = cell_coords{x, y + 1};

    std::vector<int> neighbors_ids;

    char cell_char = board[x][y];
    switch (cell_char) {
        case '+':
            if (board[cellCoordsUp.x][cellCoordsUp.y] == '+' || board[cellCoordsUp.x][cellCoordsUp.y] == '|')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsUp)));
            if (board[cellCoordsDown.x][cellCoordsDown.y] == '+' || board[cellCoordsDown.x][cellCoordsDown.y] == '|')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsDown)));
            if (board[cellCoordsLeft.x][cellCoordsLeft.y] == '+' || board[cellCoordsLeft.x][cellCoordsLeft.y] == '-')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsLeft)));
            if (board[cellCoordsRight.x][cellCoordsRight.y] == '+' ||
                board[cellCoordsRight.x][cellCoordsRight.y] == '-')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsRight)));
            break;
        case '|':
            if (board[cellCoordsUp.x][cellCoordsUp.y] == '+' || board[cellCoordsUp.x][cellCoordsUp.y] == '|')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsUp)));
            if (board[cellCoordsDown.x][cellCoordsDown.y] == '+' || board[cellCoordsDown.x][cellCoordsDown.y] == '|')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsDown)));
            break;
        case '-':
            if (board[cellCoordsLeft.x][cellCoordsLeft.y] == '+' || board[cellCoordsLeft.x][cellCoordsLeft.y] == '-')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsLeft)));
            if (board[cellCoordsRight.x][cellCoordsRight.y] == '+' ||
                board[cellCoordsRight.x][cellCoordsRight.y] == '-')
                neighbors_ids.push_back(get_id(shift_back(cellCoordsRight)));
            break;
        default:
            break;
    }
    return neighbors_ids;
}

cell_coords shift_back(cell_coords coords) {
    return cell_coords{coords.x - 1, coords.y - 1};
}


void print_ranges(std::vector<std::vector<int>> &ranges) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            printf("%d ", ranges[i][j]);
        }
        printf("\n");
    }
}