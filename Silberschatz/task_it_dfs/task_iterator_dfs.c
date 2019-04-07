#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/string.h>

#define BUF_SIZE 128

char buf[BUF_SIZE];

MODULE_DESCRIPTION("Task Iterator module");
MODULE_AUTHOR("Wesley");
MODULE_LICENSE("GPL");



static void visit_task(struct task_struct *task, int nspaces)
{
	struct list_head *list;
	struct task_struct *child_task;

	memset(buf, 0, BUF_SIZE);
	memset(buf, '\t', nspaces);
	strcpy((((void*)buf)+nspaces), task->comm);
	printk(KERN_INFO "%s (%d)", buf, task->pid);
	list_for_each(list, &task->children){
		child_task = list_entry(list, struct task_struct, sibling);
		if(task)
			visit_task(child_task, nspaces+1);
	}
		
}

static int task_iterator_init(void)
{
	visit_task(&init_task, 0);
	return  0;
}

static void task_iterator_exit(void)
{
	printk(KERN_INFO "Ended Task Iterator Module");
}

module_init(task_iterator_init);
module_exit(task_iterator_exit);
