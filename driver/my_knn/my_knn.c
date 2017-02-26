#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <asm/io.h>

#define DEVICE_NAME         "my_knn_dev"

#define MY_KNN_DEV_ADDR	0x6A000000
#define MY_KNN_REG_NUM     11
#define MY_KNN_REG_WIDTH   32

static void __iomem *Knn_Regs;

static int my_knn_open(struct inode * inode , struct file * filp)
{
	return 0;
}

static int my_knn_release(struct inode * inode, struct file *filp)
{
	return 0;
}

static int my_knn_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
	int bytes_read=-1;
	int i=0;
	if(filp->f_flags & O_NONBLOCK)
		return -EAGAIN;
	if(length>0 && length<=(MY_KNN_REG_NUM*4))
	{
		for(i=0; i<length; i++)
		{
			*(buffer+i)=(char)ioread8(Knn_Regs+i);
		}
		bytes_read=i;
	}
	//返回-1表示错误
	return bytes_read;
}

static int my_knn_ioctl(struct file *filp, unsigned int reg_num, unsigned long arg)
{
	if(reg_num>=0 && reg_num<MY_KNN_REG_NUM)
	{
		iowrite32(arg, Knn_Regs+reg_num*4);
	}
	else
	{
		return -EINVAL;
	}
  
	return 0;
}

static const struct file_operations my_knn_fops =
{
	.owner = THIS_MODULE,
	.open = my_knn_open,
	.release = my_knn_release,
	.read = my_knn_read,
	.unlocked_ioctl = my_knn_ioctl,  
};

static struct miscdevice my_knn_dev =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &my_knn_fops,
};

int __init my_knn_init(void)
{
	int ret;
	Knn_Regs = ioremap(MY_KNN_DEV_ADDR, MY_KNN_REG_NUM);
	if(Knn_Regs == NULL)
	{
		return -EIO;
	} 
	ret = misc_register(&my_knn_dev);
	if (ret)
	{
		return ret;
	}
	return 0;
}

void __exit my_knn_exit(void)
{
	iounmap(Knn_Regs);
	misc_deregister(&my_knn_dev);
}

module_init(my_knn_init);
module_exit(my_knn_exit);

MODULE_AUTHOR("xiaoming");
MODULE_ALIAS("my_knn");
MODULE_DESCRIPTION("zedboard my_knn module");
MODULE_LICENSE("GPL");
