#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/init_task.h>
#include <linux/ktime.h>
#include <linux/delay.h>

#define KEYBOARD_IRQ 1
#define KBD_DATA_REG 0x60
#define KBD_SCANCODE_MASK 0x7f
#define KBD_STATUS_MASK 0x80
#define KEYS_COUNT 83

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kostev Dmitry");

static int id;

static struct workqueue_struct *wq;

typedef struct
{
	struct work_struct work;
	unsigned long data;
} work_t;

work_t *kb_work;
work_t *time_work;

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

void kb_wq_handler(struct work_struct *work)
{
	printk(KERN_INFO "KEYBOARD WORK: -------------------------");

	printk(KERN_INFO "KEYBOARD WORK: data - %d\n", kb_work->data);
	unsigned long scancode = kb_work->data;

	if (scancode & KBD_STATUS_MASK)
	{
		scancode &= KBD_SCANCODE_MASK;
		if (scancode > KEYS_COUNT)
			printk("KEYBOARD WORK: there is no such keyboard key");
		else
			printk("KEYBOARD WORK: keyboard key %s is released", keyboard_key[scancode - 1]);
	}
	else
	{
		scancode &= KBD_SCANCODE_MASK;
		if (scancode > KEYS_COUNT)
			printk("KEYBOARD WORK: there is no such keyboard key");
		else
			printk("KEYBOARD WORK: keyboard key %s is pressed", keyboard_key[scancode - 1]);
	}

	printk(KERN_INFO "KEYBOARD WORK: -------------------------");
}

void time_wq_handler(struct work_struct *work)
{
	printk(KERN_INFO "TIME WORK: -------------------------");

	printk(KERN_INFO "TIME WORK: time work sleep begin");
	msleep(30);
	printk(KERN_INFO "MTIME WORK: tine work sleep end");

	struct timespec64 tm;
	ktime_get_real_ts64(&tm);
	tm.tv_sec += 3 * 3600;

	printk(KERN_INFO "TIME WORK: data - %ld, time - %.2llu:%.2llu:%.2llu\n",
		   time_work->data,
		   (tm.tv_sec / 3600) % (24),
		   (tm.tv_sec / 60) % (60),
		   tm.tv_sec % 60);

	printk(KERN_INFO "TIME WORK: -------------------------");
}

static irqreturn_t interrupt_handler(int irq, void *dev_id)
{
	if (irq == KEYBOARD_IRQ)
	{
		unsigned long scancode = inb(KBD_DATA_REG);
		printk(KERN_INFO "WORKQUEUE: Keyboard works queued\n");

		kb_work->data = scancode;

		queue_work(wq, &kb_work->work);

		time_work->data = scancode;

		queue_work(wq, &time_work->work);

		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}

static int __init mod_init(void)
{

	if (request_irq(KEYBOARD_IRQ, interrupt_handler, IRQF_SHARED, "interrupt_with_worqueue", &interrupt_handler))
	{
		printk(KERN_ERR "WORKQUEUE: Error on request_irq\n");
		return -1;
	}

	wq = create_workqueue("work_queue");
	if (!wq)
	{
		free_irq(KEYBOARD_IRQ, &id);
		printk(KERN_INFO "WORKQUEUE: error create_workqueue()!\n");
		return -1;
	}
	printk(KERN_INFO "WORKQUEUE: workqueue created!\n");

	kb_work = (work_t *)kmalloc(sizeof(work_t), GFP_KERNEL);
	if (!kb_work)
	{
		destroy_workqueue(wq);
		free_irq(KEYBOARD_IRQ, &interrupt_handler);
		printk(KERN_INFO "WORKQUEUE: memory allocation error!\n");
		return -1;
	}

	time_work = (work_t *)kmalloc(sizeof(work_t), GFP_KERNEL);
	if (!time_work)
	{
		kfree(kb_work);
		destroy_workqueue(wq);
		free_irq(KEYBOARD_IRQ, &id);
		printk(KERN_INFO "WORKQUEUE: memory allocation error!\n");
		return -1;
	}

	INIT_WORK(&kb_work->work, kb_wq_handler);
	INIT_WORK(&time_work->work, time_wq_handler);
	printk(KERN_INFO "WORKQUEUE: Module loaded!\n");
	return 0;
}

static void __exit mod_exit(void)
{
	kfree(kb_work);
	kfree(time_work);
	flush_workqueue(wq);
	destroy_workqueue(wq);

	free_irq(KEYBOARD_IRQ, &id);
	printk(KERN_INFO "WORKQUEUE: Module unloaded!\n");
}

module_init(mod_init);
module_exit(mod_exit);