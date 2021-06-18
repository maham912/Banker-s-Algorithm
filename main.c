#include <stdio.h>
#include <stdlib.h>

/* Declare dynamic arrays and global variables*/

int *resource = NULL;
int *available = NULL;
int *max_claim = NULL;
int *allocation = NULL;
int *need = NULL;

int num_processes;
int num_resources;


/***********************************************************/
void print_resource() {
	/* declare local variables */
	int i;
				printf("\n");

	/* for loop: print each resource index */
	printf("Resources: ");
				printf("\n");

	for (i = 0; i < num_resources; i++)
	    printf("\tr%d", i);
		printf("\n");

	/* for loop: print number of total units of each resource index */
	
	for (i = 0; i < num_resources; i++)
	    printf("\t%d", resource[i]);
	    printf("\n");
	return;
}


/***********************************************************/
void print_avaliable() {
	/* declare local variables */
	int i;
				printf("\n");

	/* for loop: print each resource index */
	printf("Avaliable: ");
				printf("\n");

	for (i = 0; i < num_resources; i++)
	    printf("\tr%d", i);
		printf("\n");
	/* for loop: print number of available units of each resource index */
	for (i = 0; i < num_resources; i++)
	    printf("\t%d", available[i]);
	    printf("\n");
	return;
}


/***************************************************************/
void print_max_claim() { 
	/* declare local variables */
	int i;
	int j;
				printf("\n");

	printf("Max claim: \n");
				printf("\n");


	/* for loop: print each resource index */
		for (i = 0; i < num_resources; i++)
	    printf("\tr%d", i);
		printf("\n");
		
	/* for each process: */
	for (i = 0; i <num_processes; i++){
	    printf("p%d", i);
	    	for (j = 0; j < num_resources; j++){
		         printf("\t%d", max_claim[i * num_resources+j]);

	           }
	           		         	    printf("\n");

	}
		/* for each resource: print maximum number of units each process may request from each resource */
	
			
			
	
}


/***************************************************************/
void print_allocation() {
	/* declare local variables */
	int i;
	int j;
			printf("\n");

	printf("Allocation: \n");
				printf("\n");

	/* for loop: print each resource index */
		for (i = 0; i < num_resources; i++)
	    printf("\tr%d", i);
		printf("\n");
		
	/* for each process: */
	for (i = 0; i <num_processes; i++){
	    printf("p%d", i);
	    for (j = 0; j < num_resources; j++){
		    printf("\t%d", allocation[i*num_resources+j]);

		}
				    	    printf("\n");

	}
		/* for each resource: */
		
			/* print maximum number of units each process may request from each resource */
	return;
}


/***************************************************************/
void print_need() {
	/* declare local variables */
	int i;
	int j;
			printf("\n");

	printf("Need: \n");
				printf("\n");

	/* for loop: print each resource index */
		for (i = 0; i < num_resources; i++)
	    printf("\tr%dd", i);
		printf("\n");
		
	/* for each process: */
	for (i = 0; i <num_processes; i++){
	    printf("p%d", i);
	    			for (j = 0; j < num_resources; j++){
		    printf("\t%d", need[i*num_resources+j]);

		}
				    	    printf("\n");

	}
		/* for each resource: */
	
			/* print maximum number of units each process may request from each resource */
	return;
}


/****************************************************************/
void parameter() {
	/* declare local variables */
	int i;
	int j;
	int units;
	
	/* prompt for number of processes and number of resources */
	printf("Enter number of processes: ");
	scanf("%d", &num_processes);
	
	printf("Enter the number of resource: ");
	scanf("%d", &num_resources);
	printf("\n");

	
	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
	
	resource = (int *)malloc(num_resources * sizeof(int));
	available = (int *)malloc(num_resources * sizeof(int));
	max_claim = (int *)malloc(num_resources * num_processes * sizeof(int));
	
	allocation = (int *)malloc(num_resources * num_processes * sizeof(int));
	need = (int *)malloc(num_resources * num_processes * sizeof(int));


        printf("Enter number of units for resources(r0 to r%d): ", num_resources-1);
	/* for each resource, prompt for number of units, set resource and available vectors indices*/
    for (i = 0; i < num_resources; i++){
                scanf("%d", &units);

        resource[i] = units;
        available[i] = units;
    }
    
	/* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */ 
    for (i = 0; i < num_processes; i++){
        printf("Enter maximum number of units process p%d will request from each resource (r0 to r%d): ", i, num_resources-1);
        for (j = 0; j < num_resources; j++){
            scanf("%d", &units);
            max_claim[i*num_resources+j] = units;
            need[i*num_resources+j] = units;
        }
    }
	/* for each process, for each resource, prompt for number of resource units allocated to process */
	
	for (i = 0; i < num_processes; i++){
        printf("Enter number of units of each resource (r0 to r%d) allocated to process p%d: ", num_resources-1, i);
        for (j = 0; j < num_resources; j++){
            scanf("%d", &units);
            allocation[i*num_resources+j] = units;
            available[j] -= units;
            need[i*num_resources+j] -= units;
        }
   
    }
    
    
	/* print resource vector, available vector, max_claim array, allocated array, need array */
	print_resource();
	print_avaliable();
	print_max_claim();
	print_allocation();
	print_need();
	return;
}


/********************************************************************/
void determine() {

	/* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
    int num_sequenced = 0;
    int *safe = (int *)calloc(num_processes , sizeof(int)); //should it be num_processes or num_resources
    int i;
    int j;
    int less_than;
    
		
	/* while not all processed are sequenced */
	while (num_sequenced < num_processes){
		for (i = 0; i < num_processes; i++){
		    less_than = 1;

			if (safe[i] == 0){
						 
		           // for (i = 0; i < num_processes; i++){
					    
		             printf("\n");
                    printf("Checking: < ");
				for (j = 0; j < num_resources; j++)
				    printf("%d ", need[i*num_resources+j]);
				  					printf(" > <= < ");
				for (j = 0; j < num_resources; j++)
				    printf("%d ", available[j]);
				    			printf(" > ");

                for (j = 0; j < num_resources; j++)
					less_than = less_than & (need[i*num_resources+j] <= available[j]);
	      			if (less_than == 1){
	      			    printf(" :p%d safely sequenced",i);
	      			    printf("\n");
	      			    safe[i] = 1;
    					for (j=0; j <num_resources; j++){
        					available[j] += allocation[i*num_resources+j];
        					allocation[i*num_resources+j] = 0;
				       }//for loop
					
						/* increment number of sequenced processes */
						num_sequenced++;
						
		            } //if less_than == 1 statement
			}//if safe = 0
		}//for loop
	}//while num_sequenced < num_processes loop
return;
}


/********************************************************************/
void quit() {
	/* check if vectors/array are not NULL--if so, free each vector/array */	
	
	if(resource != NULL)
	    free(resource);
	if(available != NULL)
	    free(available);
	if(max_claim != NULL)
	    free(max_claim);
	if(allocation != NULL)
	    free(allocation);
	if(need != NULL)
	    free(need);
	return;
}


/***************************************************************/
int main() {

/* Declare local variables */
	int choice;
	
	/* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
while ( choice != 3)
{
    printf("Banker's Algorithm\n");
	printf("-------------------\n");
	printf("1) Enter parameters\n");
	printf("2) Determine safe sequence\n");
	printf("3) Quit program \n\n");
	
	printf("Enter selection: ");
	scanf("%d", &choice);

	
	if (choice == 1)
	{
	   parameter();
	}
	
	else if (choice == 2)
	{
	   determine();
	}
	
	else if (choice == 3)
	{
	   quit();
	}

} //end while loop

  return 1;
}


