#include"header.h"
#include"declarations.h"
int Writedevice(int fd)
{
	printf("%sBegin\n",__func__);
	char buff[]="Hello!!";
	int count;
	count=write(fd,buff,strlen(buff));
	printf("No. of bytes written:%d\n",count);
	printf("%sEnd\n",__func__);
	return 0;
}
