#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include "train.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

/**
* Défintion de la classe Collection :
* Elle possède :
* - Cinq variables
* - Un constructeur
* - Quatorze méthodes
**/

class Collection {
public:
    vector<Train> listeTrain;       // Liste des trains
    vector<int>   liTarr;           // Liste des trains arrêtés
    vector<float> liVarr;           // Liste des vitessses des trains arrêtés
    vector<int>   liTral;           // Liste des trains ralentis
    vector<float> liVral;           // Liste des vitesses initiales des trains ralentis

public:
    Collection();
    void addTrain(Train _train);

    void stopTrain(int IDT);
    void raleTrain(int IDT, float _speed);
    void demarreTrain(int IDT);
    void accelerTrain(int IDT);

    void ralentir();
    void arreter();

    void accelerer();
    void demarrer();

    void drawTrains();
    void deplaceTrains();

    bool testSommet(int _IDT);      // vrai si le sommet est libre et faux sinon
    int testTroncon(int _IDT);      // renvoie l'id du train devant et -1 si pas de train
    int testArc(int _IDT);          // renvoie l'id du train sur l'autre arc et -1 si pas de train
};

#endif // COLLECTION_H
