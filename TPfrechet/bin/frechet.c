#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int lecturefichier(char *nomfichier){
  FILE *fic;
  fic = fopen(argv[1], "r");
  uint32_t n;
  uint32_t m;
  if (fic != NULL){
    fscanf(fic, "%d %d ", &n, &m);
    int tableauP[n];
    int tableauQ[m];
    for(uint32_t i=0; i<2*n; i++){
      fscanf(fic,"%d", &tableauP[i]);
    }
    for(uint32_t j=0; j<2*m; j++){
      fscanf(fic,"%d", &tableauQ[j]);
    }
  }
  fclose(fic);
  return (tableauP, tableauQ);
}

// V2
