#ifndef WAGON_H
#define WAGON_H
#include "../API/CDonneesGraphe.h"
#include "../API/CGraphe.h"
#include "../API/CSommet.h"
#include "vecteur.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/**
* Défintion de la classe Wagon :
* Elle possède :
* - Onze variables
* - Un constructeur
* - Huit méthodes
**/

class Wagon {
    public:
        int IDW;            // Id du wagon
        int IDA,IDPA;       // Id de l'arc et celui du prochain point annexe
        int IDAS;           // Id de l'arc suivant
        int IDSI,IDSF;      // Id du SI et du SF
        float H,V;          // Orientation
        float speed;        // Vitesse
        float D,Dmax;       // Distance aux prochain point annexe
        Vecteur *posIni;    // Position du premier point du troncon
        Vecteur *posVers;   // Position du premier point du troncon
        int color;          // Couleur du wagon : 0 bleu, 1 rouge
        CGraphe *graphe;

    public:
        Wagon(int _IDW, int _IDA, CGraphe *_graphe, float _speed, int color);
        void changeTroncon();
        void drawWagon();
        void deplace();
        bool dernierTroncon();
        bool premierTroncon();
        bool avDerniTroncon();
        Vecteur position(Vecteur ecart);
};

#endif // WAGON_H
