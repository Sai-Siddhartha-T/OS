#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int main(){
    int n; printf("Enter count: "); if(scanf("%d",&n)!=1) return 0;
    int a[n]; printf("Enter %d numbers: ", n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    // simple bubble sort
    for(int i=0;i<n-1;i++) for(int j=0;j<n-i-1;j++)
        if(a[j]>a[j+1]) { int t=a[j]; a[j]=a[j+1]; a[j+1]=t; }

    pid_t pid = fork();
    if(pid<0) { perror("fork"); return 1; }
    if(pid==0){ // child will execve new program with sorted numbers
        char *argv[n+2];
        argv[0] = "./child";
        for(int i=0;i<n;i++){
            char *s = malloc(16);
            snprintf(s,16,"%d", a[i]);
            argv[i+1] = s;
        }
        argv[n+1] = NULL;
        execve("./child", argv, environ);
        perror("execve"); return 1;
    } else {
        wait(NULL);
        printf("Parent: child finished.\n");
    }
    return 0;
}
