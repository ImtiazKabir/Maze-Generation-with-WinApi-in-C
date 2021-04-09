# Maze Generation with WinApi in C
This is a program that generates random mazes and solves it for you!

![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/50050890/114146859-e5a65180-9939-11eb-823b-a030b36d207e.gif)


## Running the program
Clone this repository and open `main.exe`. This should execute without any problem on most machines. If there is any problem, you need to build the source (`main.c`) on your own. [See the following instructions for building]


## Building the program

### Building without any IDE
Clone this repository and open `make.bat`. This will build your project.

### Building with an IDE
If you prefer an IDE like <a href="https://visualstudio.microsoft.com/">`Visual Studio`</a> or <a href=https://www.codeblocks.org/>`Code::Blocks`</a> then you need to link to <a href="https://docs.microsoft.com/en-us/windows/win32/">`libgdi32`</a>.

For `Code::Blocks` do the following-

(!) Create a new empty project.

(!) Create a new file with `.c` extension

(!) Copy everything from my `main.c` to your file

![O3Moc](https://user-images.githubusercontent.com/50050890/114013437-58a3bf80-9889-11eb-9293-7119f5c5c909.png)

(!) Go to `Project`->`Build Options`->`Linker Settings` -> `Add` (See the above image)

(!) When the prompt appears type `gdi32` and then confirm with `Ok` (See the above image)

Now the project should build just fine



## Algorithm

I have used recursive backtracking to generate the maze (see the `recursive implementation` of <a href="https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search">Maze Generation</a>)

And to solve the maze this program runs a <a href="https://en.wikipedia.org/wiki/Depth-first_search">Depth first search</a>

The rendering is done with the <a href="https://docs.microsoft.com/en-us/windows/win32/">Win32 API</a>
