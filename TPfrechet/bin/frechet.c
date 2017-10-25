#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

void lecture_fichier(char *nom_fichier, int *tableauP, int *tableauQ){
  FILE *fic;
  fic = fopen(nom_fichier, "r");
  uint32_t n;
  uint32_t m;
  if (fic != NULL){
    fscanf(fic, "%d %d ", &n, &m);
    tableauP = malloc(sizeof(int)*(2*n));
    tableauQ = malloc(sizeof(int)*(2*m));
    for(uint32_t i=0; i<2*n; i++){
      fscanf(fic, "%d", &tableauP[i]);
    }
    for(uint32_t j=0; j<2*m; j++){
      fscanf(fic, "%d", &tableauP[j]);
    }
  }
  fclose(fic);
}


void ecrire_fichier(char *nom_fichier, int *tab_optim, int taille_tableau, int dist_frechet, int long_optim){
  FILE *fic;
  fic = fopen(nom_fichier, "w"); //ATTENTION MODIFIER LE NOM DE FICHIER POUR QUE CE SOIT LE MEME QUE L'ENTRÉE
  fprintf(fic, "%f\n", pow(dist_frechet,2));
  fprintf(fic, "%d\n", long_optim);
  for(uint32_t i = 0 ; i < taille_tableau ; i++){
    fprintf(fic, "%d ", tab_optim[i]);
  }
  fclose(fic);
}



char* creation_nom_fichier_out(char* nom_fichier_in){
  //A voir si les fichiers d'entrés sont en .in ou pas ???
  char* nom_fichier_out = strcat(nom_fichier_in, ".out");
  return(nom_fichier_out);
}


int main(int argc, char* argv[]){
  int* tableauP;
  int* tableauQ;
  char* nom_fichier_out = creation_nom_fichier_out(argv[1]);
  lecture_fichier(argv[1], tableauP, tableauQ);
  int tab[4] = {1,2,3,4};
  int taille_tableau = 4;
  ecrire_fichier(nom_fichier_out, tab, 4, 10, 111);
  return(0);
}
