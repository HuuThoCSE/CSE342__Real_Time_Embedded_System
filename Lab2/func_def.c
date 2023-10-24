#include <stdio.h>
#include "edf.h"

// Funciton to enter the parameters of the task
void get_tasks(task *t1, int n){  				
	int i = 0;
	while (i < n){
		printf("Enter Task %d parameters \n", i+1);
		printf("Arrival time: ");
		scanf("%d", &t1->T[arrival]); 			// Save to the arrival variable
		printf("Executon time: ");
		scanf("%d", &t1->T[execution]); 		// Save to the execution variable 			
		printf("Deadline time: ");
		scanf("%d", &t1->T[deadline]);			// Save to the deadline variable 			
		printf("Period: ");
		scanf("%d", &t1->T[period]);			// Save to the period variable 				
		t1->T[abs_arrival] = 0;					// Initialize the abs_arrial value 			
		t1->T[execution_copy] = 0;				// Initialize the execution_copy value 		
		t1->T[abs_deadline] = 0;				// Initialize the abs_deadline value 		
		t1->instance = 0;						// Initialize the abs_deadline value 		
		t1->alive = 0;							// Initialize the alive value 				
		t1++;
		i++;
	}
}

// Function to calculate the CPU utilization
float cpu_util(task *t1, int n){						
	int i = 0;	
	float cu = 0;
	while (i < n){
		cu = cu + (float)t1->T[execution]/(float)t1->T[period];  
		t1++;
		i++;
	}
	return cu;
}

// Function to calculate the hyperperiod
int hyperperiod_calc(task *t1, int n){ 	
	int i = 0, ht, a[10];
	while(i<n){
		a[i] = t1->T[period];				
		t1++;
		i++;
	}
	ht = lcm(a, n);

	return ht;
}

// Function to calculate the gcd and lcm
int gcd(int a, int b){					
	if(b == 0) 
		return a;
	else
		return gcd(b, a % b);

}

// Function to calculate the lcm
int lcm(int *a, int n){			
	int res = 1, i;
	for (i = 0; i < n; i++){
		res = res * a[i] / gcd(res, a[i]);
	}
	return res;
}

// Function to check if any task has arrived
int sp_interrupt(task *t1, int tmr, int n){ 			
	int i = 0, n1 = 0, a = 0;
	task *t1_copy;
	t1_copy = t1;

	// Check if any task has arrived
	while (i < n){
		if(tmr == t1->T[abs_arrival]){					
			t1->alive = 1;
			a++;
		}
		t1++;
		i++;
	}

	t1 = t1_copy;
	i = 0;

	// Check if all the tasks are dead
	while (i < n){
		if(t1->alive == 0)
			n1++;
		t1++;
		i++;
	}

	// If all the tasks are dead or any task has arrived
	if(n1 == n || a != 0){
		return 1;
	}

	return 0;
}

// Function to update the abs_deadline value
void update_abs_deadline(task *t1, int n, int all){ 		
	int i = 0;

	// If all the tasks are to be updated
	if(all){
		while (i < n){
			t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival]; 	
			t1++;
			i++;
		}
	} else { // If only one task is to be updated
		t1 += n;
		t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];			
	}
}

// Function to update the abs_arrival value
void update_abs_arrival(task *t1, int n, int k, int all){ 		
	int i = 0;

	//	If all the tasks are to be updated
	if (all){
		while (i < n){
			t1->T[abs_arrival] = t1->T[arrival] + k * (t1->T[period]);  //	abs_arrival = arrival + k * period
			t1++;
			i++;
		}
	} else { // If only one task is to be updated
		t1 += n;
		t1->T[abs_arrival] = t1->T[arrival] + k * (t1->T[period]);		// abs_arrival = arrival + k * period
	}
}

// Function to copy the execution time to execution copy
void copy_execution_time(task *t1, int n, int all){ 			
	int i = 0;

	// If all the tasks are to be updated
	if (all){
		while(i<n){
			t1->T[execution_copy] = t1->T[execution];		
			t1++;
			i++;
		}
	} else { // If only one task is to be updated
		t1 += n;
		t1->T[execution_copy] = t1->T[execution];				
	}
}

// Function to find the task with the smallest value of p
int min(task *t1, int n, int p){							
	int i = 0, min = 0x7FFF, task_id = IDLE_TASK_ID;

	// Find the task with the smallest value of p
	while (i < n){
		if(min > t1->T[p] && t1->alive == 1){				// If the value of p is smaller than min and the task is alive
			min = t1-> T[p];
			task_id = i;
		}
		t1++;
		i++;
	}
	return task_id;
}

