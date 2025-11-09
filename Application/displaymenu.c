#include"header.h"
#include"declarations.h"
int displaymenu()
{
	int choice;
	printf("%s Begin\n",__func__);
	printf("<---------Displaymenu in Applications -------->\n");
	printf("1 : Open Device\n");
	printf("2 : Write in Device\n");
	printf("3 : Release Device\n");
	printf("0 : Exit\n");
	printf("Enter Choice\n");
	scanf("%d",&choice);
	printf("%s End\n",__func__);
	return choice;
}
