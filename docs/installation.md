# Installation

Open your terminal and follow the instructions below to install the game.

Clone the repository:

```bash
git clone https://github.com/Roiqk7/sudoku.git
```

Enter the repo directory:

```bash
cd sudoku
```

Build the project:

```bash
./build.sh (dev) (test)
```
* `dev` - build the project in development mode
* `test` - build the tests for the project (then run them with `./build/test`)
**Note:** You may need to make the build script executable with `chmod +x build.sh`

Run the game:

```bash
./build/sudoku
```

# Dependencies

All dependencies will be automatically downloaded and installed by the build script. The only dependency you need to have is `git` to clone the repository. All shell commands are written for MacOS. If you are using a different operating system, you may need to adjust the commands accordingly.