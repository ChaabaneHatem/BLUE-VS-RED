/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jeu.h
 * Author: hatem
 *
 * Created on December 13, 2017, 11:54 PM
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Map.h"

#ifndef JEU_H
#define JEU_H


class Jeu {
public:
    Jeu();
    virtual ~Jeu();
    void initialiser();
    void executer();
    void libererMemoire();
private:
    SDL_Surface* imageBackround;
    SDL_Surface* imageSprite;
    SDL_Window* win;
    SDL_Renderer* render;
    SDL_Texture* imageFinalBackround;
    SDL_Event event;
    const Uint8* state;
    bool isRunning = true;
    Map* m;
    Sprite* sprite;
    int wS;
    int hS;
    
};

#endif /* JEU_H */

