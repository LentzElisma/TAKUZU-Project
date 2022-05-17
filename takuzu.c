//
// Created by Lek_Kervin on 09/04/2022.
//

#include "takuzu.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
# include <unistd.h>



void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}
///////////////////////////////////////////////////////////////////////////////////
int ** creer_matrice(int size) {
    int** Mat;
    int i;

    Mat = (int **) malloc(size * sizeof(int *));
    for ( i = 0; i < size; i++) {
        Mat[i] = (int *) malloc(size* sizeof(int));
    }
    return Mat;
}
////////////////////////////////////////////////////////////////
int nombre_case_vide(int** grille_jeu,int taille) {
    int i, j, cpt = 0;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            if ((grille_jeu[i][j] != 0) && (grille_jeu[i][j] != 1)) {
                cpt ++;
            }
        }
    }
    return cpt;
}
//////////////////////////////////////////////////////////////
void verifier_les_0_et_les_1(int **Matrice, int taille) {
    int i;
    int j = 0, cpt_ligne = 0, cpt_colonne = 0;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            cpt_ligne = cpt_ligne + Matrice[i][j];
        }
        if (cpt_ligne > 2) {
            printf("Les saisies faites a la  ligne  %d sont incorrectes ",i++);
        } else
            printf("Les saisies faites a la  ligne %d sont correctes",i++);
    }
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++) {
            cpt_colonne = cpt_colonne + Matrice[i][j];
        }
        if (cpt_colonne > 2) {
            printf("Les saisies faites a la  ligne  %d sont incorrectes ",j++);
        } else
            printf("Les saisies faites a la  ligne  %d sont correctes ",j++);
    }
}
////////////////////////////////////////////////////////////
int **remplir_matrice_4x4(int size){
    int i, j;
    int Matrice_solution_4X4 [4][4]={
            {1,0,0,1},
            {1,0,1,0},
            {0,1,1,0},
            {0,1,0,1}
    };
    int** Matrice_sol_4x4= creer_matrice(size);

    for (i=0;i<size;i++) {
        for (j = 0; j < size; j++) {
            Matrice_sol_4x4[i][j] = Matrice_solution_4X4[i][j];
        }
    }

    return Matrice_sol_4x4;
}
////////////////////////////////////////////////////////////
int ** remplir_matrice_8x8 (int size){
    int i, j;
    int Matrice_solution_8x8[8][8] = {
            {1, 0, 1, 1, 0, 1, 0, 0},
            {1, 0, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 1, 0},
            {1, 0, 1, 0, 0, 1, 0, 1},
            {0, 1, 0, 0, 1, 0, 1, 1},
            {0, 0, 1, 1, 0, 1, 1, 0},
            {1, 1, 0, 0, 1, 0, 0, 1}
    };
    int**Matrice_sol_8x8= creer_matrice(size);
    for (i=0;i<size;i++) {
        for (j = 0; j < size; j++) {
            Matrice_sol_8x8[i][j] = Matrice_solution_8x8[i][j];
        }
    }
    return Matrice_sol_8x8;
}
////////////////////////////////////////////////////////////
void regles_du_jeu() {
    printf("-----------------------------------------\n");
    printf(" | Lisez attentivement les regles du jeu |\n");
    printf("-----------------------------------------\n");
    printf("1-Dans une ligne, il doit y avoir autant de 0 que de 1. \n");
    printf("2-Dans une colonne, il doit y avoir autant de 0 que de 1. \n");
    printf("3-Il ne peut pas y avoir deux lignes identiques dans une grille. \n");
    printf("4-Il ne peut pas y avoir deux colonnes identiques dans une grille. \n");
    printf("5-Dans une ligne ou une colonne, il ne peut y avoir plus de deux 0 ou deux 1 à la suite. \n");
}
///////////////////////////////////////////////////////////
void afficher_matrice(int** Matrice, int dim) {
    int i, j;
    char caractere='a';
    for (i=0;i<dim;i++){
        printf ("  %d ",i); // bordure
    }
    printf("\n");
    for (i = 0; i < dim; i++) {
    }
    for (i = 0; i < dim; i++) {
        printf("%c||",caractere); // bordure
        for (j = 0; j < dim; j++) {
            if (Matrice[i][j]==9){
                printf("_ |");
            } else
            {
                printf(" %d |", Matrice[i][j]);
            }
        } caractere++;
        printf("\n");
        printf("  -----------------------------\n");

    }


}
//////////////////////////////////////////////////////////
int ** creer_masque_manuel(int size) {
    int i, j, valeur;
printf("-- Masque manuel --\n");
    int **masque = creer_matrice(size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            do {
                printf("Saisir les donnees du masque pour la ligne: %d, et la colonne %d:\n",i,j);
                scanf("%d", &masque[i][j]);
            }
            while (masque[i][j] > 1 || masque[i][j] <0);
        }
    }
    return masque;
}
///////////////////////////////////////////////////////////
int ** creer_masque_aleatoire(int size) {
    int i, j;
    srand(time(NULL));
    int **masque;
    masque = creer_matrice(size);
    printf("-- Masque aleatoire --\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            masque[i][j] = rand() % 2;
        }

    }

    return masque ;
}
//////////////////////////////////////////////////////////
int** generer_jeu(int** solution,int** masque,int size){
    int i,j;
    printf("-- Grille de jeu --\n");
    int** grille_jeu= creer_matrice(size);
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(masque[i][j]==1){
                grille_jeu[i][j]=solution[i][j];
            } else{
                grille_jeu[i][j]=9;
            }
        }
    }
    return grille_jeu;
}
//////////////////////////////////////////////////////////////////////////
void saisir_chiffre_utilisateur(int **Matrice, int** solution, int taille) { // a completer
    int niveau_de_vie=3;
    int  nbe_trou;
    int ligne, valeur, colonne;
    int true;
    nbe_trou= nombre_case_vide(Matrice, taille);
    do {
        do {
            printf("Jouer 1 ou 0 :");
            scanf("%d", &valeur);
        } while (valeur != 1 && valeur != 0);

        do {
            printf("Saisir la ligne :");
            scanf("%d", &ligne);
        } while (ligne < 0 || ligne > taille-1);

        do {
            printf("Saisir la colonne  :");
            scanf("%d", &colonne);
        }while  (colonne < 0 || colonne > taille-1);

        Matrice[ligne][colonne] = valeur;
        afficher_matrice(Matrice, taille);
        if (Matrice[ligne][colonne] != solution[ligne][colonne]) {
            true = 1;
        }
        else{
            true = 2;
        }

Color (12,0);
        if (true == 1) {
            printf("La Saisie de la ligne %d,et de la colonne %d est non conforme\n ",ligne,colonne);
            printf("Faites un nouveau choix a la ligne %d,et de la colonne %d \n",ligne,colonne);
            nbe_trou++;
            niveau_de_vie = niveau_de_vie - 1;
            printf("Il vous reste %d essaies\n", niveau_de_vie);
            Color(15,0);
        } else {
                printf((" Good well !\n"));
                printf("\n");
                nbe_trou--;

        }
        if(nbe_trou==0){
            printf("-----------------------------------------------------------------\n");
            printf("      Vous avez gangner la partie, Felicitations !!!             \n");
            printf("-----------------------------------------------------------------\n");
            replay_game();

        }

if(niveau_de_vie==0){
    printf("-------------------------------------------------\n");
    printf("        Vous avez perdu la partie  !             \n");
    printf("-------------------------------------------------\n");
    replay_game();

}
    }
    while (nbe_trou>0);
}
//////////////////////////////////////////////////////////////////////////
void begin_the_game_1() {
    int dimension_choisie;
    char user_name[30];
    printf(" Saissez vote username :\n");
    scanf("%s", &user_name);

    Color(12, 0);
    printf(" |1| Bienvenue dans le jeu de Takuzu - %s - |0| \n", user_name);
    Color(15, 0);
    printf(" \n");

    do {
        printf("Saisir le type de la grille de jeu,  4 ou 8 : ");
        scanf("%d", &dimension_choisie);
    } while (dimension_choisie != 4 && dimension_choisie != 8);
    int** solution;
    if(dimension_choisie==4){
        solution = remplir_matrice_4x4(dimension_choisie);
    }
    else
    {
        solution = remplir_matrice_8x8(dimension_choisie);

    }

        int** masque = creer_masque_aleatoire(dimension_choisie);
    afficher_matrice(masque,dimension_choisie);
    printf("\n");
        int** grille_jeu = generer_jeu(solution, masque, dimension_choisie);
        afficher_matrice(grille_jeu, dimension_choisie);
        saisir_chiffre_utilisateur(grille_jeu, solution, dimension_choisie);

}
/////////////////////////////////////////////////////////////////////////
int** comparer_grille_jeu_et_grille_sol(int** grille,int** sol, int size){

    int i,j;
    if (size==4){
        sol= remplir_matrice_4x4(size);
    }else{
        sol= remplir_matrice_8x8(size);
    }
    if (grille[i][j]!=sol[i][j]){
        printf("La Saisie de la ligne %d,et de la colonne %d est non conforme\n ",i,j);
        grille[i][j]=sol[i][j];
    }
return grille;
}
///////////////////////////////////////////////////////////////
int** remplir_grille_jeu_automatique(int** grille_jeu,int size) {
    int i,cpt, j;
    int niveau_de_vie = 3;
    int true = 0;
    Color(12, 0);
    do {
        printf("|------------------------------------------------------------------------------------|\n");
        printf("   Saisir la dimension de la grille de jeu a remplir automatiquement,  4x4 ou 8x8 : \n");
        printf("|------------------------------------------------------------------------------------|\n");
        scanf("%d", &size);
        Color(15, 0);
    } while (size != 4 && size != 8);
    int **solution;
  if (size == 4) {
       solution = remplir_matrice_4x4(size);
   } else {
       solution = remplir_matrice_8x8(size);
  }

    int **masque = creer_masque_aleatoire(size);
    afficher_matrice(masque, size);
    grille_jeu = generer_jeu(solution, masque, size);
    afficher_matrice(grille_jeu, size);

    for (i = 0; i < size ; i++) {
        for (j = 0; j < size ; j++) {
            if ((grille_jeu[i][j] != 0) && (grille_jeu[i][j] != 1)) {
                grille_jeu[i][j] = rand() % 2;
            }
            sleep(3);
            afficher_matrice(grille_jeu, size);
            if (grille_jeu[i][j] != solution[i][j]){
                printf("La Saisie de la ligne %d,et de la colonne %d est non conforme\n ",i,j);
                niveau_de_vie--;
                printf("Il vous reste %d essaies\n",niveau_de_vie);
                grille_jeu[i][j]=solution[i][j];
            }
        }

if(niveau_de_vie==0){
    Color (12,0);
    printf("-------------------------------------------------\n");
    printf("        Vous avez perdu la partie  !             \n");
    printf("-------------------------------------------------\n");
    printf("\n");
    printf("-------------------------------------------------\n");
    printf("        Fin du remplissage automatique  !        \n");
    printf("-------------------------------------------------\n");
    replay_game();
    break;
Color(15,0);
}


}
    printf("-------------------------------------------------\n");
    printf("        Fin du remplissage automatique  !        \n");
    printf("-------------------------------------------------\n");
    return grille_jeu;
    }
////////////////////////////////////////////////////
    void menu_du_jeu() {
        int the_user_choice;
        int** M;
        Color(12, 0);
     int size;
        printf("|----------------------------------------------------------------------|\n");
        printf("                          |  Menu du jeu  |                          ");
        printf("\n");
        printf("Appuyez sur :\n"
               "");
        printf(" - 1 pour lancer le jeu avec un masque aleatoire.\n");
        printf(" - 2 pour lancer le jeu avec un masque manuel.\n");
        printf(" - 3 pour resoudre une grille automatique\n");
        printf(" - 4 pour quitter le jeu.\n");
        printf(" - 5 pour afficher les regles du jeu.\n");
        printf("|----------------------------------------------------------------------|\n");
        Color(15, 0);
        do {
            printf(" Saisir votre choix:");
            scanf("%d", &the_user_choice);
        } while ((the_user_choice < 1) || (the_user_choice > 6));

        switch (the_user_choice) {
            case 1:
                begin_the_game_1();
                printf("\n");
                break;
            case 2:
                begin_the_game_manuel();
                printf("\n");
                break;
            case 3:
                remplir_grille_jeu_automatique(M,size);
                printf("\n");
                break;
            case 4:
                printf(" oops !!! Vous avez fait le choix de quitter le jeu ; )\n");
                break;
            case 5:
                regles_du_jeu();
                break;
            default:
                break;


        }
    }
///////////////////////////////////////////////////
    void replay_game() {

        int choix;
        do {
            printf("Appuyez sur 1 ou 2 pour retourner au menu principal:\n");
            scanf("%d", &choix);
            Color(15,0);
        } while (choix!=1);
        switch (choix) {
            case 1:
                menu_du_jeu();
                printf("\n");
                break;
            case 2:
                menu_du_jeu();
                break;
            default:
                break;
        }
    }
//////////////////////////////////////////////
void begin_the_game_manuel() {
    int dimension_choisie;
    char user_name[30];
    printf(" Saissez vote username :\n");
    scanf("%s", &user_name);

    Color(12, 0);
    printf(" |1| Bienvenue dans le jeu de Takuzu - %s - |0| \n", user_name);
    Color(15, 0);
    printf(" \n");
    do {
        printf("Saisir le type de la grille de jeu,  4 ou 8 : ");
        scanf("%d", &dimension_choisie);
    } while (dimension_choisie != 4 && dimension_choisie != 8);
    int** solution;
    if(dimension_choisie==4){
        solution = remplir_matrice_4x4(dimension_choisie);
    }
    else
    {
        solution = remplir_matrice_8x8(dimension_choisie);

    }

    int** masque = creer_masque_manuel(dimension_choisie);
    afficher_matrice(masque,dimension_choisie);
    printf("\n");
    int** grille_jeu = generer_jeu(solution, masque, dimension_choisie);
    afficher_matrice(grille_jeu, dimension_choisie);
    saisir_chiffre_utilisateur(grille_jeu, solution, dimension_choisie);

}



