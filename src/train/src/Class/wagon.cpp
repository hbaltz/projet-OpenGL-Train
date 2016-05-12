#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "../../include/graphic.h"
#include "../../Include/Class/wagon.h"
#include "../../Include/Class/vecteur.h"

using namespace std;

/*************************************
************ Variables : *************
*************************************/

int rand_ab(int a, int b) {
    return rand()%(b-a) + a;
}


/*************************************
************ Constructeurs : *********
*************************************/

Wagon::Wagon(int _IDW, int _IDA, CGraphe *_graphe, float _speed) {
    IDW = _IDW;
    IDA = _IDA;
    IDAS = -1;
    graphe = _graphe;

    IDSI = graphe->list_arc[IDA].id_sommet_ini;
    IDSF = graphe->list_arc[IDA].id_sommet_fin;
    IDPA = graphe->list_arc[IDA].list_point_annexe[0];
    D=0, Dmax=-1;
    if(IDW==0) D = 1;
    speed = _speed;

    estPremier = false;

    posIni = new Vecteur(graphe->list_sommet[IDSI].X,graphe->list_sommet[IDSI].Y,graphe->list_sommet[IDSI].Z);
    posVers = new Vecteur(0,0,0);

    changeTroncon();
}

/*************************************
************ Méthodes : **************
*************************************/

void Wagon::changeTroncon() {
    CArc arc = graphe->list_arc[IDA];
    Vecteur from,to;
    // Premier point de l'arc
    if (IDPA==arc.list_point_annexe[0]) {
        from = Vecteur(graphe->list_sommet[IDSI].X,graphe->list_sommet[IDSI].Y,graphe->list_sommet[IDSI].Z);
        to = Vecteur(graphe->list_point_annexe[IDPA].X,graphe->list_point_annexe[IDPA].Y,graphe->list_point_annexe[IDPA].Z);

        IDPA++;
    } else { // Dernier point annexe (changement d'arc)
        if (IDPA == arc.list_point_annexe.size()+arc.list_point_annexe[0]) {
            from = Vecteur(graphe->list_point_annexe[IDPA-1].X,graphe->list_point_annexe[IDPA-1].Y,graphe->list_point_annexe[IDPA-1].Z);
            to = Vecteur(graphe->list_sommet[IDSF].X,graphe->list_sommet[IDSF].Y,graphe->list_sommet[IDSF].Z);

            // Changement d'arc
            CSommet S = graphe->list_sommet[IDSF];
            if(IDW==0) {
                int nran = rand_ab(0,S.id_arc_sortant.size());
                IDAS = S.id_arc_sortant.at(nran);
            }
            IDA = IDAS;
            arc = graphe->list_arc[IDA];
            IDPA = arc.list_point_annexe[0];
            IDSI = arc.id_sommet_ini;
            IDSF = arc.id_sommet_fin;
        }  else {
            from = Vecteur(graphe->list_point_annexe[IDPA-1].X,graphe->list_point_annexe[IDPA-1].Y,graphe->list_point_annexe[IDPA-1].Z);
            to = Vecteur(graphe->list_point_annexe[IDPA].X,graphe->list_point_annexe[IDPA].Y,graphe->list_point_annexe[IDPA].Z);
            IDPA++;
        }
    }

    *posIni = from;
    *posVers = to;

    if (fmod(D,1) != 0) D = D - Dmax;
    Dmax = (from-to).norm();

    Vecteur delta = to-from;
    V = asin(delta.getZ()/delta.norm());
    H = 2*atan(delta.getX()/(delta.getY()+delta.norm()*cos(V)));
    V *= 180/M_PI;
    H *= 180/M_PI;
}

void Wagon::drawWagon() {
    // On s'est inspiré de l'hyperloop, on dessine donc des cylindres
    glPushMatrix();
    glColor3d(1, 1, 1);

    // On se place on milieu du wagon dans la direction du rail :
    glTranslatef(posIni->getX(), posIni->getY(), posIni->getZ());
    glRotatef(90-H, 0, 0, 1);
    glRotatef(-V, 0, 1, 0);
    glTranslatef(D, 0, 0.30);
    glRotated(90,0,1,0);

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);

    GLUquadricObj *wag;
    wag = gluNewQuadric();
    gluQuadricTexture(wag,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, wagon);
    gluCylinder(wag,0.15,0.15,0.9,100,100);
    gluDeleteQuadric(wag);

    dessinerPolygone(0.15, 12);

    glTranslatef(0, 0, 0.9);

    // Si c'est la locomotive on ajoute un cône à l'avant du cône
    if(estPremier){
        GLUquadricObj *avt;
        avt = gluNewQuadric();
        gluQuadricTexture(avt,GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, avt_wagon);
        gluCylinder(avt,0.15,0,0.4,100,100);
        gluDeleteQuadric(avt);
    }

    dessinerPolygone(0.15, 12);

    glPopMatrix();
}

void Wagon::deplace() {
    if (D > Dmax) {changeTroncon();}
    D += speed;
}

bool Wagon::dernierTroncon() {
    CArc arc = graphe->list_arc[IDA];
    if (IDPA==arc.list_point_annexe[0]) {return true;} else {return false;}
}

bool Wagon::premierTroncon() {
    CArc arc = graphe->list_arc[IDA];
    if (IDPA==arc.list_point_annexe[0]+1) {return true;} else {return false;}
}

bool Wagon::avDerniTroncon() {
    CArc arc = graphe->list_arc[IDA];
    if (IDPA==arc.list_point_annexe.size()+arc.list_point_annexe.at(0)) {return true;} else {return false;}
}

Vecteur Wagon::position(Vecteur ecart) {
    Vecteur pos(posIni->getX()*(1-D/Dmax)+D/Dmax*posVers->getX(), posIni->getY()*(1-D/Dmax)+D/Dmax*posVers->getY(), posIni->getZ()*(1-D/Dmax)+D/Dmax*posVers->getZ());
    return pos + ecart;
}

