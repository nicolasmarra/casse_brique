#include "Game.h"
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int PLATFORM_WIDTH = 125;
const int PLATFORM_HEIGHT = 15;
const int PLATFORM_SPEED = 10;

const int BALL_RADIUS = 5;
const double BALL_SPEED_X = 0.08;
const double BALL_SPEED_Y = 0.09;

const int BRICK_WIDTH = 59;
const int BRICK_HEIGHT = 15;

const int BRICKS_COUNT = 88;
const int BRICKS_PER_ROW = 11;
const int BRICKS_DISTANCE = 15;

const int PROBABILITY_POWER_UP = 15;
const int PROBABILITY_CONTAINS_BALL = 30;

Game::Game() : _isRunning(false), _window(nullptr), _renderer(nullptr) {}

Game::~Game() { clean(); }

void Game::run(std::string configuration) {

    init(configuration);
    while (_isRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::init(std::string configuration) {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL_Init : " << SDL_GetError() << std::endl;
        _isRunning = false;
        return;
    }

    // Création de la fenêtre
    _window = SDL_CreateWindow("Casse-briques", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (_window == nullptr) {
        std::cerr << "Erreur SDL_CreateWindow : " << SDL_GetError()
                  << std::endl;
        _isRunning = false;
        return;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Erreur TTF_Init : " << TTF_GetError() << std::endl;
        _isRunning = false;
        return;
    }

    // Création du renderer
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (_renderer == nullptr) {
        std::cerr << "Erreur SDL_CreateRenderer : " << SDL_GetError()
                  << std::endl;
        _isRunning = false;
        return;
    }

    // showMenu();

    // Création de la plateforme et de la balle
    _platform = std::make_shared<Platform>(
        WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20, PLATFORM_WIDTH, PLATFORM_HEIGHT,
        SDL_Color{255, 255, 0, 255}, PLATFORM_SPEED);

    // Création des briques
    setPosition_balle(WINDOW_HEIGHT / 2);
    if (configuration == "rectangle" || configuration == "RECTANGLE") {
        createBricks(RECTANGLE);
    } else if (configuration == "triangle" || configuration == "TRIANGLE") {
        createBricks(TRIANGLE);
    } else if (configuration == "hexagon" || configuration == "HEXAGON") {
        createBricks(HEXAGON);
    } else {
        loadBricksFromFile(configuration);
    }

    _ball.push_back(std::make_shared<Ball>(
        WINDOW_WIDTH / 2, getPosition_balle(), BALL_RADIUS,
        SDL_Color{0, 255, 0, 255}, BALL_SPEED_X, BALL_SPEED_Y));

    _isRunning = true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            _isRunning = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _platform->move(-1, WINDOW_WIDTH);
                break;
            case SDLK_RIGHT:
                _platform->move(1, WINDOW_WIDTH);
                break;
            }
        }
    }
}

void Game::update() {
    for (auto &ball : _ball) {
        ball->move(WINDOW_WIDTH, WINDOW_HEIGHT);
        ball->collideWithPlatform(_platform->getX(), _platform->getY(),
                                  _platform->getWidth(),
                                  _platform->getHeight());
        if (ball->getY() + ball->getRadius() > WINDOW_HEIGHT) {

            setScore(getScore() - 5);

            ball->setIsActive(false);
            if (isAllBallDown()) {
                setLives(getLives() - 1);
            }

            ball->setSpeedX(0);
            ball->setSpeedY(0);
            ball->setInvisible();
            ball->setColor(SDL_Color{0, 0, 0, 255});
            ball->draw(_renderer);
            if (getLives() > 0) {

                if (isAllBallDown()) {

                    _ball.push_back(std::make_shared<Ball>(
                        WINDOW_WIDTH / 2, getPosition_balle(), BALL_RADIUS,
                        SDL_Color{0, 255, 0, 255}, BALL_SPEED_X, BALL_SPEED_Y));
                }
            }
        }
    }

    if (isAllBallDown() && getLives() == 0) {
        _isRunning = false;
        std::cout << "PERDU !" << std::endl;
    }

    int count_bricks_destroyed = 0;
    for (auto &brick : _bricks) {
        if (brick->getDestroyed() == true)
            count_bricks_destroyed++;
    }

    if (count_bricks_destroyed == _bricks.size()) {
        _isRunning = false;
        std::cout << "GAGNE !" << std::endl;
    }

    checkBallBrickCollision();

    for (auto &powerUp : _powerUps) {
        powerUp->move(WINDOW_WIDTH, WINDOW_HEIGHT);
        if (powerUp->getIsActive() || powerUp->getIsUsed()) {
            continue;
        }

        if (powerUp->collideWithPlatform(_platform->getX(), _platform->getY(),
                                         _platform->getWidth(),
                                         _platform->getHeight())) {
            powerUp->setInvisible();
            powerUp->draw(_renderer);
            powerUp->setX(WINDOW_HEIGHT - 50);
            applyPowerUp(powerUp);
        }
    }

    for (auto &powerUp : _powerUps) {

        if (powerUp->getIsActive() && powerUp->getIsUsed() == false) {
            std::cout << "Duration : " << powerUp->getDuration() << std::endl;
            if (powerUp->getHasDuration() >= 0) {
                powerUp->setDuration(powerUp->getDuration() - 1);
                if (powerUp->getDuration() <= 0) {
                    desapplyPowerUp(powerUp);
                }
            }
        }
        std::cout << "IsActive : " << powerUp->getIsActive() << std::endl;
        std::cout << "IsUsed : " << powerUp->getIsUsed() << std::endl;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    _platform->draw(_renderer);

    for (auto &ball : _ball) {
        ball->draw(_renderer);
    }

    for (auto &brick : _bricks) {
        brick->draw(_renderer);
    }

    for (auto &powerUp : _powerUps) {
        powerUp->draw(_renderer);
    }

    drawScore(); // Afficher le score
    drawLives(); // Afficher le nombre de vies
    SDL_RenderPresent(_renderer);
}

void Game::clean() {
    SDL_Quit();
    TTF_Quit();
}

void Game::checkBallBrickCollision() {
    for (auto &brick : _bricks) {

        if (brick->getDestroyed())
            continue;

        for (auto &ball : _ball) {
            if (!ball->getIsActive())
                continue;

            if (ball->collideWithBrick(brick->getX(), brick->getY(),
                                       brick->getWidth(), brick->getHeight(),
                                       brick->getType())) {
                brick->setResistance(brick->getResistance() - 1);
                if (brick->getResistance() == 0) {
                    setScore(getScore() + 10);
                    brick->setDestroyed(true);
                    brick->setInvisible();
                    brick->draw(_renderer);
                    if (brick->getContainsBall() == 1) {
                        _ball.push_back(std::make_shared<Ball>(
                            brick->getX(), brick->getY(), BALL_RADIUS,
                            SDL_Color{0, 255, 0, 255}, BALL_SPEED_X,
                            BALL_SPEED_Y));
                        break;
                    }
                    if (brick->getContainsPowerUp() == 1) {
                        // Gestion des power-ups

                        std::cout << "power up" << std::endl;
                        PowerUpType type = static_cast<PowerUpType>(
                            rand() % 6); // 6 types de power-ups
                        SDL_Color color;
                        std::cout << "type : " << type << std::endl;
                        if (type == BONUS_INCREASE_PLATFORM_LENGTH ||
                            type == BONUS_INCREASE_PLATFORM_SPEED ||
                            type == BONUS_EXTRA_LIFE) {
                            // Couleur blanche pour les bonus
                            color = SDL_Color{255, 255, 255, 255};
                        } else {
                            // Couleur grise pour les malus
                            // couleur rouge pour les malus
                            color = SDL_Color{255, 0, 0, 255};
                        }
                        auto powerUp = std::make_shared<PowerUp>(
                            brick->getX(), brick->getY(), BALL_RADIUS, color, 0,
                            0.08, type);

                        if (type == BONUS_INCREASE_PLATFORM_LENGTH ||
                            type == BONUS_INCREASE_PLATFORM_SPEED ||
                            type == MALUS_DECREASE_PLATFORM_SPEED) {
                            powerUp->setHasDuration(true);
                            powerUp->setDuration(1000);
                        }

                        _powerUps.push_back(powerUp);
                    }
                } else {
                    setScore(getScore() + 1);
                }
                brick->changeColor(_renderer);
            }
        }
    }
}

void Game::loadBricksFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur ouverture du fichier " << filename << std::endl;
        return;
    }

    std::string type;
    std::getline(file, type); // Récupération de la première ligne
    std::cout << "Type de brique : " << type << std::endl;

    BrickType brickType;
    if (type == "RECTANGLE" || type == "rectangle") {
        brickType = RECTANGLE;
    } else if (type == "TRIANGLE" || type == "triangle") {
        brickType = TRIANGLE;
    } else if (type == "HEXAGON" || type == "hexagon") {
        brickType = HEXAGON;
    }

    std::string line;
    int y = 50;
    while (std::getline(file, line)) {
        int x = 0;
        for (char &c : line) {
            if (c == '#' || c == '+' ||
                c == '*') { // Ces symboles répresentent la résistance et la
                            // couleur des briques

                SDL_Color color;
                int resistance;
                bool containsBall =
                    rand() % 100 < PROBABILITY_CONTAINS_BALL ? 1 : 0;

                switch (c) {
                case '#':
                    // Couleur rouge pour une résistance de 1
                    color = SDL_Color{255, 0, 0, 255};
                    resistance = 1;
                    break;
                case '+':
                    // Couleur verte pour une résistance de 2
                    color = SDL_Color{0, 255, 0, 255};
                    resistance = 2;
                    break;
                case '*':
                    // Couleur bleue pour une résistance de 3
                    color = SDL_Color{0, 0, 255, 255};
                    resistance = 3;
                    break;
                }
                bool containsPowerUp = false;
                if (containsBall == false) {
                    // containsPowerUp =
                    //     rand() % 100 < PROBABILITY_CONTAINS_BALL ? 1 : 0;
                    containsPowerUp = true;
                }

                _bricks.push_back(std::make_shared<Brick>(
                    x, y, BRICK_WIDTH, BRICK_HEIGHT, color, resistance,
                    containsBall, containsPowerUp, brickType));
            }
            x += BRICK_WIDTH + BRICKS_DISTANCE;
        }
        y += BRICK_HEIGHT + BRICKS_DISTANCE;
        setPosition_balle(y + 5);
    }

    file.close();
}

void Game::drawScore() {
    std::string scoreText = "Score: " + std::to_string(getScore());
    drawText(scoreText, 10, 10, 20, SDL_Color{255, 255, 255, 255});
}

void Game::drawText(const std::string &text, int x, int y, int size,
                    SDL_Color color) {
    TTF_Font *font = TTF_OpenFont("../assets/arial.ttf", size);
    if (font == nullptr) {
        std::cerr << "Erreur TTF_OpenFont : " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        std::cerr << "Erreur TTF_RenderText_Solid : " << TTF_GetError()
                  << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Erreur SDL_CreateTextureFromSurface : " << SDL_GetError()
                  << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(_renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Game::createBricks(BrickType type) {
    int x;
    int y;
    for (int i = 0; i < BRICKS_COUNT; i++) {

        x = (i % BRICKS_PER_ROW) * (BRICK_WIDTH + BRICKS_DISTANCE);
        y = (i / BRICKS_PER_ROW) * (BRICK_HEIGHT + BRICKS_DISTANCE) + 50;

        int resistance = rand() % 3 + 1;
        bool containsBall = rand() % 100 < PROBABILITY_CONTAINS_BALL ? 1 : 0;

        SDL_Color color;
        switch (resistance) {
        case 1:
            // Couleur rouge pour une résistance de 1
            color = SDL_Color{255, 0, 0, 255};
            break;
        case 2:
            // Couleur verte pour une résistance de 2
            color = SDL_Color{0, 255, 0, 255};
            break;
        case 3:
            // Couleur bleue pour une résistance de 3
            color = SDL_Color{0, 0, 255, 255};
            break;
        }
        bool containsPowerUp = false;
        if (containsBall == false) {
            // containsPowerUp = rand() % 100 < PROBABILITY_CONTAINS_BALL ?
            // 1 : 0;
            containsPowerUp = true;
        }
        _bricks.push_back(std::make_shared<Brick>(
            x, y, BRICK_WIDTH, BRICK_HEIGHT, color, resistance, containsBall,
            containsPowerUp, type));
    }
}

void Game::drawLives() {
    std::string livesText = "Vies: " + std::to_string(getLives());
    drawText(livesText, WINDOW_WIDTH - 100, 10, 20,
             SDL_Color{255, 255, 255, 255});
}

bool Game::isAllBallDown() {
    int count_balls_down = 0;
    for (auto &ball : _ball) {
        if (ball->getIsActive() == false)
            count_balls_down++;
    }
    if (count_balls_down == _ball.size())
        return true;

    return false;
}

void Game::applyPowerUp(std::shared_ptr<PowerUp> powerUp) {
    switch (powerUp->getType()) {

    case BONUS_INCREASE_PLATFORM_LENGTH:
        if (_platform->getWidth() >= 300)
            break;
        _platform->setWidth(_platform->getWidth() + 80);
        break;
    case BONUS_INCREASE_PLATFORM_SPEED:
        _platform->setSpeed(_platform->getSpeed() + 2);
        break;
    case BONUS_EXTRA_LIFE:
        setLives(getLives() + 1);
        break;
    case MALUS_DECREASE_PLATFORM_LENGTH:
        if (_platform->getWidth() <= 50)
            break;
        _platform->setWidth(_platform->getWidth() - 80);
        break;
    case MALUS_DECREASE_PLATFORM_SPEED:
        _platform->setSpeed(_platform->getSpeed() - 2);
        break;
    case MALUS_LOSE_LIFE:
        if (getLives() > 0) {
            setLives(getLives() - 1);
        } else {
            _isRunning = false;
            std::cout << "PERDU !" << std::endl;
        }
        break;
    }
    powerUp->setIsActive(true);
}

void Game::desapplyPowerUp(std::shared_ptr<PowerUp> powerUp) {
    switch (powerUp->getType()) {
    case BONUS_INCREASE_PLATFORM_LENGTH:
        _platform->setWidth(_platform->getWidth() - 80);
        break;
    case BONUS_INCREASE_PLATFORM_SPEED:
        _platform->setSpeed(_platform->getSpeed() - 2);
        break;
    case BONUS_EXTRA_LIFE:
        break;
    case MALUS_DECREASE_PLATFORM_LENGTH:
        _platform->setWidth(_platform->getWidth() + 80);
        break;
    case MALUS_DECREASE_PLATFORM_SPEED:
        _platform->setSpeed(_platform->getSpeed() + 2);
        break;
    case MALUS_LOSE_LIFE:
        break;
    }
    powerUp->setIsActive(false);
    powerUp->setIsUsed(true);
}