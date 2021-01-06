#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

static int __init key_interrupt_counter_init(void) {
    printk(KERN_INFO "Key interrupt counter has beed loaded\n");
    return 0;
}

static void __exit key_interrupt_counter_exit(void) {
    printk(KERN_INFO "Key interrupt counter has beed unloaded\n");
}

module_init(key_interrupt_counter_init);
module_exit(key_interrupt_counter_exit);