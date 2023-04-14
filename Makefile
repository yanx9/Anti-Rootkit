EXTRA_CFLAGS=include/
CC = gcc
obj-m += ARKm.o
ARKm-objs :=  main.o src/cr0.o src/syscall_handler.o src/interval.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean