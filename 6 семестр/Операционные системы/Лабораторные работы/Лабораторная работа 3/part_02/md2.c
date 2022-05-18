// Вызывающий модуль ядра Linux
#include <linux/init.h>
#include <linux/module.h>

#include "md.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KOSTEV");

static int __init md_init(void)
{
	printk("oslabmodule Module md2 was loaded\n");
    printk("oslabmodule Value exported from md1 : %s\n", md1_data);
    printk("oslabmodule Value returned from function md1_proc is : %s\n", md1_proc()); // md1_noexport());

	return 0;
}

static void __exit md_exit(void)
{
	printk("oslabmodule Module md2 was unloaded\n"); 
}

module_init(md_init);
module_exit(md_exit);