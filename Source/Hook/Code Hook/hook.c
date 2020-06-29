#include <asm/unistd.h>
#include <asm/cacheflush.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/pgtable_types.h>
#include <linux/highmem.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <asm/cacheflush.h>
#include <linux/fdtable.h>
MODULE_LICENSE("GPL");
/*MY sys_call_table address*/

void **system_call_table_addr;
/*my custom syscall that takes process name*/
asmlinkage long (*open) (const char*, int, umode_t);
asmlinkage long (*write) (unsigned int, const char*, size_t);
///*hook*/
asmlinkage long hook_open(const char* filename, int flags, umode_t mode)
{
 	char buff[100];
 	copy_from_user(buff, filename, 100);
	if(strcmp(current->comm,"test") == 0){
 	printk(KERN_INFO "process name opens file: %s | hooked open: filename = %s\n", current->comm , buff);}
 return open(filename, flags, mode);
}
asmlinkage long hook_write(unsigned int fd, const char* buf, size_t len)
{

 	char *tmp;
        char *pathname;
        struct file *file;
        struct path *path;

        spin_lock(&current->files->file_lock);
        file = fcheck_files(current->files, fd);
        if (!file) {
                spin_unlock(&current->files->file_lock);
                return -ENOENT;
        }

        path = &file->f_path;
        path_get(path);
        spin_unlock(&current->files->file_lock);

        tmp = (char *)__get_free_page(GFP_KERNEL);

        if (!tmp) {
                path_put(path);
                return -ENOMEM;
        }

        pathname = d_path(path, tmp, PAGE_SIZE);
        path_put(path);
	if (IS_ERR(pathname)) {
                free_page((unsigned long)tmp);
                return PTR_ERR(pathname);
        }

	ssize_t bytes;
        bytes = (*write)(fd, buf, len);
	if(strcmp(current->comm,"test") == 0){
	printk(KERN_INFO "process name writes file: %s | hooked write: filename = %s, len = %d\n", current->comm, pathname, bytes);}
        free_page((unsigned long)tmp);
        return bytes;
}
/*Make page writeable*/
	int make_rw(unsigned long address){
 	unsigned int level;
 	pte_t *pte = lookup_address(address, &level);
 	if(pte->pte &~_PAGE_RW){
 	pte->pte |=_PAGE_RW;
 }
 return 0;
}
/* Make the page write protected */
int make_ro(unsigned long address){
 	unsigned int level;
 	pte_t *pte = lookup_address(address, &level);
 	pte->pte = pte->pte & ~_PAGE_RW;
 return 0;
}
static int __init entry_point(void){
 	printk(KERN_INFO "Hook loaded successfully..\n");
 	/*MY sys_call_table address*/
 	system_call_table_addr = (void*)0xffffffff81801680;
 	/* Replace custom syscall with the correct system call name
(write,open,etc) to hook*/
 	open = system_call_table_addr[__NR_open];
 	write = system_call_table_addr[__NR_write];
 /*Disable page protection*/
 	make_rw((unsigned long)system_call_table_addr);
 /*Change syscall to our syscall function*/
 	system_call_table_addr[__NR_open] = hook_open;
	 system_call_table_addr[__NR_write] = hook_write;
 return 0;
}
static int __exit exit_point(void){
	 printk(KERN_INFO "Unloaded Captain Hook successfully\n");
 /*Restore original system call */
	 system_call_table_addr[__NR_open] = open;
	 system_call_table_addr[__NR_write] = write;
 /*Renable page protection*/
	 make_ro((unsigned long)system_call_table_addr);
 return 0;
}
module_init(entry_point);
module_exit(exit_point);

