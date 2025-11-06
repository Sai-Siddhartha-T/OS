#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];
    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&alloc[i][j]);
    printf("Enter Max Matrix:\n");
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&max[i][j]);
    printf("Enter Available Resources:\n");
    for(i=0;i<m;i++) scanf("%d",&avail[i]);

    int finish[n], safe[n], ind=0;
    for(i=0;i<n;i++) finish[i]=0;

    int need[n][m];
    for(i=0;i<n;i++) for(j=0;j<m;j++) need[i][j]=max[i][j]-alloc[i][j];

    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            if(!finish[i]){
                int flag=0;
                for(j=0;j<m;j++)
                    if(need[i][j]>avail[j]){flag=1;break;}
                if(!flag){
                    for(j=0;j<m;j++) avail[j]+=alloc[i][j];
                    safe[ind++]=i; finish[i]=1;
                }
            }
        }
    }

    int safeFlag=1;
    for(i=0;i<n;i++) if(!finish[i]) safeFlag=0;
    if(safeFlag){
        printf("\nSystem is in Safe State\nSafe Sequence: ");
        for(i=0;i<n;i++) printf("P%d ",safe[i]);
    } else printf("\nSystem is NOT in Safe State\n");
}
