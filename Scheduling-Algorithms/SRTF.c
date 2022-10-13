#include<stdio.h>
#include<stdlib.h>

struct Process{
    int pid,at,bt,ct,tat,wt,st,rt;
};

void sort(struct Process *p,int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                struct Process temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

int FINDPOS(int t,struct Process *p,int n,int *rem){
    int minval=10000,minpos=-1;
    for(int i=0;i<n;i++){
        if(rem[i]>0 && minval>rem[i] && p[i].at<=t){
            minval=rem[i];
            minpos=i;
        }
    }
    
    return minpos;
}

int main(){
    int n;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    
    struct Process p[n];
    int rem[n];
    for(int i=0;i<n;i++){
        printf("\nEnter AT and BT:");
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].pid=i+1;
        p[i].st=-1;
    }
    
    sort(p,n);
    for(int i=0;i<n;i++)
    { rem[i]=p[i].bt;
    }
    int t=0,com=0;
    
    
    int totalTAT=0,totalWT=0,cycleLength=0,idealTime;
    float avgTAT=0,avgWT=0,cpuUti=0,throughPut=0;
    
    while(com<n){
        int pos=FINDPOS(t,p,n,rem);
        if(pos==-1){
           t++;
           idealTime++;
           continue;
        }
        else{
            if(p[pos].st==-1){
                p[pos].st=t;
            }
            rem[pos]--;
        }
        
        if(rem[pos]==0){
            com++;
            p[pos].ct=t+1;
            p[pos].tat=p[pos].ct-p[pos].at;
            p[pos].wt=p[pos].tat-p[pos].bt;
            p[pos].rt=p[pos].st-p[pos].at;
            
            totalTAT+=p[pos].tat;
            totalWT+=p[pos].wt;
        }
        t++;
    }
    
    cycleLength=t;
    avgTAT=(float)totalTAT/(float)n;
    avgWT=(float)totalWT/(float)n;
    cpuUti=((float)(cycleLength-idealTime)/(float)cycleLength)*100;
    throughPut=(float)cycleLength/(float)n;
    
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tST\tRT\n");
    for(int i=0;i<n;i++){
        printf("p-%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].st,p[i].rt);
    }
    
    printf("Average TAT:%f\n",avgTAT);
    printf("Average WT:%f\n",avgWT);
    printf("CPU Utilization:%f\n",cpuUti);
    printf("Throughput:%f\n",throughPut);
    printf("Ideal Time:%d",idealTime);
    
}
