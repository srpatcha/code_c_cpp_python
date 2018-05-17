Makefile help 

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello_data __init_data= 47;
static int __init hello2_init(void)
{
	printk("<1>Hello world 2. %d \n", hello_data);
	return 0;
}

static void __exit hello2_exit(void)
{
	printk("KERN_ALERT "Goodbye cruel world 2.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
"


WARN := −W −Wall −Wstrict−prototypes −Wmissing−prototypes
INCLUDE := −isystem /lib/modules/`uname −r`/build/include
CFLAGS := −O2 −DMODULE −D__KERNEL__ ${WARN} ${INCLUDE}
CC := gcc−3.0
OBJS := ${patsubst %.c, %.o, ${wildcard *.c}}
all: ${OBJS}
.PHONY: clean
clean:
rm −rf *.o




           Debugging Techniques

printk()  Oops
CONFIG_DEBUG_KERNEL
SysRq keys
(Unofficial) kernel debuggers [Not ARM]
gdb, kdb, kgdb, nlkd
/proc
strace
User Mode Linux (UML)
Linux Trace Toolkit (LTT)
Dynamic Probes (DProbes) [Intel]
- Intermittent or timing-related bugs very difficult

Sources:
Love 2e: Chapter 18 "Debugging" (2.6)
Corbet, Rubini, Kroah-Hartman 3e: Chapter 4 "Debugging Techniques" (2.6)


