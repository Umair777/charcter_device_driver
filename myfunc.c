#include"header.h"
#include"declarations.h"
#include"fileoperations.h"
//EXPORT_SYMBOL(Mymodules);
int majorno,minorno,nod,devno,devno1;
int regsize,noofreg,devsize,datasize;
Dev *dev;
dev_t devid;
module_param(nod,int,S_IRUGO);
static int __init myfunc(void)
{
	int ret,i;
	printk(KERN_ALERT "hello kernel\n");
	majorno = MAJORNO;
	minorno = MINORNO;
	noofreg = NOOFREG;
	regsize = REGSIZE;
	devsize = DEVSIZE;
	datasize = DATASIZE;
	
        devno = alloc_chrdev_region(&devid,1,10,DEVNAME);
        if(devno != 0)
        {
                printk(KERN_ERR "register_chrdev failed\n");
                goto OUT;
        }
	majorno = MAJOR(devid);
//	minorno = MINOR(devid);
	printk(KERN_ALERT "Major no:%d\n",majorno);
//	printk("Minor no:%d\n",minorno);
	dev = kmalloc(sizeof(Dev)*nod,GFP_KERNEL);
	if(!dev)
	{
                printk(KERN_ERR "kmalloc failed\n");
		goto OUT;	
	}
	memset(dev,'\0',sizeof(Dev)*nod);
	for(i=0;i<nod;i++)
	{
	cdev_init(&dev[i].c_dev,&fops);
	devno1=MKDEV(majorno,i);	
	dev[i].noofreg = NOOFREG;
	dev[i].regsize = REGSIZE;
	dev[i].devsize = DEVSIZE;
	dev[i].datasize = DATASIZE;
	ret=cdev_add(&dev[i].c_dev,devno1,1);
	if(ret == -1)
	{
                printk(KERN_ERR "kmalloc failed\n");
		goto OUT;	
	}
	minorno = MINOR(devno1);
	printk(KERN_INFO "Minor no:%d\n",minorno);
	}
//	Mymodules();
	return 0;
OUT:
	return -1;
}
module_init(myfunc);
