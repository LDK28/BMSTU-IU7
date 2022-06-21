ifneq ($(KERNELRELEASE),)
	obj-m := main.o
else
	CURRENT = $(shell uname -r)
	KDIR = /lib/modules/$(CURRENT)/build
	PWD = $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	#make clean

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions

disclean: clean
	@rm *.ko *.symvers
	@rm *.mod
endif 

load:
	sudo insmod main.ko
mod:
	lsmod 
log:
	sudo dmesg -wH
remove:
	sudo rmmod main.ko