##Nested thread
 	1.thread inisde thread can be created
	2.added pthread_join in main() only for nested thread , still main is not waited until nested thread terminates as parent thread terminated.
	3.added pthread_join for nested thread in parent thread still it won't wait until nested thread completes.
	4.added pthread_join for parent thread, not for nested thread in this case nested thread perfomrs inconsistancy thread


All three threads here same

sharable resources;-
	1.Heap memory
	2.Global and Static
	3.code
	4.open files/sockets/fds
	5.Address space(virtual memory)

Distinct:-
	1.thread Stack
	2.Registers(cpu context and program counter)
	3.threadID
	

from thread1 while we create nested thread, if we want pass any arguments that should heap(dynamic based) else don't share.
