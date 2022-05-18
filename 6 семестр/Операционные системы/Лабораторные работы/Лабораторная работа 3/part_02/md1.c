// Вызываемый модуль ядра Linux
#include <linux/init.h>	  // ​Макросы __init и ​__exit
#include <linux/module.h> // MODULE_LICENSE, MODULE_AUTHOR

#include "md.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KOSTEV");

// До тех пор, пока число ссылок на любой модуль в системе 
// не станет нулевым, модуль не может быть выгружен;

// API ядра - это множество экспортируемых имён ядра.

char *md1_data = "Hello, World!";

extern char *md1_proc(void)
{
	return md1_data;
}

static char *md1_local(void)
{
	return md1_data;
}

extern char *md1_noexport(void)
{
	return md1_data;
}

// Любой другой модуль может использовать в своём
// коде любые экспортируемые имена.
EXPORT_SYMBOL(md1_data);
EXPORT_SYMBOL(md1_proc);

static int __init md_init(void)
{
	// "+" - это маркер, отмечающий вывод из собственных модулей.
	// Чтобы дальше можно было легко найти сообщения с помощью grep.
	printk(KERN_INFO "+ module md1 start!\n");
	return 0;
}

static void __exit md_exit(void)
{
	printk(KERN_INFO "+ module md1 unloaded!\n");
}

module_init(md_init);
module_exit(md_exit);