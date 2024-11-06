// Copyright 2024 Wilson Van

#include "Sokoban.hpp"

const int XPixel = 64;
const int YPixel = 64;


    std::istream& SB::operator>>(std::istream &input, SB::Sokoban& game) {
        input >> game._height;
        input >> game._width;
        game._map = new char[game._height * game._width];
        game._original_map = new char[game._height * game._width];
        game._spriteMap = new sf::Sprite[game._height * game._width];
        for (int i = 0; i < game._height * game._width; i++) {
            game._map[i] = input.get();
            if (game._map[i] == '\n')
                i--;
            game._original_map[i] = game._map[i];
        }
        return input;
    }
    std::ostream& SB::operator<<(std::ostream &out, const SB::Sokoban& game) {
        out << game._height << game._width;
        for (int i = 0; i < game._height * game._width; i++) {
            if (i%game._width == 0)
                out << std::endl;
            out << game._map[i];
        }
        return out;
    }

SB::Sokoban::Sokoban() {
    _width = 0;
    _height = 0;

    this->_ground.loadFromFile("sokoban/ground_01.png");
    this->_storage.loadFromFile("sokoban/ground_04.png");
    this->_box.loadFromFile("sokoban/crate_03.png");
    this->_wall.loadFromFile("sokoban/block_06.png");
    this->_player.loadFromFile("sokoban/player_05.png");
}

int const SB::Sokoban::width() {
    return _width;
}

int const SB::Sokoban::height() {
    return _height;
}

sf::Vector2i const SB::Sokoban::playerLoc() {
    int pos = std::find(_map, _map + _width * _height, '@') - _map;
    return {pos%_width, pos/_width};
}

void SB::Sokoban::movePlayer(SB::Direction d) {
    sf::Vector2i curLoc = playerLoc();
    int curIndex = curLoc.x + curLoc.y * _width;
    int desIndex;
    if (d == Left) {
        desIndex = curIndex - 1;
    } else if (d == Right) {
        desIndex = curIndex + 1;
    }  else if (d == Up) {
        desIndex = curIndex - _width;
    } else {
        desIndex = curIndex + _width;
    }
    if (!checkValidMove(desIndex, d))
        return;
    if (_map[desIndex] == 'A' || _map[desIndex] == '1')
        moveBox(desIndex, d);
    _map[desIndex] = '@';
    if (_original_map[curIndex] == 'a' || _original_map[curIndex] == '1')
        _map[curIndex] = 'a';
    else
        _map[curIndex] = '.';
}

bool const SB::Sokoban::isWon() {
    int storageCount = std::count(_original_map, _original_map + _width * _height, 'a') +
    std::count(_original_map, _original_map + _width * _height, '1');
    int boxCount = std::count(_original_map, _original_map + _width * _height, 'A') +
    std::count(_original_map, _original_map + _width * _height, '1');
    int finishedCount = 0;
    int expectedFinished = std::min(boxCount, storageCount);
    for (int i =0; i < _width * _height; i++) {
        if ((_original_map[i] == '1' || _original_map[i] == 'a') && _map[i] == '1')
            finishedCount++;
    }
    return finishedCount == expectedFinished;
}

void SB::Sokoban::resetMap() {
    for (int i =0; i < _width * _height; i++)
        _map[i] = _original_map[i];
}

void SB::Sokoban::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (int i = 0; i < _height * _width; i++) {
        if (_map[i] == '#') {
            _spriteMap[i].setTexture(_wall);
        } else if (_map[i] == '.') {
            _spriteMap[i].setTexture(_ground);
        } else if (_map[i] == 'a') {
            _spriteMap[i].setTexture(_storage);
        } else if (_map[i] == 'A') {
            _spriteMap[i].setTexture(_ground);
            target.draw(_spriteMap[i]);
            _spriteMap[i].setTexture(_box);
        } else if (_map[i] == '1') {
            _spriteMap[i].setTexture(_storage);
            target.draw(_spriteMap[i]);
            _spriteMap[i].setTexture(_box);
        } else if (_map[i] == '@') {
            if (_original_map[i] == 'a' || _original_map[i] == '1')
                _spriteMap[i].setTexture(_storage);
            else
                _spriteMap[i].setTexture(_ground);
            target.draw(_spriteMap[i]);
            _spriteMap[i].setTexture(_player);
        }
        _spriteMap[i].setPosition(XPixel * (i%_width), YPixel * (i/_width));
        target.draw(_spriteMap[i]);
    }
}


bool SB::Sokoban::checkValidMove(int desIndex, SB::Direction d) {
    if (_map[desIndex] == '#') {
        return false;
    } else if (_map[desIndex] == 'A' || _map[desIndex] == '1') {
        if (checkMoveBox(desIndex, d))
            return true;
        else
            return false;
    }
    if ((d == Left && desIndex % _width == _width - 1) || desIndex < 0) {
        return false;
    } else if (d == Right && desIndex % _width == 0) {
        return false;
    } else if (d == Up && desIndex < 0) {
        return false;
    } else if (d == Down && desIndex >= _width * _height) {
        return false;
    }
    return true;
}

bool SB::Sokoban::checkMoveBox(int boxIndex, SB::Direction d) {
    if (d == Left) {
        if (_map[boxIndex - 1] == '#' || _map[boxIndex - 1] == 'A'
        || _map[boxIndex - 1] == '1' || boxIndex % _width == 0)
            return false;
    } else if (d == Right) {
        if (_map[boxIndex + 1] == '#' || _map[boxIndex + 1] == 'A'
        || _map[boxIndex + 1] == '1' || boxIndex % _width == _width - 1)
            return false;
    } else if (d == Up) {
        if (_map[boxIndex - _width] == '#' || _map[boxIndex - _width] == 'A'
        || _map[boxIndex - _width] == '1' || boxIndex / _height == 0)
            return false;
    } else if (d == Down) {
        if (_map[boxIndex + _width] == '#' || _map[boxIndex + _width] == 'A'
        || _map[boxIndex + _width] == '1' || boxIndex / _height == _width - 1)
            return false;
    }
    return true;
}

void SB::Sokoban::moveBox(int boxPos, SB::Direction d) {
    int boxDesPos;
    if (d == Left) {
        boxDesPos = boxPos - 1;
    } else if (d == Right) {
        boxDesPos = boxPos + 1;
    } else if (d == Up) {
        boxDesPos = boxPos - _width;
    } else if (d == Down) {
        boxDesPos = boxPos + _width;
    }
    if (_map[boxDesPos] == 'a')
        _map[boxDesPos] = '1';
    else
        _map[boxDesPos] = 'A';
}
