#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#define MAX 32
/////// 314 -> PNAMETOID
/////// 315 -> PIDTONAME
int main(){
    char process_name[MAX]; ///PNAMETOID
    printf("Enter process' name to find: ");
    scanf("%s",process_name);
    strtok(process_name, "\n");
    printf("Your Input: %s \n",process_name);
    long int id = syscall(314,process_name); //syscall number 314 and passing in the string.
    printf("System call return: %ld \n",id); 
    if(id==-1){
	printf("Status: Process' name not found!\n");}
    else{
	    printf("Status: success!\n");
	    printf("Name = %s \n",process_name);    
	    printf("PID =  %ld \n",id);
	}


    char process_name_out[MAX]; ///PIDTONAME -> NAME OUT
    int ID; //----> Input ID
    printf("Input ID of process to find: \n");
    scanf("%d", &ID);
    int ret = syscall(315, ID, process_name_out, MAX);//syscall number 314 and passing in the ID
    if(ret!=-1){
    printf("Status: Success!\n");
    printf("Process' name: = %s\n",process_name_out);
    printf("PID =  %d \n",ID);
    }


    return 0;
}
