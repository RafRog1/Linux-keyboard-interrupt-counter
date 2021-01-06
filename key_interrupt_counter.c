#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/ktime.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define GET_COUNT       _IOR('a', 'a', uint64_t*)
#define RESET_COUNT     _IO('a', 'b')
#define GET_COUT_TIME   _IOR('a', 'c', uint32_t*)

static uint64_t count = 0;
static int irq = 1, dev_irq = 0;
static ktime_t time;

static ssize_t read(struct file *file, char __user *buf, size_t len, loff_t *off);
static ssize_t write(struct file *file, const char __user *buf, size_t len, loff_t *off);
static int open(struct inode *inode, struct file *file);
static long ioctl(struct file *file, unsigned int cmd, unsigned long arg);
static int release(struct inode *inode, struct file *file);

static struct file_operations fops = {
    .owner          = THIS_MODULE,
    .read           = read,
    .write          = write,
    .open           = open,
    .unlocked_ioctl = ioctl,
    .release        = release,
};

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
    count++;

    return (irq_handler_t)IRQ_HANDLED;
}

static int __init key_interrupt_counter_init(void) 
{
    printk(KERN_INFO "Key interrupt counter has beed loaded\n");
    time = ktime_get_real();
    return request_irq (irq, (irq_handler_t)irq_handler, IRQF_SHARED, "kbd_irq_handler", (void *)(&dev_irq));
}

static void __exit key_interrupt_counter_exit(void) 
{
    printk(KERN_INFO "Key interrupt counter has beed unloaded\n");
    synchronize_irq(irq);
    free_irq(irq, &dev_irq);
}

static ssize_t read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Read function\n");
    return 0;
}
static ssize_t write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Write function\n");
    return 0;
}
static int open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device file open!\n");
    return 0;
}
static int release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Device file close!\n");
    return 0;
}
static long ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    uint32_t sec;
    
    switch(cmd){
        case GET_COUNT:
            copy_to_user((uint64_t *)arg, &count, sizeof(count));
            break;
        case RESET_COUNT:
            count = 0;
            time = ktime_get_real();
            break;
        case GET_COUT_TIME:
            sec = time / (1000 * 1000 * 1000);
            copy_to_user((uint32_t *)arg, &sec, sizeof(sec));
        default:
            break;
    }
    return 0;
}


module_init(key_interrupt_counter_init);
module_exit(key_interrupt_counter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafal Rogalski");
MODULE_DESCRIPTION("Module for counting interrupts from keyboard.");
MODULE_VERSION("0.1");
