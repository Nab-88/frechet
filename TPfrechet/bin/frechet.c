#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int max(int a, int b) {
  if (b < a) {
    return a;
  }
  return b;
}

typedef struct element element;

struct element{
  int val;
  struct element *next;
};
typedef element* llist;


llist ajouterEnTete(llist liste, int valeur){
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->val = valeur;
    nouvelElement->next = liste;
    return nouvelElement;
}

llist ajouterEnFin(llist liste, int valeur){
    element* nouvelElement = malloc(sizeof(element));
    nouvelElement->val = valeur;
    nouvelElement->next = NULL;
    if(liste == NULL){
        return nouvelElement;
    }
    else{
        element* temp=liste;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nouvelElement;
        return liste;
    }
}

llist element_i(llist liste, int indice){
    int i;
    for(i=0; i<indice && liste != NULL; i++){
        liste = liste->next;
    }
    if(liste == NULL){
        return NULL;
    }
    else{
        return liste;
    }
}

void lecture_taille(char *nom_fichier, int *n, int *m){
  FILE *fic;
  fic = fopen(nom_fichier, "r");
  if (fic != NULL){
    fscanf(fic, "%d %d ", n, m);
  }
  fclose(fic);
}

void lecture_fichier(char *nom_fichier, int *tableauP, int *tableauQ, int *n, int *m){
  FILE *fic;
  fic = fopen(nom_fichier, "r");
  if (fic != NULL){
    fscanf(fic, "%d %d ", n, m);
    for(int i=0; i<2*(*n); i++){
      fscanf(fic, "%d", &tableauP[i]);
    }
    for(int j=0; j<2*(*m); j++){
      fscanf(fic, "%d", &tableauQ[j]);
    }
  }
  fclose(fic);
}


void ecrire_fichier(char *nom_fichier, llist parcours_optim, int taille_tableau, int dist_frechet){
  int long_optim = taille_tableau/2;
  FILE *fic;
  fic = fopen(nom_fichier, "w"); //ATTENTION MODIFIER LE NOM DE FICHIER POUR QUE CE SOIT LE MEME QUE L'ENTRÉE
  fprintf(fic, "%f\n", pow(dist_frechet,2));
  fprintf(fic, "%d\n", long_optim);
  for(int i = 0 ; i < taille_tableau ; i++){
    int valeur = element_i(parcours_optim, i)->val;
    fprintf(fic, "%d ", valeur);
  }
  fclose(fic);
}


char* creation_nom_fichier_out(char* nom_fichier_in){
  //A voir si les fichiers d'entrés sont en .in ou pas ???
  char* nom_fichier_out = strcat(nom_fichier_in, ".out");
  return(nom_fichier_out);
}

int calcul_distance(int *tableauP, int *tableauQ, int indiceP, int indiceQ){
  return (pow((tableauP[indiceP*2] - tableauQ[indiceQ*2]),2) + pow((tableauP[indiceP*2+1] - tableauQ[indiceQ*2+1]),2));
}

int frechet(int *tableauP, int *tableauQ, int n, int m){
  int **tableauFrechet;
  tableauFrechet = malloc(sizeof(*tableauFrechet)*n);
  for(int i=0; i < n*m; i++){
    tableauFrechet[i] = malloc(sizeof(int)*m);
  }
  // TableauFrechet[i][j] = Df(i,j)
  tableauFrechet[0][0] = calcul_distance(tableauP, tableauQ, 0, 0);

  for (int i=1; i<m; i++){
      int maxi = calcul_distance(tableauP, tableauQ, 0, 1);
      for (int j=0; j<=i; j++){
          printf("Dist maxi : %i \n", maxi);
          printf("nouv dist : %i \n", calcul_distance(tableauP, tableauQ, 0, j));
          if (calcul_distance(tableauP, tableauQ, 0, j) > maxi){
              maxi = calcul_distance(tableauP, tableauQ, 0, j);
          }
      }
      tableauFrechet[0][i] = maxi;
  }

   for (int i=1; i<n; i++){
      int maxi = calcul_distance(tableauP, tableauQ, 1, 0);
      for (int j=0; j<=i; j++){
          if (calcul_distance(tableauP, tableauQ, j, 0) > maxi){
              maxi = calcul_distance(tableauP, tableauQ, j, 0);
          }
      }
      tableauFrechet[i][0] = maxi;
  }

  for (int i=1; i < n; i++){
    for (int j=1; j < m; j++){
      tableauFrechet[i][j] = max(calcul_distance(tableauP, tableauQ, i, j), min(tableauFrechet[i-1][j], min(tableauFrechet[i][j-1], tableauFrechet[i-1][j-1])));
    }
  }
  /*for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      printf("tab[i][j] : %i", tableauFrechet[i][j]);
    }
  }
  printf("\n");*/
  return (tableauFrechet[n-1][m-1]);
}



llist calcul_parcours_optimal(int *tableauP, int *tableauQ, int n, int m, int *taille_tab_opti){
  int dist_frech = frechet(tableauP, tableauQ, n, m);
  llist parcours_optim = NULL;
  ajouterEnTete(parcours_optim, 1);
  ajouterEnFin(parcours_optim, 1);
  int i = 1;
  int j = 1;
  *taille_tab_opti = 0;
  while((i != n) & (j != m)){
    if(i == n){
        j++;
        ajouterEnFin(parcours_optim, i);
        ajouterEnFin(parcours_optim, j);
      }
    else if(j == n){
        i++;
        ajouterEnFin(parcours_optim, i);
        ajouterEnFin(parcours_optim, j);
    }
    else if (frechet(tableauP, tableauQ, i+1, j+1) <= dist_frech){
      i++;
      j++;
      ajouterEnFin(parcours_optim, i);
      ajouterEnFin(parcours_optim, j);
    }
    else if (frechet(tableauP, tableauQ, i+1, j) <= dist_frech){
      i++;
      ajouterEnFin(parcours_optim, i);
      ajouterEnFin(parcours_optim, j);
    }
    else if (frechet(tableauP, tableauQ, i, j+1) <= dist_frech){
        j++;
        ajouterEnFin(parcours_optim, i);
        ajouterEnFin(parcours_optim, j);
      }
    *taille_tab_opti += 2;
  }
  return (parcours_optim);
}


int main(int argc, char* argv[]){
  int *n = malloc(sizeof(int));
  int *m = malloc(sizeof(int));
  //char* nom_fichier_out = creation_nom_fichier_out(argv[1]);
  // char* nom_fichier_out = creation_nom_fichier_out("test1");
  int *taille_tab_opti = malloc(sizeof(int));
  lecture_taille("benchmark1", n, m);
  printf(" n : %d, m : %d \n", *n, *m);
  int* tableauP = malloc(sizeof(int)*2*(*n));
  int* tableauQ = malloc(sizeof(int)*2*(*m));
  lecture_fichier("benchmark1", tableauP, tableauQ, n, m);
/*
  printf("Affichage de P \n");
  for (int i=0; i<2*(*n); i++){
      printf("%d /", tableauP[i]);
  }
  printf("\n");
  printf("Affichage de Q \n");
  for (int i=0; i<2*(*m); i++){
      printf("%d /", tableauQ[i]);
  }
  printf("\n");
  */
  //llist parcours_opti = calcul_parcours_optimal(tableauP, tableauQ, *n, *m, taille_tab_opti);
  int dist_frechet = frechet(tableauP, tableauQ, *n, *m);
  printf("distance de frechet :%i", dist_frechet);
  printf("\n");
  //ecrire_fichier("test.out", parcours_opti, *taille_tab_opti, dist_frechet);
  return EXIT_SUCCESS;
}
