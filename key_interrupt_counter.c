#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafal Rogalski");
MODULE_DESCRIPTION("Module for counting interrupts from keyboard");
MODULE_VERSION("0.1");

static uint64_t count = 0;

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
    count++;

    return (irq_handler_t)IRQ_HANDLED;
}

static int __init key_interrupt_counter_init(void) 
{
    printk(KERN_INFO "Key interrupt counter has beed loaded\n");
    return 0;
}

static void __exit key_interrupt_counter_exit(void) 
{
    printk(KERN_INFO "Key interrupt counter has beed unloaded\n");
}

module_init(key_interrupt_counter_init);
module_exit(key_interrupt_counter_exit);
