#include<stdio.h>

void pagereplacementFIFO(int pages[],int n,int frames){
    int frame[frames];
    int page_faults=0;
    for(int i=0;i<frames;i++){
        frame[i]=-1;
    }
    int index=0;
    for(int i=0;i<n;i++){
        int page_found=0;
        for(int j=0;j<frames;j++){
            if(frame[j]==pages[i]){
                page_found=1;
                break;
            }
        }
        if(page_found==0){
            frame[index]=pages[i];
            index=(index+1)%frames;
            page_faults++;
        }
    }

    printf("The number of page faults in fifo is %d\n",page_faults);

}

void pagereplacementLRU(int pages[],int n,int frames){
    int frame[frames],recent[frames];
    int frame_count=0;
    int page_faults=0;
    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        recent[i] = -1;
    }
    for(int i=0;i<n;i++){
        int page_found=0;
        for(int j=0;j<frames;j++){
            if(frame[j]==pages[i]){
                page_found=1;
                recent[j]=i;
                break;
            }
        }
        if(page_found==0){
            if(frame_count<frames){
                frame[frame_count]=pages[i];
                recent[frame_count]=i;
                page_faults++;
                frame_count++;
            }
            else{
                int min_index=0;
                for(int j=0;j<frames;j++){
                    if(recent[j]<recent[min_index]){
                        min_index=j;
                    }
                }
                frame[min_index]=pages[i];
                recent[min_index]=i;
                page_faults++;
            }
        }
    }
    printf("The number of page faults for lru is %d\n",page_faults);
}

void pagereplacementMRU(int pages[],int n,int frames){
    int frame[frames];
    int recent[frames];
    int frame_count=0;
    int page_faults=0;

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        recent[i] = -1;
    }

    for(int i=0;i<n;i++){
        int page_found=0;
        for(int j=0;j<frames;j++){
            if(frame[j]==pages[i]){
                page_found=1;
                recent[j]=i;
                break;
            }
        }
        if(page_found==0){
            if(frame_count<frames){
                frame[frame_count]=pages[i];
                recent[frame_count]=i;
                page_faults++;
                frame_count++;
            }
            else{
                int max_index=0;
                for(int j=0;j<frames;j++){
                    if(recent[j]>recent[max_index]){
                        max_index=j;
                    }
                }

                frame[max_index]=pages[i];
                recent[max_index]=i;
                page_faults++;
            }
        }
    }
     printf("The number of page faults in mru is %d\n",page_faults);
}

void pagereplacementOptimal(int pages[],int n,int frames){
    int frame[frames];
    int page_faults=0;

    for(int i=0;i<frames;i++){
        frame[i]=-1;
    }

    for(int i=0;i<n;i++){
        int page_found=0;
        for(int j=0;j<frames;j++){
            if(frame[j]==pages[i]){
                page_found=1;
                break;
            }
        }

        if(page_found==0){
            int farthest=i;
            int index=-1;
            for(int j=0;j<frames;j++){
                int next=i+1;
                while(next<n && pages[next]!=frame[j]){
                    next++;
                }
                if(next>farthest){
                    farthest=next;
                    index=j;
                }
            }
            if(index==-1){
                index=0;
            }
            frame[index]=pages[i];
            page_faults++;
        }
    }

    printf("The number of page faults in optimal is %d\n",page_faults);
}

int main()
{
    int pages[] = {3, 1, 0, 2, 4, 1, 2, 3, 4, 5, 1, 2, 5, 0, 7, 1, 3, 2, 8, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    pagereplacementFIFO(pages, n, frames);
    pagereplacementLRU(pages, n, frames);
    pagereplacementOptimal(pages, n, frames);
    pagereplacementMRU(pages, n, frames);

    return 0;
}