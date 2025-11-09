#include"header.h"
#include"declarations.h"
int main()
{
	int choice,fd;
	printf("In app : %sBegin\n",__func__);
	while(1)
	{
	choice=displaymenu();
	printf("%d\n",choice);
	switch(choice)
	{
		case 1:
			fd=OpenDevice();
			break;
		case 2:
			Writedevice(fd);
			break;
		case 3:
			close(fd);
			break;
		default:
			return -1;
	}
	}
	printf("In app : %sEnd\n",__func__);
	return 0;
}
