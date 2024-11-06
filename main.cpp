// Copyright 2024 Wilson Van

#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

const int XPixel = 64;
const int YPixel = 64;

int main(int argc, char* argv[]) {
    std::string level = argv[1];
    std::ifstream lvl_file(level);
    SB::Sokoban s;
    if (lvl_file.is_open()) {
        lvl_file >> s;
        unsigned h = s.height() * 64;
        unsigned w = s.width() * 64;
        sf::RenderWindow window(sf::VideoMode(w, h), "Sokoban");
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(10);
        sf::Texture t;
        t.loadFromFile("win_screen.png");
        sf::Sprite win;
        sf::Vector2u win_size = t.getSize();
        sf::Vector2f win_scale = {static_cast<float>(win_size.x), static_cast<float>(win_size.y)};
        win_scale.x /= w;
        win_scale.y /= h;
        win.setTexture(t);
        win.scale(1.0/win_scale.x, 1.0/win_scale.y);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                s.movePlayer(SB::Up);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                s.movePlayer(SB::Down);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                s.movePlayer(SB::Left);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                s.movePlayer(SB::Right);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                s.resetMap();

            window.clear(sf::Color::Black);
            window.draw(s);

            if (s.isWon()) {
                window.draw(win);
            }

            window.display();
        }
    }
    return 0;
}
