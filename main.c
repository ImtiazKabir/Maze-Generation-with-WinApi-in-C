/**************************************************************************************************************
This is a program that generates random mazes and solves it for you!
Press SPACE to see the solution or move on to the next one!
*************************************************************************************************************/




/*********************************************************************
                                INCLUDES
**********************************************************************/
#include <windows.h> // this line includes WinApi for windows. This is important for showing the maze!
#include <stdlib.h> // standard library is needed for the randomness
#include <time.h> // including time to generate random number

/*-----------------------------------------------------------------------------------------------*/




/*********************************************************************
                                CONSTANTS
**********************************************************************/
// These variables are never meant to be changed throughout the program


// the WIDTH and HEIGHT sets the screen resolution.
#define WIDTH 500
#define HEIGHT 500

// The maze is essentially a board. So number of rows and columns is necessary
#define row 50
#define col 50


// These three constants represent the three states a cell can have while *creating* the maze
#define wall 1          // A cell can be a wall or obstacle
#define visited 0       // It can be visited when the createMaze function reaches it
#define unvisited 2     // Or It can be yet to visit by the function


// These three constants represent the three states a cell can have while *solving* the maze
#define unmarked 0      // It can be unmarked (similar to unvisited)
#define marked 1        // or Marked (similar to visited)
#define sol 2           // At the end some cells are part of the solution while some aren't!
/*--------------------------------------------------------------------------------------------------*/






/*********************************************************************
                                FUNCTION Prototypes
**********************************************************************/
// Here are the name of the functions that make everything possible

void initiateEverything();              // this function makes everything ready to go!
void createMaze(int, int);              // createMaze function creates a random Maze
int hasUnvisitedNeighbour(int, int);    // this checks whether a cell has a neighbor yet to be visited
int solveMaze(int, int);                // solveMaze solves the created Maze
void renderMaze(HDC hdc);               // At last the maze gets displayed to the screen with this function
/*--------------------------------------------------------------------------------------------------*/







/*********************************************************************
                                MISCELLANEOUS
**********************************************************************/

/* this variable is an indicator to the program whether it is time to show the solution or not.
0 means dont show and 1 means it is time to show the solution
This variable is toggled when user presses SPACE  */
int showSolution = 0;


int arr[row][col];      // This array holds all the informations of the maze.
int solution[row][col]; // This solution array has the solution to maze!



// This array holds the basic directions for the computer
int dir[4][2] = {
    {0, -2},  // SOUTH
    {-2, 0},  // WEST
    {0, 2},   // NORTH
    {2, 0}    // EAST
};


/*
There are three brushes for coloring the cells
The wallBrush colors the walls, the rest of the cells are colored with the cellBrush
But the solution path is colored with the solBrush
*/
HBRUSH wallBrush, cellBrush, solBrush;
/*--------------------------------------------------------------------------------------------------*/









/*********************************************************************
                                Functions definition
**********************************************************************/
// Here lies the core codes of the functions. These codes determine their behavior






void initiateEverything() {
    /** This function has to ready three things before anything happens
     * (1) It has to create the arrays ready to carry the information of the maze and the solution
     * (2) after preparing the array this function pokes createMaze function to create a maze
     * (3) Now that a maze is created this function pokes the solveMaze function to solve the maze
     */


    // Doing number (1) task. These loops just clears any garbage in the array. So that useful information can reside
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {


            // these two lines are clearing the array responsible for holding the maze
            if (i%2 || j%2) arr[i][j] = wall;    // carrying information for the wall
            else arr[i][j] = unvisited;          // all the other cells go here


            solution[i][j] = unmarked;          // this line clears the array responsible for holding the solution
        }
    }

    // Everything is ready. It is time to poke the other functions
    createMaze(0, 0);  // calling createMaze
    solveMaze(0, 0);   // calling solveMaze
}




void createMaze(int i, int j) {
    /*
        This algorithm is commonly known as recursive backtracking.
        This function starts from the very beginning cell of the maze (the top left corner).
        Then randomly goes to one of its neighbors.
        After going there, it then proceeds to go to one of the neighbor's neighbor. And these continues.
        But it does not want to visit the neighbors it has already visited. In other words this looks for the 'unvisited-neighbors'
        Once it does not find any unvisited neighbor, it becomes sad and tries to go home following the path it took to reach here. ------ This is called backtracking
        But when it is trying to reach home by going back, it finds a neighbor that it didn't visit before!
        He goes there and tries to reach some more new neighbor!

        But how does that create a maze! before the function starts, there were walls everywhere. But when this function walks it breaks some walls to reach neighboring cells.
        And after it has finished walking. Many walls are broken while some still stands..
        Thus a maze is generated
    */


    arr[i][j] = visited;
    while (1) {
        int p = hasUnvisitedNeighbour(i, j);
        if (p==-1) return;
        int ni = i + dir[p][0];
        int nj = j + dir[p][1];
        arr[(i+ni)/2][(j+nj)/2] = visited;
        createMaze(ni, nj);
    }
}







int hasUnvisitedNeighbour(int i, int j) {
    /* for creating the maze it is important to see whether there exists any neighbor that createMaze function has yet to visit
        This function takes care of that job. In other words it looks for new neighbors
    */


    // make a list of all the unvisited neighbors
    int list[4];
    int count = 0;
    if (i-2 >= 0 && arr[i-2][j] == unvisited) {
        list[count] = 1; ++count;
    }
    if (i+2 < row && arr[i+2][j] == unvisited) {
        list[count] = 3; ++count;
    }
    if (j-2 >= 0 && arr[i][j-2] == unvisited) {
        list[count] = 0; ++count;
    }
    if (j+2 < col && arr[i][j+2] == unvisited) {
        list[count] = 2; ++count;
    }
    if (count) return list[rand() % count];
    return -1;
}









int solveMaze(int i, int j) {
    /*
        This function solves an already created maze. It works really simply.
        It tries to go to all possible direction (NORTH, SOUTH, EAST, WEST) to reach the destination cell (the bottom left corner)
        When it reaches the destination it writes the path in solution array.

        But here is the catch. Since it is a maze, it is easy to get lost.
        So wherever the function goes it marks that cell so that it knows which path is yet to explore and which is already explored
    */



    if (i==row-2 && j==col-2) {
        solution[i][j] = sol;
        return 1;
    }
    solution[i][j] = marked;

    // trying to go NORTH
    if (i-1 >= 0 && arr[i-1][j] != wall && solution[i-1][j] == unmarked) {
        if (solveMaze(i-1,j)) {
            solution[i][j] = sol;
            return 1;
        }
    }

    // trying to go WEST
    if (j+1 < col && arr[i][j+1] != wall && solution[i][j+1] == unmarked) {
        if (solveMaze(i,j+1)) {
            solution[i][j] = sol;
            return 1;
        }
    }

    // trying to go SOUTH
    if (i+1 < row && arr[i+1][j] != wall && solution[i+1][j] == unmarked) {
        if (solveMaze(i+1,j)) {
            solution[i][j] = sol;
            return 1;
        }
    }

    // trying to go EAST
    if (j-1 >= 0 && arr[i][j-1] != wall && solution[i][j-1] == unmarked) {
        if (solveMaze(i,j-1)) {
            solution[i][j] = sol;
            return 1;
        }
    }

    solution[i][j] = unmarked;
    return 0;
}











void renderMaze(HDC hdc) {
    /*
        This function has less algorithm and more code. It waits for the maze to be created and solved
        Once these are done this displays the maze on the screen.
        Every cell is essentially a rectangle.
        The colors vary depending on whether the cell is a wall or not.
        Also the solution is shown with a different color.
    */


    RECT rect;
    int w = WIDTH/col;
    int h = HEIGHT/row;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {

            int x1 = j * w;
            int y1 = i * h;
            int x2 = x1 + w;
            int y2 = y2 + h;
            SetRect(&rect, x1, y1, x2, y2);

            if (arr[i][j] == wall) FillRect(hdc, &rect, wallBrush);
            else if (showSolution && solution[i][j] == sol) FillRect(hdc, &rect, solBrush);
            else FillRect(hdc, &rect, cellBrush);
        }
    }
}







/*****************************************************************************************************
 *                                          BOILERPLATE CODES!!!!!
*****************************************************************************************************/
/*
    The rest of the program just makes sure that the WinApi is up and running properly
    WinApi is an API (Application Programming Interface) that talks with the GPU (graphics processing unit) for rendering 2D and 3D scenes.
    It also takes care of when the user presses SPACE to see the solution or generate a new one
*/




char ClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    HWND hw;

    switch(msg) {

        case WM_CREATE:
            initiateEverything();

        case WM_PAINT : {
            hdc = BeginPaint(hwnd, &ps);
            renderMaze(hdc);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_KEYDOWN:
            if (wParam == VK_SPACE) {
                if (showSolution) initiateEverything();
                showSolution = 1 - showSolution; // toggle showSolution flag
                RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE previnstance, LPSTR lpcmdline, int ncmdshow) {


    srand(time(0));

    wallBrush  = CreateSolidBrush(RGB(0,0,0));
    cellBrush  = CreateSolidBrush(RGB(255,255,255));
    solBrush  = CreateSolidBrush(RGB(128,0,128));

    WNDCLASSEX wc;
    MSG msg;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255,255,255));
    wc.lpszMenuName = NULL;
    wc.lpszClassName = ClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (RegisterClassEx(&wc) == 0)
    {
        MessageBox(NULL,
            "Windows class failed to register",
            "Error",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND MainWindow;
    MainWindow = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        ClassName,
        "Maze",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIDTH,
        HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (MainWindow == NULL)
    {
        MessageBox(NULL,
            "Failed to create window",
            "Error",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(MainWindow, ncmdshow);
    UpdateWindow(MainWindow);

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
    return 0;
}






