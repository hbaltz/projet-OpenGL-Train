#ifndef WAGON_H
#define WAGON_H
#include "../API/CDonneesGraphe.h"
#include "../API/CGraphe.h"
#include "../API/CSommet.h"
#include "vecteur.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Wagon {
    public:
        int IDW;            // id du wagon
        int IDA,IDPA;       // id de l'arc et celui du prochain point annexe
        int IDAS;           // id de l'arc suivant
        int IDSI,IDSF;      // id du SI et du SF
        float H,V;          // orientation
        float speed;        // vitesse
        float D,Dmax;       // distance aux prochain point annexe
        Vecteur *posIni;    // position du premier point du troncon
        Vecteur *posVers;    // position du premier point du troncon
        int color;          // couleur du wagon : 0 bleu, 1 rouge
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
