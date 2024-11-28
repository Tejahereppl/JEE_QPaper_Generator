#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completion_time;
    int priority;
}Process;

void priorpree(Process process[],int n){
    int current_time=0;
    int completed=0;

    

    for (int i = 0; i < n; i++) {
        process[i].remaining_time = process[i].burst_time;
        process[i].waiting_time = 0; // Initialize waiting time
        process[i].turnaround_time = 0; // Initialize turnaround time
    }

    while(completed!=n){
        int index=-1;
        int prior=INT_MIN;
        for(int i=0;i<n;i++){
            if(process[i].arrival_time<=current_time && process[i].remaining_time>0 && process[i].priority>prior){
                index=i;
                prior=process[i].priority;
            }
        }

        if(index==-1){
            current_time++;
            continue;
        }
        else{
            current_time++;
            process[index].remaining_time--;
            printf("P%d %d\n",process[index].process_id,current_time);

            if(process[index].remaining_time==0){
                process[index].completion_time=current_time;
                process[index].turnaround_time=process[index].completion_time-process[index].arrival_time;
                process[index].waiting_time=process[index].turnaround_time-process[index].burst_time;
                completed++;
            }
        }
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t\n", process[i].process_id,
               process[i].arrival_time, process[i].burst_time,
               process[i].priority, process[i].waiting_time,
               process[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter the arrival time of process P%d: ", processes[i].process_id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time of process P%d: ", processes[i].process_id);
        scanf("%d", &processes[i].burst_time);
        printf("Enter the priority of process P%d (higher number = higher priority): ", processes[i].process_id);
        scanf("%d", &processes[i].priority);
    }

    priorpree(processes, n);

    return 0;
}