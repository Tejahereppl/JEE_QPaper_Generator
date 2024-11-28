#include<stdio.h>

typedef struct{
    int id;
    int burst;
    int arrival;
    int rem_burst;
    int wait;
    int turn;
}process;
process p[30];

void rr(int n,int tq){

    int completed = 0;
    int current = 0;
    int queue[100];
    int front =0;
    int rear = 0;

    for(int i = 0;i<n;i++){
        p[i].rem_burst = p[i].burst;
    }

    while(completed<n){
        for(int i=0;i<n;i++){
            int in_queue = 0;
            if(p[i].arrival<=current && p[i].rem_burst>0){
                for(int j = front;j<rear;j++){
                    if(queue[j]==i){
                        in_queue =1;
                        break;
                    }
                }
                if(!in_queue){
                    queue[rear++] = i;

                }
            }
        }

        if(front<rear){
            process* temp = &p[queue[front]];

            if(temp->rem_burst<=tq){
                printf("P%d (%d-%d)",temp->id,current,current+temp->rem_burst);
                current +=temp->rem_burst;
                temp->rem_burst = 0;
                temp->turn = current-temp->arrival;
                temp->wait = temp->turn- temp->burst;
                completed++;
                front++;
            }
            else{
                printf("P%d (%d-%d)",temp->id,current,current+tq);
                    current+=tq;
                    for(int i=0;i<n;i++){
                        int in_queue = 0;
                        if(p[i].arrival<=current && p[i].rem_burst>0){
                            for(int j = front;j<rear;j++){
                                if(queue[j]==i){
                                    in_queue =1;
                                    break;
                                }
                            }
                            if(!in_queue){
                                queue[rear++] = i;

                            }
                        }
                    }
                    temp->rem_burst-=tq;
                    queue[rear++] = queue[front];
                    front++;



                
            }
        }
        else{
            current++;
        }
    }
    printf("process id\tarrival_time\tburst_time\twaiting time\tturnaround time\n");
    for(int i = 0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].arrival,p[i].burst,p[i].wait,p[i].turn);
    }
}
int main(){

    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);


    for (int i = 0; i < n; i++) {
        p[i].id = i ;
        printf("Enter arrival time of process P%d: ", p[i].id+1);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time of process P%d: ", p[i].burst);
        scanf("%d", &p[i].burst);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    rr( n, time_quantum);

    return 0;
}