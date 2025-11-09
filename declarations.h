#ifndef MAJORNO
#define MAJORNO 0
#endif
#ifndef MINORNO
#define MINORNO 0
#endif
#ifndef NOD
#define NOD 1
#endif
extern int majorno;
extern int minorno,nod;
#ifndef DEVNAME
#define DEVNAME "UMAIRS_FIRST_DRIVER"
#endif
typedef struct Qset
	{
		struct Qset *next;
		void **data;
	}Qset;

typedef struct
{
	struct cdev c_dev;
	struct Qset *first;

}Dev;
extern Dev *dev;
extern int dev2;
extern dev_t devid;
int opendev(struct inode *,struct file *);
