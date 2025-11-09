#include"header.h"
#include"declarations.h"
static void __exit clean(void)
{
	int i;
        printk(KERN_ALERT "Bye kernel\n");
	kfree(dev);
	unregister_chrdev_region(devid,nod);
	for(i=0;i<nod;i++)
	{
	cdev_del(&dev[i].c_dev);
	}
}
module_exit(clean);

