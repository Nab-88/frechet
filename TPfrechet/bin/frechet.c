#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
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
      printf("%d", tableauP[i]);
      printf("\n");
    }
    for(uint32_t j=0; j<2*m; j++){
      fscanf(fic,"%d", &tableauQ[j]);
      printf("%d", tableauQ[j]);
      printf("\n");
    }
  }
  fclose(fic);
  return 0;
}
