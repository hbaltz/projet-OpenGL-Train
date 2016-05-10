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
extern GLuint herbe, neige, ciel, bois, feuille, pont, gravier, poutre_bois, cote_0, face_0, dessus_0, cote_1, face_1, dessus_1;

#endif // GLOALES_H
