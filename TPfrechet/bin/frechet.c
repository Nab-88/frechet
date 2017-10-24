#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
  printf("%s", argv[1]);
  FILE* fichier = NULL;
  fichier = fopen(argv[1], "r");
  uint32_t n;
  uint32_t m;
  char *poubelle;
  if (fichier != NULL){
    fscanf(fichier, "%d, %d", &n, &m);
    fscanf(fichier, "%s", poubelle);
    int tableauP[n];
    int tableauQ[m];

    for(uint32_t i=0; i<2*n; i++){
      fscanf(fichier,"%d", &tableauP[i]);
      printf("%d", tableauP[i]);
    }
    fscanf(fichier,"%s", poubelle);
    for(uint32_t j=0; j<2*m; j++){
      fscanf(fichier,"%d", &tableauQ[j]);
      printf("%d", tableauQ[j]);
    }

  }
  else{
    printf("pas de fichier");
  }
  fclose(fichier);
  return 0;
}
