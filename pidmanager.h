#ifndef _PIDMANAGER_H_
#define _PIDMANAGER_H_
int allocate_map();
int allocate_pid();
void release_pid(int pid);

int isValidBlock(int blockIndex);
int isValidPidNumber(int pid);
int createPidNumber(int blockIndex, int pidIndex);
int moreBlocksExist(int blockIndex);
int blockIsFull(int blockIndex);
int pidToPidIndex(int pid);
int pidToBlockIndex(int pid);
void markPidAsTaken(int blockIndex, int pidIndex);
void markPidAsFree(int blockIndex, int pidIndex);
int findFreePidInBlock(int blockIndex);
int findFreeBlockIndex();
#endif
