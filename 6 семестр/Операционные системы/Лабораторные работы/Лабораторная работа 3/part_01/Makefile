CURRENT=$(shell uname -r)
KDIR=/lib/modules/$(CURRENT)/build
PWD=$(shell pwd)
TARGET1 = md
obj-m := $(TARGET1).o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order Module.*
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions

disclean: clean
	@rm *.ko *.symvers *.mod

load:
	sudo insmod md.ko

remove:
	sudo rmmod md.ko

info:
	modinfo md.ko

logs:
	dmesg 
