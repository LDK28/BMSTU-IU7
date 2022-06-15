#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/time.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Kostev Dmitry");

#define FS_MAGIC 0x11100D23
#define SLAB_NAME "my_vfs_cache"

// структура кеша slab
static struct kmem_cache *cache = NULL;
static void **cache_mem_area = NULL;

static void my_vfs_put_super(struct super_block *sb)
{
    printk(KERN_INFO "+ superblock destroy called.\n");
}

static struct super_operations const my_vfs_sup_ops = {
    .put_super = my_vfs_put_super,
    .statfs = simple_statfs,
    .drop_inode = generic_delete_inode,
};

static int my_vfs_fill_sb(struct super_block *sb, void *data, int silent)
{
    struct dentry *root;
    struct inode *root_inode;

    sb->s_blocksize = PAGE_SIZE;       // поскольку файловая система виртуальная, выделяемый объём памяти - страница
    sb->s_blocksize_bits = PAGE_SHIFT; // количество битов для сдвига для получения номера соответствующей страницы
    sb->s_magic = FS_MAGIC;
    sb->s_op = &my_vfs_sup_ops;

    root_inode = new_inode(sb);
    if (!root_inode)
    {
        printk(KERN_INFO "+ can't make root inode.");
        return -ENOMEM;
    }

    root_inode->i_ino = 1;
    printk(KERN_INFO "+ root inode = %lu", root_inode->i_ino);


    // 7 - все разрешено 5 - чтение и выполнение  владелец-член группы-другие
    // маска S_IFDIR - каталог
    root_inode->i_mode = S_IFDIR | 0755;

    root_inode->i_atime = root_inode->i_mtime = root_inode->i_ctime = current_time(root_inode);
    root_inode->i_op = &simple_dir_inode_operations;
    root_inode->i_fop = &simple_dir_operations;

    root = d_make_root(root_inode);
    if (!root)
    {
        printk(KERN_ERR "+ can't d_make_root.");
        return -ENOMEM;
    }

    sb->s_root = root;

    return 0;
}

static struct dentry *my_vfs_mount(struct file_system_type *type, int flags, const char *dev, void *data)
{
    // my_vfs_fill_sb - указатель на функцию, которая будет вызвана из mount_nodev для создания суперблока
    // nodev - Не различает файловые системы символьно-специальных и блочно-специальных устройств.
    struct dentry *const root_dentry = mount_nodev(type, flags, data, my_vfs_fill_sb);

    if (IS_ERR(root_dentry))
        printk(KERN_ERR "+ can't mount_nodev\n");
    else
        printk(KERN_INFO "+ VFS has been mounted.\n");

    return root_dentry;
}

static void my_kill_super(struct super_block *sb){
    printk(KERN_INFO "+ kill super block.\n");
    kill_anon_super(sb);
}

static struct file_system_type my_vfs_type = {
    .owner = THIS_MODULE,
    .name = "my_fs",
    .mount = my_vfs_mount,       
    .kill_sb = my_kill_super, 
};

static int __init my_vfs_init(void){
    int result_register = register_filesystem(&my_vfs_type);

    if (result_register != 0){
        printk(KERN_ERR "+ can't register_filesystem.");
        return result_register;
    }

    if ((cache_mem_area = kmalloc(sizeof(void*), GFP_KERNEL)) == NULL)
    {
        printk(KERN_ERR "+ failed to allocate memory.\n");
        return -ENOMEM;
    }

    if ((cache = kmem_cache_create(SLAB_NAME, 7, 0, SLAB_HWCACHE_ALIGN, NULL)) == NULL)
    {
        printk(KERN_ERR "+ can't kmem_cache_create.\n");
        kmem_cache_destroy(cache); 
        return -ENOMEM;
    }

    printk(KERN_INFO "+ module loaded.");
    return 0;
}

static void __exit my_vfs_exit(void)
{
    kmem_cache_destroy(cache);

    int result_unregister = unregister_filesystem(&my_vfs_type);
    if (result_unregister != 0){
        printk(KERN_ERR "+ can't unregister file system.");
    }
    else{
        printk(KERN_INFO "+ module is unloaded.");
    }
}

module_init(my_vfs_init);
module_exit(my_vfs_exit);