#include "Game.h"
#include <iostream>

// Valeurs des constantes pour la taille de la fenêtre
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Valeurs des constantes pour la plateforme
const int PLATFORM_WIDTH = 125;
const int PLATFORM_HEIGHT = 15;
const int PLATFORM_SPEED = 10;

// Valeurs des constantes pour la balle
const int BALL_RADIUS = 5;
const double BALL_SPEED_X = 0.08;
const double BALL_SPEED_Y = 0.09;

// Valeurs des constantes pour les briques
const int BRICK_WIDTH = 59;
const int BRICK_HEIGHT = 15;
const int BRICKS_COUNT = 88;
const int BRICKS_PER_ROW = 11;
const int BRICKS_DISTANCE = 15;

// Valeurs des constantes pour la probabilité d'apparition des power-ups et
// multi-balles
const int PROBABILITY_POWER_UP = 25;
const int PROBABILITY_CONTAINS_BALL = 40;

// Valeurs des constantes pour les power-ups
const int VIE_MAX = 6;
const int INCREASE_PLATFORM_MAX = 300;
const int DECREASE_PLATFORM_MIN = 50;

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
    // On initialise la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL_Init : " << SDL_GetError() << std::endl;
        _isRunning = false;
        return;
    }

    // On crée la fenêtre
    _window = SDL_CreateWindow("Casse-briques", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                               WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (_window == nullptr) {
        std::cerr << "Erreur lors de la création de la SDL : " << SDL_GetError()
                  << std::endl;
        _isRunning = false;
        return;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Erreur lors de l'initiaisation de la TTF  : "
                  << TTF_GetError() << std::endl;
        _isRunning = false;
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (_renderer == nullptr) {
        std::cerr << "Erreur lors de la création du SDL_CreateRenderer : "
                  << SDL_GetError() << std::endl;
        _isRunning = false;
        return;
    }

    // Création de la plateforme
    _platform = std::make_shared<Platform>(
        WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20, PLATFORM_WIDTH, PLATFORM_HEIGHT,
        SDL_Color{255, 255, 0, 255}, PLATFORM_SPEED);

    // Création des briques selon le type choisi
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

    // création de la balle
    _ball.push_back(std::make_shared<Ball>(
        WINDOW_WIDTH / 2, getPosition_balle(), BALL_RADIUS,
        SDL_Color{0, 255, 0, 255}, BALL_SPEED_X, BALL_SPEED_Y));

    // on démarre le jeu
    _isRunning = true;
}

void Game::handleEvents() {
    SDL_Event event;
    // On gère les événements
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

            // On perd 5 points à chaque fois qu'une balle tombe
            setScore(getScore() - 5);

            // On désactive la balle
            ball->setIsActive(false);

            // On vérifie si toutes les balles sont tombées
            if (isAllBallDown()) {
                // On perd une vie si toutes les balles sont tombées
                setLives(getLives() - 1);
            }

            // On détruit la balle
            ball->setSpeedX(0);
            ball->setSpeedY(0);
            ball->setInvisible();
            ball->setColor(SDL_Color{0, 0, 0, 255});
            ball->draw(_renderer);

            // On crée une nouvelle balle si on a encore des vies et si toutes
            // les balles sont tombées
            if (getLives() > 0) {

                if (isAllBallDown()) {

                    _ball.push_back(std::make_shared<Ball>(
                        WINDOW_WIDTH / 2, getPosition_balle(), BALL_RADIUS,
                        SDL_Color{0, 255, 0, 255}, BALL_SPEED_X, BALL_SPEED_Y));
                }
            }
        }
    }

    // On vérifie si on a perdu
    if (isAllBallDown() && getLives() == 0) {
        _isRunning = false;
        std::cout << "PERDU !" << std::endl;
    }

    // On vérifie si on a gagné
    // on compte le nombre de briques détruites
    int count_bricks_destroyed = 0;
    for (auto &brick : _bricks) {
        if (brick->getDestroyed() == true)
            count_bricks_destroyed++;
    }

    // Si toutes les briques sont détruites, on a gagné
    if (count_bricks_destroyed == _bricks.size()) {
        _isRunning = false;
        std::cout << "GAGNE !" << std::endl;
    }

    // On vérifie si la balle a frappé une brique
    checkBallBrickCollision();

    for (auto &powerUp : _powerUps) {

        if (powerUp->getIsActive())
            continue;

        powerUp->move(WINDOW_WIDTH, WINDOW_HEIGHT);

        // On vérifie si le power-up a frappé la plateforme
        if (powerUp->collideWithPlatform(_platform->getX(), _platform->getY(),
                                         _platform->getWidth(),
                                         _platform->getHeight())) {
            powerUp->setInvisible();
            powerUp->draw(_renderer);
            powerUp->setX(WINDOW_HEIGHT - 50);
            // On applique le power-up
            applyPowerUp(powerUp);
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    // On affiche la plateforme
    _platform->draw(_renderer);

    // On affiche les balles
    for (auto &ball : _ball) {
        ball->draw(_renderer);
    }

    // On affiche les briques
    for (auto &brick : _bricks) {
        brick->draw(_renderer);
    }

    // On affiche les power-ups
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

        // Si la brique est détruite, on passe à la suivante
        if (brick->getDestroyed())
            continue;

        // On vérifie si la balle a frappé la brique
        for (auto &ball : _ball) {
            // Si la balle n'est pas active, on passe à la suivante
            if (!ball->getIsActive())
                continue;

            // Si la brique est détruite, on passe à la suivante
            if (ball->collideWithBrick(brick->getX(), brick->getY(),
                                       brick->getWidth(), brick->getHeight(),
                                       brick->getType())) {

                // On diminue la résistance de la brique
                brick->setResistance(brick->getResistance() - 1);
                // Si la résistance de la brique est à 0, on la détruit
                if (brick->getResistance() == 0) {
                    setScore(getScore() + 10);
                    brick->setDestroyed(true);
                    brick->setInvisible();
                    brick->draw(_renderer);

                    // On vérifie si la brique contient une balle ou un power-up
                    if (brick->getContainsBall() == 1) {

                        // On n'ajoute plus de balle, si on a déjà 5 balles
                        if (getNumberOfBall(true) > 5) {
                            break;
                        }

                        int x = brick->getX();
                        if (x < 30) {
                            x += 30;
                        } else if (x > WINDOW_WIDTH - 30) {
                            x -= 30;
                        }

                        // On ajoute une nouvelle balle
                        _ball.push_back(std::make_shared<Ball>(
                            x, brick->getY(), BALL_RADIUS,
                            SDL_Color{0, 255, 0, 255}, BALL_SPEED_X,
                            BALL_SPEED_Y));
                        break;
                    }

                    // Gestion des power-ups

                    if (brick->getContainsPowerUp() == 1) {

                        PowerUpType type = static_cast<PowerUpType>(
                            rand() % 4); // 4 types de power-ups
                        SDL_Color color;

                        if (type == BONUS_INCREASE_PLATFORM_LENGTH ||
                            type == BONUS_EXTRA_LIFE) {
                            // Couleur blanche pour les bonus
                            color = SDL_Color{255, 255, 255, 255};
                        } else {
                            // couleur rouge pour les malus
                            color = SDL_Color{255, 0, 0, 255};
                        }

                        int x = brick->getX();
                        if (x < 30) {
                            x += 30;
                        } else if (x > WINDOW_WIDTH - 30) {
                            x -= 30;
                        }

                        // On ajoute un power-up
                        auto powerUp = std::make_shared<PowerUp>(
                            x, brick->getY(), BALL_RADIUS, color, 0, 0.08,
                            type);

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

    // On détermine le type de brique
    BrickType brickType;
    if (type == "RECTANGLE" || type == "rectangle") {
        brickType = RECTANGLE;
    } else if (type == "TRIANGLE" || type == "triangle") {
        brickType = TRIANGLE;
    } else if (type == "HEXAGON" || type == "hexagon") {
        brickType = HEXAGON;
    }

    // On lit le fichier ligne par ligne
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
                    containsPowerUp =
                        rand() % 100 < PROBABILITY_POWER_UP ? 1 : 0;
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
            containsPowerUp = rand() % 100 < PROBABILITY_POWER_UP ? 1 : 0;
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

    if (getNumberOfBall(false) == _ball.size())
        return true;

    return false;
}

void Game::applyPowerUp(std::shared_ptr<PowerUp> powerUp) {

    switch (powerUp->getType()) {

    case BONUS_INCREASE_PLATFORM_LENGTH:
        std::cout << "plateforme agrandie" << std::endl;
        if (_platform->getWidth() >= INCREASE_PLATFORM_MAX)
            break;
        _platform->setWidth(_platform->getWidth() + 15);
        break;
    case BONUS_EXTRA_LIFE:
        std::cout << "vie gagnée" << std::endl;
        // Limiter le nombre de vies à 6
        if (getLives() >= VIE_MAX)
            break;
        setLives(getLives() + 1);
        break;
    case MALUS_DECREASE_PLATFORM_LENGTH:
        std::cout << "plateforme réduite" << std::endl;
        if (_platform->getWidth() <= DECREASE_PLATFORM_MIN)
            break;
        _platform->setWidth(_platform->getWidth() - 15);

        break;
    case MALUS_LOSE_LIFE:
        if (getLives() > 0) {
            setLives(getLives() - 1);
            std::cout << "vie perdue" << std::endl;
        } else {
            _isRunning = false;
            std::cout << "PERDU !" << std::endl;
        }
        break;
    }
    powerUp->setIsActive(true);
    powerUp->setInvisible();
    powerUp->draw(_renderer);
}

int Game::getNumberOfBall(bool isActive) {
    int count_balls = 0;
    for (auto &ball : _ball) {
        if (ball->getIsActive() == isActive)
            count_balls++;
    }
    return count_balls;
}