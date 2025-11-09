
#include"headers.h"
#include"prototypes.h"
int displaymenu()
{
	printf("%s : Begin\n",__func__);
	int choice;
	
	printf("Do you want to open file in the device driver\n");
	printf("press 1 to open Device_driver file\n");
	printf("press 2 to close Device_driver file\n");
	scanf("%d",&choice);
	printf("%s : End\n",__func__);
	return choice;
}
