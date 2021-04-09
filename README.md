# Maze Generation with WinApi in C
This is a program that generates random mazes and solves it for you!

![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/50050890/114146859-e5a65180-9939-11eb-823b-a030b36d207e.gif)


## Running the program
Clone this repository and open `main.exe`. This should execute without any problem on most machines. If there is any problem, you need to build the source (`main.c`) on your own. [See the <a href = "https://github.com/ImtiazKabir/Maze-Generation-with-WinApi-in-C#building-the-program" >instructions for building </a>]


## Building the program

### Building without any IDE
Clone this repository and open `make.bat`. This will build your project.

### Building with an IDE
If you prefer an IDE like <a href="https://visualstudio.microsoft.com/">`Visual Studio`</a> or <a href=https://www.codeblocks.org/>`Code::Blocks`</a> then you need to link to <a href="https://docs.microsoft.com/en-us/windows/win32/">`libgdi32`</a>.

For `Code::Blocks` do the following-

(!) Create a new empty project. <br>
(!) Create a new file with `.c` extension <br>
(!) Copy everything from my `main.c` to your file <br>
![O3Moc](https://user-images.githubusercontent.com/50050890/114013437-58a3bf80-9889-11eb-9293-7119f5c5c909.png) <br>
(!) Go to `Project`->`Build Options`->`Linker Settings` -> `Add` (See the above image) <br>
(!) When the prompt appears type `gdi32` and then confirm with `Ok` (See the above image) <br>

Now the project should build just fine


## Algorithm
I have used recursive backtracking to generate the maze (see the `recursive implementation` of <a href="https://en.wikipedia.org/wiki/Maze_generation_algorithm#Randomized_depth-first_search">Maze Generation</a>) <br>
And to solve the maze this program runs a <a href="https://en.wikipedia.org/wiki/Depth-first_search">Depth first search</a> <br>
The rendering is done with the <a href="https://docs.microsoft.com/en-us/windows/win32/">Win32 API</a><br>


## FAQ
**(1) How to see the solution?** <br>
When a maze is generated press `SPACE` and this should generate a solution. After that you can press `SPACE` again and a new random maze will be generated for you. <br> <br>
**(2) I want a bigger / smaller maze!** <br>
You need to change the source file and build your project again. [See the <a href = "https://github.com/ImtiazKabir/Maze-Generation-with-WinApi-in-C#building-the-program" >instructions for building </a>] <br>
There are two lines you need to change. Go to the `CONSTANTS` section of `main.c`. You will see two define statements defining `col` and `row`. This two constants represent number of columns and rows. Change them to your liking. *[It is recommended that you set them to the same value. eg. `#define col 30` and `#define row 30`]* <br><br>
**(3) When I press `SPACE` the program crashes** <br> 
This can happen if you have changed the column and rows to some odd number. This program assumes that the destinition of the maze is the `[row-2][col-2]`. In your case this cell is a wall. You can fix this by setting the column and rows (See the above FAQ) to some even number or change the destinion cell from the `solveMaze` function. *[You can always create an issue in this repository]* <br><br>
**(4) I want bigger/smaller screen resolution** <br>
You need to alter the source code and build your project again.[See the <a href = "https://github.com/ImtiazKabir/Maze-Generation-with-WinApi-in-C#building-the-program" >instructions for building </a>] <br>
There are two lines you need to change. Go to the `CONSTANTS` section of `main.c`. You will see two define statements defining `WIDTH` and `HEIGHT`. This two constants represent number of columns and rows. Change them to your liking. *[It is recommended to make them integer multiple of `col` and `row`]* <br><br>
**(5) I dont see the entire maze when I run the program** <br>
I am currently working on this. For now you can resize the window dragging bottom right corner of the window. (Sorry for the inconvenience)

