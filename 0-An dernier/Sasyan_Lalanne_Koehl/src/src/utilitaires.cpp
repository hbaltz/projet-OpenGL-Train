#include "utilitaires.h"

std::string float2str(float n) {
    std::ostringstream ss;
    ss << n;
    std::string s(ss.str());
    return s;
}


bool isLeft(CPoint3f p1, CPoint3f p2, CPoint3f newp) {
// Teste si point newp est : à Gauche|Sur| à Droite de la droite (p1p2).
// Result: >0 si newp est à gauche de la droite P1-P2
//           =0 si le point est surla droite
//          <0 ... droite
// NB : surface du triangle = Isleft / 2 .

  return ((p2.X - p1.X) * (newp.Y - p1.Y) - (newp.X - p1.X) * (p2.Y - p1.Y) <= 0);
}
