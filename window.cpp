#include "window.h"

GameWindow::GameWindow(int width, int height) : window(sf::VideoMode(width, height), "Game of Life"), gameGrid(width, height), pause(false) {}

void GameWindow::run() {
    // Ініціалізація вікна
    window.setFramerateLimit(FPS); // Обмеження частоти кадрів

    // Встановнення іконки вікна
    sf::Image icon;
    icon.loadFromFile("icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    gameGrid.generate(); // Ініціалізація ігрової сітки випадковими значеннями
    std::vector<std::vector<bool>> nextGrid(gameGrid.getRowCount(), std::vector<bool>(gameGrid.getColCount(), false)); // Створення сітки наступного покоління

    // Цикл роботи ігрового вікна
    while (window.isOpen()) {
        eventHandler(); // Обробка подій
        if (!pause) { // Перевірка стану паузи
            gameGrid.update(nextGrid); // Оновлення стану ігрової сітки
        }

        render(); // Відображення ігрової сітки
    }
}

void GameWindow::eventHandler() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close(); // Закриття вікна
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mousePosition = sf::Mouse::getPosition(window);
            // Визначення клітини, на якій знаходиться курсор миші
            int row = mousePosition.y / CELL_SIZE;
            int col = mousePosition.x / CELL_SIZE;
            gameGrid.setCellState(row, col, !gameGrid.getCellState(row, col)); // Змінення стану клітини після натискання на неї лівою кнопкою миші
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            pause = !pause; // Зміна стану паузи
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C) {
            gameGrid.clear(); // Очистка ігрової сітки
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
        {
            gameGrid.clear();
            gameGrid.generate(); // Генерація нової ігрової сітки
        }
    }
}

void GameWindow::render() {
    window.clear(); // Очистка ігрової сітки

    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1)); // Клітини, розмір яких вказується на 1 піксель мешний для утворення рамки

    // Перегляд стану всіх клітин
    for (int i = 0; i < gameGrid.getRowCount(); i++) {
        for (int j = 0; j < gameGrid.getColCount(); j++) {
            if (gameGrid.getCellState(i, j)) {
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE); // Положення клітини
                window.draw(cell); // Якщо клітина є "живою", то вона відображається
            }
        }
    }

    window.display(); // Відображення вмісту вікна
}