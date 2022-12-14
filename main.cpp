// Welcome to my biggest piece of code yet and by far
// This program let's you play Sudoku!
// Author: Roiqk
// Started: 28. 11. 2022
// Finished: 14. 12. 2022

#include "board.h"
#include "gui.h"
#include "difficultyWindow.h"
#include "menu.h"
#include <SFML/Graphics.hpp>


void sfml();
void doEveryFrame(Gui &gui, Board &board, Menu &menu);


int main()
{
    if (!font.loadFromFile(PATH_TO_FONT)
        || !titleFont.loadFromFile(PATH_TO_TITLE_FONT)
        || !arrowTexture.loadFromFile(PATH_TO_ARROW_PNG)
        || !pencilTexture.loadFromFile(PATH_TO_PENCIL_PNG)) 
            return EXIT_SUCCESS;
    std::cout << "\nWelcome to Sudoku!\nPlease read about before you play!\nHope you will enjoy my program :)\n\n"; 
    srand(clock());
    sfml();
    return EXIT_SUCCESS;
}


// draws the window
void sfml()
{
    window.setFramerateLimit(FPS);
    selectorWindow.setFramerateLimit(FPS);
    difficultyWindow.setFramerateLimit(FPS);

    std::cout << "menu, board and gui initiation\n";
    stopwatch();
    Menu menu = Menu();
    Board board = Board();
    Gui gui = Gui();
    stopwatch();

    // main loop
    while (window.isOpen()) {
        sf::Event event;
        // main window
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) gui.handleClick(MAIN_WINDOW_NUM, board, menu);
            }
            if (event.type == sf::Event::KeyPressed) {
                // new game with last selected difficulty
                if (event.key.code == sf::Keyboard::N) gui.handleNewGameCreation(board, menu, board.difficulty);
            }
        }
        // selector window
        while (selectorWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) selectorWindow.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) gui.handleClick(SELECTOR_WINDOW_NUM, board, menu);
            }
        }
        // difficulty window
        while (difficultyWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) difficultyWindow.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) gui.handleClick(DIFFICULTY_WIDOW_NUM, board, menu);
            }
        }

        doEveryFrame(gui, board, menu);
    }
}

// needs to happen every frame
void doEveryFrame(Gui &gui, Board &board, Menu &menu)
{
    window.clear(sf::Color{BLACK});
    selectorWindow.clear(sf::Color{WHITE});
    difficultyWindow.clear(sf::Color{WHITE});
    
    difficultySelector.call(menu.newGame);
    if (menu.show) menu.call();
    else gui.call(board);

    window.display();
    selectorWindow.display();
    difficultyWindow.display();
}