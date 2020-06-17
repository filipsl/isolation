#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <unordered_set>
#include <list>
#include <climits>

int W, H, L, K;

struct bfs_node {
    int id;
    int reach;
};

struct cell_coords {
    int x;
    int y;
};

struct cell_range {
    int id;
    int range;

    bool operator<(const cell_range &str) const {
        return (range < str.range);
    }
};

std::vector<std::vector<char>> read_board();

void print_board(std::vector<std::vector<char>> &board);

std::vector<std::vector<int>> get_ranges(std::vector<std::vector<char>> &board);

std::unordered_set<int> visit_cells(std::vector<std::vector<char>> &board, int x, int y);

int get_cell_range(std::vector<std::vector<char>> &board, int x, int y);

int get_id(int x, int y);

int get_id(cell_coords coords);

std::vector<int> get_neighbors(std::vector<std::vector<char>> &board, int id);

void print_ranges(std::vector<std::vector<int>> &ranges);

void place_people(std::vector<std::vector<char>> &board, std::vector<std::vector<int>> &ranges);

int main() {

    std::ios::sync_with_stdio(false);

    scanf("%d %d %d %d", &W, &H, &L, &K);

    char string[256];
    scanf("%s", string);

    std::vector<std::vector<char>> board = read_board();
//    print_board(board);
    std::vector<std::vector<int>> ranges = get_ranges(board);
//    print_ranges(ranges);
    place_people(board, ranges);

    return 0;
}

std::vector<std::vector<char>> read_board() {
    std::vector<std::vector<char>> board(H + 2, std::vector<char>(W + 2, '.'));
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

std::vector<std::vector<int>> get_ranges(std::vector<std::vector<char>> &board) {
    std::vector<std::vector<int>> ranges(H + 2, std::vector<int>(W + 2, 0));

    for (int i = 1; i < H + 1; i++) {
        for (int j = 1; j < W + 1; j++) {
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
            if (visited_cells.find(neighbor) == visited_cells.end() && current_node.reach - 1 >= 0) {
                bfs_node new_node{neighbor, current_node.reach - 1};
                cells_queue.push(new_node);
            }
        }
    }
    return visited_cells;
}

int get_cell_range(std::vector<std::vector<char>> &board, const int x, const int y) {
    if (board[x][y] == '.')
        return 0;
    return visit_cells(board, x, y).size();
}

int get_id(const int x, const int y) {
    return x * (W + 2) + y;
}

int get_id(const cell_coords coords) {
    return coords.x * (W + 2) + coords.y;
}

cell_coords get_coords(const int id) {
    return cell_coords{id / (W + 2), id % (W + 2)};
}

std::vector<int> get_neighbors(std::vector<std::vector<char>> &board, const int id) {
    cell_coords cellCoords = get_coords(id);
    int x = cellCoords.x;
    int y = cellCoords.y;
    cell_coords cellCoordsUp = cell_coords{x - 1, y};
    cell_coords cellCoordsDown = cell_coords{x + 1, y};
    cell_coords cellCoordsLeft = cell_coords{x, y - 1};
    cell_coords cellCoordsRight = cell_coords{x, y + 1};

    std::vector<int> neighbors_ids;

    char cell_char = board[x][y];
    switch (cell_char) {
        case '+':
            if (board[cellCoordsUp.x][cellCoordsUp.y] == '+' || board[cellCoordsUp.x][cellCoordsUp.y] == '|')
                neighbors_ids.push_back(get_id(cellCoordsUp));
            if (board[cellCoordsDown.x][cellCoordsDown.y] == '+' || board[cellCoordsDown.x][cellCoordsDown.y] == '|')
                neighbors_ids.push_back(get_id(cellCoordsDown));
            if (board[cellCoordsLeft.x][cellCoordsLeft.y] == '+' || board[cellCoordsLeft.x][cellCoordsLeft.y] == '-')
                neighbors_ids.push_back(get_id(cellCoordsLeft));
            if (board[cellCoordsRight.x][cellCoordsRight.y] == '+' ||
                board[cellCoordsRight.x][cellCoordsRight.y] == '-')
                neighbors_ids.push_back(get_id(cellCoordsRight));
            break;
        case '|':
            if (board[cellCoordsUp.x][cellCoordsUp.y] == '+' || board[cellCoordsUp.x][cellCoordsUp.y] == '|')
                neighbors_ids.push_back(get_id(cellCoordsUp));
            if (board[cellCoordsDown.x][cellCoordsDown.y] == '+' || board[cellCoordsDown.x][cellCoordsDown.y] == '|')
                neighbors_ids.push_back(get_id(cellCoordsDown));
            break;
        case '-':
            if (board[cellCoordsLeft.x][cellCoordsLeft.y] == '+' || board[cellCoordsLeft.x][cellCoordsLeft.y] == '-')
                neighbors_ids.push_back(get_id(cellCoordsLeft));
            if (board[cellCoordsRight.x][cellCoordsRight.y] == '+' ||
                board[cellCoordsRight.x][cellCoordsRight.y] == '-')
                neighbors_ids.push_back(get_id(cellCoordsRight));
            break;
        default:
            break;
    }
    return neighbors_ids;
}

void print_ranges(std::vector<std::vector<int>> &ranges) {
    for (int i = 0; i < H + 2; i++) {
        for (int j = 0; j < W + 2; j++) {
            printf("%d ", ranges[i][j]);
        }
        printf("\n");
    }
}

void place_people(std::vector<std::vector<char>> &board, std::vector<std::vector<int>> &ranges) {
    std::list<cell_range> cells;

    for (int i = 1; i < H + 1; i++) {
        for (int j = 1; j < W + 1; j++) {
            if (ranges[i][j])
                cells.push_back(cell_range{get_id(i, j), ranges[i][j]});
        }
    }

    cells.sort();

    std::vector<std::vector<bool>> is_covered(H + 2, std::vector<bool>(W + 2, false));

//    for (const auto &cell : cells) {
//        printf("Id %d   range %d\n", cell.id, cell.range);
//    }

    int placed_people = 0;

    while (placed_people < K && !cells.empty()) {

        cell_coords currentCellCords = get_coords(cells.front().id);
        if (is_covered[currentCellCords.x][currentCellCords.y]) {
            cells.pop_front();
            continue;
        }

        std::unordered_set<int> same_range_cells;
        int current_range = cells.front().range;
//        printf("Current range: %d\n", current_range);
        same_range_cells.insert(cells.front().id);
        cells.pop_front();

        while (!cells.empty() && cells.front().range == current_range) {
            currentCellCords = get_coords(cells.front().id);
            if (!is_covered[currentCellCords.x][currentCellCords.y])
                same_range_cells.insert(cells.front().id);
            cells.pop_front();
        }

        while (!same_range_cells.empty() && placed_people < K) {
            int max_neighbour_range = 0;
            int min_real_cover = INT_MAX;
            int cell_with_max_neighbor = *same_range_cells.begin();
            int cell_with_min_real_cover = *same_range_cells.begin();
            cell_coords cellCoords;
            for (auto cell_id : same_range_cells) {
                cellCoords = get_coords(cell_id);
                std::unordered_set<int> visited_cells = visit_cells(board, cellCoords.x, cellCoords.y);
                int current_real_cover = 0;
                for (auto visited_cell_id : visited_cells) {
                    cell_coords visitedCellCoords = get_coords(visited_cell_id);
                    if (!is_covered[visitedCellCoords.x][visitedCellCoords.y]) {
                        current_real_cover++;
                    }
                }

                if (current_real_cover < min_real_cover) {
                    min_real_cover = current_real_cover;
                    cell_with_min_real_cover = cell_id;
                }

                std::vector<int> neighbours = get_neighbors(board, cell_id);
                for (auto neighbor_id : neighbours) {
                    cell_coords neighbor_coords = get_coords(neighbor_id);
                    if (!is_covered[neighbor_coords.x][neighbor_coords.y] &&
                        max_neighbour_range < ranges[neighbor_coords.x][neighbor_coords.y]) {
                        max_neighbour_range = ranges[neighbor_coords.x][neighbor_coords.y];
                        cell_with_max_neighbor = cell_id;
                    }
                }
            }
            if (min_real_cover < current_range) {
                cellCoords = get_coords(cell_with_min_real_cover);
                printf("%d %d\n", cellCoords.y - 1, cellCoords.x - 1);
            } else {
                cellCoords = get_coords(cell_with_max_neighbor);
                printf("%d %d\n", cellCoords.y - 1, cellCoords.x - 1);
            }
            std::unordered_set<int> visited_cells = visit_cells(board, cellCoords.x, cellCoords.y);
            for (auto visited_cell_id : visited_cells) {
                cell_coords visitedCellCoords = get_coords(visited_cell_id);
                is_covered[visitedCellCoords.x][visitedCellCoords.y] = true;
                same_range_cells.erase(visited_cell_id);
            }
            placed_people++;
        }
    }
}