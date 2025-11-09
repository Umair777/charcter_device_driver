#include"headers.h"
#include"prototypes.h"
int main()
{
	int choice;
	printf("App %s : Begin\n",__FILE__);
	choice = displaymenu();
	int fd;
	switch(choice)
	{
		case 1:	
			fd = device();	
/*			if(!fd)
			{
				perror("open_failed");
				exit(EXIT_FAILURE);
			}
*/
			printf("File opened with kernel fd = %d\n",fd);
			break;

		case 2:

			close(fd);
			break;

	}
	printf("App %s : End\n",__FILE__);
	return 0;
}
