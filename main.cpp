#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "grid.h"
#include "window.h"
#include "settings.h"

int main() {
    GameWindow gameWindow(WIDTH, HEIGHT); // Створення екземпляра класу Game
    gameWindow.run(); // Виконання головного ігрового циклу

    return 0;
}