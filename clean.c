#include"headers.h"
#include"declarations.h"

static void  __exit remove(void)
{
	printk(KERN_ALERT "Bye For Now Kernel\n");
	kfree(dev);
	
	unregister_chrdev_region(devid,NOD);
}
module_exit(remove);
