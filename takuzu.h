//
// Created by Lek_Kervin on 09/04/2022.
//

#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H


#include <stdlib.h>

int choisir_dimension_grille(int dimension);
int ** creer_matrice(int);
int** remplir_matrice_4x4(int size);
int** remplir_matrice_8x8 (int size );
void begin_the_game_1();
int ** creer_masque_aleatoire(int size);
void verifier_les_0_et_les_1(int **Matrice, int );
void afficher_matrice(int** M,int dim);
int ** creer_masque_manuel(int size);
void regles_du_jeu();
void saisir_chiffre_utilisateur(int **Matrice, int** sol, int taille);
int **solution_4_4();
int **solution_8_8();
int** creer_grille_jeu(int** Matrice_sol, int** masque, int size);
int verif_ligne (int** Matrice, int size);
int verif_colonne(int** Matrice, int size);
void bienvenue();

void menu_game_loose();
int saisir_chiffre(int);
int** generer_jeu(int**,int**,int);
int nombre_case_vide(int** grille_jeu,int taille);
void replay_game();
void menu_du_jeu();
int** remplir_grille_jeu_automatique(int**  tableau_de_jeu,int size);
int** comparer_grille_jeu_et_grille_sol(int** grille,int**sol, int size);
void begin_the_game_manuel();
void choix_grille_utilisateur(int val);
#endif //TAKUZU_TAKUZU_H