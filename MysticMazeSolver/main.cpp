#include <iostream>
#include <graphics.h>
#include <conio.h> // for kbhit and getch

using namespace std;

void DFS();
void BFS();
void Dijkstra();
void A_Star();

void drawExitButton();
bool isMouseClickOnExitButton(int x, int y);

int main()
{
    int n;
    bool running = true;

    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    cleardevice();

    outtextxy(10, 50, "Welcome");

    rectangle(180, 150, 420, 200);
    rectangle(180, 220, 420, 270);
    rectangle(180, 290, 420, 340);
    rectangle(180, 360, 420, 410);

    outtextxy(200, 175, "1. DFS");
    outtextxy(200, 245, "2. BFS");
    outtextxy(200, 315, "3. Dijkstra");
    outtextxy(200, 385, "4. A*");

    int x, y;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 180 && x <= 420 && y >= 150 && y <= 200)
            {
                DFS();
            }
            else if (x >= 180 && x <= 420 && y >= 220 && y <= 270)
            {
                BFS();
            }
            else if (x >= 180 && x <= 420 && y >= 290 && y <= 340)
            {
                Dijkstra();
            }
            else if (x >= 180 && x <= 420 && y >= 360 && y <= 410)
            {
                A_Star();
            }
        }
    }




   /* settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    drawExitButton();

    outtextxy(100, 50, "Enter 1 for DFS traversal");
    outtextxy(100, 100, "Enter 2 for BFS traversal");
    outtextxy(100, 150, "Enter 3 for Dijkstra traversal");
    outtextxy(100, 200, "Enter 4 for A* traversal");
    outtextxy(100, 250, "Enter 5 to exit");
    outtextxy(100, 300, "Enter your choice: ");

    while (running)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == '5' || isMouseClickOnExitButton(mousex(), mousey()))
            {
                running = false;
            }
        }

        cin >> n;

        switch (n)
        {
        case 1:
            DFS();
            break;

        case 2:
            BFS();
            break;
        case 3:
            Dijkstra();
            break;
        case 4:
            A_Star();
            break;
        case 5:
            running = false;
            break;
        default:
            break;
        }
    }

    closegraph(); */

    return 0;
}
