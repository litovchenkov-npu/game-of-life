#include "grid.h"

GameGrid::GameGrid(int width, int height) : rows(height / CELL_SIZE), cols(width / CELL_SIZE), grid(rows, std::vector<bool>(cols, false)) {}

void GameGrid::generate() {
    // ��������� ���������� ����� ������� �� 0 �� 1
    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());
    std::uniform_int_distribution<int> distribution(0, 1);

    // ������� ����������� �������� ����� ����� ����
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = distribution(randomEngine) == 1;
        }
    }
}

void GameGrid::clear() {
    // ��������� �������� 0 ����� �����
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = 0;
        }
    }
}

int GameGrid::countNeighbors(int x, int y) {
    int count = 0; // ˳������� "�����" ����� ������
    int nx, ny; // ���������� ������ �����

    // ������ ����� ������ � ����� 3x3 ������
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            // ������, ��� ������������, ����������
            if (i == 0 && j == 0)
                continue;

            // ���������� ��������� �����
            nx = x + i;
            ny = y + j;

            // ��������, �� ���� ����������� � ����� ����
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                // ���� ���� � "�����", �������� ����������
                if (grid[nx][ny])
                    count++;
            }
        }
    }

    return count;
}

void GameGrid::update(std::vector<std::vector<bool>>& nextGrid) {
    int neighbors; // ʳ������ "�����" ����� ������
    // ������ ���� ������ ���� �� ���������� �� ����� �������� �� ������ ���
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            neighbors = countNeighbors(i, j); // ϳ�������� "�����" ����� ������

            if (grid[i][j]) {
                // ���� ������� "�����" ����� ����� �� 2 ��� ����� �� 3, �� ������ �� � �����
                if (neighbors < 2 || neighbors > 3)
                    nextGrid[i][j] = false;
                else
                    nextGrid[i][j] = true;
            }
            else {
                if (neighbors == 3) // ���� ������� ����� ������� 3, �� ������ � �����
                    nextGrid[i][j] = true;
                else
                    nextGrid[i][j] = false;
            }
        }
    }

    std::swap(grid, nextGrid); // ����� ������� ���� �� ��������
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