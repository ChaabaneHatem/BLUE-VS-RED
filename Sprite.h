/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.h
 * Author: hatem
 *
 * Created on December 4, 2017, 11:31 PM
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef SPRITE_H
#define SPRITE_H

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))




class Sprite {
public:
    
    int x;
    int y;
    int velocity;
    int row_SubImage;
    SDL_Rect positionSprite;
    SDL_Rect positionFrameCourant;
    int nbr_frame;
    int width;
    int height;
    int vecteurDeplacementx;
    int vecteurDeplavementy;
    int nbr_SubImageVertical;
    int nbr_SubImageHorizontal;
    
    
    
    Sprite();
    
    static SDL_Surface* LoadSprite(Sprite* sprite);
    
    static void EvolueSprite(const Uint8* state,SDL_Rect* mur,Sprite* sprite);
    
    static void freeSprite(Sprite* sprite);
    
    static void spriteFrame(Sprite* sprite, int nbr_SubImageHorizontal, int nbr_SubImageVertical, int row_SubImage, int nbr_frame);
    
    
    
    
    
    
    
    
    
    
};

#endif /* SPRITE_H */

