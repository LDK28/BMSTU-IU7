#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Serova Maria");

#define MAX_COOKIE_LENGTH PAGE_SIZE

static char tmp[256];

static struct proc_dir_entry *proc_file = NULL;
static struct proc_dir_entry *proc_dir = NULL;
static struct proc_dir_entry *proc_link = NULL;

static char *cookie_pot = NULL;  
static int cookie_index = 0;  
static int next_seq_file = 0;  

ssize_t seq_file_write(struct file *filep, const char __user *buf,
    size_t len, loff_t *offp);

static int seq_file_show(struct seq_file *m, void *v) {
  
  printk(KERN_INFO "seq_file: show\n");
  if (!cookie_index)
    return 0;

  if (next_seq_file >= cookie_index) {
    next_seq_file = 0;
  }

  int len = snprintf(tmp, MAX_COOKIE_LENGTH, "%s\n", &cookie_pot[next_seq_file]);
  seq_printf(m, "%s", tmp);
  next_seq_file += len;
  return 0;
} 

static void *seq_file_start(struct seq_file *m, loff_t *pos)
{

  printk(KERN_INFO "seq_file: start\n");
  static unsigned long counter =0;
  if (!*pos) {
    return &counter;
  }
  else {
    *pos = 0;
    return NULL;
  }
}

static void *seq_file_next(struct seq_file *m, void *v, loff_t *pos) {
  printk(KERN_INFO "seq_file: next\n");
  unsigned long *tmp = (unsigned long *) v;
  (*tmp)++;
  (*pos)++;
  return NULL;
}

static void seq_file_stop(struct seq_file *m, void *v) {
  printk(KERN_INFO "seq_file: stop\n");
}

static struct seq_operations seq_file_ops = {
  .start = seq_file_start,
  .next = seq_file_next,
  .stop = seq_file_stop,
  .show = seq_file_show
};

static int seq_file_open(struct inode *i, struct file * f) {
    printk(KERN_DEBUG "seq_file: open seq_file\n");
    return seq_open(f, &seq_file_ops);
}

static struct proc_ops ops = {
    .proc_open = seq_file_open,
    .proc_read = seq_read,
    .proc_write = seq_file_write,
    .proc_lseek = seq_lseek,
    .proc_release = seq_release, 
};

void cleanup_seq_file_module(void);

static int __init init_seq_file_module(void) {

  cookie_pot = (char *)vmalloc(MAX_COOKIE_LENGTH);
  if(!cookie_pot) {
    printk(KERN_ERR "seq_file: vmalloc error\n");
    return -ENOMEM;
  }
  memset(cookie_pot, 0, MAX_COOKIE_LENGTH);

  proc_dir = proc_mkdir("seq_file_dir", NULL);
  if (!proc_dir) {
    printk(KERN_INFO "seq_file: Couldn't create proc dir.\n");
    
    cleanup_seq_file_module();
    return -ENOMEM;
  }

  proc_file = proc_create("seq_file", 0666, proc_dir, &ops);
  if (!proc_file) {
    printk(KERN_INFO "seq_file: Couldn't create proc file.\n");
    cleanup_seq_file_module();
    return -ENOMEM;
  } 
  proc_link = proc_symlink("proc_symlink", NULL, "seq_file_dir/seq_file");
  if (!proc_link)
  {
    printk(KERN_INFO "seq_file: Couldn't create proc symlink.\n");
    cleanup_seq_file_module();
    return -ENOMEM;
  }

  cookie_index = 0;
  next_seq_file = 0;
  printk(KERN_INFO "seq_file: Module loaded.\n");

  return 0;
}

void cleanup_seq_file_module(void) {
  if (cookie_pot)
    vfree(cookie_pot);
  if (proc_link)
    remove_proc_entry("proc_symlink", NULL);
  if (proc_file)
    remove_proc_entry("seq_file", proc_dir);
  if (proc_dir)
    remove_proc_entry("seq_file_dir", NULL);
}

static void __exit exit_seq_file_module(void) {
  cleanup_seq_file_module();
  printk(KERN_INFO "seq_file: unloaded\n");
}

module_init(init_seq_file_module);
module_exit(exit_seq_file_module);

ssize_t seq_file_write(struct file *filep, const char __user *buf,
    size_t len, loff_t *offp) {

  printk(KERN_INFO "seq_file: write\n");

  int avail = (MAX_COOKIE_LENGTH - cookie_index) + 1;

  if(len > avail) {
    printk(KERN_ERR "seq_file: cookie_pot overflow\n");
    return -ENOSPC;
  }

  if(copy_from_user(&cookie_pot[cookie_index], buf, len)) {
    
    printk(KERN_ERR "seq_file: copy from user error\n");
    return -EFAULT;
  }

  cookie_index += len;
  cookie_pot[cookie_index-1] = '\0';

  return len;
}
