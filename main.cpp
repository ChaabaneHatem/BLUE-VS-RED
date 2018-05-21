/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hatem
 *
 * Created on December 2, 2017, 8:09 PM
 */

#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

#include "Map.h"
#include "Sprite.h"
#include "Jeu.h"


using namespace std;



/*
 * 
 */
int main(int argc, char** argv) {
    
    Jeu* j = new Jeu();
    j->initialiser();
    j->executer();
    j->libererMemoire();
    return 0;
}

