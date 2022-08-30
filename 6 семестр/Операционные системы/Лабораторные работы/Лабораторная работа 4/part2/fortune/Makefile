# ifneq ($(KERNELRELEASE),)
obj-m := fortune.o
# else
CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build/
PWD = $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions
disclean: clean
	@rm *.ko *.symvers
# endif