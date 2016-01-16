/* Pid Manager - Implementation of process identifier manager similar to those used in an operating system.
*/

#include <stdlib.h>
#include <limits.h>
#include "pidmanager.h"

#define MIN_PID 300
#define MAX_PID 5000
#define BITS_PER_BYTE 8
#define BITS_PER_BLOCK (sizeof(unsigned int) * BITS_PER_BYTE)

int numPidBlocks = 0;
unsigned int * pids;

int allocate_map(){
	int numPidsNeeded = MAX_PID - MIN_PID + 1;
	numPidBlocks = numPidsNeeded / BITS_PER_BLOCK;
	if(numPidsNeeded % BITS_PER_BLOCK != 0){
		numPidBlocks++;
	}

	pids = (unsigned int *)calloc(numPidBlocks, sizeof(unsigned int));

	if(pids){
		return 1;
	}

	return 0;
}

int allocate_pid(){
	int blockIndex = findFreeBlockIndex();

	if(!isValidBlock(blockIndex)){
		return -1;
	}

	int freePidIndex = findFreePidInBlock(blockIndex);
	int pidNumber = createPidNumber(blockIndex, freePidIndex);	
	if(!isValidPidNumber(pidNumber)){
		return -1;
	}
	markPidAsTaken(blockIndex, freePidIndex);
	return pidNumber; 
}	

void release_pid(int pid){
	int pidIndex = pidToPidIndex(pid);
	int blockIndex =  pidToBlockIndex(pid);

	markPidAsFree(blockIndex, pidIndex);	
}

int isValidBlock(int blockIndex){
	return moreBlocksExist(blockIndex) && blockIndex >= 0;
} 

int isValidPidNumber(int pid){
	return pid >= MIN_PID && pid <= MAX_PID;
}

int createPidNumber(int blockIndex, int pidIndex){
	return (MIN_PID + (BITS_PER_BLOCK*blockIndex) + pidIndex);		
}

int moreBlocksExist(int blockIndex){
	return blockIndex < numPidBlocks;
}

int blockIsFull(int blockIndex){
	return pids[blockIndex] == UINT_MAX;
}

int pidToPidIndex(int pid){
	return (pid - MIN_PID) % BITS_PER_BLOCK;
}

int pidToBlockIndex(int pid){
	return (pid - MIN_PID)/ BITS_PER_BLOCK;	
}

void markPidAsTaken(int blockIndex, int pidIndex){
	pids[blockIndex] = pids[blockIndex] | (1 << pidIndex);
}

void markPidAsFree(int blockIndex, int pidIndex){
	pids[blockIndex] = pids[blockIndex] ^ (1 << pidIndex);
}

int findFreeBlockIndex(){
	int blockIndex = 0;
	while(blockIsFull(blockIndex) && moreBlocksExist(blockIndex)){
		blockIndex++;
	}
	return blockIndex;
}

int findFreePidInBlock(int blockIndex){
	unsigned int pidBlock = pids[blockIndex];
	int freePidIndex = 0;

	while((pidBlock & 1) == 1){
		pidBlock = pidBlock >> 1;
		freePidIndex++;
	}

	return freePidIndex;
}
