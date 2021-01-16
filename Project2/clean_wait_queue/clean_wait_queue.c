#include<linux/wait.h>
#include<linux/kernel.h>
#include<linux/list.h>

asmlinkage int sys_clean_wait_queue(int x)
{
    DECLARE_WAIT_QUEUE_HEAD(project_queue1);
    DECLARE_WAIT_QUEUE_HEAD(project_queue2);
    DECLARE_WAIT_QUEUE_HEAD(project_queue3);
    if(x ==1)
    {        
        wake_up(&project_queue1);
    }
    else if(x == 2)
    {
        wake_up(&project_queue2);
    }
    else
    {
        wake_up(&project_queue3);
    }       

    return 1;
}