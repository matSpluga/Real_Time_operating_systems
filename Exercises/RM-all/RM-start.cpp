// compile with: g++ -O0 -lpthread <sourcename> -o <executablename>
// Optimization is disabled to ensure that threads have a more
// repeatable behaviour.
// If you want more determinism in execution time, you also need to disable 
// turbo performance in the cpu settings
// sudo cpupower frequency-set -g performance
// sudo bash -c 'echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo'
// This exercise demonstrates Rate Monotonic Scheduling (RMS) for
// periodic tasks. The periodic tasks have real-time constraints and
// their deadlines are monitored. 

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/mman.h>
#include <cstring>

// ---------------------------------------------
// Declaration of periodic task work functions
// The p parameter is to enable or disable 
// printing
// ---------------------------------------------

// ---------------------------------------------
// Thread routines (task body loops)
// ---------------------------------------------


// Loop constants used to artificially generate CPU load
#define INNERLOOP 3000
#define OUTERLOOP 1000

// Task count (only periodic tasks remain)
#define NPERIODICTASKS 3
#define NTASKS (NPERIODICTASKS)  

// Scheduling and timing data structures (sized for periodic tasks only)
long int periods[NTASKS];                       // Task periods (ns)
struct timespec next_arrival_time[NTASKS];      // Next activation time
double WCET[NTASKS];                            // Worst-case execution time estimates
pthread_attr_t attributes[NTASKS];              // Thread attributes for scheduling
pthread_t thread_id[NTASKS];                    // Thread identifiers
struct sched_param parameters[NTASKS];          // Scheduling priorities
int missed_deadlines[NTASKS];                   // Deadline miss counter (periodic only)

// CPU number where tasks are scheduled
int cpun = 4;

// Function to compute wcet. Parameters correspond to
// the task to be evaluated and the nuber of runs to
// ompute statistics
double measure_task_wcet(int task_index, int nruns);

//print the scheduling trace on memory (mf=1) or screen (mf=0)
int mf = 0; 
char schedtrack[64000]="";
char *psched=schedtrack;
//mutex to protect the memory 
pthread_mutex_t mm = PTHREAD_MUTEX_INITIALIZER;

// -------------------------------------------------------
// If mf=0, the scheduling trace is printed on standard output.
// Otherwise, it is printed on schedtrack and then printed on 
// standard output when the main thread ends.
// -------------------------------------------------------
void printm(const char *p, int mf)
{
	if (!mf)
	{
		printf("%s", p);
		fflush(stdout);
	}
	else
	{
		pthread_mutex_lock(&mm);
		memcpy(psched, p, 4);
		psched += 4;
		*psched='\0';
		pthread_mutex_unlock(&mm);
	}		
}

int main()
{
    // -------------------------------------------------------
    // Lock all current and future pages in RAM
    // This is necessary to reduce variance in task execution
    // -------------------------------------------------------
 
    //    

    // -------------------------------------------------------
    // Assign periods to tasks
    // -------------------------------------------------------


    // -------------------------------------------------------
    // Initialize the number of missed deadlines
    // -------------------------------------------------------


    // -------------------------------------------------------
    // If running as root, allow main thread to set priority
    // as the highest priority in the system (it cannot be
    // preempted by other tasks)
    // -------------------------------------------------------


    // -------------------------------------------------------
    // Measure WCET of each periodic task (important for schedulability test)
    // -------------------------------------------------------

    // Touch the code to store pages into memory
    task1_code(0); 
    task2_code(0); 
    task3_code(0); 

    // Call the function to estimate the worst case execution time   


    // -------------------------------------------------------
    // Rate Monotonic Schedulability Test
    // U = sum(Ci / Ti)   (only periodic tasks)
    // -------------------------------------------------------

    
    // Wait for one second to allow the user to read the results of
    // shedulability tests
    sleep(1);

    // Return main thread to low priority


    // -------------------------------------------------------
    // Assign priorities to periodic tasks using RMS
    // Shorter period = higher priority
    // The tasks are already ordered according to their priority.
    // -------------------------------------------------------


    // -------------------------------------------------------
    // Initialize next arrival times for periodic tasks
    // -------------------------------------------------------
    struct timespec t;
    clock_gettime(CLOCK_REALTIME,&t);



    // -------------------------------------------------------
    // Create periodic threads
    // -------------------------------------------------------


    // Wait for periodic tasks to finish


    // Print how many deadlines were missed
    for(int i=0;i<NTASKS;i++){
        printf("\nMissed Deadlines Task %d = %d",i,missed_deadlines[i]);
    }
    
    if (mf) 
    	printf("\n %s \n", schedtrack); 
    
    fflush(stdout);

    exit(0);
}


volatile int sink;  // global volatile to prevent optimization

void workload(int inner, int outer)
{
    int uno = 0;
    for (int i = 0; i < outer; i++)
        for (int j = 0; j < inner; j++)
        {
            uno += (int)(i ^ j);
        }
    sink = uno;  // store final result to volatile global
}

// -------------------------------------------------------
// Periodic task work code
// -------------------------------------------------------
void task1_code(int p)
{

    if (p) {printm(" 1[ ", mf);}

    workload(INNERLOOP, OUTERLOOP);
    
    if (p) {printm(" ]1 ", mf);}
}

// -------------------------------------------------------
// Periodic task execution loop
// Includes deadline miss detection
// -------------------------------------------------------
void *task1(void *ptr)
{
    // Bind task to CPU core cpun

    for(int i=0;i<100;i++)
    {
        struct timespec finish;
        task1_code(1);

        // Measure finish time of task execution

        // Check if finish time passed deadline
        if((finish.tv_sec > next_arrival_time[0].tv_sec) ||
           (finish.tv_sec==next_arrival_time[0].tv_sec &&
            finish.tv_nsec>next_arrival_time[0].tv_nsec))
            missed_deadlines[0]++;

        // Sleep until the next activation (absolute time scheduling)

        // Compute next activation time

    }
    return NULL;
}

void task2_code(int p)
{
    if (p) {printm(" 2[ ", mf);}

    workload(INNERLOOP, OUTERLOOP*4);

    if (p) {printm(" ]2 ", mf);}
}

void *task2(void *ptr)
{

    for(int i=0;i<50;i++)
    {

    }
    return NULL;
}

void task3_code(int p)
{
    if (p) {printm(" 3[ ", mf);}

    workload(INNERLOOP, OUTERLOOP*8);

    if (p) {printm(" ]3 ", mf);}
}

void *task3(void *ptr)
{

    for(int i=0;i<25;i++)
    {

    }
    return NULL;
}

// -------------------------------------------------------
// Function to measure worst-case execution times
// -------------------------------------------------------
double measure_task_wcet(int task_index, int nruns) {

    double *times = (double*)malloc(nruns*sizeof(double));

    for(int r = 0; r < nruns; r++)
    {
        struct timespec t1, t2;
        clock_gettime(CLOCK_REALTIME, &t1);

        // Execute the selected task
        switch(task_index)
        {
            case 0: task1_code(0); break;
            case 1: task2_code(0); break;
            case 2: task3_code(0); break;
            default: 
                printf("Error: invalid task index %d\n", task_index);
                return -1;
        }

        clock_gettime(CLOCK_REALTIME, &t2);

        times[r] = 1e9*(t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec);
    }

    // Compute statistics
    double sum = 0.0;
    double max = times[0];
    int maxi;
    
    for(int r = 0; r < nruns; r++)
    {
        sum += times[r];
        if(times[r] > max)
        {
            max = times[r];
            maxi=r;
        }
    }
    double mean = sum / nruns;

    double var_sum = 0.0;
    for(int r = 0; r < nruns; r++)
        var_sum += (times[r] - mean)*(times[r] - mean);

    double std_dev = sqrt(var_sum / nruns);

    // Print statistics
    printf("\nTask %d timing results:\n", task_index);
    printf("  Average time   = %.2f ns\n", mean);
    printf("  Std deviation  = %.2f ns\n", std_dev);
    printf("  Maximum (WCET) = %.2f ns\n", max);
    printf("  Maximum i = %d \n", maxi);
    fflush(stdout);
    free(times);
    
    return max; // Return WCET (maximum time)
}

