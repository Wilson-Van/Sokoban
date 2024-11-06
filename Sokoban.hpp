// Copyright 2024 Wilson Van

#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <SFML/Graphics.hpp>

namespace SB {
enum Direction {Up, Down, Left, Right};
class Sokoban : public sf::Drawable {
 public:
    Sokoban();
    int const width();
    int const height();
    sf::Vector2i const playerLoc();
    void movePlayer(Direction d);
    bool const isWon();
    void resetMap();
    friend std::istream& operator>>(std::istream& is, Sokoban& game);
    friend std::ostream& operator<<(std::ostream &out, const Sokoban& game);

 private:
    int _width;
    int _height;
    sf::Texture _wall;
    sf::Texture _player;
    sf::Texture _ground;
    sf::Texture _box;
    sf::Texture _storage;
    char* _map;
    char* _original_map;
    sf::Sprite* _spriteMap;
    bool checkValidMove(int desIndex, Direction d);
    bool checkMoveBox(int boxPos, Direction d);
    void moveBox(int boxPos, Direction d);

 protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
std::istream& operator>>(std::istream& is, Sokoban& game);
std::ostream& operator<<(std::ostream &out, const Sokoban& game);
};  // namespace SB

#endif
