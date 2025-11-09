#include"header.h"
#include"declarations.h"
int trimdev(Dev *ldev)
{
	#ifdef DEBUG
	printk(KERN_ALERT "trimdev Begins\n");
	#endif
	if(!ldev)
	{
	#ifdef DEBUG
	printk(KERN_ERR "Error in ldev\n");
	#endif	
	}
	if(ldev->first)
	{
	#ifdef DEBUG
	printk(KERN_ERR "ldev->first\n");
	#endif	
	}
	#ifdef DEBUG
	printk(KERN_ALERT "trimdev Ends\n");
	#endif
	return 0;
}
