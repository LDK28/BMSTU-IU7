#include <linux/module.h> // MODULE_LICENSE, MODULE_AUTHOR
#include <linux/kernel.h> // KERN_INFO
#include <linux/init.h>	  // ​Макросы __init и ​__exit
#include <linux/init_task.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KOSTEV");
MODULE_DESCRIPTION("My first module!");

static int __init md_init(void)
{
	struct task_struct *task = &init_task;

	do
	{
		printk(KERN_INFO "Module: %s - %d, parent: %s - %d\n",
			   task->comm, task->pid, task->parent->comm, task->parent->pid);
	} while ((task = next_task(task)) != &init_task);

	printk(KERN_INFO "Module: current: %s - %d, parent: %s - %d\n",
		   current->comm, current->pid, current->parent->comm, current->parent->pid);

	// printk(KERN_INFO "Module: module md start!\n");

	printk(KERN_INFO "Module: Hello world!\n");

	return 0;
}

static void __exit md_exit(void)
{
	printk(KERN_INFO "Module: Goodbye!\n");
}

module_init(md_init);
module_exit(md_exit);