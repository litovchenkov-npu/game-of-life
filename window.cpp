#include "window.h"

GameWindow::GameWindow(int width, int height) : window(sf::VideoMode(width, height), "Game of Life"), gameGrid(width, height), pause(false) {}

void GameWindow::run() {
    // ����������� ����
    window.setFramerateLimit(FPS); // ��������� ������� �����

    // ������������ ������ ����
    sf::Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    gameGrid.generate(); // ����������� ������ ���� ����������� ����������
    std::vector<std::vector<bool>> nextGrid(gameGrid.getRowCount(), std::vector<bool>(gameGrid.getColCount(), false)); // ��������� ���� ���������� ��������

    // ���� ������ �������� ����
    while (window.isOpen()) {
        eventHandler(); // ������� ����
        if (!pause) { // �������� ����� �����
            gameGrid.update(nextGrid); // ��������� ����� ������ ����
        }

        render(); // ³���������� ������ ����
    }
}

void GameWindow::eventHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close(); // �������� ����
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mousePosition = sf::Mouse::getPosition(window);
            // ���������� ������, �� ��� ����������� ������ ����
            int row = mousePosition.y / CELL_SIZE;
            int col = mousePosition.x / CELL_SIZE;
            gameGrid.setCellState(row, col, !gameGrid.getCellState(row, col)); // ������� ����� ������ ���� ���������� �� �� ���� ������� ����
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            pause = !pause; // ���� ����� �����
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
            gameGrid.clear(); // ������� ������ ����
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
        {
            gameGrid.clear();
            gameGrid.generate(); // ��������� ���� ������ ����
        }
    }
}

void GameWindow::render() {
    window.clear(); // ������� ������ ����

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)); // ������, ����� ���� ��������� �� 1 ������ ������ ��� ��������� �����

    // �������� ����� ��� �����
    for (int i = 0; i < gameGrid.getRowCount(); i++) {
        for (int j = 0; j < gameGrid.getColCount(); j++) {
            if (gameGrid.getCellState(i, j)) {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE); // ��������� ������
                window.draw(cell); // ���� ������ � "�����", �� ���� ������������
            }
        }
    }

    window.display(); // ³���������� ����� ����
}