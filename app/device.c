#include"headers.h"
#include"prototypes.h"
int device()
{
	int fd;
	printf("%s:Begin\n",__func__ );
	fd = open("../Mydriver",O_WRONLY);
	if(fd==-1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("%s:End\n",__func__ );
	return fd;
}
