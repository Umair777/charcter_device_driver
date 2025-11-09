# Character Device Driver — Detailed Guide

This README describes the architecture, user-to-kernel interaction, file-level responsibilities, usage commands, and a Makefile for a simple Linux character device driver. Replace placeholder names with the real file names and device name found in your updated-version branch.

## Quick summary
This project implements a loadable kernel module that registers a character device. User programs open the device node, issue read/write/ioctl calls, and the kernel driver services those requests using the Linux kernel APIs (cdev, file_operations, copy_to_user/copy_from_user, wait queues or mutexes).

---

## Contents
- Detailed description and design
- User ↔ kernel interaction flow
- Commands and usage (build, install, test, remove)
- Per-file descriptions
- Example Makefile (kernel module)
- Example user-space test program
- Troubleshooting checklist

---

## Detailed description and design

Driver responsibilities
- Register a device major number (dynamic or static).
- Initialize a cdev instance and add it to the kernel.
- Implement file operations: open, release, read, write, and optionally llseek, ioctl, poll.
- Use safe user-memory helpers: copy_to_user(), copy_from_user(), get_user(), put_user().
- Protect shared data with appropriate synchronization (mutex for sleeping contexts, spinlock for atomic contexts).
- Export kernel messages via pr_info/pr_err for debugging.

Typical internal data structures
- Device buffer: a byte buffer that stores data written by user space.
- Device state struct: holds cdev, dev_t (major/minor), mutex/wait_queue, buffer pointer, buffer size, and flags (open count, nonblocking).
- File operations table: struct file_operations with pointers to implemented callbacks.

Error handling
- Check and return appropriate -errno values for invalid inputs, buffer overflows, and failed memory allocations.
- Validate user pointers with access_ok (when necessary) and use copy_* helpers to avoid kernel crashes.

Memory model
- Keep kernel memory small and short-lived; allocate with kmalloc/kzalloc and free on module exit.
- Avoid sleeping in atomic contexts.

---

## User ↔ kernel interaction flow (step-by-step)

1. Installation
   - User runs insmod to insert the module. Kernel calls module_init, which:
     - Allocates/requests major number with alloc_chrdev_region()
     - Initializes and adds cdev with cdev_init() + cdev_add()
     - Allocates buffers and sets initial state
     - Prints device node info to dmesg (major/minor)

2. Device node
   - udev or the administrator creates /dev/<device_name> with mknod if necessary:
     - mknod /dev/<device_name> c <major> <minor>

3. Open
   - User process calls open("/dev/<device_name>", flags).
   - VFS calls driver -> open()
   - Driver checks exclusive-open constraints or increments open count and initializes per-file private data.

4. Read
   - User calls read(fd, buf, count).
   - VFS calls driver's read().
   - Driver copies data from kernel buffer to user buffer via copy_to_user().
   - If non-blocking and no data, return -EAGAIN or 0; if blocking, use wait queues to sleep until data arrives.

5. Write
   - User calls write(fd, buf, count).
   - VFS calls driver's write().
   - Driver copies data from user buffer to kernel via copy_from_user().
   - Driver may wake readers via wake_up_interruptible().

6. IOCTL / custom control
   - User calls ioctl(fd, request, arg).
   - Driver switches on request (use ioctl number macros _IO, _IOR, _IOW, _IOWR).
   - Use get_user/put_user or copy_from_user/copy_to_user for numeric or structured data.

7. Release
   - User closes file descriptor.
   - Kernel calls release(); driver frees per-file resources and decrements open count.

8. Removal
   - Admin calls rmmod; module_exit undoes cdev_add, frees buffers, and unregisters device numbers.

Key kernel APIs referenced
- alloc_chrdev_region, register_chrdev_region
- cdev_init, cdev_add, cdev_del
- copy_to_user, copy_from_user, get_user, put_user
- mutex_init / mutex_lock / mutex_unlock or spin_lock
- wait_queue_head_t, init_waitqueue_head, wait_event_interruptible, wake_up_interruptible

---

## Commands and common workflows

Prerequisites:
- Kernel headers matching running kernel
- build-essential (gcc, make)
- sudo or root

Build
- make

Install (insert module)
- sudo insmod <driver_module>.ko
- Check dmesg for the major number: dmesg | tail

Create device node (if not created)
- Get major from dmesg or /proc/devices
- sudo mknod /dev/<device_name> c <major> 0
- sudo chown $(whoami):$(whoami) /dev/<device_name>
- sudo chmod 660 /dev/<device_name>

Check module info
- lsmod | grep <module_name>
- modinfo <driver_module>.ko
- dmesg -w          # watch kernel messages live

Basic runtime tests
- echo "hello" > /dev/<device_name>
- cat /dev/<device_name>
- dd if=/dev/zero of=/dev/<device_name> bs=1 count=16
- ./userspace_test /dev/<device_name>  (if provided)

Use ioctl (example)
- Example: ioctl(fd, IOCTL_RESET)
- Build user-space test and call with device path and command names as defined in ioctl header.

Remove and clean
- sudo rmmod <module_name>
- make clean

---

## Files: purpose and description

Note: Replace placeholder names with actual file names in your updated-version branch.

- src/char_driver.c
  - Kernel module implementation.
  - Registers device numbers, initializes cdev, implements file_operations: open, release, read, write, llseek, ioctl (if present), and module init/exit.
  - Manages internal buffer and synchronization primitives.

- include/char_driver.h
  - Shared definitions used by kernel source and user-space tools (e.g., BUFFER_SIZE, IOCTL command codes).
  - Exposes ioctl numbers defined with _IO/_IOR/_IOW macros.

- src/ioctl_cmds.h (optional)
  - Central place for ioctl command definitions and data structures used for control calls.

- userspace/userspace_test.c
  - Example user-space program that demonstrates open, read, write, and ioctl usage.
  - Useful for functional tests and examples.

- Makefile
  - Kernel build integration that compiles the module against the running kernel headers.
  - Target names: all, clean, install (optional), test (optional).

- README.md
  - This file: usage and developer documentation.

- .gitignore
  - Ignore build artifacts (.o, *.ko, .mod.*, modules.order, etc.)

- udev rules (optional) e.g., 99-char-device.rules
  - Automatically creates device node with correct owner and mode on module load.

If your repo contains additional batch scripts (Batchfile is a major language), describe them here:
- build.bat / build.sh
  - Convenience wrappers for building or inserting modules on different OSes or environments.

---

## Example Makefile (kernel module)

```make
# Makefile - build the char driver against kernel headers
obj-m += char_driver.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

install: all
	sudo cp char_driver.ko /lib/modules/$(shell uname -r)/kernel/
	sudo depmod -a

.PHONY: all clean install
```

Replace char_driver.o with the actual module object name(s). If your source lives in subdirectories, adjust obj-m and M accordingly.

---

## Example user-space test program (simplified)

```c
/* userspace_test.c
   Compile: gcc -o userspace_test userspace_test.c
   Run: ./userspace_test /dev/<device_name>
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 128
/* Replace IOCTL_* with the real macros from include/ioctl_cmds.h */
#define IOCTL_GET_STATUS _IOR('q', 1, int)
#define IOCTL_RESET      _IO('q', 2)

int main(int argc, char **argv) {
    int fd, ret;
    char wbuf[] = "hello from user";
    char rbuf[BUF_SIZE];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s /dev/<device>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    ret = write(fd, wbuf, strlen(wbuf));
    if (ret < 0) perror("write");

    lseek(fd, 0, SEEK_SET); // if driver supports llseek semantics

    ret = read(fd, rbuf, BUF_SIZE-1);
    if (ret < 0) perror("read");
    else {
        rbuf[ret] = '\0';
        printf("read: '%s' (%d bytes)\n", rbuf, ret);
    }

    int status;
    if (ioctl(fd, IOCTL_GET_STATUS, &status) == 0) {
        printf("ioctl status: %d\n", status);
    } else {
        perror("ioctl");
    }

    if (ioctl(fd, IOCTL_RESET) != 0) {
        perror("ioctl reset");
    }

    close(fd);
    return 0;
}
```

---

## Common pitfalls and troubleshooting

- Module build fails:
  - Ensure linux-headers for currently running kernel are installed.
  - Verify KDIR in Makefile points to the correct kernel build directory.

- Module won't insert (insmod):
  - Inspect dmesg for init errors (missing memory, invalid parameters).
  - Resolve unresolved symbols by compiling against correct kernel version.

- Access denied to /dev/<device_name>:
  - Fix permissions: sudo chown $(whoami) /dev/<device_name>
  - Provide udev rule to set correct permissions automatically.

- copy_to_user/copy_from_user failures:
  - Validate user buffers and return -EFAULT on copying failures.

- Race conditions:
  - Use mutexes or spinlocks depending on whether your callbacks may sleep.

---

## Next steps
- Replace the placeholder file names and ioctl macros with exact names from your updated-version branch.
- Add unit tests or CI that builds the module on kernel headers available in your CI environment.
- Add udev rules if you want automatic /dev node creation and correct permissions on insertion.

---

If you provide the actual file names or paste the kernel module source and the main README contents here, I will:
- merge and remove placeholders,
- extract exact ioctl constants,
- update code examples to match your APIs,
- produce a finalized README.md to drop into the updated-version branch.
