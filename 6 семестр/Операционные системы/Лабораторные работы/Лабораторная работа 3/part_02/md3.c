// Модифицированная версия модуля md2
#include <linux/init.h>
#include <linux/module.h>

#include "md.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KOSTEV");

// extern char *md1_noexport(void);
// extern char *md1_local(void);

static int __init md_init(void)
{
	printk("+ module md3 start!\n");
	printk("+ data string exported from md1 : %s\n", md1_data);
	printk("+ string returned md1_proc() is : %s\n", md1_proc());

	// printk("+ Попытка вызвать md1_noexport\n");
	// printk("+ string returned md1_noexport() is : %s\n", md1_noexport());
	// printk("+ md1_noexport был вызван\n");

	// printk("+ Попытка вызвать md1_local\n");
	// printk("+ string returned md1_local() is : %s\n", md1_local());
	// printk("+ md1_local был вызван\n");

	// Возвращает код ошибки, что приводит к тому, что модуль не будет загружен в ядро.
	// Но произойдёт это уже после выполнения кода инициализирующей функции модуля в пространстве ядра
	return -1;
}

module_init(md_init);

// Если такой модуль по замыслу не загружается,
// то он, в принципе, может не иметь функции выгрузки.