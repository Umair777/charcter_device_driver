#include"header.h"
#include"declarations.h"
	int noi;
	int noq;
	int i,j;
	Qset *qset;
	Qset *first;
Qset * allocdev(size_t fsize)
{	

	printk(KERN_ALERT "Allocdev Begins\n");
	noi=fsize/(noofreg*regsize);
	if(fsize%(noofreg*regsize)!=0)
	{
		noi++;
	}
	noq=fsize/(regsize);
	if(fsize%(regsize)!=0)
	{
		noq++;
	}
	for(i=0;i<noi;i++)
	{
		if(i==0)
		{
			first=(Qset *)kmalloc(sizeof(Qset),GFP_KERNEL);
			qset=first;
			if(!first)
			{
				printk(KERN_ERR "ldev->first ERROR\n");
			}
			memset(first,'\0',sizeof(Qset));
		}
		else
		{
			qset->next=(Qset*)kmalloc(sizeof(Qset),GFP_KERNEL);	
			if(!qset)
			{
				printk(KERN_ERR "qset ERROR\n");
			}
			memset(qset,'\0',sizeof(Qset));	
			qset=qset->next;
		}
		
	}
	for(i=0;i<noi;i++)
	{
		qset->data = kmalloc(sizeof(char *)*(noofreg*regsize),GFP_KERNEL);
			if(!qset->data)
			{
				printk(KERN_ERR "qset->next ERROR\n");
			}
		memset(qset->data,'\0',sizeof(char *)*(noofreg*regsize));	
		for(j=0;j<noofreg;j++)
		{
			qset[j].data = kmalloc(sizeof(char)*regsize,GFP_KERNEL);
			noq--;
			if(noq==0)
				break;
			memset(qset[j].data,'\0',sizeof(char)*regsize);	
		}
	
	}

#ifdef DEBUG
	printk(KERN_ALERT "Allocdev Ends\n");
#endif
//	return ldev->first;
	return 0;
}
