#include "grid.h"
#include "window.h"
#include "settings.h"

int main() {
    GameWindow gameWindow(WIDTH, HEIGHT); // ��������� ���������� ����� Game
    gameWindow.run(); // ��������� ��������� �������� �����

    return 0;
}