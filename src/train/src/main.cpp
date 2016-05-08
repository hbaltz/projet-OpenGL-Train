#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <SDL/SDL.h>
//#include "graphic.h"

#include "API/CDonneesGraphe.h"
#include "API/CGraphe.h"
#include "API/CSommet.h"
#include "Librairies/sdlglutils.h"
#include "Class/vecteur.h"
#include "Class/Triangle.h"
#include "Class/Triangulation.h"
#include "globales.h"

#define mSPF 30

using namespace std;

/**
* Déclaration des variables :
**/

// Déclaration des images :
GLuint herbe, neige, ciel, bois, feuille, pont, gravier, poutre_bois, cote_0, face_0, dessus_0, cote_1, face_1, dessus_1;

// Fonctions :
void genererTriangulation();

// Construction de la triangulation :
Triangulation triangulation;

/**
* Récupération du graphe :
**/

// Déclaration des tables du graphe
CDonneesGraphe gdata("data/SXYZ.TXT", "data/SIF.TXT", "data/PAXYZ.TXT", "data/AXYZ.TXT");
// Constrcuction de la base de donnees orientee objet du graphe
CGraphe graphe(gdata);

int main(int argc, char **argv) {
    genererTriangulation();

    /*------------------------------*/
   return 0;
}

void genererTriangulation() {
    triangulation.ajouterTriangle(Triangle(CPoint3f(10,14,0), CPoint3f(9.5,16,3), CPoint3f(7,16,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(10,18.8,3), CPoint3f(9.5,16,3), CPoint3f(7,16,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(10,18.8,3), CPoint3f(9,21,0), CPoint3f(7,16,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(10,18.8,3), CPoint3f(9,21,0), CPoint3f(11.5,19,3), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(12,21,0), CPoint3f(9,21,0), CPoint3f(11.5,19,3), &herbe));

    triangulation.ajouterTriangle(Triangle(CPoint3f(12,21,0), CPoint3f(13.5,18.8,3), CPoint3f(11.5,19,3), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(12,21,0), CPoint3f(13.5,18.8,3), CPoint3f(14,20,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(13.5,18.8,3), CPoint3f(14,20,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(17,16,0), CPoint3f(14,20,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(17,16,0), CPoint3f(16,14,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(18,14,0), CPoint3f(17,16,0), CPoint3f(16,14,2), &herbe));

    triangulation.ajouterTriangle(Triangle(CPoint3f(18,14,0), CPoint3f(18,12,2), CPoint3f(16,14,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(18,14,0), CPoint3f(18,12,2), CPoint3f(21,12,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(18,14,0), CPoint3f(21,15,0), CPoint3f(21,12,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(22,14,1), CPoint3f(21,15,0), CPoint3f(21,12,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(22,14,1), CPoint3f(21,15,0), CPoint3f(22.1,16,0), &herbe));

    triangulation.ajouterTriangle(Triangle(CPoint3f(22,14,1), CPoint3f(23,14,0), CPoint3f(22.1,16,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(22,14,1), CPoint3f(23,14,0), CPoint3f(22,11,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(22,14,1), CPoint3f(21,12,2), CPoint3f(22,11,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(18,12,2), CPoint3f(21,12,2), CPoint3f(22,11,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(18,12,2), CPoint3f(17,11,0), CPoint3f(22,11,0), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(18,12,2), CPoint3f(17,11,0), CPoint3f(16.1,14,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(15,12,0), CPoint3f(17,11,0), CPoint3f(16.1,14,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(15,12,0), CPoint3f(16.1,14,2), CPoint3f(13,14,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(15,12,0), CPoint3f(10,14,0), CPoint3f(13,14,2), &herbe));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(10,14,0), CPoint3f(13,14,2), &herbe));

    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(16.1,14,2), CPoint3f(13,14,2), &neige));
    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(13.5,18.8,3), CPoint3f(13,14,2), &neige));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(13.5,18.8,3), CPoint3f(13,14,2), &neige));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(13.5,18.8,3), CPoint3f(11.5,19,3), &neige));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(10,18.8,3), CPoint3f(11.5,19,3), &neige));
}


