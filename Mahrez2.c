
#include <stdio.h>
#include <stdlib.h>

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

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;
int compteurListe = 0;
int *c = &compteurListe;
/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*  Renvoie vraie s'il ya un 0 en première, deuxième ou troisième position de la liste  */
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l);

/*  Renvoie vraie si l1 est plus courte que l2  */
bool PlusCourte(Liste l1, Liste l2);

/*  Renvoie le nombre de 0 du début de la liste à la K-ième position, en itératif */
int NombreDe0AvantPositionK1(Liste l, int pos);
/*  Renvoie le nombre de 0 du début de la liste à la K-ième position, en récursif sans sous-fonctionnalité */
int NombreDe0AvantPositionK2(Liste l, int pos);
/*  Renvoie le nombre de 0 du début de la liste à la K-ième position, en récursif terminale avec sous-fonction */
int NombreDe0AvantPositionK3(Liste l, int pos);
int NombreDe0AvantPositionK3_aux(Liste l, int pos, int compteur);
/*  Renvoie le nombre de 0 du début de la liste à la K-ième position, en récursif terminale avec sous-procédure */
int NombreDe0AvantPositionK4(Liste l, int pos);
void NombreDe0AvantPositionK4_aux(Liste l, int pos, int *compteur);

/*  Renvoie le nombre de 0 de la droite où à la K-ième position du fond */
int NombreDe0ApresRetroPositionK(Liste l, int pos);
void NombreDe0ApresRetroPositionK_aux(Liste l, int *pos, int *compteur);

/*  Renvoie une nouvelle liste dans laquelle tous les éléments strictement positifs sont recopiés deux fois, en récursive simple. */
Liste fctBegaye1(Liste l);
/*  Renvoie une nouvelle liste dans laquelle tous les éléments strictement positifs sont recopiés deux fois, en récursive terminale avec sous-fonction. */
Liste fctBegaye2(Liste l);
Liste fctBegaye2_aux(Liste l, Liste *res);
/*  Renvoie une nouvelle liste dans laquelle tous les éléments strictement positifs sont recopiés deux fois, en itératif. */
Liste fctBegaye3(Liste l);

/*  Renvoie une nouvelle liste dans laquelle tous les éléments strictement positifs sont recopiés deux fois, en récurdif terminal avec sous-procédure. */
Liste procBegaye(Liste l);
void procBegaye_aux(Liste *res);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    *c = *c +1;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
      *c = *c -1;
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

//QUESTION 1 :
bool ZeroEnPositionUnOuDeuxOuTrois(Liste l){
    if(estVide(l)){
        return FALSE;
    }
    else{
        if(premier(l) == 0){
            return TRUE;
        }
        else{
            if(estVide(suite(l))){
                return FALSE;
            }
            else{
                if(premier(suite(l)) == 0){
                    return TRUE;
                }
                else{
                    if(estVide(suite(suite(l)))){
                        return FALSE;
                    }
                    else{
                        return premier(suite(suite(l))) == 0;
                    }
                }
            }
        }
    }
}

//QUESTION 2 :
bool PlusCourte(Liste l1, Liste l2){
    if(estVide(l1)){
        return !estVide(l2);
    }
    else if(estVide(l2)){
        return FALSE;
    }
    else{
        return PlusCourte(suite(l1), suite(l2));
    }
}

//QUESTION 3 :
//VERSION ITÉRATIVE 
int NombreDe0AvantPositionK1(Liste l, int pos){
    int compteur = 0;
    Liste tmp = l;
    int k = pos;
    while(k > 0 && !estVide(tmp)){
        if(premier(tmp) == 0){
            compteur++;
        }
        k--;
        tmp = suite(tmp);
    }
    return compteur;
}

//VERSION RÉCURSIVE SIMPLE SANS SOUS-FONCTIONNALITÉ
int NombreDe0AvantPositionK2(Liste l, int pos){
    if(pos == 0 || estVide(l)){
        return 0;
    }
    else{
        if(premier(l) == 0){
            return 1 + NombreDe0AvantPositionK2(suite(l), pos-1);
        }
        else{
            return NombreDe0AvantPositionK2(suite(l), pos-1);
        }
    }
}

//VERSION RÉCURSIVE TERMINAL AVEC SOUS-FONCTION
int NombreDe0AvantPositionK3(Liste l, int pos){
    return NombreDe0AvantPositionK3_aux(l, pos, 0);
}
int NombreDe0AvantPositionK3_aux(Liste l, int pos, int compteur){
    if(pos == 0 || estVide(l)){
        return compteur;
    }
    else{
        if(premier(l) == 0){
            return NombreDe0AvantPositionK3_aux(suite(l), pos-1, compteur+1);
        }
        else{
            return NombreDe0AvantPositionK3_aux(suite(l), pos-1, compteur);
        }
    }
}

//VERSION RÉCURSIVE TERMINAL AVEC SOUS-PROCÉDURE
int NombreDe0AvantPositionK4(Liste l, int pos){
    int compteur = 0;
    NombreDe0AvantPositionK4_aux(l, pos, &compteur);
    return compteur;
}
void NombreDe0AvantPositionK4_aux(Liste l, int pos, int *compteur){
    if(pos > 0 && !estVide(l)){
        if(premier(l) == 0){
            *compteur = *compteur + 1;
        }
        NombreDe0AvantPositionK4_aux(suite(l), pos-1, compteur);
    }
}

//QUESTION 4 :
int NombreDe0ApresRetroPositionK(Liste l, int pos){
    int compteur = 0;
    int pos_k = pos;
    NombreDe0ApresRetroPositionK_aux(l, &pos_k, &compteur);
    return compteur;
}
void NombreDe0ApresRetroPositionK_aux(Liste l, int *pos, int *compteur){
    if(!estVide(l)){
        NombreDe0ApresRetroPositionK_aux(suite(l), pos, compteur);  
        if(premier(l) == 0 && *pos > 0){
            *compteur = *compteur + 1;
        }
        (*pos) = (*pos)-1;
    }
}

//QUESTION 5 :
//VERSION RÉCURSIVE SIMPLE SANS SOUS-FONCTIONNALITÉ
Liste fctBegaye1(Liste l){
    if(estVide(l)){
        return l;
    }
    else{
        if(premier(l) > 0){
            return ajoute(premier(l),ajoute(premier(l), fctBegaye1(suite(l))));
        }
        else{
            return fctBegaye1(suite(l));
        }
        
    }
}

//VERSION RÉCURSIVE TERMINAL AVEC SOUS-FONCTION
Liste fctBegaye2(Liste l){
    Liste res;
    initVide(&res);
    fctBegaye2_aux(l, &res);
    return res;
}

Liste fctBegaye2_aux(Liste l, Liste *res){
    if(estVide(l)){
        return *res;
    }
    else{
        if(premier(l) > 0){
            empile(premier(l), res);
            res = &((**res).suivant);
            empile(premier(l), res);
            res = &((**res).suivant);
            return fctBegaye2_aux(suite(l), res);
        }
        else{
            return fctBegaye2_aux(suite(l), res);
        }
    }
}

//VERSION ITÉRATIVE 
Liste fctBegaye3(Liste l){
    Liste res;
    initVide(&res);
    Liste tmp = l;
    Liste *q = &res;
    while(!estVide(tmp)){
        if(premier(tmp) > 0){
            empile(premier(tmp), q);
            q = &((**q).suivant);
            empile(premier(tmp), q);
            q = &((**q).suivant);
        }
        tmp = suite(tmp);
    }
    return res;
}

//QUESTION 6 :
Liste procBegaye(Liste l){
    //Liste *res = &l;
    procBegaye_aux(&l);
    return l;
}
void procBegaye_aux(Liste *res){
    if(!estVide(*res)){
        procBegaye_aux(&(*res)->suivant);
        if(premier(*res) > 0){
            empile(premier(*res), res);
        }
        else{
            depile(res);
        }
    }
}

//QUESTION 7 :

/*************************************************/
/*                                               */
/*       definition type liste de listes         */
/*                                               */
/*************************************************/


int compteurLListes = 0;
int *cs = &compteurLListes;

typedef struct Blocs
{
    Liste liste;
    struct Blocs *suivant;
} Blocs;

typedef Blocs *LListes ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste de listes vide */
void initVideLL(LListes *L);

/* renvoie 1 si la Liste de liste en parametre est vide, 0 sinon */
bool estVideLL(LListes l);

/* renvoie le premier element de la Liste de liste en parametre */
Liste premierLL(LListes l);

/* renvoie une nouvelle Liste de liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
LListes ajouteLL(Liste x, LListes l);

/* modifie la Liste de liste en parametre: x est ajoute comme premier element */
void empileLL(Liste x, LListes* L);

/* renvoie une nouvelle Liste de liste correspondant a celle en parametre sans son premier element */
LListes suiteLL(LListes l);

/* modifie la Liste de liste en parametre: le premier element est retire */
void depileLL(LListes* l);

/* ajoute l'élément x en tête de toute les listes */
LListes AETTL(int x, LListes l);

/* ajoute l'élément x dans toute les positions d'une liste */
LListes ATP(int x, Liste l);

/* ajoute l'élément x dans toute les positions des differentes listes de l */
LListes ATLTP(int x, LListes l);

/* Elle concaténe la liste de listes l1 et la liste de listes l2 */
LListes concat(LListes l1, LListes l2);

/* rend une liste de listes de toutes les permutations de [1..n] */
LListes Permutations(int n);

/* affichage simple en recursif d'une liste de listes */
void affiche_rec_LListes(LListes l);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVideLL(LListes *L)
{
    *L = NULL ;
}



bool estVideLL(LListes l)
{
    return l == NULL ;
}



Liste premierLL(LListes l)
{
    return l->liste ; 
}


LListes ajouteLL(Liste x, LListes l)
{
    LListes tmp = (LListes) malloc(sizeof(Blocs)) ;
    tmp->liste = x ;
    tmp->suivant = l ;
    *cs = *cs +1;
    return tmp ;
}


void empileLL(Liste x, LListes *L)
{
      *L = ajouteLL(x,*L) ; 
      *cs = *cs -1;
}



LListes suiteLL(LListes l)
{
    return l->suivant ;
}

void depileLL(LListes *L)
{
    LListes tmp = *L ;
    *L = suiteLL(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideLListes(LListes *L){  //j'ai remarqué qu'il m'était impossible de désallouer le dernier bloc d'une liste (erreur). 
                               //Je remarque aussi que j'ai 4 leaks alors que je suis censé en avoir 6, donc 2 ont été désalloué et 4 non.
    if(NOT(estVideLL(*L))){
        //VideListe(&(*L)->liste); //je remarque que le nombre de leaks baisse comme il faut mais ca produit une erreur
        *cs = *cs-1;
        depileLL(L);
        VideLListes(L);
    }
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/


void affiche_rec_LListes(LListes l)
{
    if(estVideLL(l))
        printf("\n");
    else
    {
        poup(premierLL(l));
        affiche_rec_LListes(suiteLL(l));
    }
}

void poupLL (LListes l)
{
        affiche_rec_LListes(l) ;
}

/*************************************************/
/*                                               */
/*    Le reste des fonctions pour permutation    */
/*                                               */
/*************************************************/

/*
Permutation(3) :
J'ai rajouter un compteur pour le type Liste et pour le type Listes (liste de listes), puis à la fin de l'execution de ma fonction permutation
j'ai un total de 16 mallocs effectués par permutation pour allouer des Liste et 20 mallocs effectués par permutation pour allouer des listes de listes.
Je pense qu'il ya une fuite mémoire sur les deux types car la fonction permutation s'appelle récursivement et à chaque fois appelle d'autres 
fonctions qui allouent de la mémoire pour créer des listes avec ajouteLL et ajoute : ils ne sont jamais dépilé après.
De plus, en utilisant la commande leaks sur le terminal, j'ai pu identifier 42 fuites mémoires au total dans le main.
J'ai ensuite optimisé au maximum mes fonctions pour éliminer (ou réduire) les fuites mémoires, pour cela, j'ai privilégier les empile par rapport
au ajoute ce qui m'a fait passer de 42 leaks à 4 leaks. De plus je n'utilise plus de malloc puisque empile ne crée pas une nouvelle liste à chaque
appel. 
Après optimisation j'ai 0 mallocs effectués pour les listes et 5 mallocs effectués pour les listes de listes qui sont dépilé et ramené à -1 puisqu'il ya 6 listes de liste.
Donc pour conclure, je n'ai plus de fuites mémoires.

*/

LListes AETTL(int x, LListes l){
    if(estVideLL(l)){
        return l;
    }
    else{
        Liste tmp = (l)->liste;
        empile(x, &tmp);
        depileLL(&l);
        LListes res = AETTL(x, l);
        empileLL(tmp, &res);
        return res;
    }
}

LListes ATP(int x, Liste l){
    if(estVide(l)){
        empile(x, &l);
        return ajouteLL(l,NULL);
    }
    else{
        empile(x, &l);
        LListes tmp = AETTL(premier(suite(l)), ATP(x, suite(suite(l))));
        empileLL(l, &tmp);
        return tmp;
    }

}

LListes ATLTP(int x, LListes l){
    if(estVideLL(l)){
        return l;
    }
    else{
        Liste tmp = premierLL(l);
        depileLL(&l);
        return concat(ATP(x, tmp), ATLTP(x, l));
    }
}

LListes concat(LListes l1, LListes l2){
    if(estVideLL(l1)){
        return l2;
    }
    else if(estVideLL(l2)){
        return l1;
    }
    else{
        Liste tmp = premierLL(l1);
        depileLL(&l1);
        LListes res = concat(l1, l2);
        empileLL(tmp, &res);
        return res;
    }
}

LListes Permutations(int n){
    if(n == 0){
        return ajouteLL(NULL,NULL);
    }
    else{
        return ATLTP(n, Permutations(n-1));
    }
}

//QUESTION 8 :

/*************************************************/
/*                                               */
/*          definition type listeBis             */
/*                                               */
/*************************************************/

typedef struct BlocBis
{
    int nombre;
    struct BlocBis *suivant;
    struct BlocBis **prec;
} BlocBis;

typedef BlocBis *ListeBis ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Listebis vide */
void initVideListeBis(ListeBis *L);

/* renvoie 1 si la Listebis en parametre est vide, 0 sinon */
bool estVideListeBis(ListeBis l);

/* renvoie le premier element de la Listebis en parametre */
int premierListeBis(ListeBis l);

/* renvoie une nouvelle Listebis correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
ListeBis ajouteListeBis(int x, ListeBis l, ListeBis *ptrL);

/* modifie la Listebis en parametre: x est ajoute comme premier element */
void empileListeBis(int x, ListeBis* L);

/* renvoie une nouvelle Listebis correspondant a celle en parametre sans son premier element */
ListeBis suiteListeBis(ListeBis l);

/* modifie la Listebis en parametre: le premier element est retire */
void depileListeBis(ListeBis* l);

/*  Elimination du dernier element  */
void VireDernier_iter_Bis (ListeBis *L);

/* renvoie le pointeur pred qui est pointée par p */
ListeBis determineBlocPointee(ListeBis l, struct BlocBis ***p);

/* retire le bloc qui est pointée par p */
void RetirerPPointee(ListeBis *l, struct BlocBis ***p);

/* affichage simple récursif d'une listeBis */
void affiches_rec_ListeBis(ListeBis l);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVideListeBis(ListeBis *L)
{
    *L = NULL ;
}

bool estVideListeBis(ListeBis l)
{
    return l == NULL ;
}

int premierListeBis(ListeBis l)
{
    return l->nombre ; 
}

ListeBis ajouteListeBis(int x, ListeBis l, ListeBis *ptrL){
    ListeBis tmp = (ListeBis) malloc(sizeof(BlocBis)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    tmp->prec = ptrL;
    if(!estVideListeBis(l)){
        (l->prec) = &(tmp->suivant);
    }
    return tmp ;
}
void empileListeBis(int x, ListeBis *L){
    *L = ajouteListeBis(x,*L, L) ; 
}

ListeBis suiteListeBis(ListeBis l)
{
    return l->suivant ;
}

ListeBis precListeBis(ListeBis l)
{
    return *l->prec ;
}

void depileListeBis(ListeBis *L)
{
    ListeBis tmp = *L ;
    *L = suiteListeBis(*L) ;
    (*L)->prec = L;
    free(tmp) ;
}

void VireDernier_iter_Bis (ListeBis *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiches_rec_ListeBis(ListeBis l)
{
    if(estVideListeBis(l))
        printf("\n");
    else
    {
        printf("%d ", premierListeBis(l));
        affiches_rec_ListeBis(suiteListeBis(l));
    }
}

void poupListeBis (ListeBis l)
{
        affiches_rec_ListeBis(l) ;
}

/*************************************************/
/*                                               */
/*    Le reste des fonctions pour la question    */
/*                                               */
/*************************************************/

ListeBis determineBlocPointee(ListeBis l, struct BlocBis ***p){
    ListeBis *tmp = &l;
    while(!estVideListeBis(*tmp)){
        if(premierListeBis(precListeBis(*tmp))  == premierListeBis(**p)){
            return precListeBis(*tmp);
        }
        else{
            *tmp = suiteListeBis(*tmp);
        }
    }
    return NULL;
}

void RetirerPPointee(ListeBis *l, struct BlocBis ***p){
    ListeBis x = determineBlocPointee(*l, p);
    ListeBis *lst = l;
    while(!estVideListeBis(*lst)){ //tant que la liste n'est pas vide
        if(precListeBis(*lst) == x){ //si l'élement à enlever est le premier de la liste
            depileListeBis(lst); //depile
            break;
        }
        if(precListeBis(suiteListeBis(*lst)) == x){ //si l'élement pointée est le suivant
            if(estVideListeBis(suiteListeBis(suiteListeBis(*lst)))){ // si l'élement suivant est le dernier de la liste
                VireDernier_iter_Bis(lst);
                break;
            }
            else{
                ListeBis toRemove = (*lst)->suivant;
                (*lst)->suivant = (*lst)->suivant->suivant;
                ((*lst)->suivant)->prec = &((*lst)->suivant);
                free(toRemove);
                break;
            }
        }
        lst = &(*lst)->suivant;
    }
}


int main(int argc, char** argv){
    /*
    Liste l ;
    initVide (&l) ;
    empile(0, &l) ;
    empile(1, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(-2, &l) ;
    empile(9, &l) ;
    empile(6, &l) ;
    empile(-5, &l) ;
    empile(0, &l) ;
    empile(2, &l) ;
    poup(l);
    //printf(ZeroEnPositionUnOuDeuxOuTrois(l) ? "True\n" : "False\n");
    */

    /*
    LListes l = Permutations(3);
    poupLL(l);
    printf("le nombre de malloc pour liste : %d\n", compteurListe);
    printf("le nombre de malloc pour liste de listes : %d\n", compteurLListes);
    VideLListes(&l);
    printf("le nombre de malloc pour liste : %d\n", compteurListe);
    printf("le nombre de malloc pour liste de listes : %d\n", compteurLListes);
    */

    /*
    //Testes ListeBis :
    ListeBis l ;
    initVideListeBis (&l) ;
    empileListeBis(4, &l) ;
    empileListeBis(5, &l) ;
    empileListeBis(6, &l) ;
    empileListeBis(7, &l) ;
    empileListeBis(8, &l) ;
    empileListeBis(9, &l) ;
    poupListeBis(l);
    RetirerPPointee(&l, &(l->suivant->suivant->suivant->suivant->suivant->prec));
    poupListeBis(l);
    RetirerPPointee(&l, &(l->suivant->suivant->suivant->prec));
    poupListeBis(l);
    RetirerPPointee(&l, &(l->prec));
    poupListeBis(l);
    */

    return 0;
}




