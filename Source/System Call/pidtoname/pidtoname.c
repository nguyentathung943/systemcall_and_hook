#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#include<linux/slab.h>
#define LENKERNEL 60

asmlinkage long sys_pidtoname(int pid, char* buf, int len){
    printk("WELCOME TO PIDTONAME\n");
    struct task_struct *task;
    char *process_name = kmalloc(LENKERNEL, GFP_KERNEL);

    for_each_process(task){  //compare to each task is running
	if (task_pid_nr(task) == pid){
  		strcpy(process_name, task->comm); //compare name
		if(strlen(task->comm) <= LENKERNEL)
		{
  			process_name[strlen(task->comm)]= 0;
		}
		
		printk("Process Name :=%s\n", process_name);
		copy_to_user(buf, process_name, len - 1);
		if (strlen(process_name) > len - 1)
		{
				return strlen(process_name); //// Length of string if found
		}
		else return 0;
		}
    }
    return -1; ///Error
}
