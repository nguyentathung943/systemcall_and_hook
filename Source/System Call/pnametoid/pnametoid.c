#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/string.h>
#define MAX 32
asmlinkage long sys_pnametoid(char* name){
    printk("WELCOME TO PNAMETOID \n"); /// DEBUG ONLY
    struct task_struct *task;
    char charname[MAX];  //Placeholder
    copy_from_user(charname, name, MAX); ///Get data from user
    printk("Process name: = %s \n",charname); ///DEBUG ONLY
    for_each_process(task){
        /*compares the current process name (defined in task->comm) to the passed in name*/
        if(strcmp(task->comm,charname) == 0){
            return task_pid_nr(task); /// return the PID
        }
    }
    return -1; //// Not found anything
}
