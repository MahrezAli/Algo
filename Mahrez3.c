
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum {FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type image                */
/*                                               */
/*************************************************/

typedef struct bloc_image{
    bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;
typedef bloc_image *image ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* Construit une image blanche à partir de rien. */
image construit_Blanc();

/* Construit une image noire à partir de rien. */
image construit_Noir();

/* Construit une image composée des sous-images NO, NE, SO, SE. */
image construit_Compose(image NO, image NE, image SO, image SE);

/* Affichage en mode simple. */
void affichage_Normal(image a);
/* Fonction auxilière pour l'affichage (Pour rajouter le \n à la fin) */
void affichage_Normal_aux(image a);

/* Affichage en mode profondeur. */
void affichage_Profondeur(image a);
/* Fonction auxilière pour l'affichage en profondeur */
void affichage_Profondeur_aux(image a, int p);

/* Rend une image à partir des caractères tapés au clavier */
image Lecture();
/* Sous fonction de Lecture pour construire l'image */
image Lecture_aux(char *quadTree);
/* Vérifie que l'image tapée au clavier est correcte */
bool verifParenthese(char quadTree[]);
/* Supprime le premier élement d'une chaîne de caractère */
void suppPremierChar(char *quadTree);
/* Supprime le dernier élement d'une chaîne de caractère */
void suppDernierChar(char quadTree[]);
/* Supprime la première parenthèse ouvrante et la dernière parenthèse fermante d'une chaîne de caractère */
void extraitPar(char quadTree[]);
/* extrait l'image à construire */
void extraitMot(char *quadTree, char* res);

/* Teste si l'image est complétement noire */
bool EstNoire(image a);

/* Teste si l'image est complétement blanche */
bool EstBlanche(image a);

/* Rend une image qui est noir sur les pixels de profondeur p qui sont sur la diagonale */
image Diagonale(int p);

/* Rend l’image en argument tournée d’un quart de tour dans le sens des aiguilles d’une montre. */
image QuartDeTour(image a);

/* Transforme l'image en argument en son négatif */
void Negatif(image *a);

/* Remplace tous les arbres monochromes à profondeur P par de simples pixels B ou N */
void SimplifieProfP(image *a, int p);

/* Procédure qui tous les arbres monochromes par de simples pixels B ou N */
void simplifie(image* a);

/* Rend le maximum des hauteurs des sous-images blanches */
int HautMaxBlanc(image a);
/* Sous-fonction qui rend le maximum des hauteurs des sous-images blanches */
void HautMaxBlanc_aux(image a, int *h, bool *b);
/* Calcul le maximum entre deux entiers */
int max(int a, int b);

/* Calcule la puissance de x par n */
int power(int x, int n);
/* Blanchit le pixel de profondeur p */
void BlanchitProfP(image *a, int p, int x, int y);
/* Sous-procédure qui blanchit le pixel de profondeur p */
void BlanchitProfP_aux(image *a, int p, int x, int y, int n);

/* Trouve la profondeur maximal(hauteur) de l'image */
int ProfondeurMax(image a);
/* Sous-procédure qui trouve la profondeur maximal de l'image */
void Profondeur_aux(image a, int *b);
/* Procédure qui met l'image à la meme profondeur maximale (soit tous les fils à la meme hauteur) */
void memeProfMax(image *a, int pM);
/* Determine si la gravité peut etre appliquée */
bool estRenverible(image a1, image a2);
/* Renverse les deux images */
void Renverse(image *a1, image *a2);
/* Renvoie l'image aux coordonnées x et y */
image* coord(image *a, int p, int x, int y, int n);
/* Libere l'espace utilisé par une image */
void videImage(image *a);
/* Applique la gravité à l'image */
void Chute(image *a);
  

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

//Question 1:
image construit_Blanc(){
    return NULL;
}

image construit_Noir(){
    image res = (image) malloc(sizeof(bloc_image));
    res->toutnoir = TRUE;
    res->fils[0] = NULL;
    res->fils[1] = NULL;
    res->fils[2] = NULL;
    res->fils[3] = NULL;
    return res;
}

image construit_Compose(image NO, image NE, image SO, image SE){
    image res = (image) malloc(sizeof(bloc_image));
    res->toutnoir = FALSE;
    res->fils[0] = NO;
    res->fils[1] = NE;
    res->fils[2] = SO;
    res->fils[3] = SE;
    return res;
}

//Question 2:
void affichage_Normal(image a){
    printf("L'affichage du QuadTree en mode simple :\n");
    affichage_Normal_aux(a);
    printf("\n");
    return;
}

void affichage_Normal_aux(image a){
    if(a == NULL){ //Si l'image est blanche
        printf("B");
    }
    else{
        if(a->toutnoir){ //Si l'image est noir
            printf("N");
        }
        else{ //Si l'image est composée
            printf("(");
            affichage_Normal_aux(a->fils[0]);
            affichage_Normal_aux(a->fils[1]);
            affichage_Normal_aux(a->fils[2]);
            affichage_Normal_aux(a->fils[3]);
            printf(")");
        }
    }
}

void affichage_Profondeur(image a){
    printf("L'affichage du QuadTree en profondeur :\n");
    affichage_Profondeur_aux(a, 0);
    printf("\n");
    return;
}

void affichage_Profondeur_aux(image a, int p){
    if(a == NULL){ //Si l'image est blanche
        printf(" B%d ", p);
    }
    else {
        if(a->toutnoir){ //Si l'image est noir
            printf(" N%d ", p);
        }
        else{ //Si l'image est composée
            printf(" ( ");
            affichage_Profondeur_aux(a->fils[0], p+1);
            affichage_Profondeur_aux(a->fils[1], p+1);
            affichage_Profondeur_aux(a->fils[2], p+1);
            affichage_Profondeur_aux(a->fils[3], p+1);
            printf(" ) ");
        }
    }
}

//Question 3:
image Lecture(){
    char quadTree[100]; 
    printf("Veuillez taper au clavier l'image à construire :\n");
    scanf("%s", quadTree);
    return Lecture_aux(quadTree);
}

image Lecture_aux(char *quadTree){
    if(verifParenthese(quadTree)){
        if(quadTree[0] == 'N'){
            suppPremierChar(quadTree);
            return construit_Noir();
        }
        else if(quadTree[0] == 'B'){
            suppPremierChar(quadTree);
            return construit_Blanc();
        }
        else{
            extraitPar(quadTree);
            char m1[100];
            extraitMot(quadTree, m1);
            char m2[100]; 
            extraitMot(quadTree, m2);
            char m3[100];
            extraitMot(quadTree, m3);
            char m4[100];
            extraitMot(quadTree, m4);

            image a1 = Lecture_aux(m1);
            image a2 = Lecture_aux(m2);
            image a3 = Lecture_aux(m3);
            image a4 = Lecture_aux(m4);
            return construit_Compose(a1, a2, a3, a4);
        }
    }
    else{
        perror("L'image est impossible à construire");
        return Lecture();
    }
}

bool verifParenthese(char quadTree[]){
    int res = 0;
    int i = 0;
    while(quadTree[i] != '\0'){
        if(quadTree[i] == '('){
            res++;
        }
        else if(quadTree[i] == ')'){
            res--;
        }
        else if(quadTree[i] != 'B' && quadTree[i] != 'N'){
            return FALSE;
        }
        i++;
    }
    return (res == 0);
}

void suppPremierChar(char *quadTree){
    int i = 0;
    while(quadTree[i] != '\0'){
        quadTree[i] = quadTree[i+1];
        i++;
    }
}

void suppDernierChar(char quadTree[]){
    int i = 0;
    while(quadTree[i] != '\0'){
        i++;
    }
    quadTree[i-1] = '\0';
}

void extraitPar(char quadTree[]){
    suppDernierChar(quadTree);
    suppPremierChar(quadTree);
}

void extraitMot(char *quadTree, char* res){
    if(quadTree[0] == 'N'){
        res[0] = quadTree[0];
        res[1] = '\0';
        suppPremierChar(quadTree);
    }
    else if(quadTree[0] == 'B'){
        res[0] = quadTree[0];
        res[1] = '\0';
        suppPremierChar(quadTree);
    }
    else{
        if(quadTree[0] == '('){
            int i = 0;
            int cpt = 1;
            res[0] = quadTree[0];
            suppPremierChar(quadTree);
            while(cpt > 0){
                res[i+1] = quadTree[0];
                if(quadTree[0] == '('){
                    cpt++;
                }
                else if(quadTree[0] == ')'){
                    cpt--;
                }
                suppPremierChar(quadTree);
                i++;
            }
            res[i+1] = '\0';

        }
    }
}



//Question 4:
bool EstNoire(image a){
    if(a == NULL){
        return FALSE;
    }
    else{
        if(a->toutnoir){
            return TRUE;
        }
        else{
            return EstNoire(a->fils[0]) && EstNoire(a->fils[1]) && EstNoire(a->fils[2]) && EstNoire(a->fils[3]);
        }

    }
}

bool EstBlanche(image a){
    if(a == NULL){
        return TRUE;
    }
    else{
        if(a->toutnoir){
            return FALSE;
        }
        else{
            return EstBlanche(a->fils[0]) && EstBlanche(a->fils[1]) && EstBlanche(a->fils[2]) && EstBlanche(a->fils[3]);
        }

    }
}

//Question 5:
image Diagonale(int p){
    if(p == 0){
        return construit_Noir();
    }
    else{
        image tmp = Diagonale(p-1);
        return construit_Compose(tmp, construit_Blanc(), construit_Blanc(), tmp);
    }
}

//Question 6:
image QuartDeTour(image a){
    if(a == NULL){
        return construit_Blanc();
    }
    else if(a->toutnoir){
        return construit_Noir();
    }
    else{
        return construit_Compose(QuartDeTour(a->fils[2]), QuartDeTour(a->fils[0]), QuartDeTour(a->fils[3]), QuartDeTour(a->fils[1]));
    }
} 

//Question 7:
void Negatif(image *a){
    if(*a == NULL){
        *a = construit_Noir();
    }
    else if((*a)->toutnoir){
        free(*a);
        *a = construit_Blanc();
    }
    else{
        Negatif(&((*a)->fils[0]));
        Negatif(&((*a)->fils[1]));
        Negatif(&((*a)->fils[2]));
        Negatif(&((*a)->fils[3]));
    }
}

//Question 8:
void SimplifieProfP(image *a, int p){
    if(*a == NULL){}
    else if((*a)->toutnoir){}
    else{
        SimplifieProfP(&(*a)->fils[0], p-1);
        SimplifieProfP(&(*a)->fils[1], p-1);
        SimplifieProfP(&(*a)->fils[2], p-1);
        SimplifieProfP(&(*a)->fils[3], p-1);
        if(p == 0){
            if(EstBlanche(*a)){
                videImage(a); //Faut aussi appeler la fonction ici car il se peut que c'est une image composée d'images blanches
                *a = construit_Blanc();
            }
            else if(EstNoire(*a)){
                videImage(a);
                *a = construit_Noir();
            }
        }
    }
}

//Question 9:
bool incluse(image a1, image a2){
    if(EstBlanche(a1)){
        return TRUE;
    }
    else{
        if(EstNoire(a1)){
            return EstNoire(a2);
        }
        else{
            if(a2 == NULL){
                return FALSE;
            }
            else if(a2->toutnoir){
                return TRUE;
            }
            else{
                return incluse(a1->fils[0], a2->fils[0]) && incluse(a1->fils[1], a2->fils[1]) && incluse(a1->fils[2], a2->fils[2]) && incluse(a1->fils[3], a2->fils[3]);
            }
        }
        
    }
}

//Question 10:
int HautMaxBlanc(image a){
    int h;
    bool b;
    HautMaxBlanc_aux(a, &h, &b);
    return h;
}

void HautMaxBlanc_aux(image a, int *h, bool *b){
    if(a == NULL){
        *h = 0;
        *b = TRUE;
    }
    else if(a->toutnoir){
        *h = -1;
        *b = FALSE;
    }
    else{
        int h0, h1, h2, h3;
        bool b0, b1, b2, b3;
        HautMaxBlanc_aux(a->fils[0], &h0, &b0);
        HautMaxBlanc_aux(a->fils[1], &h1, &b1);
        HautMaxBlanc_aux(a->fils[2], &h2, &b2);
        HautMaxBlanc_aux(a->fils[3], &h3, &b3);
        *b = b0 && b1 && b2 && b3;
        int m1 = max(h0, h1);
        int m2 = max(h2, h3);
        if(*b){
            *h = max(m1, m2) + 1;
        }
        else{
            *h = max(m1, m2);
        }
    }
}

int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

//Question 11:
int power(int x, int n){
    if(n == 0){
        return 1;
    }
    else{
        int y = power(x, n/2);
        if(n % 2 == 0){
            return y * y;
        }
        else{
            return x * y * y;
        }
    }
}
void BlanchitProfP(image *a, int p, int x, int y){
    int max = power(2, p);
    if(x < 0 || x >= max || y < 0 || y >= max ){
        printf("Les coordonnées sont incorrectes\n");
    }
    else{
        BlanchitProfP_aux(a, p, x, y, max);
    }
}

void BlanchitProfP_aux(image *a, int p, int x, int y, int n){
    if(p == 0){
        videImage(a);
        *a = construit_Blanc();
    }
    else{
        if((*a) != NULL){
            if((*a)->toutnoir){
                free(*a);
                *a = construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Noir());
            }   
            if(x < n/2 && y < n/2){
                BlanchitProfP_aux(&(*a)->fils[2], p-1, x, y, n/2);
            }
            else if(x < n/2 && y >= n/2){
                BlanchitProfP_aux(&(*a)->fils[0], p-1, x, y-(n/2), n/2);
            }
            else if(x >= n/2 && y < n/2){
                BlanchitProfP_aux(&(*a)->fils[3], p-1, (x-(n/2)), y, n/2);
            }
            else if(x >= n/2 && y >= n/2){
                BlanchitProfP_aux(&(*a)->fils[1], p-1, (x-(n/2)), y-(n/2), n/2);   
            }
        }
    }
}

//Question 12:
int ProfondeurMax(image a){
    int p;
    Profondeur_aux(a, &p);
    return p;
}

void Profondeur_aux(image a, int *p){
    if(a == NULL || a->toutnoir || EstBlanche(a) || EstNoire(a)){
        *p = 0;
    }
    else{
        int p0, p1, p2, p3;
        Profondeur_aux(a->fils[0], &p0);
        Profondeur_aux(a->fils[1], &p1);
        Profondeur_aux(a->fils[2], &p2);
        Profondeur_aux(a->fils[3], &p3);
        int tmp1 = max(p0, p1);
        int tmp2 = max(p2, p3);
        *p = max(tmp1, tmp2) + 1;
    }
}

void memeProfMax(image *a, int pM){
    if(pM > 0){
        if(*a == NULL){
            *a = construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc());
        }
        else if((*a)->toutnoir){
            free(*a);
            *a = construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Noir());
        }
        memeProfMax(&(*a)->fils[0], pM-1);
        memeProfMax(&(*a)->fils[1], pM-1);
        memeProfMax(&(*a)->fils[2], pM-1);
        memeProfMax(&(*a)->fils[3], pM-1);
    }
}

bool estRenverible(image a1, image a2){
    if(a1 == NULL){
        return NOT(a2 == NULL);
    }
    return FALSE;
}

void Renverse(image *a1, image *a2){
    free(*a1);
    *a1 = construit_Noir();
    free(*a2);
    *a2 = construit_Blanc();
}

image* coord(image *a, int p, int x, int y, int n){
    if(p == 0){
        return a;
    }
    else{
        if(x < n/2 && y < n/2){
            return coord(&(*a)->fils[2], p-1, x, y, n/2);
        }
        else if(x < n/2 && y >= n/2){
            return coord(&(*a)->fils[0], p-1, x, y-(n/2), n/2);
        }
        else if(x >= n/2 && y < n/2){
            return coord(&(*a)->fils[3], p-1, (x-(n/2)), y, n/2);
        }
        else if(x >= n/2 && y >= n/2){
            return coord(&(*a)->fils[1], p-1, (x-(n/2)), y-(n/2), n/2);
        }
        else{
            return 0;
        }
    }
}

void simplifie(image* a){
    if(*a != NULL && NOT((*a)->toutnoir)){
        simplifie(&(*a)->fils[0]);
        simplifie(&(*a)->fils[1]);
        simplifie(&(*a)->fils[2]);
        simplifie(&(*a)->fils[3]);
        if((*a)->fils[0] == NULL && (*a)->fils[1] == NULL && (*a)->fils[2] == NULL && (*a)->fils[3] == NULL){
            free(*a);
            *a = construit_Blanc();
        }
        else if((*a)->fils[0] != NULL && (*a)->fils[1] != NULL && (*a)->fils[2] != NULL && (*a)->fils[3] != NULL){
            if((*a)->fils[0]->toutnoir && (*a)->fils[1]->toutnoir && (*a)->fils[2]->toutnoir && (*a)->fils[3]->toutnoir){
                videImage(a);
                *a = construit_Noir();
            }
        }
    }
}

/*
L'idée est de mettre l'image a la meme hauteur, ce qui facilitera l'application de la gravité puisqu'il suffira de renverser les images
noires et les images blanches de chaque lignes pour chaque colonnes.
*/

void Chute(image *a){ 
    int p = ProfondeurMax(*a);
    memeProfMax(a, p); //Met l'image a la meme hauteur
    int n = power(2, p); //La taille de l'image
    int i = 0;
    while(i < n){ //parcours de l'abscisse
        int j = 0;
        while(j < n){ // parcours de l'ordonnée
            image *tmp1 = coord(a, p, i, j, n);
            if(*tmp1 == NULL){ //Verifier que l'image ou l'on se trouve est vide (Blanche)
                int k = j+1;
                while(k < n){ //Cherche si l'une des images au dessus de celle ou l'on se trouve est remplie (Noire)
                    image *tmp2 = coord(a, p, i, k, n);
                    if(estRenverible(*tmp1, *tmp2)){ //Si une image noir est au dessus d'une image blanche
                        Renverse(tmp1, tmp2);
                        break;
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }
    simplifie(a); //Simplifier l'image
}

void videImage(image *a){
    if(*a == NULL){}
    else if((*a)->toutnoir){
        free(*a);
    }
    else{
        videImage(&(*a)->fils[0]);
        videImage(&(*a)->fils[1]);
        videImage(&(*a)->fils[2]);
        videImage(&(*a)->fils[3]);
        free(*a);
    }
}

int main(int argc, char** argv){

    //TESTS DE FONCTIONS :
    image a1 = construit_Noir();
    image a2 = construit_Compose(construit_Noir(), construit_Blanc(), construit_Compose(construit_Noir(), construit_Noir(), construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Noir()), construit_Noir()), construit_Blanc());
    image a3 = construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc())));
    image a4 = construit_Compose(construit_Blanc(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc()), construit_Blanc());
    image A = construit_Compose(a1, a2, a3, a4);

    image b1 = construit_Blanc();
    image b2 = construit_Compose(construit_Blanc(), construit_Noir(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc()), construit_Blanc()), construit_Noir());
    image b3 = construit_Compose(construit_Blanc(), construit_Noir(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Noir(), construit_Blanc(), construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Noir())));
    image b4 = construit_Compose(construit_Noir(), construit_Noir(), construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Noir()), construit_Noir());
    image B = construit_Compose(b1, b2, b3, b4);

    image c1 = construit_Compose(construit_Compose(construit_Blanc(), construit_Blanc(),construit_Blanc(), construit_Blanc()), construit_Noir(), construit_Blanc(), construit_Noir());
    image c2 = construit_Blanc();
    image c3 = construit_Noir();
    image c4 = construit_Compose(construit_Compose(construit_Blanc(), construit_Blanc(), construit_Noir(), construit_Noir()), construit_Blanc(), construit_Blanc(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Blanc(), construit_Noir()));
    image C = construit_Compose(c1, c2, c3, c4);

    image d1 = construit_Compose(construit_Blanc(), construit_Noir(), construit_Noir(), construit_Noir());
    image d2 = construit_Compose(construit_Blanc(), construit_Blanc(), construit_Noir(), construit_Blanc());
    image d3 = construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Noir());
    image d4 = construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Compose(construit_Noir(), construit_Noir(), construit_Noir(), construit_Blanc()));
    image D = construit_Compose(d1, d2, d3, d4);

    image e1 = construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc());
    image e2 = construit_Noir();
    image e3 = construit_Compose(construit_Blanc(), construit_Noir(), construit_Blanc(), construit_Noir());
    image e4 = construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc()), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Blanc(), construit_Blanc(), construit_Blanc()))), construit_Noir())));
    image E = construit_Compose(e1, e2, e3, e4);

    image f1 = construit_Compose(construit_Noir(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Noir()), construit_Noir(), construit_Noir());
    image f2 = construit_Blanc();
    image f3 = construit_Noir();
    image f4 = construit_Blanc();
    image F = construit_Compose(f1, f2, f3, f4);

    image g1 = construit_Noir();
    image g2 = construit_Compose(construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Noir()), construit_Noir(), construit_Blanc(), construit_Compose(construit_Blanc(), construit_Noir(), construit_Blanc(), construit_Noir()));
    image g3 = construit_Compose(construit_Noir(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Blanc(), construit_Noir()), construit_Compose(construit_Blanc(), construit_Noir(), construit_Noir(), construit_Noir()), construit_Compose(construit_Noir(), construit_Blanc(), construit_Noir(), construit_Blanc()));
    image g4 = construit_Compose(construit_Noir(), construit_Noir(), construit_Compose(construit_Noir(), construit_Blanc(), construit_Blanc(), construit_Blanc()), construit_Compose(construit_Blanc(), construit_Noir(), construit_Blanc(), construit_Noir()));
    image G = construit_Compose(g1, g2, g3, g4);

    //Negatif :
    printf("Negatif\n");
    affichage_Normal(B);
    Negatif(&B);
    affichage_Normal(B);
    printf("\n");

    //SimplifieProfP :
    printf("SimplifieProfP\n");
    affichage_Normal(A);
    SimplifieProfP(&A, 2);
    affichage_Normal(A);
    printf("\n");

    //Incluse :
    printf("Incluse\n");
    printf(incluse(C, D) ? "La 1ere est incluse dans la 2eme\n" : "La 1ere n'est pas incluse dans la 2eme\n");
    printf("\n");

    //HautMaxBlanc :
    printf("HautMaxBlanc\n");
    printf("La hauteur maximale blanche est de : %d\n", HautMaxBlanc(E));
    printf("\n");

    //BlanchitProfP :
    printf("BlanchitProfP\n");
    affichage_Normal(F);
    BlanchitProfP(&F, 2, 1, 3);
    affichage_Normal(F);
    printf("\n");

    //Chute :
    printf("Chute\n");
    affichage_Normal(G);
    Chute(&G);
    affichage_Normal(G);

    return 0;
}




