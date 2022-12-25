#include <stdio.h>
#include <stdlib.h>

//Question 1 :
float exponential(){
    float res = 1.0; //le résultat à rendre.
    float res_pred = 0.0; // le résultat précédent.
    float fact = 1.0; //représente 1/i! à un instant donné.
    int i = 0;
    while((res_pred) != (res)){ // la boucle tourne tant que res et res_pred sont differents. S'ils sont identiques, cela veut dire qu'ils convergent
        if (i==0)
            i=1;
        fact /=  i;
        res_pred = res;//res aura un nouveau résultat donc on affecte à res_prec l'ancien resultat.
        res += fact;
        i++;//étant donnée que c'est une somme sur i, elle doit passer à la valeur suivante.
    }
    return res;
}

//Question 2 :
double suite(int n){
    if(n == 0){
        double y = exponential() - 1;
        printf("Le %d terme : %f\n", n , y);
        return y;
    }
    else{
        double y = n * suite(n-1) - 1;
        printf("Le %d terme : %f\n", n , y);
        return y;
    }
}

//Question 3 :
//CODE1: Récursif simple par n-1.
double pow_positif(double x, long n){ 
    if(n == 0){
        return 1.;
    }
    else{
        return x * pow_positif(x, n-1);
    }
}
double pow_negatif(double x, long n){ 
    if(n == 0){
        return 1.;
    }
    else{ 
        return 1./x * pow_negatif(x, n+1);
    }
}
double power1(double x, long n){ 
    if(n == 0){
        return 1.;
    }
    else{
        if(n > 0){ //puissance positive
            return pow_positif(x, n);
        }
        else{ //puissance négative
            return pow_negatif(x, n);
        }
    }
}
//CODE2: Itératif par n-1
double power2(double x, long n){
    double res = 1;
    if(n >= 0){
        for(int i = 0; i < n; i++){
            res *=  x;
        }
    }
    else{
        for(int i = 0; i > n; i--){
            res *=  1./x;
        }
    }
    return res;
}
//CODE3: Récursif terminal avec sous-procédure par n-1 
void pow3(double x, long n, double *r){
    if(n != 0){
        *r = (*r) * x;
        pow3(x, n-1, r);
    }
}
double power3(double x, long n){
    double r = 1;
    pow3(x, n, &r);
    return r;
}
//CODE4: Récursif terminal avec sous-fonction par n-1 
double pow4(double x, long n, double r){
    if(n == 0){
        return r;
    }
    else{
        return pow4(x, n-1, r*x);
    }
}
double power4(double x, long n){
    return pow4(x, n, 1.);
}
//CODE5: Récursif simple par n/2
double power5(double x, long n){
    if(n == 0){
        return 1.;
    }
    else{
        if(n % 2 == 0){
            return power5(x, n/2) * power5(x, n/2);
        }
        else{
            return x * power5(x, n/2) * power5(x, n/2);
        }
    }
}
//CODE6: Récursif simple par n/2
double power6(double x, long n){
    if(n == 0){
        return 1.;
    }
    else{
        double y = power6(x, n/2);
        if(n % 2 == 0){
            return y * y;
        }
        else{
            return x * y * y;
        }
    }
}
//CODE7: Récursif simple par n/2, variante
double power7(double x, long n){
    if(n == 0){
        return 1.;
    }
    else{
        if(n % 2 == 0){
            return power7(x*x, n/2);
        }
        else{
            return x * power7(x*x, n/2);
        }
    }
}
//CODE8: Récursif simple par n/2, avec sous-fonction
double pow8(double x, long n, double r){
    if(n == 0){
        return r;
    }
    else{
        if(n % 2 == 0){
            return pow8(x*x, n/2, r);
        }
        else{
            return pow8(x*x, n/2, r*x);
        }
    }
}
double power8(double x, long n){
    return pow8(x, n, 1.);
}
//CODE9: Récursif simple par n/2, avec sous-procédure
void pow9(double x, long n, double *r){
    if(n != 0){
        if(n % 2 == 1){
            *r = (*r) * x ;
        }
        pow9(x*x, n/2, r);
    }
}
double power9(double x, long n){
    double r = 1.;
    pow9(x, n, &r);
    return r;
}
//CODE10: Itératif par n/2
double power10(double x, long n){
    double r = 1.;
    long *p = &n;
    while(*p > 0){
        if(*p % 2 != 0){
            r = r * x;
        }
        (*p) = *p / 2;
        x = x*x;
    }
    return r;
}

//Question 4 :
int AckermannRecursive(int m, int n){
    if(m == 0){
        return n+1;
    }
    else{
        if(n == 0){
            return AckermannRecursive(m-1, 1);
        }
        else{
            return AckermannRecursive(m-1, AckermannRecursive(m, n-1));
        }
    }
}
int AckermannRecursoIterative(int m, int n){
    if(m == 0){
        return n+1;
    }
    else{
        int r = 1;
        for (int i = 1; i <= n+1; i++){
            r = AckermannRecursoIterative(m-1, r);
        }
        return r;
    }
}

//Question 5 :

//Fonction X(n) itérative :
float X1(int n){
    float res = 1;
    for(int i = 1; i <= n; i++){
        res = res + 2./res;
    }
    return res;
}
//Fonction X(n) récursive :
float X2(int n){
    if(n==0){
        return 1;
    }
    else{
        float y = X2(n-1);
        return y + 2./y;
    }
}
//Fonction X(n) récursive terminal avec sous-fonction :
float X3_aux(int n, float res){
    if(n == 0){
        return res;
    }
    else{
        return X3_aux(n-1, res + 2./res);
        
    }
}
float X3(int n){
    return X3_aux(n, 1);
}
//Fonction X(n) récursive terminal avec sous-procédure :
void X4_aux(int n, float *res){
    if(n == 0){
    }
    else{
        *res = *res + 2./(*res);
        X4_aux(n-1, res);
    }
}
float X4(int n){
    float res = 1;
    X4_aux(n, &res);
    return res;
}

int main(void){
    //Résultat question 1 :
    //printf("le résultat est : %f\n", exponential());

    /*
    Résultat question 2 :
    On constate au début que plus les termes avancent et plus la valeur de la suite diminue puis à partir d'un certain moment la valeur des
    termes augmente de manière considerable pour chacun des termes.
    mon explication est qu'au début la valeur de suite(n) est petite (inférieur à 1) et le fait de la multiplier avec un chiffre 
    inférieur à 10 n'a pas d'effet considérable sur la valeur, surtout qu'on soustrait de 1 par la suite.
    Ensuite à partir de 10, une valeur inferieur à 1 voit sa virgule se déplacer de 1 vers la droite ce qui fait passer le nombre de 
    inférieur  à 1 à supérieur à 1. Ensuite le fait de multiplier le réel à chaque terme par une valeur grande ne le fera que l'augmenter.
    Voilà pourquoi la suite baisse au début puis augmente de manière considérable à partir de 10.

    //suite(50);
    
    */

    //Résultat question 3 :
    /*
    //power1 et power2 qui fonctionnent avec n positif et négatif :
    double x = 2;
    long np = 8;
    long nn = -5;
    printf("Power1(%f,%ld) = %f\n", x, np, power1(x,np));
    printf("Power2(%f,%ld) = %f\n", x, np, power2(x,np));
    printf("Power1(%f,%ld) = %f\n", x, nn, power1(x,nn));
    printf("Power2(%f,%ld) = %f\n", x, nn, power2(x,nn));
    long n = 1000000000;
    //Je remarque que plus on augmente la valeur de n et plus la résultat tend vers exponentielle(1).
    //printf("Power1 (1+1/%ld, %ld) = %f\n", n, n, power1(1+1./n,n)); //"segmentation error – a memory violation" à partir de 10^6 car le programme tente d'accéder à un espace mémoire qui ne lui est pas permis.
    //printf("Power2 (1+1/%ld, %ld) = %f\n", n, n, power2(1+1./n,n)); //Fonctionne mais prend 10s pour renvoyer le résultat.
    //printf("Power3 (1+1/%ld, %ld) = %f\n", n, n, power3(1+1./n,n)); //"segmentation error – a memory violation" à partir de 10^6.
    //printf("Power4 (1+1/%ld, %ld) = %f\n", n, n, power4(1+1./n,n)); //"segmentation error – a memory violation" à partir de 10^6.
    //printf("Power5 (1+1/%ld, %ld) = %f\n", n, n, power5(1+1./n,n)); //Il tourne sans donner de résultat.
    //printf("Power6 (1+1/%ld, %ld) = %f\n", n, n, power6(1+1./n,n)); //Il renvoie le résultat immédiatement.
    //printf("Power7 (1+1/%ld, %ld) = %f\n", n, n, power7(1+1./n,n)); //Il renvoie le résultat immédiatement.
    //printf("Power8 (1+1/%ld, %ld) = %f\n", n, n, power8(1+1./n,n)); //Il renvoie le résultat immédiatement.
    //printf("Power9 (1+1/%ld, %ld) = %f\n", n, n, power9(1+1./n,n)); //Il renvoie le résultat immédiatement.
    //printf("Power10(1+1/%ld, %ld) = %f\n", n, n, power10(1+1./n,n)); //Il renvoie le résultat immédiatement.
    //Je ne pense pas que mon compilateur effectue l'optimisation du récursif terminal puisque les programmes semble s'arrêter avec un out of memory.
    */

    /* 
    Résultat question 4 :
    Je remarque que les deux fonction à savoir purement récursive et récurso-itérative donnent le bon résultat mais à partir d'un certain
    temps (environ 20s).
    Ensuite je remarque que les deux fonctions ont un comportement identique pour A(6,0) qui est qu'elles tournent sans jamais donner de
    résultat, elles n'affichent aucune erreur donc on peut supposer qu'elles effectuent les calculs et qu'elles vont s'arrêter au bout d'un 
    certain temps.
    Donc globalement, on peut dire que les deux versions ont bien un comportement identiques.
    //printf("%d\n", AckermannRecursive(5,0));
    */
    //Résultat question 5 :
    /*
    printf("Le résultat de X(100) avec X1 est : %f\n", X1(100));
    printf("Le résultat de X(100) avec X2 est : %f\n", X2(100));
    printf("Le résultat de X(100) avec X3 est : %f\n", X3(100));
    printf("Le résultat de X(100) avec X4 est : %f\n", X4(100));
    */
    return 0;
}