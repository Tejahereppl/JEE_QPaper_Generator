#include<stdio.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int response_time;
    int remaining_time;
    bool is_started;
    bool is_completed;

}Process;


void srtf(Process process[],int n){
    int current_time=0;
    int completed=0;
    for(int i=0;i<n;i++){
        process[i].remaining_time=process[i].burst_time;
    }

    while(completed!=n){
        int min_index=-1;
        int min_burst=INT_MAX;
        for(int i=0;i<n;i++){
            if(process[i].arrival_time<=current_time && process[i].remaining_time>0 && process[i].remaining_time<min_burst){
                min_index=i;
                min_burst=process[i].remaining_time;
            }
        }

        if(min_index==-1){
            current_time++;
            continue;
        }
        else{
            if(!process[min_index].is_started){
                process[min_index].is_started=true;
                process[min_index].response_time=current_time-process[min_index].arrival_time;
            }
            current_time++;
            printf("P%d %d\n",process[min_index].process_id,current_time);
            process[min_index].remaining_time--;
            
            if(process[min_index].remaining_time==0){
                process[min_index].completion_time=current_time;
                process[min_index].turnaround_time=process[min_index].completion_time-process[min_index].arrival_time;
                process[min_index].waiting_time=process[min_index].turnaround_time-process[min_index].burst_time;
                process[min_index].is_completed=true;
                completed++;
            }
        }
    }
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n", process[i].process_id,
               process[i].arrival_time,
               process[i].burst_time,
               process[i].waiting_time,
               process[i].turnaround_time,
               process[i].response_time);
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
    }

    srtf(processes, n);

    return 0;
}