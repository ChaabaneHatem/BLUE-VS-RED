/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Map.cpp
 * Author: hatem
 * 
 * Created on December 3, 2017, 1:18 PM
 */

#include <iostream>
#include <stdlib.h>

#include "Map.h"
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#define CACHE_SIZE 5000


Map::Map() {
}


SDL_Surface* LoadTileSet(const char* fichier_image)
{
    SDL_Surface* image_result;
    image_result = IMG_Load(fichier_image);	// charge l'image dans image_ram en RAM
    if (image_result== NULL)
    {
        printf("Image %s introuvable !! \n",fichier_image);
        SDL_Quit();
        system("pause");
        exit(-1);
    }
    return image_result;
}

void ChargerMap_tileset(FILE* F,Map* m)
{
    int numtile,i,j;
    char buf[CACHE_SIZE];  // un buffer, petite mémoire cache
    char buf2[CACHE_SIZE];  // un buffer, petite mémoire cache
    fscanf(F,"%s",buf); // nom du fichier
    m->tileSet = LoadTileSet(buf);
    fscanf(F,"%d %d",&m->nbTilesX,&m->nbTilesY);
    m->larguerTile = m->tileSet->w/m->nbTilesX;
    m->longueurTile = m->tileSet->h/m->nbTilesY;
    //m->tilesProps = malloc(m->nbTilesX*m->nbTilesY*sizeof(TileProp));
    m->tilesProps = new TileProp[m->nbTilesX*m->nbTilesY*sizeof(TileProp)];
    //printf("le size de tile prop est : %d ", sizeof(m->tilesProps));
    for(j=0,numtile=0;j<m->nbTilesY;j++)
    {
        for(i=0;i<m->nbTilesX;i++,numtile++)
        {
            //printf("le numero de tile :  %d  ", numtile);
            m->tilesProps[numtile].tilePosition.w = m->larguerTile;
            m->tilesProps[numtile].tilePosition.h = m->longueurTile;
            m->tilesProps[numtile].tilePosition.x = i*m->larguerTile;
            m->tilesProps[numtile].tilePosition.y = j*m->longueurTile;
            fscanf(F,"%s %s",buf,buf2);
            m->tilesProps[numtile].danger = 0;
            if (strcmp(buf2,"danger")==0)
                m->tilesProps[numtile].danger = 1;
        }
    }
}

void ErrorQuit(const char* error)
{
    puts(error);
    SDL_Quit();
    system("pause");
    exit(-1);
}

void ChargerMap_level(FILE* F,Map* m)
{
    int i,j;
    fscanf(F,"%d %d",&m->nbTilesLargueurMonde,&m->nbTilesLongueurMonde);
    //m->schemaLevel = malloc(m->nbTilesLargueurMonde*sizeof(m->tileIndex*));
    m->schemaLevel = new char*[m->nbTilesLargueurMonde*(sizeof(char*))];
    //printf("le size de schema est : %d ", sizeof(m->schemaLevel));
    for(i=0;i<m->nbTilesLargueurMonde;i++)
        //m->schemaLevel[i] = malloc(m->nbTilesLongueurMonde*sizeof(m->tileIndex));
        m->schemaLevel[i] = new char[m->nbTilesLongueurMonde*sizeof(char)];
        //printf("le size de schema[i] est : %d ", sizeof(m->schemaLevel[i]));
        for(j=0;j<m->nbTilesLongueurMonde;j++)
        {
            //printf("\n");
            for(i=0;i<m->nbTilesLargueurMonde;i++)
            {
                int tmp;
                fscanf(F,"%d",&tmp);
                if (tmp>=m->nbTilesX*m->nbTilesY)
                    ErrorQuit("level tile hors limite\n");
                //printf("%d", tmp);
                m->schemaLevel[i][j] = tmp;
                
                //printf("%d", m->schemaLevel[i][j]);
            }
        }
}


Map* Map::ChargerMap(const char* level)
{
    FILE* F;
    Map* m;
    char buf[CACHE_SIZE];
    F = fopen(level,"r");
    if (!F)
        ErrorQuit("fichier level introuvale\n");
    fgets(buf,CACHE_SIZE,F);
    if (strstr(buf,"Tilemapping Version 1.0") == NULL)
        ErrorQuit("Mauvaise version du fichier level. Ce programme attend la version 1.0\n");
    //m = malloc(sizeof(Map));
    m = new Map[sizeof(Map)];
    do 
    {
        fgets(buf,CACHE_SIZE,F);
        if (strstr(buf,"#tileset"))
            ChargerMap_tileset(F,m);
        if (strstr(buf,"#level"))
            ChargerMap_level(F,m);
    } while (strstr(buf,"#fin") == NULL);
    m->xscroll = 0;
    m->yscroll = 0;
    
    m->largeur_fenetre = 800;
    m->hauteur_fenetre = 700;
    
    fclose(F);
    return m;
}

int Map::AfficherMap(Map* m,SDL_Surface* surfaceJeuBackround)
{
    int i,j;
    SDL_Rect Rect_dest;
    int numero_tile;
    int minx,maxx,miny,maxy;
    minx = m->xscroll / m->larguerTile - 1;
    miny = m->yscroll / m->longueurTile - 1;
    maxx = (m->xscroll + m->largeur_fenetre)/m->larguerTile + 1;
    maxy = (m->yscroll + m->hauteur_fenetre)/m->longueurTile +1 ;
    //printf("minx et miny %d %d" , minx, miny);
    //printf("maxx et maxy %d %d" , maxx, maxy);
    
    
    //printf("affichage de map : \n");
    for(i=miny;i<maxy;i++)
    {
        //printf("\n");
        
        for(j=minx;j<=maxx;j++)
        {
            Rect_dest.x = j*m->larguerTile - m->xscroll;
            Rect_dest.y = i*m->longueurTile - m->yscroll;
            
            
            Rect_dest.w = m->larguerTile;
            Rect_dest.h = m->longueurTile;
            
            
            if (i<0 || i>=m->nbTilesLongueurMonde || j<0 || j>=m->nbTilesLargueurMonde)
                numero_tile = 54;
            else            
                numero_tile = m->schemaLevel[j][i];
            
            //printf("%d", numero_tile);
            SDL_BlitSurface(m->tileSet,&(m->tilesProps[numero_tile].tilePosition),surfaceJeuBackround,&Rect_dest);
        }
    }
    return 0;
}

int Map::LibererMap(Map* m)
{
    int i;
    SDL_FreeSurface(m->tileSet);
    for(i=0;i<m->nbTilesLongueurMonde;i++)
        delete(m->schemaLevel[i]);
    delete(m->schemaLevel);
    delete(m->tilesProps);
    delete(m);
    return 0;
}



SDL_Rect Map::CollisionTile(Sprite* sprite, Map* map) {
    SDL_Rect tileDangerPosition;
    int xmin,xmax,ymin,ymax,i,j,titleaTester;
    //        if ((sprite->x) <0 || (sprite-> x + sprite->width -1)>=map->nbTilesLargueurMonde*map->larguerTile 
    //                || sprite->y<0 || (sprite->y + sprite->height -1)>=map->nbTilesLongueurMonde*map->longueurTile)
    //            return 1;
    xmin = sprite->x / map->larguerTile;
    ymin = sprite->y / map->longueurTile;
    xmax = (sprite->x + 50 -1) / map->larguerTile;
    ymax = (sprite->y + 75 -1) / map->longueurTile;
    for(i=xmin;i<=xmax;i++)
    {
        for(j=ymin;j<=ymax;j++)
        {
            titleaTester = map->schemaLevel[i][j];
            if (map->tilesProps[titleaTester].danger) {
                tileDangerPosition.x = i*map->larguerTile;
                tileDangerPosition.y = j*map->longueurTile;
                tileDangerPosition.w = map->larguerTile;
                tileDangerPosition.h = map->longueurTile;
                return tileDangerPosition;
            }
        }
    }
    return tileDangerPosition;
}

