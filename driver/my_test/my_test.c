#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/ioport.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <asm/io.h>

#define DEVICE_NAME         "my_test_dev"

#define MY_TEST_DEV_ADDR	0x75c20000	
#define MY_TEST_REG_NUM     2
#define MY_TEST_REG_WIDTH   32

static void __iomem *Test_Regs;

static int my_test_open(struct inode * inode , struct file * filp)
{
	return 0;
}

static int my_test_release(struct inode * inode, struct file *filp)
{
	return 0;
}

static int my_test_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
	int bytes_read = 0; 
	int i=0;
  
	if (filp->f_flags & O_NONBLOCK)
		return -EAGAIN;
  
	if (length>0 && length<=(MY_TEST_REG_NUM*4))
	{
		for(i=0;i<length;i++)
		{
			*(buffer+i)=(char)ioread8(Test_Regs+i);
		}
		bytes_read=i;
	}
	return bytes_read;
}

static int my_test_ioctl(struct file *filp, unsigned int reg_num, unsigned long arg)
{
	if(reg_num>=0 && reg_num<MY_TEST_REG_NUM)
	{
		iowrite32(arg, Test_Regs+reg_num*4);
		printk("my_test: Write 0x%x to 0x%x!\n", arg, Test_Regs+reg_num*4);
	}
	else
	{
		printk("my_test:[ERROR] Wrong register number!\n");
		return -EINVAL;
	}
  
	return 0;
}

static const struct file_operations my_test_fops =
{
	.owner = THIS_MODULE,
	.open = my_test_open,
	.release = my_test_release,
	.read = my_test_read,
	.unlocked_ioctl = my_test_ioctl,  
};

static struct miscdevice my_test_dev =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &my_test_fops,
};

int __init my_test_init(void)
{
	int ret, val;
	Test_Regs = ioremap(MY_TEST_DEV_ADDR, MY_TEST_REG_NUM);
	printk("my_test: Access address to device is:0x%x\n", (unsigned int)Test_Regs);
	if(Test_Regs == NULL)
	{
		printk("my_test:[ERROR] Access address is NULL!\n");
		return -EIO;
	} 
	ret = misc_register(&my_test_dev);
	if (ret)
	{
		printk("my_test:[ERROR] Misc device register failed\n");
		return ret;
	}
	printk("my_test: Tata! Module init complete\n");
	
	val = ioread32(Test_Regs);
	printk("my_test: Read 0x%x from switches, writing to LED...", val); 
//	iowrite32(val, Test_Regs+4);
	printk("OK!\n");

	return 0;
}

void __exit my_test_exit(void)
{
	iounmap(Test_Regs);
	misc_deregister(&my_test_dev);
  
	printk("my_test: Module exit\n");
}

module_init(my_test_init);
module_exit(my_test_exit);

MODULE_AUTHOR("xiaoming");
MODULE_ALIAS("my_test");
MODULE_DESCRIPTION("zedboard my_test module");
MODULE_LICENSE("GPL");
