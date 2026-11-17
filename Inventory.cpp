#include "GameController.hpp"
#include "SaveManager.hpp"
#include <iostream>

GameController::GameController() 
    : window(sf::VideoMode(1000, 700), "Elementoria"), 
      currentState(WELCOME_MENU), 
      player("Maria"), 
      selectedElem1(""), 
      selectedElem2(""), 
      messageBoxText("Select two elements and combine them!") {
    
    if (!font.loadFromFile("arial.ttf")) { // Ensure arial.ttf or a valid font exists in your assets
        // Fallback or handle missing font gracefully in your local build
    }
}

void GameController::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (currentState == WELCOME_MENU) {
                    handleMenuClicks(mousePos);
                } else if (currentState == GAMEPLAY) {
                    handleGameplayClicks(mousePos);
                } else if (currentState == INSTRUCTIONS) {
                    // Click anywhere or back button returns to menu
                    currentState = WELCOME_MENU;
                }
            }
        }

        window.clear(sf::Color(245, 247, 250)); // Clean light background matching proposal UI

        if (currentState == WELCOME_MENU) {
            renderWelcome();
        } else if (currentState == GAMEPLAY) {
            renderGameplay();
        } else if (currentState == INSTRUCTIONS) {
            renderInstructions();
        }

        window.display();
    }
}

void GameController::handleMenuClicks(sf::Vector2f mousePos) {
    // Simple coordinate bounding box checks for menu buttons
    if (mousePos.x >= 350 && mousePos.x <= 650) {
        if (mousePos.y >= 300 && mousePos.y <= 360) {
            currentState = GAMEPLAY; // New Game
        } else if (mousePos.y >= 380 && mousePos.y <= 440) {
            // Load Game test
            vector<string> loadedElems;
            string loadedName;
            if (SaveManager::loadGame("savegame.txt", loadedName, loadedElems)) {
                player.setName(loadedName);
                inventory.setUnlockedElements(loadedElems);
                player.setTotalDiscovered(inventory.getUnlockedCount());
            }
            currentState = GAMEPLAY;
        } else if (mousePos.y >= 460 && mousePos.y <= 520) {
            currentState = INSTRUCTIONS; // Instructions
        } else if (mousePos.y >= 540 && mousePos.y <= 600) {
            window.close(); // Exit
        }
    }
}

void GameController::handleGameplayClicks(sf::Vector2f mousePos) {
    // Example grid selection click handler logic for inventory tiles
    const auto& unlocked = inventory.getUnlockedElements();
    int startX = 50, startY = 150;
    int tileSizeX = 120, tileSizeY = 50;

    for (size_t i = 0; i < unlocked.size(); ++i) {
        int row = i / 2;
        int col = i % 2;
        int x = startX + col * (tileSizeX + 10);
        int y = startY + row * (tileSizeY + 10);

        if (mousePos.x >= x && mousePos.x <= x + tileSizeX && mousePos.y >= y && mousePos.y <= y + tileSizeY) {
            if (selectedElem1.empty()) {
                selectedElem1 = unlocked[i];
            } else if (selectedElem2.empty()) {
                selectedElem2 = unlocked[i];
            } else {
                selectedElem1 = unlocked[i];
                selectedElem2 = "";
            }
        }
    }

    // Combine Button Check
    if (mousePos.x >= 600 && mousePos.x <= 750 && mousePos.y >= 400 && mousePos.y <= 460) {
        if (!selectedElem1.empty() && !selectedElem2.empty()) {
            string result = recipeBook.findCombination(selectedElem1, selectedElem2);
            if (!result.empty()) {
                if (!inventory.hasElement(result)) {
                    inventory.unlockElement(result);
                    player.setTotalDiscovered(inventory.getUnlockedCount());
                    messageBoxText = "NEW DISCOVERY: " + result + "!";
                } else {
                    messageBoxText = "Already discovered: " + result;
                }
            } else {
                messageBoxText = "No valid combination found!";
            }
            selectedElem1 = "";
            selectedElem2 = "";
        }
    }

    // Save Button Check
    if (mousePos.x >= 50 && mousePos.x <= 150 && mousePos.y >= 600 && mousePos.y <= 650) {
        SaveManager::saveGame("savegame.txt", player.getName(), inventory.getUnlockedElements());
        messageBoxText = "Game Saved Successfully!";
    }

    // Menu Return Check
    if (mousePos.x >= 180 && mousePos.x <= 280 && mousePos.y >= 600 && mousePos.y <= 650) {
        currentState = WELCOME_MENU;
    }
}

void GameController::renderWelcome() {
    sf::Text title("ELEMENTORIA", font, 40);
    title.setFillColor(sf::Color::Black);
    title.setPosition(370, 100);
    window.draw(title);

    // Draw buttons (New Game, Load Game, Instructions, Exit)
    sf::RectangleShape btn(sf::Vector2f(300, 60));
    btn.setFillColor(sf::Color(114, 9, 183));
    
    btn.setPosition(350, 300); window.draw(btn);
    btn.setPosition(350, 380); window.draw(btn);
    btn.setPosition(350, 460); window.draw(btn);
    btn.setPosition(350, 540); window.draw(btn);
}

void GameController::renderGameplay() {
    // Render collection items and workbench panels
    sf::Text header("Your Element Lab - Player: " + player.getName(), font, 24);
    header.setFillColor(sf::Color::Black);
    header.setPosition(50, 30);
    window.draw(header);

    const auto& unlocked = inventory.getUnlockedElements();
    int startX = 50, startY = 150;
    int tileSizeX = 120, tileSizeY = 50;

    for (size_t i = 0; i < unlocked.size(); ++i) {
        int row = i / 2;
        int col = i % 2;
        int x = startX + col * (tileSizeX + 10);
        int y = startY + row * (tileSizeY + 10);

        sf::RectangleShape tile(sf::Vector2f(tileSizeX, tileSizeY));
        tile.setFillColor(sf::Color(254, 228, 199));
        tile.setPosition(x, y);
        window.draw(tile);

        sf::Text t(unlocked[i], font, 16);
        t.setFillColor(sf::Color::Black);
        t.setPosition(x + 15, y + 15);
        window.draw(t);
    }
}

void GameController::renderInstructions() {
    sf::Text instructions("How to Play:\nSelect two elements and press combine to discover new recipes.", font, 20);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition(100, 150);
    window.draw(instructions);
}