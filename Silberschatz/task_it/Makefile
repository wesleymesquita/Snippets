KDIR = /lib/modules/`uname -r`/build
EXTRA_CFLAGS = -Wall -g

obj-m = task_iterator.o

kbuild:
	make -C $(KDIR) M=`pwd`

clean:
	make -C $(KDIR) M=`pwd` clean
