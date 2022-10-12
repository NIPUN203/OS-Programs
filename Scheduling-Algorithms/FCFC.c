#include<stdio.h>
#include<stdlib.h>
struct Process{
 int pid,at,bt,ct,wt,st,rt,tat;
};
void sort(struct Process *p,int n){
 for(int i=0;i<n;i++){
 for(int j=i+1;j<n;j++){
 if(p[i].at > p[j].at){
 struct Process temp=p[i];
 p[i]=p[j];
 p[j]=temp;
 }
 }
 }
}
int main(){
 int n;
 printf("Enter the number of process: ");
 scanf("%d",&n);
 struct Process p[n];
 for(int i=0;i<n;i++){
 printf("Enter the arrival and burst time for process ID %d: ",i+1);
 scanf("%d%d",&p[i].at,&p[i].bt);
 p[i].pid=i+1;
 }
 int totalTAT=0,totalWT=0,idealTime=0,cycleLength=0;
 float averTAT=0,averWT=0,cpuUtilization=0,throughPut=0;
 sort(p,n);
 p[0].st=p[0].at;
 p[0].ct=p[0].at+p[0].bt;
 p[0].tat=p[0].ct-p[0].at;
 p[0].wt=0;
 p[0].rt=p[0].st-p[0].at;

 totalTAT+=p[0].tat;
 for(int i=1;i<n;i++){
 if(p[i-1].ct < p[i].at){
 p[i].st=p[i].at;
 p[i].ct=p[i].at+p[i].bt;
 idealTime+=p[i].at-p[i-1].ct;
 }
 if(p[i-1].ct <= p[i].at){
 p[i].st=p[i].at;
 p[i].ct=p[i].at+p[i].bt;
 }
 else{
 p[i].st=p[i-1].ct;
 p[i].ct=p[i-1].ct+p[i].bt;
 }
 p[i].tat=p[i].ct-p[i].at;
 p[i].wt=p[i].tat-p[i].bt;
 p[i].rt=p[i].st-p[i].at;
 totalTAT+=p[i].tat;
 totalWT+=p[i].wt;
 }
 cycleLength=p[n-1].ct-p[0].st;
 cpuUtilization=((float)(cycleLength-idealTime)/(float)cycleLength)*100;
 throughPut=(float)n/(float)cycleLength;
 averTAT=(float)totalTAT/(float)n;
 averWT=(float)totalWT/(float)n;
 printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
 for(int i=0;i<n;i++){
 printf("P-%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
 }
 printf("\nTotal Turn Around Time: %d\n",totalTAT);
 printf("Average Turn Around Time: %f\n",averTAT);
 printf("Total Waiting Time: %d\n",totalWT);
 printf("Average Waiting Time: %f\n",averWT);
 printf("Cycle Length: %d\n",cycleLength);
 printf("Ideal Time: %d\n",idealTime);
 printf("CPU Utilization: %f percentage\n",cpuUtilization);
 printf("ThrorughPut: %f\n",throughPut);
}