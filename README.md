# pids
Process ID Manager

![Screenshot of threadpids](http://www.josephcmontgomery.com/uploads/4/5/8/3/45834621/6284638_orig.png)

## Description and Background
This repo includes two projects. pidmanager.c is an implementation of a process id manager similar to one found in an operating system. 
It allocates and releases pids. threadpids.c uses threads to request a pid, sleep for a random period of time, then return the pid to the pidmanager.

The two pid projects were created to solve programming projects in the Operating Systems Concepts book.

Go to the website at the top for more info about the development process.

## Building Instructions
### pids:
  
  After cloning the repo, `make -f makepids` should create the executable and `./pids` should run it. 
  And `make -f makepids clean` should clean up the executable.
  
### threadpids:
  
  `make -f makethreadpids` then `./threadpids` should run threadpids. `make -f makethreadpids clean` should clean it.
