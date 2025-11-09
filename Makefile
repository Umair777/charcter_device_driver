INSTALL_DIR=modules
ifneq (${KERNELRELEASE},)
	obj-m := lkm107.o 

lkm107-objs := insert.o clean.o opendev.o

else 
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD :=$(shell pwd)
default : 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@rm -rf $(INSTALL_DIR)
	@mkdir $(INSTALL_DIR)
	@mv -f *.o *.ko *.mod.c .*.cmd $(INSTALL_DIR)
remove: 
	rm -rf $(INSTALL_DIR)
endif	
