#ifndef GAME_H
#define GAME_H

#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <thread>
#include <future>
#include <vector>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"

class Game {
public:
    enum class GameState { MENU, PLAYER_NAME, DIFFICULTY_SELECT, PLAYING, PAUSED, GAME_OVER, VICTORY, LEADERBOARD };
    enum class Difficulty { EASY, MEDIUM, HARD, POLSL };

    Game();
    ~Game();

    const bool running() const;
    const bool getEndGame() const;

    void pollEvents();
    void update();
    void render();

    

private:
    struct PlayerScore {
        std::string name;
        int score;
        std::string difficulty;
    };

    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::Font font;

    sf::Text pointsText;
    sf::Text livesText;
    sf::Text menuText;
    sf::Text playerNameText;
    sf::Text nameErrorText; 
    sf::Text difficultyText;
    sf::Text gameOverText;
    sf::Text victoryText;
    sf::Text leaderboardText;
    sf::Text pauseText;
    sf::Text instructionsText;

    Button startButton;
    Button leaderboardButton;
    Button continueButton;
    Button menuButton;
    Button newGameButton;
    Button easyButton;
    Button mediumButton;
    Button hardButton;
    Button exitButton;
    Button polslButton;

    Paddle* paddle;
    Ball* ball;
    std::vector<Brick*> bricks;
    std::vector<PlayerScore> leaderboard;

    sf::Texture heartTexture;
    std::vector<sf::Sprite> heartSprites;

    GameState gameState;
    Difficulty selectedDifficulty;
    bool livesUpdated;
    bool endGame;
    bool victory;
    int points;
    int lives;
    int highScore;
    int wasPaused;
    std::string playerName;
    std::string inputName;

    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initGameObjects();
    void initBricks();
    void initHearts();
    void initButtons();
    void updateHearts();

    void loadLeaderboard();
    void saveLeaderboard();
    void addToLeaderboard();
    bool isValidName(const std::string& name);
    void resetGame();
    std::string getDifficultyString(Difficulty diff);

    void updateMenu();
    void updatePlayerName();
    void updateDifficultySelect();
    void updatePlaying();
    void updatePauseMenu();
    void updateGameOver();
    void updateText();
    void updateGameObjects();
    void updateCollisions();
    void updateButtonsAsync(std::vector<Button*> buttons, const sf::Vector2f& mousePos); 

    void renderArkanoid(sf::RenderTarget& target, int positionOnScreen);
    void renderMenu(sf::RenderTarget& target);
    void renderPlayerName(sf::RenderTarget& target);
    void renderDifficultySelect(sf::RenderTarget& target);
    void renderPlaying(sf::RenderTarget& target);
    void renderPauseMenu(sf::RenderTarget& target);
    void renderGameOver(sf::RenderTarget& target);
    void renderLeaderboard(sf::RenderTarget& target);
    void renderGameObjects(sf::RenderTarget& target);

    void createPolslBricks();
};

#endif