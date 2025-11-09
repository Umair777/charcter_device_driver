INSTALL_DIR=modules
ifneq (${KERNELRELEASE},)
        obj-m := lkm107.o

lkm107-objs := myfunc.o clean.o Mymodules.o Opendev.o Releasedev.o trimdev.o Writedev.o allocdev.o

else
        KERNELDIR ?= /lib/modules/$(shell uname -r)/build
        PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@rm -rf $(INSTALL_DIR)
	@mkdir $(INSTALL_DIR)
	@mv -f *.o *.ko *.mod.c .*.cmd $(INSTALL_DIR)
clean:
	rm -rf $(INSTALL_DIR)
endif
