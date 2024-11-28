
#include<stdio.h>

typedef struct{
    int id;
    int burst;
    int arrival;
    int turnaround;
    int prior;
    int wait;
    int rem_burst;
    int is_start=0;
    int is_end = 0;
}process;

void SRTF(process p[],int n){

    int completed = 0;
    int current = 0;
   



    while(completed<n){

        int priority = INT_MIN;
        int min_ind = -1;

        for(int i = 0;i<n;i++){
        if(p[i].arrival<=current && p[i].rem_burst>0 && p[i].prior>priority)
            min_ind = i;
            min = p[min_ind].rem_burst;
        }

        if(min_ind==-1){
            current++;
            continue;
        }
        else{
            printf("P%d -(%d-%d)",p[min_ind].id,current,current++);
            
            p[min_index].rem_burst-=1;
            
            if(p[min_ind].rem_burst ==0){
                
                p[min_ind].turnaround = current - p[min_ind].arrival ;
                p[min_ind].wait = p[min_ind].turnaround - p[min_ind].burst ;
                completed++;
            }
            

        }
    }
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n", p[i].id,
               p[i].arrival,
               p[i].burst,
               p[i].wait,
               p[i].turnaround
            );
    }

}
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter the arrival time of process P%d: ", p[i].id);
        scanf("%d", &p[i].arrival);
        printf("Enter the burst time of process P%d: ", p[i].id);
        scanf("%d", &p[i].burst);
        p[i].rem_burst = p[i].burst

    }

    SRTF(p, n);

    return 0;
}