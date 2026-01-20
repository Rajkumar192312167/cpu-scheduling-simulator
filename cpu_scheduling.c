#include<stdio.h> 
struct process{                                                     //structure to store all the scheduling related information
    int pid;                                                        //process id
    int arrival_time;                                               //arrival time of a particular process
    int burst_time;                                                 //time taken for the cpu to finish a certain process
    int waiting_time;                                               //time spent waiting in queue
    int turnaround_time;                                            //completion time-arrival time
};
void sortByArrival(struct process p[],int n){
    int i,j;
    struct process temp;
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(p[i].arrival_time>p[j].arrival_time){
                temp = p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}
void fcfs(struct process p[],int n){                                //first come first serve , processes which comes first are executed first
    int i;                                                          //CPU remains idle until the next process is arrived
    int completion_time[n];
    float total_wt=0,total_tat=0;
    if(p[0].arrival_time>0){
        completion_time[0]=p[0].arrival_time+p[0].burst_time;
    }
    else{
        completion_time[0]=p[0].burst_time;
    }
    for(i=1;i<n;i++){
        if(completion_time[i-1]<p[i].arrival_time){
            completion_time[i]=p[i].arrival_time+p[i].burst_time;
        }
        else{
            completion_time[i]=completion_time[i-1]+p[i].burst_time;
        }
    }
    printf("\nGANTT CHART:\n|");
for(i = 0; i < n; i++){
    printf(" P%d |", p[i].pid);
}

printf("\n");

printf("%d", p[0].arrival_time);
for(i = 0; i < n; i++){
    printf("   %d", completion_time[i]);
}
printf("\n");

    printf("\nFCFS Scheduling\n");
    printf("Process AT BT WT TAT\n");
    for(i=0;i<n;i++){
        p[i].turnaround_time=completion_time[i]-p[i].arrival_time;
        p[i].waiting_time=p[i].turnaround_time-p[i].burst_time;         //wt is derived after completion to avoid negative values
        total_wt+=p[i].waiting_time;
        total_tat+=p[i].turnaround_time;
        printf("P%d     %d  %d  %d  %d\n",
            p[i].pid,
            p[i].arrival_time,
            p[i].burst_time,
            p[i].waiting_time,
            p[i].turnaround_time);
    }
    printf("\nAverage waiting time = %.2f\n",total_wt/n);
    printf("\nAverage Turnaround time = %.2f\n",total_tat/n);
}
void sjf(struct process p[], int n) {                                   //non-preemptive sjf - once a process starts , it cant be interrupted
    int completed[n];                                                   //selects the shortest process amongst the arrived processes 
    int i, done = 0;
    int current_time;
    float total_wt = 0, total_tat = 0;

    // mark all as not completed
    for (i = 0; i < n; i++)
        completed[i] = 0;

    // start time = earliest arrival
    current_time = p[0].arrival_time;

    printf("\nSJF Scheduling (Non-preemptive)\n");
    printf("PROCESS AT BT WT TAT\n");

    while (done < n) {
        int idx = -1;
        int min_bt = 1e9;

        // select shortest arrived process
        for (i = 0; i < n; i++) {
            if (!completed[i] && p[i].arrival_time <= current_time) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    idx = i;
                }
            }
        }

        // if no process is ready, jump time to next arrival
        if (idx == -1) {
            int next_arrival = 1e9;
            for (i = 0; i < n; i++) {
                if (!completed[i] && p[i].arrival_time < next_arrival)
                    next_arrival = p[i].arrival_time;
            }
            current_time = next_arrival;
            continue;
        }

        // execute selected process
        current_time += p[idx].burst_time;

        p[idx].turnaround_time = current_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

        total_wt += p[idx].waiting_time;
        total_tat += p[idx].turnaround_time;

        completed[idx] = 1;
        done++;

        printf("P%d      %d  %d  %d  %d\n",
               p[idx].pid,
               p[idx].arrival_time,
               p[idx].burst_time,
               p[idx].waiting_time,
               p[idx].turnaround_time);
    }

    printf("Average WT = %.2f\n", total_wt / n);
    printf("Average TAT = %.2f\n", total_tat / n);
}
void round_robin(struct process p[], int n, int tq) {                   //uses time slicing to ensure fairness to every process
    int remaining_bt[n];
    int i, completed = 0;
    int current_time;
    float total_wt = 0, total_tat = 0;

    // initialize remaining burst times
    for (i = 0; i < n; i++)
        remaining_bt[i] = p[i].burst_time;

    // start time = earliest arrival
    current_time = p[0].arrival_time;

    printf("\nROUND ROBIN SCHEDULING (Time Quantum = %d)\n", tq);       // if a process is not finished within the time quantum,it re-enters the queue
    printf("PROCESS AT BT WT TAT\n");

    while (completed < n) {
        int did_execute = 0;

        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && remaining_bt[i] > 0) {
                did_execute = 1;

                if (remaining_bt[i] > tq) {
                    current_time += tq;
                    remaining_bt[i] -= tq;
                } else {
                    current_time += remaining_bt[i];
                    remaining_bt[i] = 0;

                    p[i].turnaround_time = current_time - p[i].arrival_time;
                    p[i].waiting_time =
                        p[i].turnaround_time - p[i].burst_time;

                    total_wt += p[i].waiting_time;
                    total_tat += p[i].turnaround_time;

                    completed++;

                    printf("P%d      %d  %d  %d  %d\n",
                           p[i].pid,
                           p[i].arrival_time,
                           p[i].burst_time,
                           p[i].waiting_time,
                           p[i].turnaround_time);
                }
            }
        }

        // if no process was ready, jump to next arrival
        if (!did_execute) {
            int next_arrival = 1e9;
            for (i = 0; i < n; i++) {
                if (remaining_bt[i] > 0 &&
                    p[i].arrival_time < next_arrival)
                    next_arrival = p[i].arrival_time;
            }
            current_time = next_arrival;
        }
    }

    printf("Average WT = %.2f\n", total_wt / n);
    printf("Average TAT = %.2f\n", total_tat / n);
}

int main(){
    int n,i;
    printf("Enter the number of processors : ");
    scanf("%d",&n);
    struct process p[n];
    for(i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter arrival time and burst time for P%d : ",p[i].pid);
        scanf("%d %d",&p[i].arrival_time,&p[i].burst_time);

    }
    printf("\n Process at BT\n");
    for(i=0;i<n;i++){
        printf("P%d    %d  %d\n",
            p[i].pid,
            p[i].arrival_time,
            p[i].burst_time);
    }
    sortByArrival(p,n);
    fcfs(p,n);
    struct process p_sjf[n];
    for(i=0;i<n;i++){
        p_sjf[i]=p[i];
    }
    sjf(p_sjf,n);
    int tq;
    printf("\nEnter time quantum : ");
    scanf("%d",&tq);
    struct process p_rr[n];
    for(i=0;i<n;i++){
        p_rr[i]=p[i];
    }
    round_robin(p_rr,n,tq);
    return 0;
}