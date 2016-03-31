KERN_SRC = /home/hello/linux-digilent-master
obj-m := my_test.o

all:
	make -C $(KERN_SRC) ARCH=arm M=`pwd` modules
clean:
	make -C $(KERN_SRC) ARCH=arm M=`pwd=` clean
