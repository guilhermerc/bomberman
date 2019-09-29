#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "element.hpp"

using namespace Model;

void Element::read_sprite(char * sprite_path)
{
    std::ifstream sprite_file;
    std::string value;

    sprite_file.open(sprite_path);

    // Reading the number of lines and columns of sprite's matrix
    getline(sprite_file, value, ',');
    this->sprite.l = std::stoi(value);
    getline(sprite_file, value, '\n');
    this->sprite.c = std::stoi(value);

    // Allocating heap memory for sprite
    this->sprite.matrix = (char **) malloc(sizeof(char *) * this->sprite.l);
    for(int i = 0; i < this->sprite.l; i++)
        this->sprite.matrix[i] = (char *) malloc(sizeof(char) * this->sprite.c);

    // Reading the sprite's matrix
    for(int i = 0; i < this->sprite.l; i++)
    {
        for(int j = 0; j < this->sprite.c; j++)
        {
            char delim = 0;
            delim = ',';
            // If this char is the last one from its line, the delimiter must be
            // '\n'
            if(j == this->sprite.c - 1)  delim = '\n';
            getline(sprite_file, value, delim);
            this->sprite.matrix[i][j] = (value.c_str())[0];
        }
    }
    sprite_file.close();
}

Element::Element(char * sprite_path)
{
    this->update(sprite_path, 0, 0);
}

Element::Element(char * sprite_path, int x_pos, int y_pos)
{
    this->update(sprite_path, x_pos, y_pos);
}

Element::~Element()
{
    for(int i = 0; i < this->sprite.c; i++)
        free(this->sprite.matrix[i]);
    free(this->sprite.matrix);
}

void Element::update(int x_pos, int y_pos)
{
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void Element::update(char * sprite_path, int x_pos, int y_pos)
{
    this->update(x_pos, y_pos);
    this->read_sprite(sprite_path);
}

// TODO: Implement this
void Element::render()
{

}
