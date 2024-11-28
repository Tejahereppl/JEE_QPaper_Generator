#include<stdio.h>


typedef struct{
    int id;
    int arrival;
    int burst;
    int wait;
    int turnaround;
    int complete;
}process;

void fcfs(process p[],int n){   
    
    for(int i =0;i<n-1;i++){
        for(int j=i;j<n-1;j++){
            if(p[j].arrival>p[j+1].arrival){
                process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    int time = p[0].arrival;
    printf("Process id\t\tarrival\t\tBurst\t\tTurnaround\t\twaitTime\n");

    for(int i = 0;i<n;i++){
        p[i].complete = time+p[i].burst;
        p[i].turnaround = p[i].complete-p[i].arrival;
        p[i].wait = p[i].turnaround-p[i].burst;
        
        time = p[i].complete;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].arrival,p[i].burst,p[i].turnaround,p[i].wait);
        
    }

   

    


}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter the arrival time of process P%d: ", p[i].id);
        scanf("%d", &p[i].arrival);
        printf("Enter the burst time of process P%d: ", p[i].id);
        scanf("%d", &p[i].burst);
    }

    fcfs(p, n);

    return 0;
}
