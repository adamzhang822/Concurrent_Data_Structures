(1): Member: Yan (Adam) Zhang, no one else

(2): 

I merged plock implementations with spin-lock implementations in the same header / .c files. 
In order to pass the unit tests, I commented out my implementations for pthread locks in .h and .c files. 

For the simulation that produces the data for the plots, in order to run the executable for sim.c, need to: 
1. Uncomment the commented out parts of .h & .c files (which are the pthread implementations), or comment out the pthread simulations in the .c code and only run simulations for spinlock.
2. execute the makefile commands
3. type "export LD_LIBRARY_PATH=." in the shell on UChicago Linux machine 

(3): 
Makefile is for running the simulations.
Another Makefile (Makefile2) is included. This Makefile is for running the unit-tests, since no Makefile was supplied for the unit-test part. It is essentially the same Makefile except that compilation instructions for sim.c are removed.

