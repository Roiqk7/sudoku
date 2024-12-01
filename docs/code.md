# Code Explanation

The code is separated into three folders:
- `src`: Contains the source code of the project.
- `include`: Contains the header files of the project.
- `test`: Contains the tests for the project.

The code follows strong object-oriented principles with all the main components having a class of their own. The entire game is controlled by the `Application` class which is constructed in the main function. The application ends once the application object is destroyed.

The entire graphical user interface is controlled by the `GUI` class which is an attribute of the `application` class. The GUI class is responsible for rendering, updating and handling all the user inputs. The `Scene` class is one logical GUI element with many gui `Objects` which are the smallest graphical elements. The `Scene` class is responsible for handling all the gui objects and rendering them. More `Scene` classes can be rendered at the same time.

The `GameHandler` class which is another attribute of the `GUI` class is responsible for the sudoku game logic and serves as a bridge between the GUI and the game logic. The `GameHandler` class is responsible for generating the sudoku board, checking the validity of the board, solving the board and checking if the board is solved. The `GameHandler` class has available other helper classes which are single responsibility classes that help the `GameHandler` class in its tasks.

The events in the GUI are handled using the command pattern. The `Command` and `Invoker` classes are responsible for handling the events. The `Command` class stores the command and the `Invoker` class executes the command.

## Development

The project was developed using the C++ programming language and the SFML library for the graphical user interface. Once of the arguments for the `build.sh` files is `dev` which will build the project with additional logging and debugging information. It may also be helpful to use the `test` argument to run the tests.

Command:
```bash
./scripts/build.sh dev && ./build/sudoku
```

will be your best friend during development.

## Testing

TODO: Finish tests