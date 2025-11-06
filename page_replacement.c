#include <stdio.h>

int findLRU(int time[], int n){
    int i, min = time[0], pos = 0;
    for(i=1;i<n;i++) if(time[i]<min){min=time[i]; pos=i;}
    return pos;
}

int main(){
    int pages[30], n, frames[10], f, i, j, k, time[10], count=0, flag1, flag2, pos, faults;
    printf("Enter number of pages: "); scanf("%d",&n);
    printf("Enter reference string: "); for(i=0;i<n;i++) scanf("%d",&pages[i]);
    printf("Enter number of frames (min 3): "); scanf("%d",&f);

    // FCFS
    faults=0; k=0;
    for(i=0;i<f;i++) frames[i]=-1;
    for(i=0;i<n;i++){
        flag1=flag2=0;
        for(j=0;j<f;j++) if(frames[j]==pages[i]){flag1=flag2=1;break;}
        if(flag1==0){frames[k]=pages[i]; k=(k+1)%f; faults++;}
    }
    printf("\nFCFS Page Faults: %d\n",faults);

    // LRU
    for(i=0;i<f;i++) frames[i]=-1;
    faults=0; count=0;
    for(i=0;i<n;i++){
        flag1=flag2=0;
        for(j=0;j<f;j++) if(frames[j]==pages[i]){flag1=flag2=1; count++; time[j]=count;}
        if(flag1==0){
            for(j=0;j<f;j++) if(frames[j]==-1){frames[j]=pages[i]; flag2=1; count++; time[j]=count; faults++; break;}
        }
        if(flag2==0){pos=findLRU(time,f); frames[pos]=pages[i]; count++; time[pos]=count; faults++;}
    }
    printf("LRU Page Faults: %d\n",faults);

    // Optimal
    for(i=0;i<f;i++) frames[i]=-1;
    faults=0;
    for(i=0;i<n;i++){
        flag1=flag2=0;
        for(j=0;j<f;j++) if(frames[j]==pages[i]){flag1=flag2=1; break;}
        if(flag1==0){
            for(j=0;j<f;j++) if(frames[j]==-1){frames[j]=pages[i]; flag2=1; faults++; break;}
        }
        if(flag2==0){
            int future[10]={0};
            for(j=0;j<f;j++){
                for(k=i+1;k<n;k++){
                    if(frames[j]==pages[k]){future[j]=k; break;}
                }
                if(future[j]==0) future[j]=9999;
            }
            int max=0; pos=0;
            for(j=0;j<f;j++) if(future[j]>max){max=future[j]; pos=j;}
            frames[pos]=pages[i]; faults++;
        }
    }
    printf("Optimal Page Faults: %d\n",faults);
}
