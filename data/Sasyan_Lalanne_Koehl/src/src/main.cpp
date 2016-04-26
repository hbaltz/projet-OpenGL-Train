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

// Déclaration des images :
GLuint herbe, neige, ciel, bois, feuille, pont, gravier, poutre_bois, cote_0, face_0, dessus_0, cote_1, face_1, dessus_1;

// Déclaration de la caméra
Camera *cam;
Collection *collection;

// Déclaration des tables du graphe
CDonneesGraphe gdata("data/SXYZ.TXT", "data/SIF.TXT", "data/PAXYZ.TXT", "data/AXYZ.TXT");
// Constrcuction de la base de donnees orientee objet du graphe
CGraphe graphe(gdata);
// Construction de la triangulation :
Triangulation triangulation;

// fonctions
void Initialiser();
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void Keybord(unsigned char key, int x, int y);
void Resize(int width, int height);
void genererTriangulation();

void rotate(int value) {
    collection->deplaceTrains();
    glutPostRedisplay();
    glutTimerFunc(mSPF,rotate,value);
}

int main(int argc, char *argv[]) {
    /*---------------------------------------------*/
    glutInit(&argc, argv);
    Initialiser();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    chargerTextures();

    cam = new Camera(0,0,10,20,24,0);

    collection = new Collection;
    collection->addTrain(Train(0, 5, 0.15, 0, &graphe, 0)); cam->nb_train++;
    collection->addTrain(Train(1, 4, 0.05, 2, &graphe, 0)); cam->nb_train++;
    collection->addTrain(Train(2, 3, 0.075, 4, &graphe, 1)); cam->nb_train++;

    // On effectue la triangulation : (hors points du pont)
    //triangulation.ajouterTriangle(Triangle(CPoint3f(), CPoint3f(), CPoint3f()));
    //triangulation = listeTriangles(CPoint3f(-10,-10,0), CPoint3f(40,-10,0), CPoint3f(-10,40,0), CPoint3f(40,40,0));
    genererTriangulation();

    glutMouseFunc(Mouse);
    glutMotionFunc(Motion);
    glutKeyboardFunc(Keybord);
    glutReshapeFunc(Resize);

    glutTimerFunc(mSPF,rotate,0);
    glutDisplayFunc(dessiner);
    glutMainLoop();
    /*---------------------------------------------*/
    return EXIT_SUCCESS;
}

void Initialiser() {
    glutInitWindowSize(1920,1080);
    glutCreateWindow("Projet OpenGL - SASYAN Valentin, LALANNE Mayeul, KOEHL Guillaume");
    glClearColor(0.6,0.6,0.6,0.0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH) ;
    glPointSize(4);
    glLineWidth(2);
    glutFullScreen();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1.0,0.1,1000);
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

void Resize(int width, int height) {
    float ratio = (float)width/(float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
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
