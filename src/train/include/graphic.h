#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "API/CDonneesGraphe.h"
#include "API/CGraphe.h"
#include "API/CSommet.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include "windows.h"

#include "Librairies/sdlglutils.h"
#include "Class/wagon.h"
#include "Class/train.h"
#include "Class/Collection.h"
#include "Class/Camera.h"
#include "Class/vecteur.h"
#include "globales.h"
#ifndef M_PI
  #define M_PI 3.1415926535
#endif

void chargerTextures();
void dessiner();

// Sous-fonctions :

void dessinerCiel();
void dessinerTrains();
void dessinerVoies();
void dessinerArbres();
void dessinerLampadaires();
void dessinerPont();
void dessinerTerrain();
void dessinerTunDon();
void dessinerLune();
void dessinerGares();

// Fonctions élémentaires :

void dessinerArbre(float x, float y, float z, float hauteur);
void dessinerLampadaire(float x, float y, float z, float hauteur);
void dessinerGare(float x, float y, float z, float t1, float t2, float h);
void dessinerSapin(float x, float y, float z, float h1, float h2, float l);
void dessinerRail(Vecteur debut, Vecteur fin);
void dessinerPoteau(float V, float r,  float h, GLint s);
void dessinerDonnut(float x, float y, float z);
void dessinerTexture(GLuint texture, Vecteur a, Vecteur b, Vecteur c, Vecteur d);
void dessinerTexture(Vecteur a, Vecteur b, Vecteur c, Vecteur d);
void dessinerTextureSansDeformation(Vecteur a, Vecteur b, Vecteur c, Vecteur d);
void dessinerRectangle(Vecteur a1, Vecteur b1, Vecteur c1, Vecteur d1, Vecteur a2, Vecteur b2, Vecteur c2, Vecteur d2);
void dessinerPave(Vecteur a1, Vecteur b1, Vecteur c1, Vecteur d1, Vecteur a2, Vecteur b2, Vecteur c2, Vecteur d2);
void dessinerPolygone(double ray, double smooth);
