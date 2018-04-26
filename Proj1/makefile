all: syscall.c context.c
	gcc -Wall syscall.c  -o syscall_run
	gcc -Wall context.c  -o context_run
runsc:
	./syscall_run
runcs:
	./context_run
clean:
	rm *_run
