/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sprite.cpp
 * Author: hatem
 * 
 * Created on December 4, 2017, 11:31 PM
 */

#include "Sprite.h"
#include <stdio.h>
Sprite::Sprite() {
    x = 40;
    y = 390;
    velocity = 0;
    row_SubImage = LEFT;
    vecteurDeplacementx = vecteurDeplavementy = 0;
}




SDL_Surface* Sprite::LoadSprite(Sprite* sprite) {
    
    SDL_Surface* surfaceSprite;
    surfaceSprite = IMG_Load("img/red.png");
    
    if(surfaceSprite == NULL) {
        printf("fichier sprite introuvable \n");  
    } else {
        sprite->width = surfaceSprite->w;
        sprite->height = surfaceSprite->h;
        return surfaceSprite;
    }
    
}



void Sprite::spriteFrame(Sprite* sprite, int nbr_SubImageHorizontal, int nbr_SubImageVertical, int row_SubImage, int nbr_frame) {
    
    sprite->nbr_SubImageHorizontal = nbr_SubImageHorizontal;
    sprite->nbr_SubImageVertical = nbr_SubImageVertical;
    sprite->row_SubImage = row_SubImage;
    sprite->nbr_frame = nbr_frame;
    
    Uint32 ticks = SDL_GetTicks();
    Uint32 spriteAnimation = (ticks / 100) % (nbr_frame);
    sprite->positionFrameCourant = { (int)spriteAnimation * (sprite->width / nbr_SubImageHorizontal), (sprite->height / nbr_SubImageVertical)*(row_SubImage - 1), sprite->width / nbr_SubImageHorizontal, sprite->height / nbr_SubImageVertical };
    sprite->positionSprite = { sprite->x, sprite->y, sprite->width / nbr_SubImageHorizontal, sprite->height / nbr_SubImageVertical };
}


void move(const Uint8* state, Sprite* sprite) {
    
    sprite->vecteurDeplacementx = sprite->vecteurDeplavementy = 0;
    
    
    int posY=40;
    
    
    int orientation = 1;//   1 => RIGHT  ||   2 => LEFT
    int jumpVel = 30;
    bool jumping = true;
    int gravity = 40;
    Uint32 ticks = SDL_GetTicks();
    Uint32 spriteAnimation = (ticks / 100) % (13);
    
    
    if (orientation == 1) {
        Sprite::spriteFrame(sprite, 17, 14, 1, 8);
    }
    if (orientation == 2) {
        Sprite::spriteFrame(sprite, 17, 14, 2, 8);
    }
    
    
    if (state[SDL_SCANCODE_RIGHT]&& jumping) {
        sprite->vecteurDeplacementx +=sprite->velocity;
        Sprite::spriteFrame(sprite, 17, 14, 3, 8);
        orientation = 1;
        if (state[SDL_SCANCODE_D]) {
            if (orientation == 1)
                Sprite::spriteFrame(sprite, 17, 14, 7, 6);
            //if (orientation == 2)
            //    red.spriteFrame(renderer, 17, 14, 8, 6);
        }
    }
    
    if (state[SDL_SCANCODE_LEFT]&& jumping) {
        sprite->vecteurDeplacementx -=sprite->velocity;
        Sprite::spriteFrame(sprite, 17, 14, 4, 8);
        orientation = 2;
        if (state[SDL_SCANCODE_D]) {
            ///if (orientation == 1)
            //    red.spriteFrame(renderer, 17, 14, 7, 6);
            if (orientation == 2)
                Sprite::spriteFrame(sprite, 17, 14, 8, 6);
        }
    }
    
    if (state[SDL_SCANCODE_UP]) {
        sprite->vecteurDeplavementy -=sprite->velocity;
        if (orientation == 1){
            Sprite::spriteFrame(sprite, 17, 14, 5, 13);}
        if (orientation == 2){
            Sprite::spriteFrame(sprite, 17, 14, 6, 13);}
        if(jumping){
            jumping = false;}
    }
    
    if (state[SDL_SCANCODE_DOWN]&& jumping) {
        sprite->vecteurDeplavementy +=sprite->velocity;
        if (orientation == 1)
            Sprite::spriteFrame(sprite, 17, 14, 13, 6);
        if (orientation == 2)
            Sprite::spriteFrame(sprite, 17, 14, 14, 6);
    }
    
    if (state[SDL_SCANCODE_A]&& jumping) {
        if (orientation == 1)
            Sprite::spriteFrame(sprite, 17, 14, 9, 14);
        if (orientation == 2)
            Sprite::spriteFrame(sprite, 17, 14, 10, 14);
    }
    if (state[SDL_SCANCODE_S]&& jumping) {
        if (orientation == 1)
            Sprite::spriteFrame(sprite, 17, 14, 11, 10);
        if (orientation == 2)
            Sprite::spriteFrame(sprite, 17, 14, 12, 10);
    }
    
    
    if (!jumping){
        posY-= jumpVel;
        sprite->y = sprite->y - jumpVel;
        jumpVel -= gravity; 
        
    }
    
    if (posY>=500)
    {
        
        jumpVel = (int)spriteAnimation*20;
        jumping = true;
    }
    
    
    sprite->vecteurDeplavementy += 7;
    //sprite->y +=5;
    //sprite->y = posY;
    
    
    
}



int CollisionDecor(SDL_Rect* mur,SDL_Rect* positionSprite)
{
    SDL_Rect resultat = {1, 1, 1, 1};
    if(SDL_IntersectRect(mur, positionSprite, &resultat) == SDL_FALSE) {
        return 0; 
    }
    return 1; 
}

int EssaiDeplacement(SDL_Rect* mur,Sprite* sprite,int vx,int vy)
{
    SDL_Rect test;
    test = sprite->positionSprite;
    test.x = sprite->x;
    test.y = sprite->y;
    test.x+=vx;
    test.y+=vy;
    if (CollisionDecor(mur,&test)==0)
    {
        sprite->x = test.x;
        sprite->y = test.y;
        return 1;
    }
    return 0;
}

void Affine(SDL_Rect* mur,Sprite* sprite,int vx,int vy)
{
    int i;	
    for(i=0;i<ABS(vx);i++)
    {
        if (EssaiDeplacement(mur,sprite,SGN(vx),0)==0)
            break;
    }
    for(i=0;i<ABS(vy);i++)
    {
        if (EssaiDeplacement(mur,sprite,0,SGN(vy))==0)
            break;			
    }
}

void Deplace(SDL_Rect* mur,Sprite* sprite,int vx,int vy)
{
    if (EssaiDeplacement(mur,sprite,vx,vy)==1)
        return;
    Affine(mur,sprite,vx,vy);
}





void Sprite::EvolueSprite(const Uint8* state,SDL_Rect* mur,Sprite* sprite)
{
    
    move(state, sprite);
    Deplace(mur,sprite,sprite->vecteurDeplacementx,sprite->vecteurDeplavementy);
}


void Sprite::freeSprite(Sprite* sprite) {
    
    
    IMG_Quit();
    delete(sprite);
    
    
    
}

