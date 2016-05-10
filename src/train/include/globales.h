#ifndef GLOALES_H
#define GLOALES_H

#include "Class/Triangulation.h"

// Listes de toutes les varialbes globales utilis�es dans le projet :


extern Camera *cam; // La cam�ra est globale
extern Collection *collection; // La collection est globale

// Les donnees du graph sont globales :
extern CDonneesGraphe gdata;
extern CGraphe graphe;
extern Triangulation triangulation;

// Les images du graph sont globales :
extern GLuint wagon, herbe, neige, ciel, bois, feuille, pont, gravier, poutre_bois;

#endif // GLOALES_H
