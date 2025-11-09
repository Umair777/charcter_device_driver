#include"header.h"
#include"declarations.h"
int OpenDevice()
{
	printf("%sBegin\n",__func__);
	int fd;
	fd=open("/home/anmolzehra/Projects/drivers/Testdriver/Mydev",O_WRONLY);

	if(fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("fd is :%d\n",fd);
	printf("%sEnd\n",__func__);
	return fd;
}
