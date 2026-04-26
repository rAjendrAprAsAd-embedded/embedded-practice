## Step 1:- Basic thread creation
###problem Observed:- 
	->Thread1 and Thread2 were created from main
	->Thread1 executed first, but before Thread2 completed it's execution Main ended.
	
### Initial FIX
	--> Added "pthread_join(thread2)" to ensure main waits until the thread2 completion.

### Observation After Fix
	--> Thread2 execution is now guaranteed
	--> however Thread1 output is become inconsistant.
### Final understanding
	-->Every created thread must be joined, else outcome is inconsistent.


##Note:-
The pthread_mutex_trylock() function is the same as pthread_mutex_lock(), except
that if the mutex is currently locked, pthread_mutex_trylock() fails, returning the
error EBUSY.