#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "windows.h"
#include "../API/CPoint3f.h"
#include "vecteur.h"
#include <vector>
#include <ctgmath>
#include "../utilitaires.h"

using namespace std;

/**
* D�fintion de la classe Triangle :
* Elle poss�de :
* - Trois constructeurs ( � partir de Point3D, � partir de vecteur et par copie)
* - Une m�thode toString() pour afficher les sommets composants le triangles sous forme textuelle
* - Quatres variables : a, b ,c les sommets du triangle et texture sa texture
**/

class Triangle {
    public:
        // Constro / destro :
        Triangle(CPoint3f _a, CPoint3f _b, CPoint3f _c, GLuint *_texture);
        Triangle(Vecteur _a, Vecteur _b, Vecteur _c, GLuint *_texture);
        virtual ~Triangle();

        // Methodes :
        string toString();

        // Variables :
        CPoint3f a, b, c;
        GLuint *texture;

    protected:
    private:
};

#endif // TRIANGLE_H
