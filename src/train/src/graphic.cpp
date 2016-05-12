#include "graphic.h"


/*************************************************
************ Fonctions principales : *************
*************************************************/

// Fonction qui va cherger les différentes textures utiles pour le projet :
void chargerTextures() {
    wagon = loadTexture("textures/wagon.jpg");
    avt_wagon = loadTexture("textures/avt_wagon.jpg");
    herbe = loadTexture("textures/grass.jpg");
    neige = loadTexture("textures/snow.jpg");
    ciel  = loadTexture("textures/ciel.jpg");
    bois  = loadTexture("textures/bois.jpg");
    feuille = loadTexture("textures/feuille.jpg");
    pont = loadTexture("textures/pont.jpg");
    gravier = loadTexture("textures/gravier.jpg");
    poutre_bois = loadTexture("textures/poutre_bois.jpg");
    eau = loadTexture("textures/eau.jpg");
    sol = loadTexture("textures/sol.jpg");
    text_lune = loadTexture("textures/lune.jpg");
    lampadaire = loadTexture("textures/lampadaire.jpg");

    // Texture gare :
    avt_gare = loadTexture("textures/lampadaire.jpg");
    der_gare = loadTexture("textures/lampadaire.jpg");
    drt_gare = loadTexture("textures/lampadaire.jpg");
    gce_gare = loadTexture("textures/lampadaire.jpg");
    haut_gare = loadTexture("textures/lampadaire.jpg");
    bas_gare = loadTexture("textures/lampadaire.jpg");
}

// Fonction principale qui va dessiner l'ensemble de notre projet :
void dessiner() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // On positionne la caméra :
    Vecteur ecart(0,0,1);
    if (cam->vue != -1) {
        cam->changerPosition(collection->listeTrain[cam->vue].wagons[1].position(ecart), collection->listeTrain[cam->vue].wagons[0].position(ecart));
    }
    cam->Look();


    // Gestion lumière :
    glEnable (GL_LIGHTING);

    GLfloat global_ambient[] = { 0.1f, 1.0f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glDisable (GL_LIGHTING);

    // Rails :
    dessinerVoies();

    // Arbres :
    dessinerArbres();

    // Ciel :
    dessinerCiel();

    // Trains :
    dessinerTrains();

    // Herbe :
    dessinerTerrain();

    // Tunel-Donnut :
    dessinerTunDon();

    // Lune :
    dessinerLune();

    // Lampadaires :
    dessinerLampadaires();

    // Gares :
    dessinerGares();

    // Pont :
    glColor3f(1,1,1);
    dessinerPont();

    glFlush();
    glutSwapBuffers();
}

/*************************************************
************ Sous-fonctions : ********************
*************************************************/

// Fonction qui dessine les voies
void dessinerVoies() {
    glColor3f(1,1,1);
    Vecteur debut, fin;

    // On parcourt tous les arcs et on les dessine un par un
    for (int i=0; i<graphe.nb_arc; i++) {
        CArc arc = graphe.list_arc[i];
        int i_SI = arc.id_sommet_ini;
        int i_SF = arc.id_sommet_fin;
        int NPA = arc.list_point_annexe.size();

        // Dessin de la sphère pour le sommet de l'arc :
        glPushMatrix();
        glTranslatef(graphe.list_sommet[i_SI].X,graphe.list_sommet[i_SI].Y,graphe.list_sommet[i_SI].Z);
        glColor3f(0.8,0.8,0.8);
        glutSolidSphere(0.25,50,50);
        glPopMatrix();

        // Sommet initial :
        debut = Vecteur(graphe.list_sommet[i_SI].X, graphe.list_sommet[i_SI].Y, graphe.list_sommet[i_SI].Z);;

        // Points annexes :
        for(int j=0; j<NPA; j++) {
            int iPA = arc.list_point_annexe.at(j);
            fin = Vecteur(graphe.list_point_annexe[iPA].X, graphe.list_point_annexe[iPA].Y, graphe.list_point_annexe[iPA].Z);
            dessinerRail(debut, fin);
            debut = fin;
        }

        // Sommet final :
        fin = Vecteur(graphe.list_sommet[i_SF].X, graphe.list_sommet[i_SF].Y, graphe.list_sommet[i_SF].Z);
        dessinerRail(debut, fin);
    }
}

// Fonction qui dessine l'ensemble des arbres
void dessinerArbres() {
    glColor3f(0.1,1,0.1);

    //dessinerArbre(-1,5,0,2.2);
    dessinerArbre(4,3,0,2.4);
    dessinerArbre(8,14,0,1.9);
    dessinerArbre(-1,14,0,2.2);
    dessinerArbre(0,12,0,2.1);
    dessinerArbre(-2.5,13.8,0,2.3);
    dessinerArbre(2,11.7,0,2);
    dessinerArbre(15,-4,0,2.3);
    dessinerArbre(17,5,0,2.25);
    dessinerArbre(20,15,0,2.0);

    dessinerSapin(1,14,0,0.75,2.25,0.5);
    dessinerSapin(20,13.5,0,1.25,2,0.5);
    dessinerSapin(18,14.5,0,0.75,2.25,0.5);
}

// Fonction qui dessine le ciel
void dessinerCiel(){
    // Le ciel est une très grande sphère entourant notre scène
    // A laquelle on applique une texture

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(12.205,10.065,0.0);

    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D,ciel);
    gluSphere(sphere,20,100,100);

    gluDeleteQuadric(sphere);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

// Fonction qui dessine les trains
void dessinerTrains(){
    // Pour dessiner els trains on fait appel à la fonction drawTrains() de l'objet collection
    glColor3f(1,0.2,0.1);
    glPushMatrix();
    glTranslatef(0,0,0.25);
    collection->drawTrains();
    glPopMatrix();
}

// Fonction qui dessine le terrain
void dessinerTerrain() {
    // Dessin à z=0 :
    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, herbe);
    glBegin(GL_QUADS);
        glTexCoord2d(-10,-10); glVertex3d(-10,-10,0); glColor3ub(255,255,255);
        glTexCoord2d(40,-10);  glVertex3d(40,-10,0);  glColor3ub(255,255,255);
        glTexCoord2d(40,40);   glVertex3d(40,40,0);   glColor3ub(255,255,255);
        glTexCoord2d(-10,40);  glVertex3d(-10,40,0);  glColor3ub(255,255,255);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Dessin du relief :
    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < triangulation.triangles.size(); i++) {
        Triangle tri = triangulation.triangles[i];
        glBindTexture(GL_TEXTURE_2D, *tri.texture);
        glBegin(GL_TRIANGLES); // On va dessiner des triangles
            glTexCoord2f(tri.a.X, tri.a.Y); glVertex3f(tri.a.X, tri.a.Y, tri.a.Z);
            glTexCoord2f(tri.b.X, tri.b.Y); glVertex3f(tri.b.X, tri.b.Y, tri.b.Z);
            glTexCoord2f(tri.c.X, tri.c.Y); glVertex3f(tri.c.X, tri.c.Y, tri.c.Z);
        glEnd();
    }
}

// Fonction qui dessine un tunnel à partir de donnut
void dessinerTunDon() {
    // Le tunnel est une succesion de donnuts :

    dessinerDonnut(2.3,3,0.3);
    dessinerDonnut(2.2,3.5,0.3);
    dessinerDonnut(2.1,4,0.3);
    dessinerDonnut(2,4.5,0.3);
    dessinerDonnut(1.9,5,0.3);
    dessinerDonnut(1.8,5.5,0.3);
}

// Fonction qui dessine la lune :
void dessinerLune(){
    glPushMatrix();

    glTranslatef(5,5,20);

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *lune;
    lune = gluNewQuadric();
    gluQuadricTexture(lune,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, text_lune);
    gluSphere(lune,5,50,50);
    glRotated(180,1,0,0);
    gluDeleteQuadric(lune);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}


// Fonction qui dessine les lamapdaires :
void dessinerLampadaires() {
    dessinerLampadaire(1,1,-0.2,2);
    dessinerLampadaire(10,5,-0.2,2);
    dessinerLampadaire(15,6,-0.2,2);
    dessinerLampadaire(4.5,8,-0.2,2);
    dessinerLampadaire(20,20,-0.2,2);
}

// Fonction qui dessine les gares :
void dessinerGares(){
    dessinerGare(12, 24, 0, 3, 3, 2);
}

// Fonction qui dessine le pont :
void dessinerPont() {
    // Le pont est composé de trois pavé que l'on trace à a'aide de dessinerRectangle()

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,  pont);

    Vecteur a, b, c, d;

    dessinerRectangle(
        Vecteur(11,2.5,2), Vecteur(10,2.5,0), Vecteur(10,3.5,0), Vecteur(11,3.5,2),
        Vecteur(11,2.5,1.75), Vecteur(10,2.5,-0.25), Vecteur(10,3.5,-0.25), Vecteur(11,3.5,1.75)
    );
    dessinerRectangle(
        Vecteur(13,2.5,2), Vecteur(11,2.5,2), Vecteur(11,3.5,2), Vecteur(13,3.5,2),
        Vecteur(13,2.5,1.75), Vecteur(11,2.5,1.75), Vecteur(11,3.5,1.75), Vecteur(13,3.5,1.75)
    );
    dessinerRectangle(
        Vecteur(14,2.5,0), Vecteur(13,2.5,2), Vecteur(13,3.5,2), Vecteur(14,3.5,0),
        Vecteur(14,2.5,-0.25), Vecteur(13,2.5,1.75), Vecteur(13,3.5,1.75), Vecteur(14,3.5,-0.25)
    );

    glDisable(GL_TEXTURE_2D);
}

/*************************************************
************ Fonctions élémentaires : ************
*************************************************/

// Fonction pour dessiner une gare dont un coin est positionné en (x,y,z) de taille t1xt2xh
void dessinerGare(float x, float y, float z, float t1, float t2, float h){
    glPushMatrix();

    glTranslatef(x,y,z);

    dessinerPave(Vecteur(0,0,0), Vecteur(0,t2,0), Vecteur(t1,t2,0), Vecteur(t1,0,0), Vecteur(0,0,h), Vecteur(0,t2,h), Vecteur(t1,t2,h), Vecteur(t1,0,h),
                  avt_gare, drt_gare, der_gare, gce_gare, haut_gare, bas_gare);

    glPopMatrix();
}

// Fonction pour dessinr un pavé non fermé
void dessinerRectangle(Vecteur a1, Vecteur b1, Vecteur c1, Vecteur d1, Vecteur a2, Vecteur b2, Vecteur c2, Vecteur d2) {
    dessinerTextureSansDeformation(a1,b1,c1,d1);
    dessinerTextureSansDeformation(a2,b2,c2,d2);
    dessinerTextureSansDeformation(a1,a2,b2,b1);
    dessinerTextureSansDeformation(c1,c2,d2,d1);
}

// Fonction pour dessinr un pavé fermé avec une texture différente par face
void dessinerPave(Vecteur a1, Vecteur b1, Vecteur c1, Vecteur d1, Vecteur a2, Vecteur b2, Vecteur c2, Vecteur d2,
                  GLuint avant, GLuint droite, GLuint derriere, GLuint gauche, GLuint haut, GLuint bas) {
    dessinerTexture(bas,a1,b1,c1,d1);
    dessinerTexture(haut,a2,b2,c2,d2);
    dessinerTexture(avant,a1,a2,b2,b1);
    dessinerTexture(derriere,c1,c2,d2,d1);

    dessinerTexture(gauche,a1,a2,d2,d1);
    dessinerTexture(droite,b1,c1,c2,b2);
}

// Fonction pour tracer un sapin :
void dessinerSapin(float x, float y, float z, float h1, float h2, float l) {
    // Un sapin est un cylindre sur lequelle on dessine un cône :

    glPushMatrix();
    glTranslatef(x,y,z);

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *tronc;
    tronc = gluNewQuadric();
    gluQuadricTexture(tronc,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, bois);
    gluCylinder(tronc,0.15,0.15,h1,100,100);
    gluDeleteQuadric(tronc);

    glTranslatef(0,0,h1);

    GLUquadricObj *branches;
    branches = gluNewQuadric();
    gluQuadricTexture(branches,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, feuille);
    gluCylinder(branches, l, 0, h2, 100, 100);
    gluDeleteQuadric(branches);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Fonction pour tracer un arbre
void dessinerArbre(float x, float y, float z, float hauteur) {
    // Un arbre est un cylindre sur lequelle on dessine une sphère :

    glPushMatrix();
    glTranslatef(x,y,z);

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *tronc;
    tronc = gluNewQuadric();
    gluQuadricTexture(tronc,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, bois);
    gluCylinder(tronc,0.15,0.15,hauteur,100,100);
    gluDeleteQuadric(tronc);

    glTranslatef(0,0,hauteur);

    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, feuille);
    gluSphere(sphere,0.8,50,50);
    gluDeleteQuadric(sphere);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Fonction pour tracer un arbre
void dessinerLampadaire(float x, float y, float z, float hauteur){
    // Un lampadaire est un cylindre sur lequelle on dessine une sphère lumineuse :

    glPushMatrix();
    glTranslatef(x,y,z);

    glColor3d(0.8,0.8,0.8);
    GLUquadricObj *tronc;
    tronc = gluNewQuadric();
    gluCylinder(tronc,0.075,0.075,hauteur,100,100);
    gluDeleteQuadric(tronc);

    glTranslatef(0,0,hauteur);
    glColor3d(1,1,1);

    glEnable(GL_TEXTURE_2D);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);

    GLfloat mat_emission[] = {0.5, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, lampadaire);
    gluSphere(sphere,0.3,50,50);
    gluDeleteQuadric(sphere);

    glDisable (GL_LIGHT0);
    glDisable (GL_LIGHTING);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Fonction pour tracer un rail avec ses poteaux :
void dessinerRail(Vecteur debut, Vecteur fin) {
    // On calcul l'orientation de la caméra pour ce segment :
    Vecteur delta = fin - debut;
    float l = delta.norm();
    float V = asin(delta.getZ()/l);
    float H = 2*atan(delta.getX()/(delta.getY()+l*cos(V)));
    V *= 180.0/M_PI; H *= 180.0/M_PI;

    // Puis on déplace et on oriente le pinceau :
    glPushMatrix();
    glTranslatef(debut.getX(), debut.getY(), debut.getZ());
    //glRotatef(-V/2,0,0,1);

    // On dessine les poteaux sous le rail :
    glColor3d(0.2,0.2,0.2);
    glPushMatrix();
    glTranslatef(0, 0, -0.2); // les poteaux sont enfoncés dans le sol de 0.2
    glRotatef(90-H,0,0,1);
    glRotatef(-V,0,1,0);
    double nb_poutre = trunc((l-0.40)/0.5);
    // Le 1er poteau :
    dessinerPoteau(V, 0.02, 0.53, 30);
    glTranslatef((l-0.5*nb_poutre+0.5)/2, 0, 0);
    // Les suivants :
    for (int i = 0; i < nb_poutre; i++) {
        // On dessine la planche :
        dessinerPoteau(V, 0.02, 0.53, 30);
        glTranslatef(0.5, 0, 0);
    }
    glPopMatrix();

    // Puis son sommet :
    glColor3d(0.6,0.6,0.6);
    glPushMatrix();
    glTranslatef(0,0,0.33);
    glRotatef(90-H,0,0,1);
    glRotatef(90-V,0,1,0); // Decalage selon le segment ET pour dessiner à 90°
    GLUquadricObj *tronc;
    tronc = gluNewQuadric();
     gluCylinder(tronc,0.03,0.03,l,30,30);
    gluDeleteQuadric(tronc);
    glPopMatrix();

    glPopMatrix();

}

// Fonction pour dessiner un poteau :
void dessinerPoteau(float V, float r, float h, GLint s) {
    glPushMatrix();
    glRotatef(V,0,1,0); // Le poteau est tout le temps vertical !

    GLUquadricObj *pot;
    pot = gluNewQuadric();
    gluCylinder(pot,r,r,h,s,s);
    gluDeleteQuadric(pot);

    glPopMatrix();
}

// Fonction pour dessiner un donnut :
void dessinerDonnut(float x, float y, float z) {
    glPushMatrix();

    glTranslatef(x,y,z);
    glRotated(90,1,0,0);
    glRotated(20,0,1,0);

    glEnable(GL_TEXTURE_2D);

    glColor3d(1,0.3,0.1);
    glutWireTorus(0.3 ,1.1, 10 , 100);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

// Fonction pour tracer des polygones les typse sont précisé ci-dessous :
void dessinerPolygone(double ray, double smooth){
    glBegin(GL_POLYGON);
    // Lorsque que smooth = :
    //        - 1.5 : Dessine un Triangle
    //        -  2  : Dessine un carré
    //        -  3  : Dessine un hexagone
    //        -  4  : Dessine un octagone
    //        -  5  : Dessine un decagone
    //        -  >6 : Dessine un cercle
    for(double i = 0; i < 2 * M_PI; i += M_PI / smooth)
        glVertex3f(cos(i) * ray, sin(i) * ray, 0.0);

    glEnd();

}


void dessinerTexture(GLuint texture, Vecteur a, Vecteur b, Vecteur c, Vecteur d) {
    // Dessin de la texture avec initialisation
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 127.0f/255.0f);

    glBindTexture(GL_TEXTURE_2D, texture);

    dessinerTexture(a, b, c, d);

    glDisable(GL_TEXTURE_2D);
}

void dessinerTexture(Vecteur a, Vecteur b, Vecteur c, Vecteur d) {
    // Dessin de la texture sans initialisation
    glBegin(GL_QUADS);
        glTexCoord2f(0,0); glVertex3f(a.getX(), a.getY(), a.getZ());
        glTexCoord2f(0,1); glVertex3f(b.getX(), b.getY(), b.getZ());
        glTexCoord2f(1,1); glVertex3f(c.getX(), c.getY(), c.getZ());
        glTexCoord2f(1,0); glVertex3f(d.getX(), d.getY(), d.getZ());
    glEnd();
}

void dessinerTextureSansDeformation(Vecteur a, Vecteur b, Vecteur c, Vecteur d) {
    // Dessin de la texture sans initialisation
    glBegin(GL_QUADS);
        glTexCoord2f(a.getX(),a.getY()); glVertex3f(a.getX(), a.getY(), a.getZ());
        glTexCoord2f(b.getX(),b.getY()); glVertex3f(b.getX(), b.getY(), b.getZ());
        glTexCoord2f(c.getX(),c.getY()); glVertex3f(c.getX(), c.getY(), c.getZ());
        glTexCoord2f(d.getX(),d.getY()); glVertex3f(d.getX(), d.getY(), d.getZ());
    glEnd();
}
