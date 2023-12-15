#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <cstring>

using namespace std;

// Function to draw the maze
void drawMaze() {
    // Draw the maze here using graphics.h functions
    // You can use functions like line, rectangle, circle, etc.
}

// Function to solve the maze
void solveMaze() {
    // Implement your maze-solving algorithm here
    // Update the graphics to show the solution
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    cleardevice();

    // Draw the initial maze
    drawMaze();

    // Draw the name input field
    outtextxy(10, 400, "Enter Your Name: ");
    char name[50] = {0}; // Initialize the name array
    int nameX = 160;
    int nameY = 400;
    int ch;
    int i = 0;

    while (true) {
        ch = getch();

        if (ch == 13) { // Enter key
            name[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace key
            if (i > 0) {
                i--;
                nameX -= textwidth(&name[i]);
                outtextxy(nameX, nameY, " ");
            }
        } else {
            name[i] = ch;
            outtextxy(nameX, nameY, &name[i]);
            nameX += textwidth(&name[i]);
            i++;
        }
    }

    // Display the entered name
    outtextxy(10, 420, "Hello, ");
    outtextxy(60, 420, name);

    // Draw the "Solve Maze" button
    rectangle(50, 350, 150, 380);
    outtextxy(60, 360, "Solve Maze");

    // Detect mouse clicks
    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 50 && x <= 150 && y >= 350 && y <= 380) {
                // The user clicked the "Solve Maze" button
                solveMaze();
                break; // Exit the loop after solving the maze
            }
        }
    }

    closegraph();
    return 0;
}
