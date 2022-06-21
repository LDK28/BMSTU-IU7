#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/init_task.h>
#include <linux/ktime.h>

#define KEYBOARD_IRQ 1
#define KBD_DATA_REG 0x60
#define KBD_SCANCODE_MASK 0x7f
#define KBD_STATUS_MASK 0x80
#define KEYS_COUNT 83

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kostev Dmitry");

static int id;

struct tasklet_struct *kb_tasklet;

char *keyboard_key[] =
	{
		"[ESC]",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"-",
		"=",
		"bs",
		"[Tab]",
		"Q",
		"W",
		"E",
		"R",
		"T",
		"Y",
		"U",
		"I",
		"O",
		"P",
		"[",
		"]",
		"[Enter]",
		"[CTRL]",
		"A",
		"S",
		"D",
		"F",
		"G",
		"H",
		"J",
		"K",
		"L",
		";",
		"\'",
		"`",
		"[LShift]",
		"\\",
		"Z",
		"X",
		"C",
		"V",
		"B",
		"N",
		"M",
		",",
		".",
		"/",
		"[RShift]",
		"[PrtSc]",
		"[Alt]",
		" ", // Space
		"[Caps]",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"[Num]",
		"[Scroll]",
		"[Home(7)]",
		"[Up(8)]",
		"[PgUp(9)]",
		"-",
		"[Left(4)]",
		"[Center(5)]",
		"[Right(6)]",
		"+",
		"[End(1)]",
		"[Down(2)]",
		"[PgDn(3)]",
		"[Ins]",
		"[Del]",
};

void kb_tasklet_handler(unsigned long data)
{
	printk(KERN_INFO "TASKLET: -------------------------");

	printk(KERN_INFO "TASKLET: state - %ld, count - %d, data - %d\n",
		   kb_tasklet->state, kb_tasklet->count, kb_tasklet->data);

	int scancode = kb_tasklet->data;

	if (scancode & KBD_STATUS_MASK)
	{
		scancode &= KBD_SCANCODE_MASK;
		if (scancode > KEYS_COUNT)
			printk("TASKLET: there is no such keyboard key");
		else
			printk("TASKLET: keyboard key %s is released", keyboard_key[scancode - 1]);
	}
	else
	{
		scancode &= KBD_SCANCODE_MASK;
		if (scancode > KEYS_COUNT)
			printk("TASKLET: there is no such keyboard key");
		else
			printk("TASKLET: keyboard key %s is pressed", keyboard_key[scancode - 1]);
	}

	printk(KERN_INFO "TASKLET: -------------------------");
}

static irqreturn_t interrupt_handler(int irq, void *dev_id)
{
	int scancode = inb(KBD_DATA_REG);

	printk(KERN_INFO "TASKLET: called by keyboard_irq\n");
	kb_tasklet->data = scancode;

	printk(KERN_INFO "TASKLET: state (before) - %ld, count - %d, data - %d\n",
		   kb_tasklet->state, kb_tasklet->count, kb_tasklet->data);

	printk(KERN_INFO "TASKLET: Keyboard tasklet scheduled");

	tasklet_schedule(kb_tasklet);

	printk(KERN_INFO "TASKLET: state (after) - %ld, count - %d, data - %d\n",
		   kb_tasklet->state, kb_tasklet->count, kb_tasklet->data);

	return IRQ_HANDLED;
}

static int __init mod_init(void)
{
	if (request_irq(KEYBOARD_IRQ, interrupt_handler, IRQF_SHARED, "interrupt_with_tasklet", &interrupt_handler))
	{
		printk(KERN_ERR "TASKLET: Error on request_irq\n");
		return -1;
	}

	kb_tasklet = kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
	if (kb_tasklet == NULL)
	{
		printk(KERN_ERR "TASKLET: cannot allocate Memory");
		return -1;
	}

	tasklet_init(kb_tasklet, kb_tasklet_handler, (unsigned long)kb_tasklet->data);

	printk(KERN_INFO "TASKLET: Module loaded!\n");
	return 0;
}

static void __exit mod_exit(void)
{
	tasklet_kill(kb_tasklet);
	kfree(kb_tasklet);

	free_irq(KEYBOARD_IRQ, &interrupt_handler);
	printk(KERN_INFO "TASKLET: Module unloaded!\n");
}

module_init(mod_init);
module_exit(mod_exit);