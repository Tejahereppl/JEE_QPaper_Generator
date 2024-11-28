#include<stdio.h>
#include<stdbool.h>
#include<limits.h>


typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
   

    int complete;
    bool isdone;
   
} process;


void sjf(process p[],int n){

    int completed = 0;
    int current = 0;
    for(int i=0;i<n;i++){
        p[i].isdone = false;
    }



    while(completed<n){

        int min = INT_MAX;
        int index = -1;

        for(int i = 0;i<n;i++){
            if(p[i].arrival_time<=0 && !p[i].isdone && p[i].burst_time<min){
                index = i;
                min = p[i].burst_time;
            }


        }
        if(index==-1){
            current++;
            continue;
        }
        
        else{
            printf("P%d - (%d-%d)",p[index].process_id,p[index].current,p[index].burst_time+current);
            p[i].complete = p[i].burst_time+current;
            p[i].turnaround_time = p[i].complete-p[i].arrival_time;
            p[i].waiting_time = p[i].turnaround_time-p[i].burst_time;
            p[i].isdone = true;

            current+=p[i].burst_time;
        }

    }
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n", processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].response_time);
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
    }

    sjf(p, n);

    return 0;
}