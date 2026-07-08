#include "Game.h"

// Constructor
Game::Game() {
    try {
        initVariables();
        initWindow();
        initFonts();
        initButtons();
        initText();
        initHearts();
    }
    catch (const std::exception& e) {
        std::cerr << "Error in Game::Game() " << e.what() << std::endl;
        throw;
    }
}

Game::~Game() {
    delete window;
    if (paddle) delete paddle;
    if (ball) delete ball;

    for (auto& brick : bricks) {
        delete brick;
    }
}

void Game::initVariables() {
    window = nullptr;
    gameState = GameState::MENU;
    selectedDifficulty = Difficulty::EASY;
    livesUpdated = true;
    endGame = false;
    victory = false;
    wasPaused = false;
    points = 0;
    lives = 3;
    highScore = 0;
    playerName = "";
    inputName = "";
    loadLeaderboard();
}

void Game::initWindow() {
    videoMode = sf::VideoMode::getDesktopMode();
    window = new sf::RenderWindow(videoMode, "Arkanoid", sf::Style::Fullscreen);
    window->setFramerateLimit(60);
}

void Game::initFonts() {
    std::filesystem::path primaryFont("Fonts/111.ttf");
    std::filesystem::path fallbackFont("C:/Windows/Fonts/arial.ttf");

    if (std::filesystem::exists(primaryFont)) {
        if (!font.loadFromFile(primaryFont.string())) {
            std::cout << "ERROR GAME::initFonts 1\n";
        }
    }
    else if (std::filesystem::exists(fallbackFont)) {
        if (!font.loadFromFile(fallbackFont.string())) {
            std::cout << "ERROR GAME::initFonts 2\n";
        }
    }
    else {
        std::cout << "ERROR GAME::initFonts 3\n";
    }
}

void Game::initText() {
    float centerX = window->getSize().x / 2.f;
    float centerY = window->getSize().y / 2.f;

    pointsText.setFont(font);
    pointsText.setCharacterSize(32);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(2 * centerX - 390.f, 50.f);

    livesText.setFont(font);
    livesText.setCharacterSize(32);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(50.f, 100.f);

    menuText.setFont(font);
    menuText.setCharacterSize(48);
    menuText.setFillColor(sf::Color::White);

    playerNameText.setFont(font);
    playerNameText.setCharacterSize(36);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(centerX - 325.f, centerY - 50.f);

    nameErrorText.setFont(font);
    nameErrorText.setCharacterSize(24);
    nameErrorText.setFillColor(sf::Color::Red);
    nameErrorText.setPosition(centerX - 325.f, centerY + 100.f);

    difficultyText.setFont(font);
    difficultyText.setCharacterSize(36);
    difficultyText.setFillColor(sf::Color::White);
    difficultyText.setPosition(centerX - 200.f, centerY - 100.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER!");
    gameOverText.setPosition(centerX - 200.f, centerY - 100.f);

    victoryText.setFont(font);
    victoryText.setCharacterSize(72);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setString("VICTORY!");
    victoryText.setPosition(centerX - 150.f, centerY - 100.f);

    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(32);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setPosition(centerX - 300.f, 150.f);

    instructionsText.setFont(font);
    instructionsText.setCharacterSize(15);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(50.f, window->getSize().y - 30.f);

    pauseText.setFont(font);
    pauseText.setCharacterSize(72);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setString("PAUSED");
    pauseText.setPosition(centerX - 100.f, centerY);
}

void Game::initButtons() {
    float centerX = window->getSize().x / 2.f;
    float centerY = window->getSize().y / 2.f;

    startButton = Button(font, "Start Game", sf::Vector2f(centerX - 150, centerY - 70), sf::Vector2f(300, 50));
    leaderboardButton = Button(font, "Leaderboard", sf::Vector2f(centerX - 150, centerY), sf::Vector2f(300, 50));
    exitButton = Button(font, "Exit Game", sf::Vector2f(centerX - 150, centerY + 70), sf::Vector2f(300, 50));
    continueButton = Button(font, "Continue", sf::Vector2f(centerX - 150, centerY + 90), sf::Vector2f(300, 50));
    menuButton = Button(font, "Main Menu", sf::Vector2f(centerX - 150, centerY + 160), sf::Vector2f(300, 50));
    easyButton = Button(font, "Easy", sf::Vector2f(centerX - 150, centerY - 50), sf::Vector2f(300, 50));
    mediumButton = Button(font, "Medium", sf::Vector2f(centerX - 150, centerY + 20), sf::Vector2f(300, 50));
    hardButton = Button(font, "Hard", sf::Vector2f(centerX - 150, centerY + 90), sf::Vector2f(300, 50));
    newGameButton = Button(font, "New Game", sf::Vector2f(centerX - 150, centerY + 230), sf::Vector2f(300, 50));
    polslButton = Button(font, "POLSL", sf::Vector2f(centerX - 150, centerY + 160), sf::Vector2f(300, 50));

    startButton.setPosition(sf::Vector2f(centerX - 150, centerY - 70));
    leaderboardButton.setPosition(sf::Vector2f(centerX - 150, centerY));
    exitButton.setPosition(sf::Vector2f(centerX - 150, centerY + 70));

    continueButton.setPosition(sf::Vector2f(centerX - 150, centerY + 90));
    menuButton.setPosition(sf::Vector2f(centerX - 150, centerY + 160));

    easyButton.setPosition(sf::Vector2f(centerX - 150, centerY - 50));
    mediumButton.setPosition(sf::Vector2f(centerX - 150, centerY + 20));
    hardButton.setPosition(sf::Vector2f(centerX - 150, centerY + 90));

    newGameButton.setPosition(sf::Vector2f(centerX - 150, centerY + 230));

    polslButton.setPosition(sf::Vector2f(centerX - 150, centerY + 160));
}

void Game::initGameObjects() {
    float centerX = this->window->getSize().x / 2.f;
    float bottomY = this->window->getSize().y - 100.f;

    this->paddle = new Paddle();
    switch (this->selectedDifficulty) {
    case Difficulty::EASY:
        this->paddle->setSize(150.0f, 25.0f);
        this->paddle->setSpeed(11.0f);
        break;
    case Difficulty::MEDIUM:
        this->paddle->setSize(130.f, 25.f);
        this->paddle->setSpeed(10.0f);
        break;
    case Difficulty::HARD:
        this->paddle->setSize(90.f, 25.f);
        this->paddle->setSpeed(10.0f);
        break;
    case Difficulty::POLSL:
        this->paddle->setSize(130.f, 25.f);
        this->paddle->setSpeed(11.0f);
        break;
    }
    this->paddle->setPosition(centerX - this->paddle->getSize().x / 2.f, bottomY);

    this->ball = new Ball();
    switch (this->selectedDifficulty) {
    case Difficulty::EASY:
        this->ball->setSpeed(7.0f);
        break;
    case Difficulty::MEDIUM:
        this->ball->setSpeed(9.0f);
        break;
    case Difficulty::HARD:
        this->ball->setSpeed(10.0f);
        break;
    case Difficulty::POLSL:
        this->ball->setSpeed(8.0f);
        break;
    }
    this->ball->setPosition(centerX, bottomY - 50.f);

    this->initBricks();
}

void Game::initBricks() {
    for (auto& brick : this->bricks) {
        delete brick;
    }
    this->bricks.clear();

    if (this->selectedDifficulty == Difficulty::POLSL) {
        createPolslBricks();
        return;
    }

    int rows = 0;
    switch (this->selectedDifficulty) {
    case Difficulty::EASY: rows = 3; break;
    case Difficulty::MEDIUM: rows = 4; break;
    case Difficulty::HARD: rows = 5; break;
    case Difficulty::POLSL: rows = 7; break;
    }
    int cols = 15;

    float brickWidth = 80.f;
    float brickHeight = 40.f;
    float spacing = 5.f;

    float totalWidth = cols * brickWidth + (cols - 1) * spacing;
    float startX = (this->window->getSize().x - totalWidth) / 2.f;
    float startY = 200.f;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            float x = startX + col * (brickWidth + spacing);
            float y = startY + row * (brickHeight + spacing);

            int type = row % 5;
            Brick* brick = new Brick(x, y, type);
            this->bricks.push_back(brick);
        }
    }
}

void Game::loadLeaderboard() {
    std::filesystem::path leaderboardFile("leaderboard.txt");
    if (std::filesystem::exists(leaderboardFile)) {
        std::ifstream file(leaderboardFile.string());
        if (!file.is_open()) {
            std::cerr << "ERROR GAME::loadLeaderboard\n";
            return;
        }
        std::string line;
        this->leaderboard.clear(); // Clear existing leaderboard
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, difficulty;
            int score;

            if (std::getline(ss, name, ',') &&
                (ss >> score) &&
                ss.ignore() &&
                std::getline(ss, difficulty)) {
                PlayerScore playerScore;
                playerScore.name = name;
                playerScore.score = score;
                playerScore.difficulty = difficulty;
                this->leaderboard.push_back(playerScore);
            }
        }
        file.close();

        std::ranges::sort(this->leaderboard, std::ranges::greater{}, & PlayerScore::score);

        if (!this->leaderboard.empty()) {
            this->highScore = this->leaderboard[0].score;
        }
    }
    else {
        std::ofstream newFile(leaderboardFile.string());
        if (!newFile.is_open()) {
            std::cerr << "ERROR GAME::loadLeaderboard\n";
        }
        newFile.close();
    }
}

void Game::saveLeaderboard() {
    std::filesystem::path leaderboardFile("leaderboard.txt");
    std::ofstream file(leaderboardFile.string());
    if (!file.is_open()) {
        std::cerr << "ERROR GAME::saveLeaderboard \n";
        return;
    }
    for (const auto& score : this->leaderboard) {
        file << score.name << "," << score.score << "," << score.difficulty << std::endl;
    }
    file.close();
}

void Game::addToLeaderboard() {
    if (this->points > 0) {
        PlayerScore newScore;
        newScore.name = this->playerName;
        newScore.score = this->points;
        newScore.difficulty = this->getDifficultyString(this->selectedDifficulty);
        this->leaderboard.push_back(newScore);
        std::cout << "Added to leaderboard: " << newScore.name << ", " << newScore.score << ", " << newScore.difficulty << std::endl;
        std::ranges::sort(this->leaderboard, std::ranges::greater{}, & PlayerScore::score);
        if (this->leaderboard.size() > 10) {
            this->leaderboard.resize(10);
        }
        this->saveLeaderboard();
    }
}

bool Game::isValidName(const std::string& name) {
    std::regex nameRegex("^[a-zA-Z0-9_]{3,15}$");
    return std::regex_match(name, nameRegex);
}

void Game::resetGame() {
    this->points = 0;
    this->lives = 3;
    this->victory = false;
    this->endGame = false;

    delete this->paddle;
    delete this->ball;

    this->initGameObjects();
}

std::string Game::getDifficultyString(Difficulty diff) {
    switch (diff) {
    case Difficulty::EASY: return "Easy";
    case Difficulty::MEDIUM: return "Medium";
    case Difficulty::HARD: return "Hard";
    case Difficulty::POLSL: return "Polsl";
    default: return "Easy";
    }
}

const bool Game::running() const {
    return this->window->isOpen();
}

const bool Game::getEndGame() const {
    return this->endGame;
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::TextEntered:
            if (this->gameState == GameState::PLAYER_NAME) {
                if (this->ev.text.unicode == 8 && !this->inputName.empty()) {
                    this->inputName.pop_back();
                }
                else if (this->ev.text.unicode < 128 && std::isprint(this->ev.text.unicode)) {
                    if (this->inputName.length() < 15)
                        this->inputName += static_cast<char>(this->ev.text.unicode);
                }
            }
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape) {
                if (this->gameState == GameState::PLAYING) {
                    this->gameState = GameState::PAUSED;
                }
                else if (this->gameState == GameState::PAUSED) {
                    this->gameState = GameState::PLAYING;
                }
                else if (this->gameState == GameState::LEADERBOARD) {
                    this->gameState = GameState::MENU;
                }
            }
            break;
        }
    }
}

void Game::updateButtonsAsync(std::vector<Button*> buttons, const sf::Vector2f& mousePos) {
    for (auto* button : buttons) {
        button->update(mousePos);
    }
}

void Game::updateMenu() {
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    std::vector<Button*> buttons = { &startButton, &leaderboardButton, &exitButton };

    auto future = std::async(std::launch::async, [this, buttons, mousePos]() {
        this->updateButtonsAsync(buttons, mousePos);
        });
    future.wait();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->startButton.isHovered()) {
            this->gameState = GameState::PLAYER_NAME;
        }
        else if (this->leaderboardButton.isHovered()) {
            this->gameState = GameState::LEADERBOARD;
        }
        else if (this->exitButton.isHovered()) {
            this->window->close();
        }
    }
}

void Game::updatePlayerName() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (this->isValidName(this->inputName)) {
            this->playerName = this->inputName;
            this->gameState = GameState::DIFFICULTY_SELECT;
            this->nameErrorText.setString("");
        }
        else {
            this->nameErrorText.setString("Invalid name! Use 3-15 alphanumeric characters or underscores, no spaces.");
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->gameState = GameState::MENU;
        this->inputName.clear();
        this->nameErrorText.setString("");
    }
    else {
        if (!this->inputName.empty()) {
            if (std::regex_search(this->inputName, std::regex("\\s"))) {
                this->nameErrorText.setString("Error: No spaces allowed!");
            }
            else if (!std::regex_match(this->inputName, std::regex("^[a-zA-Z0-9]*$"))) {
                this->nameErrorText.setString("Error: Only letters and numbers allowed!");
            }
            else if (this->inputName.length() < 3) {
                this->nameErrorText.setString("Error: Name must be at least 3 characters!");
            }
            else {
                this->nameErrorText.setString("");
            }
        }
        else {
            this->nameErrorText.setString("Enter a name (3-15 characters).");
        }
    }
}

void Game::updateDifficultySelect() {
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    std::vector<Button*> buttons = { &easyButton, &mediumButton, &hardButton, &polslButton };

    auto future = std::async(std::launch::async, [this, buttons, mousePos]() {
        this->updateButtonsAsync(buttons, mousePos);
        });
    future.wait();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->easyButton.isHovered()) {
            this->selectedDifficulty = Difficulty::EASY;
            this->initGameObjects();
            this->gameState = GameState::PLAYING;
        }
        else if (this->mediumButton.isHovered()) {
            this->selectedDifficulty = Difficulty::MEDIUM;
            this->initGameObjects();
            this->gameState = GameState::PLAYING;
        }
        else if (this->hardButton.isHovered()) {
            this->selectedDifficulty = Difficulty::HARD;
            this->initGameObjects();
            this->gameState = GameState::PLAYING;
        }
        else if (this->polslButton.isHovered()) {
            this->selectedDifficulty = Difficulty::POLSL;
            this->initGameObjects();
            this->gameState = GameState::PLAYING;
        }
    }
}

void Game::updatePlaying() {
    this->updateGameObjects();
    this->updateCollisions();
}

void Game::updatePauseMenu() {
    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

    this->continueButton.update(mousePos);
    this->menuButton.update(mousePos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->continueButton.isHovered()) {
            this->gameState = GameState::PLAYING;
            this->wasPaused = true;
        }
        else if (this->menuButton.isHovered()) {
            this->resetGame();
            this->gameState = GameState::MENU;
        }
    }
}

void Game::updateGameOver() {
    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    newGameButton.update(mousePos);
    menuButton.update(mousePos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (newGameButton.isHovered()) {
            resetGame();
            gameState = GameState::PLAYING;
        }
        else if (menuButton.isHovered()) {
            resetGame();
            gameState = GameState::MENU;
        }
    }
}

void Game::updateText() {
    switch (this->gameState) {
    case GameState::MENU:
        break;

    case GameState::PLAYER_NAME: {
        std::string nameStr = "Enter your name:\n\n";
        nameStr += this->inputName + "_";
        nameStr += "\n\n\n\nPress ENTER to confirm\nESCAPE to return";
        this->playerNameText.setString(nameStr);
    } break;

    case GameState::DIFFICULTY_SELECT: {
        std::string diffStr = "Select difficulty:\n\n";
        this->difficultyText.setString(diffStr);
    } break;

    case GameState::PLAYING: {
        
        this->pointsText.setString("Points: " + std::to_string(this->points));
        this->instructionsText.setString("Arrow Keys/WASD: Move Paddle | ESC: Pause");
        
    } break;

    case GameState::LEADERBOARD: {
        std::string leaderStr = "LEADERBOARD\n\n";
        int index = 1;
        std::ranges::for_each(std::ranges::take_view(this->leaderboard, 10),
            [&](const auto& score) {
                leaderStr += std::to_string(index++) + ". " + score.name +
                    " - " + std::to_string(score.score) +
                    " (" + score.difficulty + ")\n";
            });
        leaderStr += "\nPress ESC to return";
        this->leaderboardText.setString(leaderStr);
    } break;

    default:
        break;
    }
}

void Game::updateGameObjects() {
    if (this->paddle && this->ball) {
        this->paddle->update(*this->window);
        this->ball->update(*this->window);
    }
}

void Game::updateCollisions() {
    if (!this->paddle || !this->ball) return;

    if (this->ball->getGlobalBounds().intersects(this->paddle->getGlobalBounds())) {
        float paddleCenter = this->paddle->getPosition().x + this->paddle->getGlobalBounds().width / 2.f;
        float ballCenter = this->ball->getPosition().x + this->ball->getRadius();
        float hitPosition = (ballCenter - paddleCenter) / (this->paddle->getGlobalBounds().width / 2.f);

        float newVelX = hitPosition * 0.95f;
        this->ball->setVelocity(newVelX, -abs(this->ball->getVelocity().y));

        const float minXVelocity = 0.3f;
        if (newVelX > -minXVelocity && newVelX < minXVelocity) {
            if (newVelX < 0)
                newVelX = -minXVelocity;
            else
                newVelX = minXVelocity;
        }
    }

    for (auto& brick : this->bricks) {
        if (!brick->isDestroyed() && this->ball->getGlobalBounds().intersects(brick->getGlobalBounds())) {
            brick->destroy();
            this->points += brick->getPoints();
            this->ball->reverseVelocityY();
            break;
        }
    }

    if (ball->getPosition().y + ball->getRadius() * 2 > window->getSize().y) {
        lives--;
        livesUpdated = true;
        if (lives <= 0) {
            updateHearts();
            endGame = true;
            victory = false;
            gameState = GameState::GAME_OVER;
            addToLeaderboard();
        }
        else {
            ball->reset(*window);
        }
    }

    bool allBricksDestroyed = true;
    for (auto& brick : this->bricks) {
        if (!brick->isDestroyed()) {
            allBricksDestroyed = false;
            break;
        }
    }

    if (allBricksDestroyed) {
        this->victory = true;
        this->endGame = true;
        this->gameState = GameState::VICTORY;
    }
}

void Game::update() {
    this->pollEvents();

    if (gameState == GameState::GAME_OVER || gameState == GameState::VICTORY) {
        updateGameOver();
        return;
    }

    if (livesUpdated) {
        updateHearts();
    }

    switch (this->gameState) {
    case GameState::MENU:
        this->updateMenu();
        break;
    case GameState::PLAYER_NAME:
        this->updatePlayerName();
        break;
    case GameState::DIFFICULTY_SELECT:
        this->updateDifficultySelect();
        break;
    case GameState::PLAYING:
        this->updatePlaying();
        /*if (this->wasPaused) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            this->wasPaused = false;
        }*/
        break;
    case GameState::PAUSED:
        this->updatePauseMenu();
        break;
    case GameState::GAME_OVER:
    case GameState::VICTORY:
        this->updateGameOver();
        break;
    case GameState::LEADERBOARD:
        break;
    }

    this->updateText();
}

void Game::renderArkanoid(sf::RenderTarget& target, int positionOnScreen) {
    const std::string title = "ARKANOID";
    const std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color(255,165,0), sf::Color::Yellow, sf::Color::Green,
        sf::Color::Cyan, sf::Color::Blue, sf::Color::Magenta, sf::Color(128,0,128)
    };

    const float spacing = 5.f, extraSpacing = 10.f, reduceSpacing = -5.f;
    std::vector<sf::Text> letters;
    float totalWidth = 0.f;

    for (size_t i = 0; i < title.size(); ++i) {
        sf::Text t(std::string(1, title[i]), font, 90);
        t.setFillColor(colors[i]);
        letters.push_back(t);
        totalWidth += t.getGlobalBounds().width;

        if (i < title.size() - 1) {
            float space = spacing;
            if (title[i] == 'I' && title[i + 1] == 'D') space += extraSpacing;
            else if (title[i] == 'O' && title[i + 1] == 'I') space += reduceSpacing;
            totalWidth += space;
        }
    }

    float x = target.getSize().x / 2.f - totalWidth / 2.f;
    float y = target.getSize().y / 3.f - (positionOnScreen == 1 ? 200.f : 50.f);

    for (size_t i = 0; i < letters.size(); ++i) {
        letters[i].setPosition(x, y);
        target.draw(letters[i]);
        x += letters[i].getGlobalBounds().width;

        if (i < letters.size() - 1) {
            float space = spacing;
            if (title[i] == 'I' && title[i + 1] == 'D') space += extraSpacing;
            else if (title[i] == 'O' && title[i + 1] == 'I') space += reduceSpacing;
            x += space;
        }
    }
}

void Game::renderMenu(sf::RenderTarget& target) {
    this->renderArkanoid(*this->window, 0);
    this->startButton.render(target);
    this->leaderboardButton.render(target);
    this->exitButton.render(target);
}

void Game::renderPlayerName(sf::RenderTarget& target) {
    this->renderArkanoid(*this->window, 1);
    target.draw(this->playerNameText);
    target.draw(this->nameErrorText);
}

void Game::renderDifficultySelect(sf::RenderTarget& target) {
    sf::Text title("SELECT DIFFICULTY", this->font, 40);
    title.setPosition(target.getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 375.f);
    target.draw(title);

    this->renderArkanoid(*this->window, 1);
    this->easyButton.render(target);
    this->mediumButton.render(target);
    this->hardButton.render(target);
    this->polslButton.render(target);
}

void Game::renderPlaying(sf::RenderTarget& target) {
    this->renderGameObjects(target);
    target.draw(this->pointsText);
    target.draw(this->instructionsText);

    for (auto& heart : heartSprites) {
        target.draw(heart);
    }
}

void Game::renderPauseMenu(sf::RenderTarget& target) {
    this->renderPlaying(target);

    sf::RectangleShape overlay(sf::Vector2f(target.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 240));
    target.draw(overlay);

    float centerX = target.getSize().x / 2.0f;
    float centerY = target.getSize().y / 2.0f;

    pauseText.setPosition(centerX - pauseText.getGlobalBounds().width / 2, centerY - 50.0f);
    target.draw(pauseText);

    continueButton.render(target);
    menuButton.render(target);
}

void Game::renderGameOver(sf::RenderTarget& target) {
    sf::RectangleShape overlay(sf::Vector2f(target.getSize()));
    overlay.setFillColor(victory ? sf::Color(0, 0, 0, 255) : sf::Color(255, 0, 0, 255));
    target.draw(overlay);

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(72);
    resultText.setFillColor(victory ? sf::Color::Green : sf::Color::White);
    resultText.setString(victory ? "VICTORY!" : "GAME OVER");

    sf::FloatRect textRect = resultText.getLocalBounds();
    resultText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    resultText.setPosition(target.getSize().x / 2.0f, target.getSize().y / 2.0f - 100);

    target.draw(resultText);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(48);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(points));
    scoreText.setPosition(target.getSize().x / 2.0f - scoreText.getLocalBounds().width / 2.0f,
        target.getSize().y / 2.0f);

    target.draw(scoreText);

    newGameButton.render(target);
    menuButton.render(target);
}

void Game::renderLeaderboard(sf::RenderTarget& target) {
    std::string leaderStr = "LEADERBOARD\n\n";
    int index = 1;
    std::ranges::for_each(std::ranges::take_view(this->leaderboard, 10),
        [&](const auto& score) {
            leaderStr += std::to_string(index++) + ". " + score.name +
                " - " + std::to_string(score.score) +
                " (" + score.difficulty + ")\n";
        });
    leaderStr += "\nPress ESC to return";
    this->leaderboardText.setString(leaderStr);
    target.draw(this->leaderboardText);
}

void Game::renderGameObjects(sf::RenderTarget& target) {
    if (this->paddle) this->paddle->render(target);
    
    if (this->ball) this->ball->render(target);

    for (auto& brick : this->bricks) {
        brick->render(target);
    }
    if (this->wasPaused) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->wasPaused = false;
    }
}

void Game::render() {
    this->window->clear(sf::Color::Black);

    switch (this->gameState) {
    case GameState::MENU:
        this->renderMenu(*this->window);
        break;
    case GameState::PLAYER_NAME:
        this->renderPlayerName(*this->window);
        break;
    case GameState::DIFFICULTY_SELECT:
        this->renderDifficultySelect(*this->window);
        break;
    case GameState::PLAYING:
        this->renderPlaying(*this->window);
        break;
    case GameState::PAUSED:
        this->renderPauseMenu(*this->window);
        break;
    case GameState::GAME_OVER:
    case GameState::VICTORY:
        this->renderGameOver(*window);
        break;
    case GameState::LEADERBOARD:
        this->renderLeaderboard(*this->window);
        break;
    }

    this->window->display();
}

void Game::createPolslBricks() {
    for (auto& brick : this->bricks) {
        delete brick;
    }
    this->bricks.clear();

    std::vector<std::vector<bool>> patterns = {
        {1,0,1,0,1, 1,0,0,0,1, 1,0,1,0,1, 1,0,0,0,0, 1,0,0,0,0},
        {0,1,0,1,0, 1,0,0,0,1, 1,0,0,0,1, 1,0,0,0,1, 0,1,0,1,0},
        {1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,1,0,1},
        {1,0,1,0,1, 1,0,0,0,0, 0,1,0,1,0, 0,0,0,0,1, 1,0,1,0,1},
        {1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,1,1,0}
    };

    float brickWidth = 35.f;
    float brickHeight = 25.f;
    float letterSpacing = 50.f;
    float startX = 300.f;
    float startY = 200.f;
    float tmp = 50.f;
    int colorIndex = 3;

    for (int letter = 0; letter < 5; letter++) {
        startX = startX + tmp;
        colorIndex = (colorIndex == 3) ? 4 : 3;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                if (patterns[letter][row * 5 + col]) {
                    float x = startX + letter * (5 * brickWidth + letterSpacing) + col * brickWidth;
                    float y = startY + row * brickHeight;

                    Brick* brick = new Brick(x, y, colorIndex);
                    this->bricks.push_back(brick);
                }
            }
        }
    }
}

void Game::initHearts() {
    if (!heartTexture.loadFromFile("Resource/heart.png")) {
        std::cerr << "Failed to load heart texture!\n";
        return;
    }

    heartSprites.clear();
    for (int i = 0; i < lives; i++) {
        sf::Sprite heart(heartTexture);
        heart.setPosition(10.f + i * 80.f, 20.f);
        heart.setScale(0.065f, 0.065f);
        heartSprites.push_back(heart);
    }
}

void Game::updateHearts() {
    heartSprites.clear();
    for (int i = 0; i < lives; i++) {
        sf::Sprite heart(heartTexture);
        heart.setPosition(10.f + i * 80.f, 20.f);
        heart.setScale(0.065f, 0.065f);
        heartSprites.push_back(heart);
    }
}