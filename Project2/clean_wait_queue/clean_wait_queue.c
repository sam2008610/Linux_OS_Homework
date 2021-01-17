#include <linux/wait.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/sched.h>

extern wait_queue_head_t project_queue1 ;
extern wait_queue_head_t project_queue2 ;
extern wait_queue_head_t project_queue3 ;

asmlinkage int sys_clean_wait_queue(int x)
{
    if(x == 1)
    {        
	    wake_up_interruptible_all(&project_queue1);
    }
    else if(x == 2)
    {
	    wake_up_interruptible_all(&project_queue2);
    }
    else
    {
	    wake_up_interruptible_all(&project_queue3);
    }       

    return 1;
}