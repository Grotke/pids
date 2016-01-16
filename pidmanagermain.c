#include <stdio.h>
#include "pidmanager.h"
#define NUM_OF_PIDS 4702

int main(){
	int pids[NUM_OF_PIDS];
	allocate_map();
	int i, pid;
	for(i = 0; i < NUM_OF_PIDS; i++){
		pids[i] = allocate_pid();
	}
	for(i = 0; i < NUM_OF_PIDS; i++){
		printf("pid %d: %d\n", i, pids[i]);
	}
	for(i = 0; i < NUM_OF_PIDS; i++){
		printf("Releasing pid #%d\n", pids[i]);
		release_pid(pids[i]);
	}
	
	return 0;
}
