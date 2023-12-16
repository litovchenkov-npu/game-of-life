#include "grid.h"

GameGrid::GameGrid(int width, int height) : rows(height / CELL_SIZE), cols(width / CELL_SIZE), grid(rows, std::vector<bool>(cols, false)) {}

void GameGrid::generate() {
    // Генератор випадкових цілих значень від 0 до 1
    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());
    std::uniform_int_distribution<int> distribution(0, 1);

    // Надання випадкового значення кожній клітині сітки
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = distribution(randomEngine) == 1;
        }
    }
}

void GameGrid::clear() {
    // Присвоєння значення 0 кожній клітині
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }
}

int GameGrid::countNeighbors(int x, int y) {
    int count = 0; // Лічильник "живих" сусідів клітини
    int nx, ny; // Координати сусідніх клітин

    // Перебір сусідів клітини у межах 3x3 області
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // Клітина, яка перевіряється, ігнорується
            if (i == 0 && j == 0)
                continue;

            // Обчислення координат сусіда
            nx = x + i;
            ny = y + j;

            // Перевірка, чи сусід знаходиться в межах сітки
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                // Якщо сусід є "живим", лічильник збільшується
                if (grid[nx][ny])
                    count++;
            }
        }
    }

    return count;
}

void GameGrid::update(std::vector<std::vector<bool>>& nextGrid) {
    int neighbors; // Кількість "живих" сусідів клітини
    // Перебір коєної клітини сітки та визначення її стану відповідно до правил гри
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            neighbors = countNeighbors(i, j); // Підрахунок "живих" сусідів клітини

            if (grid[i][j]) {
                // Якщо кількість "живих" сусідів менша за 2 або більша за 3, то клітина не є живою
                if (neighbors < 2 || neighbors > 3)
                    nextGrid[i][j] = false;
                else
                    nextGrid[i][j] = true;
            }
            else {
                if (neighbors == 3) // Якщо кількість сусідів дорівнює 3, то клітина є живою
                    nextGrid[i][j] = true;
                else
                    nextGrid[i][j] = false;
            }
        }
    }

    std::swap(grid, nextGrid); // Заміна поточної сітки на оновлену
}

bool GameGrid::getCellState(int x, int y) const {
    return grid[x][y];
}

void GameGrid::setCellState(int x, int y, bool state) {
    grid[x][y] = state;
}

int GameGrid::getRowCount() const {
    return rows;
}

int GameGrid::getColCount() const {
    return cols;
}