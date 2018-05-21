/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.h
 * Author: hatem
 *
 * Created on December 3, 2017, 1:18 PM
 */

#ifndef MAP_H
#define MAP_H
#include "TileProp.h"
#include "Sprite.h"

class Map {
    
    
    
public:
    
    int larguerTile, longueurTile;
    int nbTilesX, nbTilesY;
    TileProp* tilesProps;
    int nbTilesLargueurMonde, nbTilesLongueurMonde;
    SDL_Surface* tileSet;
    char** schemaLevel;
    unsigned char tileIndex;
    
    //scrolling pour une fenetre precis de largeur_fenetre et y 
    int xscroll,yscroll;
    int largeur_fenetre,hauteur_fenetre;
    
    
    
    
    Map();
    
    
    static Map* ChargerMap(const char* fic);
    static int AfficherMap(Map* m,SDL_Surface* screen);
    static int LibererMap(Map* m);
    static SDL_Rect CollisionTile(Sprite* sprite, Map* map);
    
    
    
    
};

#endif /* MAP_H */

