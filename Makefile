obj-m := jprobetest.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	@rm -f *.o *.ko *.order *.symvers *.mod.c

