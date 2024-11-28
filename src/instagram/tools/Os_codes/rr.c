#include<stdio.h>

typedef struct{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaroun_time;
    int remaining_burst;
    int completion_time;
}Process;

void rr(Process process[],int n,int tq){
    int current_time=0;
    int completed=0;
    int queue[100];
    int rear=0;
    int front=0;

    for(int i=0;i<n;i++){
        process[i].remaining_burst=process[i].burst_time;
    }

    while(completed!=n){
        for(int i=0;i<n;i++){
            if(process[i].arrival_time<=current_time && process[i].remaining_burst>0){
                int in_queue=0;
                for(int j=front;j<rear;j++){
                    if(queue[j]==i){
                        in_queue=1;
                    }
                }
                if(in_queue==0){
                    queue[rear++]=i;
                }
            }
        }

        if(front<rear){
            Process* temp=&process[queue[front]];
            if(temp->remaining_burst<=tq){
                printf("P%d,(%d-%d)",temp->process_id,current_time,current_time+temp->remaining_burst);
                current_time+=temp->remaining_burst;
                temp->completion_time=current_time;
                temp->turnaroun_time=temp->completion_time-temp->arrival_time;
                temp->waiting_time=temp->turnaroun_time-temp->burst_time;
                temp->remaining_burst=0;
                completed++;
                front++;
            }
            else{
                printf("P%d,(%d-%d)",temp->process_id,current_time,current_time+tq);
                current_time+=tq;
                for(int i=0;i<n;i++){
                    if(process[i].arrival_time<=current_time && process[i].remaining_burst>0){
                        int in_queue=0;
                        for(int j=front;j<rear;j++){
                            if(queue[j]==i){
                                in_queue=1;
                            }
                        }
                        if(in_queue==0){
                            queue[rear++]=i;
                        }
                    }
                }
                temp->remaining_burst-=tq;
                queue[rear++]=queue[front];
                front++;
            }
        }
        else{
            current_time++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", process[i].process_id, process[i].arrival_time,
               process[i].burst_time, process[i].waiting_time, process[i].turnaroun_time);
    }

}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time of process P%d: ", processes[i].process_id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time of process P%d: ", processes[i].process_id);
        scanf("%d", &processes[i].burst_time);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    rr(processes, n, time_quantum);

    return 0;
}