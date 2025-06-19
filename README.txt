

Common Instructions
• Your project must be written in C.
• Your project must be written in accordance with the Norm. 
    If you have bonus files/functions, they are included in the norm check and you will receive a 0 if there is a norm error inside.
• Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors. 
    If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
• All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
• If the subject requires it, you must submit a Makefile which will compile your source files to the required output with the flags 
    -Wall, -Wextra and -Werror, use cc, and your Makefile must not relink.
• Your Makefile must at least contain the rules $(NAME), all, clean, fclean and re.
• To turn in bonuses to your project, you must include a rule bonus to your Makefile, which will add all the various headers, 
    librairies or functions that are forbidden on the main part of the project. 
• Bonuses must be in a different file _bonus.{c/h} if the subject does not specify anything else. 
    Mandatory and bonus part evaluation is done separately.
• If your project allows you to use your libft, you must copy its sources and its associated Makefile in a libft folder with its associated Makefile. 
    Your project’s Makefile must compile the library by using its Makefile, then compile the project.
• We encourage you to create test programs for your project even though this work won’t have to be submitted and won’t be graded. 
    It will give you a chance to easily test your work and your peers’ work. You will find those tests especially useful during your defence. 
    Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
• Submit your work to your assigned git repository. Only the work in the git repository will be graded. 
    If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. 
    If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.



Overview
Here are the things you need to know if you want to succeed this assignment:
• One or more philosophers sit at a round table.There is a large bowl of spaghetti in the middle of the table.
• The philosophers alternatively eat, think, or sleep.
    While they are eating, they are not thinking nor sleeping, while thinking, they are not eating nor sleeping, 
    and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Because serving and eating spaghetti with only one fork is very inconvenient, 
    a philosopher takes their right and their left forks to eat, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and start sleeping. 
    Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers don’t speak with each other.
• Philosophers don’t know if another philosopher is about to die.
• No need to say that philosophers should avoid dying!


Global rules
You have to write a program for the mandatory part and another one for the bonus part. They both have to comply with the following rules:
• Global variables are forbidden!
• Your(s) program(s) should take the following arguments: 
    number_of_philosophers 
    time_to_die 
	time_to_eat 
    time_to_sleep 
    [number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers and also the number of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
• Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1. About the logs of your program:
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.
• A displayed state message should not be mixed up with another message.
• A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
• Again, philosophers should avoid dying!

Your program must not have any data races.

Mandatory part
Program name            philo
Turn in files           Makefile, *.h, *.c, in directory philo/
Makefile                NAME, all, clean, fclean, re
Arguments               number_of_philosophers, time_to_die time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
External functs.        memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, 
                        pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
Libft authorized        No
Description             Philosophers with threads and mutexes
The specific rules for the mandatory part are:
						• Each philosopher should be a thread.
						• There is one fork between each pair of philosophers. 
						    Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. 
						    If there is only one philosopher, there should be only one fork on the table.
						• To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

Bonus part
Program name 			philo_bonus
Turn in files 			Makefile, *.h, *.c, in directory philo_bonus/
Makefile 				NAME, all, clean, fclean, re
Arguments 				number_of_philosophers, time_to_die time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
External functs. 		memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join,
						usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink
Libft authorized 		No
Description 			Philosophers with processes and semaphores
						The program of the bonus part takes the same arguments as the mandatory program.
						It has to comply with the requirements of the Global rules chapter.
The specific rules for the bonus part are:
						• All the forks are put in the middle of the table.
						• They have no states in memory but the number of available forks is represented by a semaphore.
						• Each philosopher should be a process. But the main process should not be a philosopher.


Submission and peer-evaluation
Turn in your assignment in your Git repository as usual. Only the work inside your repository will be evaluated during the defense. 
Don’t hesitate to double check the names of your files to ensure they are correct.
Mandatory part directory: 	philo/
Bonus part directory: 		philo_bonus/



ALLOWED FUNCTIONS:


man7.org examples:

memset
	https://man7.org/linux/man-pages/man3/memset.3.html
	SYNOPSIS
		#include <string.h>
		void *memset(void s[.n], int c, size_t n);

	DESCRIPTION
		The memset() function fills the first n bytes of the memory area
		pointed to by s with the constant byte c.

	RETURN VALUE
		The memset() function returns a pointer to the memory area s.

printf
	https://man7.org/linux/man-pages/man3/fprintf.3.html
	SYNOPSIS
		#include <stdio.h>
		int printf(const char *restrict format, ...);

	DESCRIPTION
		The functions printf() and vprintf() write output to stdout, the standard output stream;

	RETURN VALUE
		Upon successful return, these functions return the number of
		bytes printed (excluding the null byte used to end output to strings).

malloc
	https://man7.org/linux/man-pages/man3/malloc.3.html
	SYNOPSIS
		#include <stdlib.h>
		void *malloc(size_t size);

	DESCRIPTION
		The malloc() function allocates size bytes and returns a pointer
		to the allocated memory.  The memory is not initialized.  If size
		is 0, then malloc() returns a unique pointer value that can later
		be successfully passed to free().  (See "Nonportable behavior" for portability issues.)

	RETURN VALUE
		The malloc(), calloc(), realloc(), and reallocarray() functions
		return a pointer to the allocated memory, which is suitably
		aligned for any type that fits into the requested size or less.
		On error, these functions return NULL and set errno.

free
	https://man7.org/linux/man-pages/man3/malloc.3.html
	SYNOPSIS
		#include <stdlib.h>
		void free(void *_Nullable ptr);

	DESCRIPTION
		The free() function frees the memory space pointed to by ptr,
		which must have been returned by a previous call to malloc() or
		related functions.  Otherwise, or if ptr has already been freed,
		undefined behavior occurs.  If ptr is NULL, no operation is
		performed.

	RETURN VALUE
		The free() function returns no value, and preserves errno.

write
	https://man7.org/linux/man-pages/man2/write.2.html
	SYNOPSIS
		#include <unistd.h>
		ssize_t write(int fd, const void buf[.count], size_t count);
	DESCRIPTION
		write() writes up to count bytes from the buffer starting at buf
		to the file referred to by the file descriptor fd.

	RETURN VALUE
		On success, the number of bytes written is returned.  On error,
		-1 is returned, and errno is set to indicate the error.

usleep
	https://man7.org/linux/man-pages/man3/usleep.3.html
	SYNOPSIS
		#include <unistd.h>
		int usleep(useconds_t usec);
	DESCRIPTION
		The usleep() function suspends execution of the calling thread
		for (at least) usec microseconds.  The sleep may be lengthened
		slightly by any system activity or by the time spent processing
		the call or by the granularity of system timers.

	RETURN VALUE
	  	The usleep() function returns 0 on success.  On error, -1 is
		returned, with errno set to indicate the error.

gettimeofday
	https://man7.org/linux/man-pages/man2/gettimeofday.2.html
	SYNOPSIS
		#include <sys/time.h>
		int gettimeofday(struct timeval *restrict tv, struct timezone *_Nullable restrict tz);

	DESCRIPTION
		The functions gettimeofday() and settimeofday() can get and set
		the time as well as a timezone.

	RETURN VALUE
		gettimeofday() and settimeofday() return 0 for success.  On
		error, -1 is returned and errno is set to indicate the error.

pthread_create
	https://man7.org/linux/man-pages/man3/pthread_create.3.html
	SYNOPSIS
		#include <pthread.h>
		int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);

	DESCRIPTION
		The pthread_create() function starts a new thread in the calling
		process.  The new thread starts execution by invoking
		start_routine(); arg is passed as the sole argument of
		start_routine().

		The new thread terminates in one of the following ways:

		•  It calls pthread_exit(3), specifying an exit status value that
			is available to another thread in the same process that calls pthread_join(3).

		•  It returns from start_routine().  This is equivalent to
			calling pthread_exit(3) with the value supplied in the return statement.

		•  It is canceled (see pthread_cancel(3)).

		•  Any of the threads in the process calls exit(3), or the main thread performs a return from main().  
			This causes the termination of all threads in the process.
	
	RETURN VALUE
		On success, pthread_create() returns 0; on error, it returns an
		error number, and the contents of *thread are undefined.

pthread_detach
	https://man7.org/linux/man-pages/man3/pthread_detach.3.html
	SYNOPSIS
		#include <pthread.h>
		int pthread_detach(pthread_t thread);

	DESCRIPTION
	The pthread_detach() function marks the thread identified by
		   thread as detached.  When a detached thread terminates, its
		   resources are automatically released back to the system without
		   the need for another thread to join with the terminated thread.

		   Attempting to detach an already detached thread results in
		   unspecified behavior.
	RETURN VALUE
	 On success, pthread_detach() returns 0; on error, it returns an
		   error number.

pthread_join
	https://man7.org/linux/man-pages/man3/pthread_join.3.html
	SYNOPSIS
		#include <pthread.h>
		int pthread_join(pthread_t thread, void **retval);

	DESCRIPTION
		The pthread_join() function waits for the thread specified by
		thread to terminate.  If that thread has already terminated, then
		pthread_join() returns immediately.  The thread specified by
		thread must be joinable.

		If retval is not NULL, then pthread_join() copies the exit status
		of the target thread (i.e., the value that the target thread
		supplied to pthread_exit(3)) into the location pointed to by
		retval.  If the target thread was canceled, then PTHREAD_CANCELED
		is placed in the location pointed to by retval.

		If multiple threads simultaneously try to join with the same
		thread, the results are undefined.  If the thread calling
		pthread_join() is canceled, then the target thread will remain
		joinable (i.e., it will not be detached).
	RETURN VALUE
		On success, pthread_join() returns 0; on error, it returns an error number.

pthread_mutex_init & pthread_mutex_destroy
	https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html
	SYNOPSIS
		#include <pthread.h>
		int pthread_mutex_destroy(pthread_mutex_t *mutex);
		int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	DESCRIPTION
		The pthread_mutex_destroy() function shall destroy the mutex
		object referenced by mutex; the mutex object becomes, in effect,
		uninitialized. An implementation may cause
		pthread_mutex_destroy() to set the object referenced by mutex to
		an invalid value.

		A destroyed mutex object can be reinitialized using
		pthread_mutex_init(); the results of otherwise referencing the
		object after it has been destroyed are undefined.
	RETURN VALUE
		If successful, the pthread_mutex_destroy() and
		pthread_mutex_init() functions shall return zero; otherwise, an
		error number shall be returned to indicate the error.

pthread_mutex_lock & pthread_mutex_unlock
	https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
	SYNOPSIS
		#include <pthread.h>
		int pthread_mutex_lock(pthread_mutex_t *mutex);
		int pthread_mutex_trylock(pthread_mutex_t *mutex);
		int pthread_mutex_unlock(pthread_mutex_t *mutex);

	DESCRIPTION
		The mutex object referenced by mutex shall be locked by a call to
		pthread_mutex_lock() that returns zero or [EOWNERDEAD].  If the
		mutex is already locked by another thread, the calling thread
		shall block until the mutex becomes available. This operation
		shall return with the mutex object referenced by mutex in the
		locked state with the calling thread as its owner. If a thread
		attempts to relock a mutex that it has already locked,
		pthread_mutex_lock() shall behave as described in the Relock
		column of the following table. If a thread attempts to unlock a
		mutex that it has not locked or a mutex which is unlocked,
		pthread_mutex_unlock() shall behave as described in the Unlock
		When Not Owner column of the following table.
	    ┌────────────┬────────────┬────────────────┬───────────────────────┐
	    │ Mutex Type │ Robustness │     Relock     │ Unlock When Not Owner │
	    ├────────────┼────────────┼────────────────┼───────────────────────┤
	    │ NORMAL     │ non-robust │ deadlock       │ undefined behavior    │
	    ├────────────┼────────────┼────────────────┼───────────────────────┤
	    │ NORMAL     │ robust     │ deadlock       │ error returned        │
	    ├────────────┼────────────┼────────────────┼───────────────────────┤
	    │ ERRORCHECK │ either     │ error returned │ error returned        │
	    ├────────────┼────────────┼────────────────┼───────────────────────┤
	    │ RECURSIVE  │ either     │ recursive      │ error returned        │
	    │            │            │ (see below)    │                       │
	    ├────────────┼────────────┼────────────────┼───────────────────────┤
	    │ DEFAULT    │ non-robust │ undefined      │ undefined behavior†   │
	    │            │            │ behavior†      │                       │
	    ├────────────┼────────────┼────────────────┼───────────────────────┤
	    │ DEFAULT    │ robust     │ undefined      │ error returned        │
	    │            │            │ behavior†      │                       │
		└────────────┴────────────┴────────────────┴───────────────────────┘

	RETURN VALUE
	 	If successful, the pthread_mutex_lock(), pthread_mutex_trylock(),
		and pthread_mutex_unlock() functions shall return zero;
		otherwise, an error number shall be returned to indicate the error.

