#include "../../Include/Class/Triangle.h"

/**
* Constructeurs :
**/

// Constructeur à l'aide de points 3D :
Triangle::Triangle(CPoint3f _a, CPoint3f _b, CPoint3f _c,  GLuint *_texture) {
    a = _a;
    b = _b;
    c = _c;

    texture = _texture;
}

// Constructeur à l'aide de vecteurs  :
Triangle::Triangle(Vecteur _a, Vecteur _b, Vecteur _c,  GLuint *_texture) {
    a = CPoint3f(_a.getX(), _a.getY(), _a.getZ());
    b = CPoint3f(_b.getX(), _b.getY(), _b.getZ());
    c = CPoint3f(_c.getX(), _c.getY(), _c.getZ());

    texture = _texture;
}

// Constructeur par copie :
Triangle::~Triangle() {
    //dtor
}

/**
* Méthodes :
**/

// Fonction qui sert à afficher les sommets composants le triangles sous forme textuelle
string Triangle::toString() {
    return "Triangle [(" + a.toString() + "), (" + b.toString() + "), (" + c.toString() + ")]";
}
