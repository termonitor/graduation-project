KERN_SRC = /home/lenovo/linux-digilent-master
obj-m := my_knn.o

all:
	make -C $(KERN_SRC) ARCH=arm M=`pwd` modules
clean:
	make -C $(KERN_SRC) ARCH=arm M=`pwd=` clean
