#ifndef MAJORNO
#define MAJORNO 1
#endif

#ifndef DEBUG
#define DEBUG 
#endif

#ifndef MINORNO
#define MINORNO 1
#endif

#ifndef NOD
#define NOD 1
#endif

#ifndef DEVNAME
#define DEVNAME "My_device"
#endif

#ifndef NOOFREG
#define NOOFREG 8
#endif

#ifndef REGSIZE
#define REGSIZE 4
#endif

#ifndef DEVSIZE
#define DEVSIZE 128
#endif
#ifndef DATASIZE
#define DATASIZE 0
#endif
typedef struct Qset
{
	struct Qset *next;
	void **data;
}Qset;


typedef struct 
{
	struct Qset *first;
	struct cdev c_dev;
	int regsize;
	int noofreg;
	int devsize;
	int datasize;
}Dev;

extern int regsize;
extern int noofreg;
extern int devsize;
extern int datasize;
extern Dev *dev;
extern int majorno,minorno,nod,devno;
extern dev_t devid;
int Mymodules(void);
int Opendev(struct inode *,struct file *);
int Releasedev(struct inode *,struct file *);
int trimdev(Dev *);
ssize_t Writedev(struct file *,const char __user *,size_t,loff_t * );
Qset * allocdev(size_t);
