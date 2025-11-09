#include"header.h"
#include"declarations.h"
ssize_t Writedev(struct file *filep,const char __user *ubuff,size_t size,loff_t *offp)
{
	Dev *ldev;
	size_t lsize;
	#ifdef DEBUG
	printk(KERN_ALERT "Writedev Begins\n");
	#endif
	ldev=filep->private_data;	
	if(size>devsize)
	{
		lsize=devsize;	
		#ifdef DEBUG
		printk(KERN_ALERT "Partial writing of data will be done\n");
		#endif
	}
	else
	{
		lsize=size;
	}
	ldev->first=allocdev(lsize);
	#ifdef DEBUG
	printk(KERN_ALERT "Writedev Ends\n");
	#endif
	return 0;
}
