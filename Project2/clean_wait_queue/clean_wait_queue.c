#include<linux/wait.h>
#include<linux/kernel.h>
#include<linux/list.h>
#include <linux/sched.h>
#include<linux/queue_wait_variable.h>

asmlinkage int sys_clean_wait_queue(int x)
{
    DECLARE_WAIT_QUEUE_HEAD(project_queue1);
    DECLARE_WAIT_QUEUE_HEAD(project_queue2);
    DECLARE_WAIT_QUEUE_HEAD(project_queue3);
    if(x ==1)
    {        
	bool q1=true;        
	wake_up_interruptible_all(&project_queue1);
    }
    else if(x == 2)
    {
	bool q2=true;        
	wake_up_interruptible_all(&project_queue2);
    }
    else
    {
	bool q3=true;        
	wake_up_interruptible_all(&project_queue3);
    }       

    return 1;
}