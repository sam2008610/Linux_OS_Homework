#include<linux/wait.h>
#include<linux/kernel.h>
#include<linux/list.h>
#include <linux/sched.h>
#include<linux/queue_wait_variable.h>

asmlinkage int sys_enter_wait_queue(int x) {
    DECLARE_WAIT_QUEUE_HEAD(project_queue1);
    DECLARE_WAIT_QUEUE_HEAD(project_queue2);
    DECLARE_WAIT_QUEUE_HEAD(project_queue3);
    
    if(x ==1)
    {        
    	bool q1=false;
	DECLARE_WAITQUEUE(wait1,current);
        add_wait_queue(&project_queue1, &wait1);
        wait_event_interruptible(project_queue1,q1);
    }
    else if(x == 2)
    {
	    bool q2=false;       
	DECLARE_WAITQUEUE(wait2,current);
        add_wait_queue(&project_queue2, &wait2);
        wait_event_interruptible(project_queue2,q2);
    }
    else
    {
	    bool q3=false;       
	DECLARE_WAITQUEUE(wait3,current);
        add_wait_queue(&project_queue3, &wait3);
        wait_event_interruptible(project_queue3,q3);
    }       

    return 1;
}