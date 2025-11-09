#include"header.h"
#include"declarations.h"
Dev *ldev;
int Opendev(struct inode *inodep,struct file *filep)
{
	int ret;
	#ifdef DEBUG
	printk(KERN_ALERT "Opendev Begins\n");
	#endif
	ldev=dev;
	ldev=container_of(inodep->i_cdev,Dev,c_dev);	
	if(!ldev)
	{
	#ifdef DEBUG
	printk(KERN_ERR "ERROR in container_of\n");
	#endif	
	goto OUT;
	}
	if((filep->f_flags & O_ACCMODE)== O_WRONLY)
	{
		ret=trimdev(ldev);	
		if(ret !=0)
		{
		#ifdef DEBUG
		printk(KERN_ERR "Error in ret\n");
		#endif	
		goto OUT;
		}
	}
	#ifdef DEBUG
	printk(KERN_ALERT "Opendev Ends\n");
	#endif
	filep->private_data=ldev;
	return 0;
OUT:
	#ifdef DEBUG
	printk(KERN_ERR "ERROR and exit\n");
	#endif	
	return -1;	
}
