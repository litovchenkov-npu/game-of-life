#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "grid.h"
#include "window.h"
#include "settings.h"

int main() {
    GameWindow gameWindow(WIDTH, HEIGHT); // ��������� ���������� ����� Game
    gameWindow.run(); // ��������� ��������� �������� �����

    return 0;
}