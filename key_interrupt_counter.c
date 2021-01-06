#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/ktime.h>

#define GET_COUNT       _IOR('a', 'a', uint64_t*)
#define RESET_COUNT     _IO('a', 'b')
#define GET_COUT_TIME   _IOR('a', 'c', uint32_t*)

static uint64_t count = 0;
static int irq = 1, dev = 0;
static ktime_t time;

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
    count++;

    return (irq_handler_t)IRQ_HANDLED;
}

static int __init key_interrupt_counter_init(void) 
{
    printk(KERN_INFO "Key interrupt counter has beed loaded\n");
    time = ktime_get_real();
    return request_irq (irq, (irq_handler_t)irq_handler, IRQF_SHARED, "kbd_irq_handler", (void *)(&dev));
}

static void __exit key_interrupt_counter_exit(void) 
{
    printk(KERN_INFO "Key interrupt counter has beed unloaded\n");
    synchronize_irq(irq);
    free_irq(irq, &dev);
}

module_init(key_interrupt_counter_init);
module_exit(key_interrupt_counter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rafal Rogalski");
MODULE_DESCRIPTION("Module for counting interrupts from keyboard.");
MODULE_VERSION("0.1");
