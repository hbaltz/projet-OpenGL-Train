#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include "train.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

class Collection {
public:
    vector<Train> listeTrain;       // liste des trains
    vector<int>   liTarr;           // liste des trains arrêtés
    vector<float> liVarr;           // liste des vitessses des trains arrêtés
    vector<int>   liTral;           // liste des trains ralentis
    vector<float> liVral;           // liste des vitesses initiales des trains ralentis

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
