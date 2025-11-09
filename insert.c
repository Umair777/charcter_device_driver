#include"headers.h"
#include"declarations.h"
#include"fileoperations.h"
int majorno,minorno,nod,dev_reg;
char *devname;
Dev *dev;
int dev2;
dev_t devid,devno;
static int __init insert(void)
{
	int cdevadd;
        nod = NOD;
        devname = DEVNAME;
	majorno=MAJORNO;
	minorno=MINORNO;
        printk(KERN_ALERT "Hello Kernel again \n");
        dev_reg = alloc_chrdev_region(&devid,minorno,nod,devname);
        if(dev_reg != 0)
        {
                printk(KERN_INFO"Device Registration Failed\n");
                goto OUT;
        }
        majorno = MAJOR(devid);
	minorno = MINOR(devid);
        printk("major no = %d\n",majorno);
        printk("minor no = %d\n",minorno);
	dev =(Dev*)kmalloc(sizeof(Dev),GFP_KERNEL);
        if(!dev)
        {
                printk(KERN_INFO"device kmalloc failed\n");
                goto OUT;
        }
	memset(dev,'\0',sizeof(Dev));
	
	cdev_init(&dev->c_dev,&fops);
//	devno =	MKDEV(majorno,nod);	
 	cdevadd = cdev_add(&dev->c_dev,devid,nod);
	if(cdevadd == 0)
	{
                printk(KERN_INFO"device adding..\n");
	}
return 0;
OUT :
        return -1;

}
module_init(insert);

