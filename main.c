#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define SIZE 9
#define EMPTY 0

void init_grid(int grid[SIZE][SIZE]);
void solve_sudoku(int grid[SIZE][SIZE]);
bool solve(int grid[SIZE][SIZE], int row, int col);
bool is_grid_full(int grid);
bool is_valid_row(int grid[SIZE][SIZE], int row, int number);
bool is_valid_col(int grid[SIZE][SIZE], int col, int number);
bool is_valid_subgrid(int grid[SIZE][SIZE], int row, int col, int number);
bool is_valid(int grid[SIZE][SIZE], int row, int col, int number);
void print_grid(int grid[SIZE][SIZE]);


int operation_counter = 0;


int main() {
    clock_t start;
    clock_t end;
    double exec_time;
    int grid[SIZE][SIZE];

    start = clock();

    init_grid(grid);
    solve_sudoku(grid);

    end = clock();
    exec_time = (double) (end - start) / CLOCKS_PER_SEC * 1000;

    printf("Execution time: %.2fms\n", exec_time);
    printf("Operation counter: %d\n", operation_counter);
    print_grid(grid);

    return 0;
}

void init_grid(int grid[SIZE][SIZE]) {
    int number;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            scanf("%d", &number);
            grid[i][j] = number;
        }
    }
}

void solve_sudoku(int grid[SIZE][SIZE]) {
    solve(grid, 0, 0);
}

bool solve(int grid[SIZE][SIZE], int row, int col) {
    if (row == SIZE) return true;
    else if (col == SIZE) return solve(grid, row + 1, 0);
    else if (grid[row][col] != EMPTY) return solve(grid, row, col + 1);

    for (int number = 1; number < 10; number++) {
        operation_counter += 1;

        if (is_valid(grid, row, col, number)) {
            grid[row][col] = number;

            if (solve(grid, row, col + 1)) {
                return true;
            }

            grid[row][col] = EMPTY;
        }
    }

    return false;
}

bool is_valid_row(int grid[SIZE][SIZE], int row, int number) {
    for (int col = 0; col < SIZE; col++) {
        if (grid[row][col] == number) return false;
    }

    return true;
}

bool is_valid_col(int grid[SIZE][SIZE], int col, int number) {
    for (int row = 0; row < SIZE; row++) {
        if (grid[row][col] == number) return false;
    }

    return true;
}

bool is_valid_subgrid(int grid[SIZE][SIZE], int row, int col, int number) {
    int subgrid_init_row = row / 3 * 3; 
    int subgrid_finish_row = row / 3 * 3 + 3;
    int subgrid_init_col = col / 3 * 3;
    int subgrid_finish_col = col / 3 * 3 + 3;

    for (int r = subgrid_init_row; r < subgrid_finish_row; r++) {
        for (int c = subgrid_init_col; c < subgrid_finish_col; c++) {
            if (grid[r][c] == number) {
                return false;
            }
        }
    }

    return true;
}

bool is_valid(int grid[SIZE][SIZE], int row, int col, int number) {
    return (
        grid[row][col] == EMPTY &&
        is_valid_row(grid, row, number) &&
        is_valid_col(grid, col, number) &&
        is_valid_subgrid(grid, row, col, number)
    );
}

void print_grid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        if (!(row % 3)) {
            printf("-------------------------\n");
        }

        for (int col = 0; col < SIZE; col++) {
            if (!(col % 3)){
                printf("| ");
            }
            printf("%d ", grid[row][col]);
        }
        printf("|\n");
    }
    printf("-------------------------\n");
}
