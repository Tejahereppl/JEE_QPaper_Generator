#include<stdio.h>
#include<stdbool.h>
#include<limits.h>


typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int priority;
   

    int complete;
    bool isdone;
   
} process;


void prioremp(process p[],int n){

    int completed = 0;
    int current = 0;
    for(int i=0;i<n;i++){
        p[i].isdone = false;
    }



    while(completed<n){

        int max = INT_MIN;
        int index = -1;

        for(int i = 0;i<n;i++){
            if(p[i].arrival_time<=current && !p[i].isdone && p[i].priority>max){
                index = i;
                max = p[i].priority;
            }


        }
        if(index==-1){
            current++;
            continue;
        }
        
        else{
            printf("P%d - (%d-%d)",p[index].process_id,current,p[index].burst_time+current);
            p[index].complete = p[index].burst_time+current;
            p[index].turnaround_time = p[index].complete-p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time-p[index].burst_time;
            p[index].isdone = true;

            current+=p[index].burst_time;
            completed++;
        }

    }
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].process_id,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].waiting_time,
               p[i].turnaround_time);
    }

}
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process p[n];
    for (int i = 0; i < n; i++) {
        p[i].process_id = i + 1;
        printf("Enter the arrival time of process P%d: ", p[i].process_id);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time of process P%d: ", p[i].process_id);
        scanf("%d", &p[i].burst_time);

        printf("Enter the priorty of the process P%d",p[i].process_id);
        scanf("%d", &p[i].priorty);
    }

    prioremp(p, n);

    return 0;
}