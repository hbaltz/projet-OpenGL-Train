#ifndef TRAIN_H
#define TRAIN_H
#include <vector>
#include "../API/CDonneesGraphe.h"
#include "../API/CGraphe.h"
#include "../API/CSommet.h"
#include "wagon.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

/**
* D�fintion de la classe Wagon :
* Elle poss�de :
* - Cinq variables
* - Deux constructeurs
* - Trois m�thodes
**/

class Train
{
public:
    int IDT;                    // Identifiant du train
    int NBW;                    // Nombre de wagons
    float speed;                // Vitesse du train
    std::vector<Wagon> wagons;  // Wagons
    CGraphe *graphe;            // Graphe

public:
    Train(int _IDT, int NBW, float _speed, int _IDA, CGraphe *_graphe);
    Train(Train const& tr);
    void deplace();
    void drawTrain();
    void setSpeed(float _speed);
};

#endif // TRAIN_H
