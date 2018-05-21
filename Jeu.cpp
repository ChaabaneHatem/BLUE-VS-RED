/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jeu.cpp
 * Author: hatem
 * 
 * Created on December 13, 2017, 11:54 PM
 */

#include <stddef.h>
#include <iostream>

#include "Jeu.h"


Jeu::Jeu() {
}

Jeu::~Jeu() {
}

void Jeu::initialiser() {
    SDL_Init(SDL_INIT_EVERYTHING);		// prepare SDL
    
    
    
    m = Map::ChargerMap("text/levelfinal.txt");
    
    wS = m->nbTilesLargueurMonde*m->larguerTile;
    hS = m->nbTilesLongueurMonde*m->longueurTile;
    
    
    SDL_CreateWindowAndRenderer(m->largeur_fenetre+200, m->hauteur_fenetre, 32, &win, &render);
    
    SDL_SetRenderDrawColor(render, 85, 180, 255, 255);
    
    
    sprite = new Sprite();
    imageSprite = Sprite::LoadSprite(sprite);
    
    
    
    imageBackround = SDL_CreateRGBSurface(0, m->largeur_fenetre, m->hauteur_fenetre, 32, 0x00000000, 0x00000000, 0x00000000, 0x00000000);
    
    SDL_SetRenderDrawColor(render, 85, 180, 255, 255);
    
    
    
    
}


void Jeu::executer() {
    SDL_Rect mur;
    SDL_Surface* surfaceMur = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
    mur.x = 200;
    mur.y = 200;
    mur.w = 200;
    mur.h = 200;
    SDL_FillRect(surfaceMur, &mur, 0x800000);
    SDL_Texture* texturemur = SDL_CreateTextureFromSurface(render, surfaceMur);
    int augmenter = 1;
    while (isRunning) {
        
        SDL_PollEvent(&event);
        state = SDL_GetKeyboardState(NULL);
        SDL_Texture* textureSprite;
        
        
        //create textute de sprite
        
        
        if(imageSprite) {
            textureSprite = SDL_CreateTextureFromSurface(render, imageSprite);
        } else {
            std::cout << "image sprite  not loaded";
        }
        
        
        if (event.type == SDL_QUIT)
            isRunning = false;
        
        
        if (state[SDL_SCANCODE_ESCAPE])
            isRunning = false;
        
        
        if (state[SDL_SCANCODE_LEFT])
            m->xscroll-=6;
        
        if (state[SDL_SCANCODE_RIGHT])
            m->xscroll+=6;
        
        if (state[SDL_SCANCODE_UP])
            m->yscroll-=0;
        
        if (state[SDL_SCANCODE_DOWN])
            m->yscroll+=0;
        
        
        
        
        Map::AfficherMap(m,imageBackround);
        
        if (imageBackround)
            imageFinalBackround = SDL_CreateTextureFromSurface(render, imageBackround);
        
        
        SDL_RenderClear(render);
        
        
        
        
        //affichage de tous le map dans le render
        SDL_Rect rect_dest = {0, 0, wS, hS};
        SDL_Rect rect_src = {0, 0, wS/5, hS};
        if (imageFinalBackround)
            SDL_RenderCopy(render, imageFinalBackround, NULL, NULL);
        
        
        //Top left corner viewport
        //        SDL_Rect topLeftViewport;
        //        topLeftViewport.x = 0;
        //        topLeftViewport.y = 0;
        //        topLeftViewport.w = m->largeur_fenetre;
        //        topLeftViewport.h = m->hauteur_fenetre*2 ;
        //        SDL_RenderSetViewport( render, &topLeftViewport );
        
        //Render texture to screen
        //SDL_RenderCopy( render, imageFinalBackround, NULL, NULL );
        
        //Top right viewport
        //        SDL_Rect topRightViewport;
        //        topRightViewport.x =  m->largeur_fenetre + 10;
        //        topRightViewport.y = 0;
        //        topRightViewport.w = m->largeur_fenetre;
        //        topRightViewport.h = m->hauteur_fenetre*2;
        //        SDL_RenderSetViewport( render, &topRightViewport );
        
        //Render texture to screen
        //SDL_RenderCopy( render, imageFinalBackround, NULL, NULL );
        
        
        
        
        //les testes des collisions
        if( (m->xscroll > -50) && (m->xscroll <=313)) {
            mur.x = -m->xscroll - 20;
            mur.y = m->yscroll + 448;
            mur.w = 313;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        
        if( (m->xscroll > 314) && (m->xscroll <=1091)) {
            while(augmenter == 1) {
                m->yscroll += 200;
                augmenter++;
            }
            mur.x = -m->xscroll ;
            mur.y = m->yscroll + 368;
            mur.w = 1131;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 1091) && (m->xscroll <=1130)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 336;
            mur.w = m->xscroll+40+50;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 1131) && (m->xscroll <=1170)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 297;
            mur.w = m->xscroll+40+50;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            ///SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 1171) && (m->xscroll <=1210)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 265;
            mur.w = m->xscroll+40+50;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 1211) && (m->xscroll <=1249)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 233;
            mur.w = m->xscroll+40+50;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 1250) && (m->xscroll <=1522)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 265;
            mur.w = 1522;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 1522) && (m->xscroll <=2925)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 368;
            mur.w = 2925;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 2926) && (m->xscroll <=3510)) {
            while (augmenter == 2) {
                m->yscroll -= 200;
                augmenter++;
            }
            
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 416;
            mur.w = 3510;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 3511) && (m->xscroll <=4600)) {
            mur.x = 30 + -m->xscroll;
            mur.y = m->yscroll + 288;
            mur.w = 4600;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        if( (m->xscroll > 4600) && (m->xscroll <=7800)) {
            while(augmenter == 3) {
                m->yscroll += 200;
                augmenter++;
            }
            mur.x = 30 + -m->xscroll ;
            mur.y = m->yscroll + 368;
            mur.w = 7800;
            mur.h = 32;
            Sprite::EvolueSprite(state, &mur , sprite);
            SDL_Rect srcr = sprite->positionFrameCourant;
            SDL_Rect destrSprite = sprite->positionSprite;
            SDL_RenderCopy(render, textureSprite, &srcr, &destrSprite);
            //SDL_RenderCopy(render, texturemur, NULL, &mur);
        }
        
        
        
        SDL_RenderPresent(render);
        
        if (imageFinalBackround)
            SDL_DestroyTexture(imageFinalBackround);
        if(textureSprite) {
            SDL_DestroyTexture(textureSprite);
        }
        
        
    }
    
    
}

void Jeu::libererMemoire() {
    SDL_FreeSurface(imageBackround);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    Map::LibererMap(m); 
    Sprite::freeSprite(sprite);
    SDL_Quit();
}

