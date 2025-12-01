#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<thread>
#include<chrono>
#include "Snake.h"
#include "Food.h"

#define WIDTH 80
#define HEIGHT 50
#define SIZE 15
#define W SIZE*WIDTH
#define H SIZE*HEIGHT

using namespace sf;

// Game states
enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

// Function to load/save high score
int loadHighScore() {
    std::ifstream file("highscore.txt");
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}

void saveHighScore(int score) {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << score;
        file.close();
    }
}

int main() {
    // Initialize game objects
    Point startPos(WIDTH / 2, HEIGHT / 2);
    Snake snake(startPos);
    Food food;
    
    // Game variables
    int score = 0;
    int highScore = loadHighScore();
    GameState gameState = MENU;
    float baseDelay = 0.1f;
    float delay = baseDelay;
    
    Clock clock;
    float timer = 0;
    
    RenderWindow window(VideoMode(W, H), "Snake Game - Enhanced Edition");
    
    // Load textures
    Texture t1, t2, t3;
    if (!t1.loadFromFile("images/green.bmp") ||
        !t2.loadFromFile("images/blue.bmp") ||
        !t3.loadFromFile("images/red.bmp")) {
        std::cout << "Error loading textures!" << std::endl;
        return -1;
    }
    
    Sprite sprite1(t1);  // Background
    Sprite sprite2(t2);  // Snake
    Sprite sprite3(t3);  // Food
    
    // Load font
    Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cout << "Unable to Load Font" << std::endl;
        return -1;
    }
    
    // Create text objects
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);
    
    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(20);
    highScoreText.setFillColor(Color::Yellow);
    highScoreText.setPosition(10, 35);
    
    Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("PAUSED\nPress P or Space to Resume");
    pauseText.setCharacterSize(40);
    pauseText.setStyle(Text::Bold);
    pauseText.setFillColor(Color::White);
    pauseText.setPosition(W / 2 - 200, H / 2 - 50);
    
    Text menuText;
    menuText.setFont(font);
    menuText.setString("SNAKE GAME\n\nControls:\nArrow Keys - Move\nP or Space - Pause\nR - Restart (after game over)\nEsc - Quit\n\nPress ENTER to Start!");
    menuText.setCharacterSize(30);
    menuText.setFillColor(Color::White);
    menuText.setPosition(W / 2 - 200, H / 2 - 150);
    
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setStyle(Text::Bold);
    gameOverText.setFillColor(Color::Red);
    
    Text speedText;
    speedText.setFont(font);
    speedText.setCharacterSize(20);
    speedText.setFillColor(Color::Cyan);
    speedText.setPosition(10, 60);
    
    // Track key states for single press detection
    bool pKeyPressed = false;
    bool spaceKeyPressed = false;
    bool enterKeyPressed = false;
    bool rKeyPressed = false;
    
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
                window.close();
        }
        
        // Handle menu state
        if (gameState == MENU) {
            // Check for Enter key to start
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                if (!enterKeyPressed) {
                    gameState = PLAYING;
                    enterKeyPressed = true;
                }
            } else {
                enterKeyPressed = false;
            }
            
            // Draw menu
            window.clear(Color(50, 50, 50));
            for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                    sprite1.setPosition(static_cast<float>(i * SIZE), static_cast<float>(j * SIZE));
                    window.draw(sprite1);
                }
            }
            window.draw(menuText);
            
            // Display high score in menu
            highScoreText.setString("High Score: " + std::to_string(highScore));
            highScoreText.setPosition(W / 2 - 100, H / 2 + 150);
            window.draw(highScoreText);
            
            window.display();
            continue;
        }
        
        // Handle pause toggle
        if (Keyboard::isKeyPressed(Keyboard::P)) {
            if (!pKeyPressed) {
                if (gameState == PLAYING) {
                    gameState = PAUSED;
                } else if (gameState == PAUSED) {
                    gameState = PLAYING;
                }
                pKeyPressed = true;
            }
        } else {
            pKeyPressed = false;
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (!spaceKeyPressed) {
                if (gameState == PLAYING) {
                    gameState = PAUSED;
                } else if (gameState == PAUSED) {
                    gameState = PLAYING;
                }
                spaceKeyPressed = true;
            }
        } else {
            spaceKeyPressed = false;
        }
        
        // Handle restart after game over
        if (gameState == GAME_OVER) {
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                if (!rKeyPressed) {
                    // Reset game
                    snake.reset(startPos);
                    food.genFood();
                    score = 0;
                    delay = baseDelay;
                    timer = 0;
                    gameState = PLAYING;
                    rKeyPressed = true;
                }
            } else {
                rKeyPressed = false;
            }
        }
        
        // Game logic only when playing
        if (gameState == PLAYING) {
            timer += time;
            
            // Handle movement input
            if (Keyboard::isKeyPressed(Keyboard::Left))
                snake.setDir('l');
            if (Keyboard::isKeyPressed(Keyboard::Right))
                snake.setDir('r');
            if (Keyboard::isKeyPressed(Keyboard::Up))
                snake.setDir('u');
            if (Keyboard::isKeyPressed(Keyboard::Down))
                snake.setDir('d');
            
            if (timer > delay) {
                snake.moveSnake();
                timer = 0;
                
                if (snake.eaten(food)) {
                    snake.grow();
                    score += 10;
                    food.genFood();
                    
                    // Increase speed every 50 points (cap at minimum delay of 0.03)
                    if (score % 50 == 0 && delay > 0.03f) {
                        delay -= 0.01f;
                    }
                    
                    // Update high score
                    if (score > highScore) {
                        highScore = score;
                        saveHighScore(highScore);
                    }
                }
            }
            
            // Check for collision (wall or self)
            if (snake.collided() || snake.selfCollided()) {
                gameState = GAME_OVER;
            }
        }
        
        // Clear and draw background
        window.clear();
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                sprite1.setPosition(static_cast<float>(i * SIZE), static_cast<float>(j * SIZE));
                window.draw(sprite1);
            }
        }
        
        // Draw snake
        std::vector<Point> snakeBody = snake.getSnakeBody();
        for (size_t i = 0; i < snakeBody.size(); i++) {
            sprite2.setPosition(static_cast<float>(snakeBody[i].X * SIZE), static_cast<float>(snakeBody[i].Y * SIZE));
            window.draw(sprite2);
        }
        
        // Draw food
        sprite3.setPosition(static_cast<float>(food.getFoodPos().X * SIZE), static_cast<float>(food.getFoodPos().Y * SIZE));
        window.draw(sprite3);
        
        // Draw score
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        
        // Draw high score
        highScoreText.setString("High Score: " + std::to_string(highScore));
        highScoreText.setPosition(10, 35);
        window.draw(highScoreText);
        
        // Draw speed level
        int speedLevel = static_cast<int>((baseDelay - delay) / 0.01f) + 1;
        speedText.setString("Speed Level: " + std::to_string(speedLevel));
        window.draw(speedText);
        
        // Draw pause overlay
        if (gameState == PAUSED) {
            // Draw semi-transparent overlay
            RectangleShape overlay(Vector2f(static_cast<float>(W), static_cast<float>(H)));
            overlay.setFillColor(Color(0, 0, 0, 150));
            window.draw(overlay);
            window.draw(pauseText);
        }
        
        // Draw game over screen
        if (gameState == GAME_OVER) {
            // Draw semi-transparent overlay
            RectangleShape overlay(Vector2f(static_cast<float>(W), static_cast<float>(H)));
            overlay.setFillColor(Color(0, 0, 0, 180));
            window.draw(overlay);
            
            std::string gameOverStr = "GAME OVER!\n\nFinal Score: " + std::to_string(score);
            if (score >= highScore && score > 0) {
                gameOverStr += "\nNEW HIGH SCORE!";
            }
            gameOverStr += "\n\nPress R to Restart\nPress Esc to Quit";
            gameOverText.setString(gameOverStr);
            gameOverText.setPosition(W / 2 - 180, H / 2 - 100);
            window.draw(gameOverText);
        }
        
        window.display();
    }
    
    return 0;
}
