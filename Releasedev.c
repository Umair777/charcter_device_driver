#include"header.h"
#include"declarations.h"
int Releasedev(struct inode *inodep,struct file *filep)
{
	printk(KERN_ALERT "Releasedev Begins\n");
	printk(KERN_ALERT "Releasedev Ends\n");
	return 0;
}
