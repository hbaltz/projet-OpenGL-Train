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
extern GLuint wagon, avt_wagon, herbe, neige, ciel, bois, feuille, pont, gravier, poutre_bois, eau, sol, text_lune, lampadaire;
extern GLuint avt_gare, der_gare, drt_gare, gce_gare, haut_gare, bas_gare;

#endif // GLOALES_H
