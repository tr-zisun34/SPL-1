#include <iostream>
#include <graphics.h>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <cstdio>

#define MAZE_ROWS 16
#define MAZE_COLS 21
#define CELL_SIZE 30

int mazeLayout[MAZE_ROWS][MAZE_COLS] = {
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1},
};

int goalFound = 0;
int pathTaken[MAZE_ROWS][MAZE_COLS];

using namespace std::chrono;

// Stack Implementation
struct Point
{
    int x, y;

    Point() : x(0), y(0) {} // Default constructor

    Point(int _x, int _y) : x(_x), y(_y) {}
};

Point stackArray[MAZE_ROWS * MAZE_COLS];
int top = -1;

void push(Point p)
{
    stackArray[++top] = p;
}

void pop()
{
    --top;
}

Point peek()
{
    return stackArray[top];
}

bool isEmpty()
{
    return top == -1;
}

// Function to render the maze
void renderMaze()
{
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            int xCoord = j * CELL_SIZE;
            int yCoord = i * CELL_SIZE;

            if (mazeLayout[i][j] == 1)
            {
                rectangle(xCoord, yCoord, xCoord + CELL_SIZE, yCoord + CELL_SIZE);
            }
            else if (mazeLayout[i][j] == 2)
            {
                circle(xCoord + CELL_SIZE / 2, yCoord + CELL_SIZE / 2, CELL_SIZE / 3);
            }
        }
    }
}

void customDelay(int milliseconds)
{
    int end_time = clock() + milliseconds;
    while (clock() < end_time) {}
}

void drawPathOnMaze()
{
    for (int i = 0; i < MAZE_ROWS; i++)
    {
        for (int j = 0; j < MAZE_COLS; j++)
        {
            if (pathTaken[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, CYAN);
                bar(j * CELL_SIZE + CELL_SIZE / 6, i * CELL_SIZE + CELL_SIZE / 6,
                    (j + 1) * CELL_SIZE - CELL_SIZE / 6, (i + 1) * CELL_SIZE - CELL_SIZE / 6);
            }
        }
    }
}


void explorePaths(int row, int col, int timeLimitSeconds)
{
    push(Point(row, col));

    while (!isEmpty() && !goalFound)
    {
        Point current = peek();
        int x = current.x;
        int y = current.y;
        pop();

        if (isTimeUp(startTime, timeLimitSeconds))
        {
            cout << "Time limit exceeded. Exiting..." << endl;
            return;
        }

        if (x < 0 || y < 0 || x >= MAZE_ROWS || y >= MAZE_COLS || mazeLayout[x][y] == 1 || pathTaken[x][y] == 1)
        {
            continue;
        }

        pathTaken[x][y] = 1;

        if (mazeLayout[x][y] == 2)
        {
            goalFound = 1;
            break;
        }

        push(Point(x + 1, y));
        push(Point(x, y + 1));
        push(Point(x, y - 1));
        push(Point(x - 1, y));

        customDelay(100);

        cleardevice();
        renderMaze();
        drawPathOnMaze();
    }
}

void manualPlay(int& startingRow, int& startingCol) {
    int key;
    bool validMove;

    while (true) {
        if (_kbhit()) {
            key = _getch();

            validMove = false;

            switch (key) {
            case 72:  // Up arrow key
                if (startingRow > 0 && mazeLayout[startingRow - 1][startingCol] != 1) {
                    startingRow--;
                    validMove = true;
                }
                break;
            case 80:  // Down arrow key
                if (startingRow < MAZE_ROWS - 1 && mazeLayout[startingRow + 1][startingCol] != 1) {
                    startingRow++;
                    validMove = true;
                }
                break;
            case 75:  // Left arrow key
                if (startingCol > 0 && mazeLayout[startingRow][startingCol - 1] != 1) {
                    startingCol--;
                    validMove = true;
                }
                break;
            case 77:  // Right arrow key
                if (startingCol < MAZE_COLS - 1 && mazeLayout[startingRow][startingCol + 1] != 1) {
                    startingCol++;
                    validMove = true;
                }
                break;
            }

            cleardevice();
            renderMaze();
            drawPathOnMaze();
            setfillstyle(SOLID_FILL, RED);
            bar(startingCol * CELL_SIZE + CELL_SIZE / 6, startingRow * CELL_SIZE + CELL_SIZE / 6,
                (startingCol + 1) * CELL_SIZE - CELL_SIZE / 6, (startingRow + 1) * CELL_SIZE - CELL_SIZE / 6);

            if (validMove && mazeLayout[startingRow][startingCol] == 2) {
                cout << "Congratulations! You reached the goal manually." << endl;
                break;
            }
        }
    }
}


int main()
{
    int startingRow = 0;
    int startingCol= 0;



    int graphicsDriver = DETECT, graphicsMode;
    initgraph(&graphicsDriver, &graphicsMode, "");

    // Initially, display a black screen
    cleardevice();

    // Merge the input handling and "Solve Maze" button code from Code 2
    outtextxy(10, 400, "Enter Your Name: ");
    char name[50] = { 0 };
    int nameX = 160;
    int nameY = 400;
    int ch,x,y;
    int i = 0;

    while (true)
    {
        ch = getch();

        if (ch == 13)
        {
            name[i] = '\0';
            break;
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                nameX -= textwidth(&name[i]);
                outtextxy(nameX, nameY, " ");
            }
        }
        else
        {
            name[i] = ch;
            outtextxy(nameX, nameY, &name[i]);
            nameX += textwidth(&name[i]);
            i++;
        }
    }

    //manualPlay(startingRow, startingCol);

    outtextxy(10, 20, "Hello, ");
    outtextxy(60, 20, name);

    outtextxy(10, 50, "Hit the Button to solve the Maze");

    rectangle(10, 120, 275, 155);
    outtextxy(20, 130, "1. Solve Maze Manually");

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 10 && x <= 275 && y >= 20 && y <= 115)
            {
                goalFound = 0;
                cleardevice();
                renderMaze();

                int timeLimitSeconds = 60; // Set your desired time limit here
                explorePaths(startingRow, startingCol, timeLimitSeconds);

            if (goalFound)
            {
                cout << "Path to reach the goal: " << endl;
                for (int i = 0; i < MAZE_ROWS; i++)
                {
                    for (int j = 0; j < MAZE_COLS; j++)
                    {
                        if (pathTaken[i][j] == 1)
                        {
                            cout << "-> [" << i << "," << j << "] ";
                        }
                    }
                }
            }
            else
            {
                cout << "Path to the goal not found within the time limit!" << endl;
            }
            }
        }
        else if (x >= 10 && x <= 275 && y >= 120 && y <= 155)
        {
            // Code to solve maze manually
            goalFound = 0;
            cleardevice();
            renderMaze();
            manualPlay(startingRow, startingCol);
        }
    }
}



    rectangle(10, 80, 275, 115);
    outtextxy(20, 90, "2. Solve Maze by Breadth First Search");

    //cout << "Enter Starting Row and Column: ";
    //cin >> startingRow;
    //cin >> startingCol;

    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if (x >= 10 && x <= 275 && y >= 20 && y <= 115)
            {
                goalFound = 0;
                cleardevice();
                renderMaze();
                explorePaths(startingRow, startingCol);

                if (goalFound)
                {
                    cout << "Path to reach the goal: " << endl;
                    for (int i = 0; i < MAZE_ROWS; i++)
                    {
                        for (int j = 0; j < MAZE_COLS; j++)
                        {
                            if (pathTaken[i][j] == 1)
                            {
                                cout << "-> [" << i << "," << j << "] ";
                            }
                        }
                    }
                }
                else
                {
                    cout << "Path to the goal not found!";
                }
            }
        }
    }

    getch();
    closegraph();

    return 0;
}

