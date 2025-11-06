#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc<=1){ printf("No numbers received.\n"); return 0; }
    printf("Child (reverse): ");
    for(int i=argc-1;i>=1;i--) printf("%s ", argv[i]);
    printf("\n");
    return 0;
}
