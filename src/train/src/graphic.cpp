#include "graphic.h"


/*************************************************
************ Fonctions principales : *************
*************************************************/

// Fonction qui va cherger les différentes textures utiles pour le projet :
void chargerTextures() {
    wagon = loadTexture("textures/wagon.jpg");
    herbe = loadTexture("textures/grass.jpg");
    neige = loadTexture("textures/snow.jpg");
    ciel  = loadTexture("textures/ciel.jpg");
    bois  = loadTexture("textures/bois.jpg");
    feuille = loadTexture("textures/feuille.jpg");
    pont = loadTexture("textures/pont.jpg");
    gravier = loadTexture("textures/gravier.jpg");
    poutre_bois = loadTexture("textures/poutre_bois.jpg");
    tunnel = loadTexture("textures/tunnel.jpg");
    eau = loadTexture("textures/eau.jpg");
}

// Fonction principale qui va dessiner l'ensemble de notre projet :
void dessiner() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Vecteur ecart(0,0,1);
    if (cam->vue != -1) {
        cam->changerPosition(collection->listeTrain[cam->vue].wagons[1].position(ecart), collection->listeTrain[cam->vue].wagons[0].position(ecart));
    }
    cam->Look();

    // Rails :
    dessinerVoies();

    // Arbres :
    dessinerArbres();

    // Ciel :
    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(12.205,10.065,0.0);
    // glutSolidSphere(16,100,100);
    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricTexture(sphere,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D,ciel);
    gluSphere(sphere,20,100,100);
    gluDeleteQuadric(sphere);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // Trains :
    glColor3f(1,0.2,0.1);
    glPushMatrix();
    glTranslatef(0,0,0.25);
    collection->drawTrains();
    glPopMatrix();

    // Herbe :
    dessinerTerrain();

    // Donnut :
    dessinerTunDon();

    // Pont :
    glColor3f(1,1,1);
    dessinerPont();

    glFlush();
    glutSwapBuffers();
}

/*************************************************
************ Sous-fonctions : ********************
*************************************************/

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
/*
    dessinerSapinNeige(11,18, 0, 4.5, 3.5);
    dessinerSapinNeige(14.4,15.5, 0, 3.5, 2.5);
    dessinerSapinNeige(13,18, 0, 3.8, 3.1);
    dessinerSapinNeige(11,16.2, 0, 4.4, 3.2);
*/
}

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
        glBegin(GL_TRIANGLES); // on va dessiner des triangles
            glTexCoord2f(tri.a.X, tri.a.Y); glVertex3f(tri.a.X, tri.a.Y, tri.a.Z);
            glTexCoord2f(tri.b.X, tri.b.Y); glVertex3f(tri.b.X, tri.b.Y, tri.b.Z);
            glTexCoord2f(tri.c.X, tri.c.Y); glVertex3f(tri.c.X, tri.c.Y, tri.c.Z);
        glEnd();
    }
}

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

void dessinerPont() {

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

    //dessinerTexture(Vecteur(13,2.5,2), Vecteur(11,2.5,2), Vecteur(11,3.5,2), Vecteur(13,3.5,2));
    //dessinerTexture(Vecteur(14,2.5,0), Vecteur(13,2.5,2), Vecteur(13,3.5,2), Vecteur(14,3.5,0));

    glDisable(GL_TEXTURE_2D);
}

void dessinerTunDon() {
    glPushMatrix();

    dessinerDonnut(2.3,3,0.3);
    dessinerDonnut(2.2,3.5,0.3);
    dessinerDonnut(2.1,4,0.3);
    dessinerDonnut(2,4.5,0.3);
    dessinerDonnut(1.9,5,0.3);
    dessinerDonnut(1.8,5.5,0.3);

    glPopMatrix();
}

/*************************************************
************ Fonctions élémentaires : ************
*************************************************/

void dessinerRectangle(Vecteur a1, Vecteur b1, Vecteur c1, Vecteur d1, Vecteur a2, Vecteur b2, Vecteur c2, Vecteur d2) {
    dessinerTextureSansDeformation(a1,b1,c1,d1);
    dessinerTextureSansDeformation(a2,b2,c2,d2);
    dessinerTextureSansDeformation(a1,a2,b2,b1);
    dessinerTextureSansDeformation(c1,c2,d2,d1);

}

void dessinerSapinNeige(float x, float y, float z, float h1, float h2) {

    glPushMatrix();
    glTranslatef(x,y,z);

    float rt = 0.05; // rayon du tronc

    glColor3d(1,1,1);
    glEnable(GL_TEXTURE_2D);
    GLUquadricObj *tronc;
    tronc = gluNewQuadric();
    gluQuadricTexture(tronc,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, bois);
    gluCylinder(tronc,rt,rt,h1,50,50);
    gluDeleteQuadric(tronc);


    float h3 = h1 - h2; // hauteur avec des branches
    //float hb = rt; // hauteur d'une branche, augmentation du rayon (= rt)
    int nb_branche = floor(h3 / (2*rt))+1; // nb de branche

    glTranslatef(0,0,h1);
    glPushMatrix();
    glTranslatef(0,0,rt);
    int slide = 40; // nb de slides pour les branches

    // On dessine les cercles verts des branches :

    GLUquadricObj *branche;
    branche = gluNewQuadric();
    gluQuadricTexture(branche,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, feuille);

    for (int i = 0; i <= nb_branche; i++) {
        float dri = rt*pow(i,1/1.2);
        gluDisk(branche, 0, dri, slide, slide);
        glTranslatef(0,0,-rt);
        gluDisk(branche, 0, dri+rt, slide, slide);
        glTranslatef(0,0,-rt);
    }
    gluDeleteQuadric(branche);
    glPopMatrix();

    // On dessiner les cylindres blancs des branches recouvertes de neige :

    GLUquadricObj *branche_neige;
    branche_neige = gluNewQuadric();
    gluQuadricTexture(branche_neige,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, neige);

    for (int i = 0; i <= nb_branche; i++) {
        float dri = rt*pow(i,1/1.2);
        gluCylinder(branche_neige, dri+rt, dri, rt, slide, slide);
        glTranslatef(0,0,-2*rt);
    }
    gluDeleteQuadric(branche_neige);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void dessinerSapin(float x, float y, float z, float h1, float h2, float l) {
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

void dessinerArbre(float x, float y, float z, float hauteur) {
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

void dessinerPoteau(float V, float r, float h, GLint s) {
    glPushMatrix();
    glRotatef(V,0,1,0); // Le poteau est tout le temps vertical !

    GLUquadricObj *pot;
    pot = gluNewQuadric();
    gluCylinder(pot,r,r,h,s,s);
    gluDeleteQuadric(pot);

    glPopMatrix();
}

void dessinerDonnut(float x, float y, float z) {
    glPushMatrix();

    glTranslatef(x,y,z);
    glRotated(90,1,0,0);
    glRotated(20,0,1,0);

    glEnable(GL_TEXTURE_2D);

    glColor3d(1,0.4,0.1);
    glutWireTorus(0.3 ,1.1, 10 , 100);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
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
