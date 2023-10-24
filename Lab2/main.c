#include <stdio.h>
#include <stdlib.h>
#include "edf.h"

//Some thing like a Timer in a Microcontroller
int timer = 0;

int main() {
	task *t;
	int n, hyper_period, active_task_id;			
	float cpu_utilization;
	printf("Enter number of task \n"); 					
	scanf("%d", &n);					 					// Enter the number of tasks
	t = malloc(n*sizeof(task));								// Allocate dynamic memory for an array of n elements of type 'task'
	get_tasks(t, n);										// Call the function to enter the parameters of the task
	cpu_utilization = cpu_util(t, n);						// Call the function to calculate the CPU utilization
	printf("CPU Utilization %f\n", cpu_utilization); 		// Show value of CPU utilization

	// Checks if the tasks can be scheduled or not
	if(cpu_utilization < 1)							
		printf("Tasks can be scheduled \n");			
	else {
		printf("Schedule is net feasible \n");
		return -1;	
	}

	// Call the function to hyperperiod_calc and save to hyper_period variable
	hyper_period = hyperperiod_calc(t, n);
	
	copy_execution_time(t, n, ALL);  			// Call the function to copy_execution_time
	update_abs_arrival(t, n, 0, ALL);			// Call the function to update_abs_arrival
	update_abs_deadline(t, n, ALL);				// Call the function to update_abs_deadline

	// Show the value of hyper_period
  	while(timer <= hyper_period){
		
		// Check if any task has arrived
  		if(sp_interrupt(t, timer, n)){ 						// If any task has arrived
			active_task_id = min(t, n, abs_deadline);		// Call the function to find the task with the smallest abs_deadline
		}

		if (active_task_id == IDLE_TASK_ID){ 				// If no task has arrived
			printf("%d Idle\n", timer);						// Print Idle
		}

		if(active_task_id != IDLE_TASK_ID){ 					// If any task has arrived
			if(t[active_task_id].T[execution_copy] != 0){ 			// If execution copy is not 0
				t[active_task_id].T[execution_copy]--;					// Decrease execution copy by 1
				printf("%d Task %d\n", timer, active_task_id + 1); 		// Show the task id
			}

			if(t[active_task_id].T[execution_copy] == 0){ 		// If execution copy is 0
				t[active_task_id].instance++;  						// Increase instance by 1
				t[active_task_id].alive = 0; 						// Set alive to 0
				copy_execution_time(t, active_task_id, CURRENT); 	// Copy execution time
				update_abs_arrival(t, active_task_id, t[active_task_id].instance, CURRENT); 	// Update abs_arrival
				update_abs_deadline(t, active_task_id, CURRENT); 								// Update abs_deadline
				active_task_id = min(t, n, abs_deadline); 										// Find the task with the smallest abs_deadline
			}
		}
		++timer;
	}
  free(t);	// Free the memory
  return 0;
}
