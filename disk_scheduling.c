#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n){for(int i=0;i<n-1;i++)for(int j=0;j<n-i-1;j++)if(a[j]>a[j+1]){int t=a[j];a[j]=a[j+1];a[j+1]=t;}}

void SSTF(int rq[],int n,int head){
    int done[50]={0}, count=0, pos, diff, min, total=0, cur=head;
    while(count<n){
        min=9999; pos=-1;
        for(int i=0;i<n;i++){
            diff=abs(rq[i]-cur);
            if(!done[i] && diff<min){min=diff; pos=i;}
        }
        done[pos]=1; total+=min; cur=rq[pos]; count++;
    }
    printf("SSTF Total Head Movement = %d\n", total);
}

void SCAN(int rq[],int n,int head,int disk){
    sort(rq,n); int total=0, pos, i;
    for(i=0;i<n;i++) if(rq[i]>=head){pos=i; break;}
    for(i=pos;i<n;i++) total+=abs(rq[i]-head), head=rq[i];
    total+=abs((disk-1)-head); head=disk-1;
    for(i=pos-1;i>=0;i--) total+=abs(rq[i]-head), head=rq[i];
    printf("SCAN Total Head Movement = %d\n", total);
}

void CLOOK(int rq[],int n,int head){
    sort(rq,n); int total=0, pos, i;
    for(i=0;i<n;i++) if(rq[i]>=head){pos=i; break;}
    for(i=pos;i<n;i++) total+=abs(rq[i]-head), head=rq[i];
    total+=abs(head-rq[0]);
    for(i=0;i<pos;i++) total+=abs(rq[i]-head), head=rq[i];
    printf("C-LOOK Total Head Movement = %d\n", total);
}

int main(){
    int n, head, disk;
    printf("Enter number of requests: "); scanf("%d",&n);
    int rq[n];
    printf("Enter request sequence: "); for(int i=0;i<n;i++) scanf("%d",&rq[i]);
    printf("Enter initial head position: "); scanf("%d",&head);
    printf("Enter disk size: "); scanf("%d",&disk);

    SSTF(rq,n,head);
    SCAN(rq,n,head,disk);
    CLOOK(rq,n,head);
}
