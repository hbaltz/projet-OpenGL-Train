# Projet OpenGL 2015 :

On considère un graphe dont la topologie est la métrique sont modélisées par 4 tables comme suit:

 - SIF: table des topologie du graphe à 2 colonnes dans l'ordre sommet_initial, sommet_final
   + de 1 à NA (le nombre d'arcs)
   + la a-ème ligne de la table correspond à l'arc numéro a.

 - SXYZ: table des coordonnées des sommets à 3 colonnes dans l'ordre X, Y, Z
    + de 1 à NS (le nombre de sommets)
    + la s-ème ligne de la table correspond au sommet numéro s

 - AXYZ: table des coordonnées des points annexes supportés par un arc. à 3 colonnes X, Y, Y
    + de 1 à NPA (le nombre de points annexes)
    + la p-ème ligne donne de les coordonnées spatiales du points annexe d'indice p

 - PAXYZ: table d'indirection vers AXYZ à 2 colonnes p_debut, nb_point_annex
    + de 1 à NA (le nombre d'arcs)
    + la a-ème ligne renseigne pour l'arc d'indice a, sur:
        * l'indice p_debut dans AXYZ du premier point annexe supportées
        * le nombre nb_point_annex de points annexes

Une base de données objets a été peuplée à partir de ces tables. Désormais, l'on dispose des classes:

    - Sommet,
    - Arc,
    - PointAnnexe, et
    - Graphe

ainsi que des relations qui existent entre elles.

Ainsi:

- Un graphe connait ses composantes : list_arc, list_sommet, list_point_annexe.
- Un point annexe porte ses coordonnées et il en est de même pour Sommet.
- Un sommet connait ses arcs entrants et sortants.
- De la même manière tout arc connait ses sommets initial et final.
- Enfin, un arc connait la liste des points annexes qu’il supporte.

Hypothèse : on considère que le graphe est non orienté et que les mobiles peuvent circuler dans les deux sens

L’objet de l’exercice est de représenter en 3D le graphe et de déplacer des mobiles dessus.