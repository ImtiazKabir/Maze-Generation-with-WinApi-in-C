# Maze Generation with WinApi in C
This is a program that generates random mazes and solves it for you! Press SPACE to see the solution or move on to the next one!

![ezgif com-gif-maker](https://user-images.githubusercontent.com/50050890/114009785-47f14a80-9885-11eb-9cfd-772d88c1fabb.gif)


## Compiling the program

### Without any IDE
Clone this repository and open `make.bat`. This will compile your project.

### Compiling with an IDE
If you prefer an IDE like `Visual Studio` or `Code::Blocks` then you need to link to `libgdi32`.

For `Code::Blocks` do the following-

(1) Create a new empty project.

(2) Create a new file with `.c` extension

(3) Copy everything from my `main.c` to your file

(4) Go to `Project`->`Build Options`->`Linker Settings` -> `Add`

(5) When the prompt appears type `gdi32` and then confirm with `Ok`

Now the project should compile just fine


## Algorithm

I have used recursive backtracking to generate the maze (see the `recursive implementation` of <a href="https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search">Maze Generation</a>

And to solve the maze this program runs a <a href="https://en.wikipedia.org/wiki/Depth-first_search">Depth first search</a>

The rendering is done with the <a href="https://docs.microsoft.com/en-us/windows/win32/">Win32 API</a>
