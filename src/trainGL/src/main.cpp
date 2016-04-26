#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

#include "../include/API/CDonneesGraphe.h"
#include "../include/API/CGraphe.h"

#define mSPF 30

using namespace std;

// Récupération des donnees du graphe :
CDonneesGraphe gdata("data/SXYZ.TXT", "data/SIF.TXT", "data/PAXYZ.TXT", "data/AXYZ.TXT");
// Constrcuction de la base de donnees orientee objet du graphe :
CGraphe graphe(gdata);

int main(int argc, char *argv[]) {
    return 0;
}
