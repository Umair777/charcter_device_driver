#include"header.h"
#include"declarations.h"
int Mymodules(void)
{	
	printk(KERN_ALERT "My module begins\n");
	printk(KERN_ALERT "My module ends\n");
	return 0;
}
