#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "API/CDonneesGraphe.h"
#include "API/CGraphe.h"
#include "API/CSommet.h"
#include "Librairies/sdlglutils.h"
#include "Class/wagon.h"
#include "Class/train.h"
#include "Class/vecteur.h"
#include "Class/Camera.h"
#define mSPF 30

std::string float2str(float n);
bool isLeft(CPoint3f p1, CPoint3f p2, CPoint3f newp);
