#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Inventory.hpp"
#include "RecipeBook.hpp"

enum GameState { WELCOME_MENU, GAMEPLAY, INSTRUCTIONS, VICTORY };

class GameController {
private:
    sf::RenderWindow window;
    GameState currentState;
    Player player;
    Inventory inventory;
    RecipeBook recipeBook;

    sf::Font font;
    
    // UI Selection state
    string selectedElem1;
    string selectedElem2;
    string messageBoxText;

    void handleMenuClicks(sf::Vector2f mousePos);
    void handleGameplayClicks(sf::Vector2f mousePos);

public:
    GameController();
    void run();
    void renderWelcome();
    void renderGameplay();
    void renderInstructions();
};

#endif