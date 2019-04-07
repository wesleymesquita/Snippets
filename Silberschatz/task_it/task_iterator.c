#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("Task Iterator module");
MODULE_AUTHOR("Wesley");
MODULE_LICENSE("GPL");

static int get_state(long state){
	if (state == -1)
		return 0;
	else if (state == 0)
		return 1;
	else
		return 2;
}

static int task_iterator_init(void)
{
	struct task_struct *task;
	int count;
	const char* TASK_STATE[3] = {"UNRUNNABLE", "RUNNABLE", "STOPPED"};
	printk(KERN_INFO "Initiated Task Iterator Module"); 
	count = 0;
	for_each_process(task){
		printk(KERN_INFO "Task %s is %s. Pid: %d", task->comm, TASK_STATE[get_state(task->state)], task->pid);
		count++;
	}		
	printk(KERN_INFO "Listed %d tasks", count);
	return  0;
}

static void task_iterator_exit(void)
{
	printk(KERN_INFO "Ended Task Iterator Module");
}

module_init(task_iterator_init);
module_exit(task_iterator_exit);
