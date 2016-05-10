#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include "graphic.h"

#include "API/CDonneesGraphe.h"
#include "API/CGraphe.h"
#include "API/CSommet.h"
#include "Librairies/sdlglutils.h"
#include "Class/Camera.h"
#include "Class/vecteur.h"
#include "Class/Triangle.h"
#include "Class/Triangulation.h"
#include "Class/wagon.h"
#include "Class/train.h"
#include "Class/Collection.h"
#include "utilitaires.h"
#include "globales.h"

#define mSPF 30

using namespace std;

/*************************************************
************ Déclaration des variables : *********
*************************************************/

// Déclaration des images pour les textures :
GLuint wagon, herbe, neige, ciel, bois, feuille, pont, gravier, poutre_bois, eau, sol, text_lune, lampadaire;

// Caméra :
Camera *cam;
// Collection :
Collection *collection;
// Triangulation :
Triangulation triangulation;

// Fonctions :
void rotate(int value);
void Init();
void genererTriangulation();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keybord(unsigned char key, int x, int y);
void Reshape(int width, int height);

/*************************************************
************ Récupération du graphe : ************
*************************************************/

// Déclaration des tables du graphe
CDonneesGraphe gdata("data/SXYZ.TXT", "data/SIF.TXT", "data/PAXYZ.TXT", "data/AXYZ.TXT");
// Constrcuction de la base de donnees orientee objet du graphe
CGraphe graphe(gdata);

/*************************************************
************ Activité main: **********************
*************************************************/

int main(int argc, char **argv) {
    //Intitilisation :
    glutInit(&argc, argv);
    Init();

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // Chargement des textures
    chargerTextures(); // Fonction dans graphic.cpp

    // Création de la caméra :
    cam = new Camera(0,0,10,20,24,0);

    // Création de la collection et ajout des trains
    collection = new Collection;
    collection->addTrain(Train(0, 5, 0.15, 0, &graphe, 0)); cam->nb_train++;
    collection->addTrain(Train(1, 4, 0.05, 2, &graphe, 0)); cam->nb_train++;
    collection->addTrain(Train(2, 3, 0.075, 4, &graphe, 1)); cam->nb_train++;

    // On effectue la triangulation : (hors points du pont)
    //triangulation.ajouterTriangle(Triangle(CPoint3f(), CPoint3f(), CPoint3f()));
    //triangulation = listeTriangles(CPoint3f(-10,-10,0), CPoint3f(40,-10,0), CPoint3f(-10,40,0), CPoint3f(40,40,0));
    genererTriangulation();

    // Gestion des mouvement à l'aide de la souris et du clavier
    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutKeyboardFunc(Keybord);
    glutReshapeFunc(Reshape);

    // On dessine :
    glutTimerFunc(mSPF,rotate,0);
    glutDisplayFunc(dessiner);

    glutMainLoop();

    /*------------------------------*/
   return 0;
}

/*************************************************
************ Fonctions : *************************
*************************************************/

void rotate(int value) {
    collection->deplaceTrains();
    glutPostRedisplay();
    glutTimerFunc(mSPF,rotate,value);
}

// Fonction qui sert à intitialiser notre projet
void Init(){
    glutInitWindowSize(1920,1080);
    glutCreateWindow("Projet OpenGL");
    glClearColor(0.6,0.6,0.6,0.0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glPointSize(4);
    glLineWidth(2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1.0,0.1,1000);

    //glutFullScreen(); // Pour le pleine écran
}

void Reshape(int width, int height)
{
  	float ratio = (float)width/(float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
}

void Mouse(int button, int state, int x, int y) {
    cam->Mouse(button, state, x, y);
}

void Motion(int x, int y) {
    cam->Motion(x,y);
}

void Keybord(unsigned char key, int x, int y) {
    cam->Keybord(key, x , y);
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

    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(16.1,14,2), CPoint3f(13,14,2), &eau));
    triangulation.ajouterTriangle(Triangle(CPoint3f(16,16,2), CPoint3f(13.5,18.8,3), CPoint3f(13,14,2), &eau));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(13.5,18.8,3), CPoint3f(13,14,2), &eau));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(13.5,18.8,3), CPoint3f(11.5,19,3), &eau));
    triangulation.ajouterTriangle(Triangle(CPoint3f(9.5,16,3), CPoint3f(10,18.8,3), CPoint3f(11.5,19,3), &eau));
}


