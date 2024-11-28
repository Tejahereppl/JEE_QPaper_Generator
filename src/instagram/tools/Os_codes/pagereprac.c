#include<stdio.h>
#include<stdbool.h>

int pages[100];
int frame[10];
int recent[10];

int FIFO(int n,int size){
    
    int framecount = 0;
    int pagefault=0;
    
   for(int i = 0;i<n;i++){
    bool found = false;
        for(int j = 0;j<size;j++){
            if(frame[j]==pages[i]){
                found = true;
                break;
            }
        }

        if(!found){
            pagefault++;
            int index = -1;
            for(int j = 0;j<size;j++){
                if(frame[j]==-1){
                    index = j;
                    break;
                }
            }
            if(index>-1){
         4554       frame[index] = pages[i];
            }
            else{
                frame[framecount] = pages[i];
                framecount = (framecount+1)%size;
            }


        }
   }
   return pagefault;

   


}
int LRU(int n,int size){
    
    int pagefault=0;

    for(int i =0;i<n;i++){
        bool found = false;
        for(int j =0;j<size;j++){
            if(frame[j]==pages[i]){
                found =  true;
                recent[j] = i;
                break;

            }
        }
        
        if(!found){
            pagefault++;
            int index = -1;
            for(int j=0;j<size;j++){
                if(frame[j]==-1){
                    index = j;
                    break;
                }
            }

            if(index>-1){
                frame[index] = pages[i];
                recent[index] = i;
            }
            else{
                int min = 0;
                for(int j = 0;j<size;j++){
                    if(recent[j]<recent[min]){
                        min = j;
                    }
                }
                recent[min] = i;
                frame[min] = pages[i];
            }

        }
    }
    return pagefault;
}

int main(){
    int n;
    printf("Enter the number of request:\n");
    scanf("%d",&n);
    
    printf("Enter the request one by one:\n");

    for(int i = 0;i<n;i++){
        scanf("%d",&pages[i]);
    }
    for(int i = 0;i<3;i++){
        frame[i] = -1;
    }

    printf("page fault :%d",FIFO(n,3));
    printf("page fault :%d",LRU(n,3));


}