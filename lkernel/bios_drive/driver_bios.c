#define _POSIX_SOURCE
#include <linux/uaccess.h>
#include <asm/uaccess.h> /* copy_from_user, copy_to_user */
#include <linux/debugfs.h>
#include <linux/errno.h> /* EFAULT */
#include <linux/fs.h> /* file_operations */
#include <linux/kernel.h> /* min */
#include <linux/module.h>
#include <linux/printk.h> /* printk */
#include <uapi/linux/stat.h> /* S_IRUSR */

#define SPI_STATISTICS_HISTO_SIZE 17;

struct spi_statistics {
  spinlock_t lock;
  unsigned long           messages;
  unsigned long           transfers;
  unsigned long           errors;
  unsigned long           timedout;
  unsigned long           spi_sync;
  unsigned long           spi_sync_immediate;
  unsigned long           spi_async;
  unsigned long long      bytes;
  unsigned long long      bytes_rx;
  unsigned long long      bytes_tx;
  unsigned long transfer_bytes_histo[SPI_STATISTICS_HISTO_SIZE];
  unsigned long transfers_split_maxsize;
};



static struct dentry *debugfs_file;
static char data[] = {'a', 'b', 'c', 'd'};

static int open(struct inode *inode, struct file *filp)
{
    pr_info("open\n");
    return 0;
}

/* @param[in,out] off: gives the initial position into the buffer.
 *      We must increment this by the ammount of bytes read.
 *      Then when userland reads the same file descriptor again,
 *      we start from that point instead.
 * */
static ssize_t read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
    ssize_t ret;

    pr_info("read\n");
    pr_info("len = %zu\n", len);
    pr_info("off = %lld\n", (long long)*off);
    if (sizeof(data) <= *off) {
        ret = 0;
    } else {
        ret = min(len, sizeof(data) - (size_t)*off);
        if (copy_to_user(buf, data + *off, ret)) {
            ret = -EFAULT;
        } else {
            *off += ret;
        }
    }
    pr_info("buf = %.*s\n", (int)len, buf);
    pr_info("ret = %lld\n", (long long)ret);
    return ret;
}

/* Similar to read, but with one notable difference:
 * we must return ENOSPC if the user tries to write more
 * than the size of our buffer. Otherwise, Bash > just
 * keeps trying to write to it infinitely. */
static ssize_t write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    ssize_t ret;

    pr_info("write\n");
    pr_info("len = %zu\n", len);
    pr_info("off = %lld\n", (long long)*off);
    if (sizeof(data) <= *off) {
        ret = 0;
    } else {
        if (sizeof(data) - (size_t)*off < len) {
            ret = -ENOSPC;
        } else {
            if (copy_from_user(data + *off, buf, len)) {
                ret = -EFAULT;
            } else {
                ret = len;
                pr_info("buf = %.*s\n", (int)len, data + *off);
                *off += ret;
            }
        }
    }
    pr_info("ret = %lld\n", (long long)ret);
    return ret;
}

/*
Called on the last close:
http://stackoverflow.com/questions/11393674/why-is-the-close-function-is-called-release-in-struct-file-operations-in-the-l
*/
static int release(struct inode *inode, struct file *filp)
{
    pr_info("release\n");
    return 0;
}

static loff_t llseek(struct file *filp, loff_t off, int whence)
{
    loff_t newpos;

    pr_info("llseek\n");
    pr_info("off = %lld\n", (long long)off);
    pr_info("whence = %lld\n", (long long)whence);
    switch(whence) {
        case SEEK_SET:
            newpos = off;
            break;
        case SEEK_CUR:
            newpos = filp->f_pos + off;
            break;
        case SEEK_END:
            newpos = sizeof(data) + off;
            break;
        default:
            return -EINVAL;
    }
    if (newpos < 0) return -EINVAL;
    filp->f_pos = newpos;
    pr_info("newpos = %lld\n", (long long)newpos);
    return newpos;
}

static const struct file_operations fops = {
    /* Prevents rmmod while fops are running.
     * Try removing this for poll, which waits a lot. */
    .owner = THIS_MODULE,
    .llseek = llseek,
    .open = open,
    .read = read,
    .release = release,
    .write = write,
};

static int __init driver_init_bios(void)
{
    debugfs_file = debugfs_create_file("lkmc_fops", S_IRUSR | S_IWUSR, NULL, NULL, &fops);
    printk(KERN_INFO "driver_bios module loaded......\n");
    return 0;
}

static void __exit exit_bios(void)
{
    debugfs_remove_recursive(debugfs_file);
    printk(KERN_INFO "driver_bios module unloading......\n");
}

module_init(driver_init_bios);
module_exit(exit_bios);
MODULE_SUPPORTED_DEVICE("bios_test");
MODULE_LICENSE("GPL");
