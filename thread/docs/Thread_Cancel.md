##thread cancellation

	1. If you need to stop the thread externally, you can use int ret = pthread_cancel(tid,&resp) to stop the thread.
        2.Even if main is waiting on pthread_join, pthread_cancel indicates that it won't black it, so I will immediately return with the macro "PTHREAD_CANCELED"
	3. The thread's return value is still present in resp if thread execution is finished before executing pthread_cancel(tid)

Note:- Use it to determine whether a thread's return value is PTHREAD_CANCELED before focusing on that thread Return value(resp); otherwise, if someone calls pthread_cancel before it finishes, segumentfault is issued.
