#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
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
static int next_fortune = 0;  

ssize_t fortune_write(struct file *filep, const char __user *buf,
    size_t len, loff_t *offp);
ssize_t fortune_read(struct file *filep, char __user *buf,
    size_t count, loff_t *offp);

int fortune_open(struct inode *i, struct file * f) {
    printk(KERN_DEBUG "fortune: open fortune\n");
    return 0;
}

int fortune_release(struct inode *i, struct file *f) {
    printk(KERN_DEBUG "fortune: close fortune\n");
    return 0;
}

static struct proc_ops ops = {
    .proc_open = fortune_open,
    .proc_read = fortune_read,
    .proc_write = fortune_write,
    .proc_release = fortune_release, 
};


void cleanup_fortune_module(void);

static int __init init_fortune_module(void) {

  cookie_pot = (char *)vmalloc(MAX_COOKIE_LENGTH);
  if(!cookie_pot) {
    printk(KERN_ERR "fortune: vmalloc error\n");
    return -ENOMEM;
  }
  memset(cookie_pot, 0, MAX_COOKIE_LENGTH);

  proc_dir = proc_mkdir("fortune_dir", NULL);
  if (!proc_dir) {
    printk(KERN_INFO "fortune: Couldn't create proc dir.\n");
    
    cleanup_fortune_module();
    return -ENOMEM;
  }

  proc_file = proc_create("fortune", 0666, proc_dir, &ops);
  if (!proc_file) {
    printk(KERN_INFO "fortune: Couldn't create proc file.\n");
    cleanup_fortune_module();
    return -ENOMEM;
  } 
  proc_link = proc_symlink("proc_symlink", NULL, "fortune_dir/fortune");
  if (!proc_link)
  {
    printk(KERN_INFO "fortune: Couldn't create proc symlink.\n");
    cleanup_fortune_module();
    return -ENOMEM;
  }

  cookie_index = 0;
  next_fortune = 0;
  printk(KERN_INFO "fortune: Module loaded.\n");

  return 0;
}

void cleanup_fortune_module(void) {
  if (cookie_pot)
    vfree(cookie_pot);
  if (proc_link)
    remove_proc_entry("proc_symlink", NULL);
  if (proc_file)
    remove_proc_entry("fortune", proc_dir);
  if (proc_dir)
    remove_proc_entry("fortune_dir", NULL);
}

static void __exit exit_fortune_module(void) {
  cleanup_fortune_module();
  printk(KERN_INFO "fortune: unloaded\n");
}

module_init(init_fortune_module);
module_exit(exit_fortune_module);

ssize_t fortune_write(struct file *filep, const char __user *buf,
    size_t len, loff_t *offp) {

    printk(KERN_INFO "fortune: write\n");

  int avail = (MAX_COOKIE_LENGTH - cookie_index) + 1;

  if(len > avail) {
    printk(KERN_ERR "fortune: cookie_pot overflow\n");
    return -ENOSPC;
  }

  if(copy_from_user(&cookie_pot[cookie_index], buf, len)) {
    
    printk(KERN_ERR "fortune: copy from user error\n");
    return -EFAULT;
  }

  cookie_index += len;
  cookie_pot[cookie_index-1] = 0;

  return len;
}

ssize_t fortune_read(struct file *filep, char __user *buf,
    size_t count, loff_t *offp) {

  int len;

  if(*offp > 0 || !cookie_index) {
    printk(KERN_INFO "fortune: read\n");
    return 0;
  }

  if(next_fortune >= cookie_index) {
    next_fortune = 0;
  }

  len = snprintf(tmp, MAX_COOKIE_LENGTH, "%s\n", &cookie_pot[next_fortune]);
  if (copy_to_user(buf, tmp, len)) {
    printk(KERN_ERR "fortune: copy to user error\n");
    return -EFAULT;
  }

  next_fortune += len;
  *offp += len;
  return len;
}