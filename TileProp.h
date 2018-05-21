/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TileProp.h
 * Author: hatem
 *
 * Created on December 3, 2017, 1:19 PM
 */

#ifndef TILEPROP_H
#define TILEPROP_H
#include <SDL2/SDL.h>

class TileProp {
public:
    SDL_Rect tilePosition;
    int danger;
    
    
    TileProp();
    virtual ~TileProp();
    
    
};

#endif /* TILEPROP_H */

