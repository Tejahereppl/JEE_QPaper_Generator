#include<stdio.h>
#include<limits.h>


int pages[100];

int FIFO(int frames,int n){
    int frame[10];
    int pagefaults=0;
    int rep = -1;
    
    for(int i=0;i<frames;i++){
        frame[i] = -1;
    }

    for(int i = 0;i<n;i++){
        int pagefound = 0;
        for(int j=0;j<frames;j++){
            if(frame[j]==pages[i]){
                pagefound = 1;
                break;
            }

        }
        if(!pagefound){
            pagefaults++;
            int emp = 0;
            for(int j=0;j<frames;j++){
                if(frame[j]==-1){
                    frame[j] = pages[i];
                    emp =1;
                    break;
                }
            }
            if(!emp){
                rep = (rep+1)%frames;
                frame[rep] = pages[i];
            }
        }
    }
    return pagefaults;
}


int MRU(int frames,int n){
    int pagefault = 0;
    int recent[10];
    
    int frame[10];
    for(int i = 0;i<frames;i++){
        frame[i] = -1;
        recent[i] = -1;
    }
    int framecount = 0;

    for(int i = 0;i<n;i++){
        int pagefound = 0;
        int index = -1;
        
        for(int j= 0;j<frames;j++){
            if(frame[j]==pages[i]){
                pagefound = 1;
                index = j;
                break;
            }
        }

        if(pagefound){
            recent[index] = i;
        }
        else{
            pagefault++;
            if(framecount<frames){
                frame[framecount] = pages[i];
                recent[framecount] = i;
                framecount++;
            }
            else{
                int max = INT_MIN;
            int max_index = -1;
            for(int j=0;j<frames;j++){
                if(recent[j]>max){
                    max_index = j;
                    max = recent[max_index];
                }
            }

            frame[max_index] = pages[i];
            recent[max_index] = i;
            }
            
        }


    }
    return pagefault;
}

int LRU(int frames,int n){
    int pagefault = 0;
    int frame[10];
    int recent[10];

    for(int i = 0;i<frames;i++){
        recent[i] = -1;
        frame[i] = -1;

    }


    for(int i = 0;i<n;i++){
        int pagefound = 0;
        int index = -1;
        for(int j=0;j<frames;j++){
            if(frame[j]==pages[i]){
                pagefound = 1;
                index = j;
                break;
            }
        }

        if(pagefound){
            recent[index] = i;
        }

        else{
            pagefault++;
            int min = INT_MAX;
            int min_index =0;
            for(int j=0;j<frames;j++){
                if(recent[j]<min){
                    min_index = j;
                    min = recent[min_index];
                }
            }

            frame[min_index] = pages[i];
            recent[min_index] = i;



        }


    }
    return pagefault;
}

int pageOpt(int frames,int n){

  
    int pageFault = 0;
    int frame[10];
    for(int i=0;i<frames;i++){
        frame[i] = -1;
    }

    for(int i = 0;i<n;i++){

        int pagefound = 0;
        for(int j=0;j<frames;j++){
            if(pages[i]==frame[j]){
                pagefound = 1;
                break;
            }
        }

        if(!pagefound){

            pageFault++;

            int farthest = i;
            int index = -1;

            for(int j=0;j<frames;j++){
                int next = i+1;

                while(next<n && pages[next]!=frame[j]){
                    next++;
                }
                if(next>farthest){
                    farthest = next;
                    index = j;
                }
                

            }

            if(index==-1){
                    index = 0;
                }

            frame[index] = pages[i];
        }
    }
    return pageFault;

}

int main(){


    int n;
    int frames;
    printf("Enter the number of pages:");
    scanf("%d",&n);

    printf("Enter the page values:");

    for(int i = 0;i<n;i++ ){
        scanf("%d",&pages[i]);
    }

    printf("Enter the number of frames:");
    scanf("%d",&frames);

   

    
    printf("%d\n",pageOpt( frames,n));
    printf("%d\n",LRU( frames,n));
    printf("%d\n",MRU( frames,n));
    printf("%d\n",FIFO( frames,n));

   
}