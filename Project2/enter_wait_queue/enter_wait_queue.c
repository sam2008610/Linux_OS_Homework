#include<linux/wait.h>
#include<linux/kernel.h>
#include<linux/list.h>

asmlinkage int sys_enter_wait_queue(int x) {
    DECLARE_WAIT_QUEUE_HEAD(project_queue1);
    DECLARE_WAIT_QUEUE_HEAD(project_queue2);
    DECLARE_WAIT_QUEUE_HEAD(project_queue3);
    if(x ==1)
    {        
        DECLARE_WAITQUEUE(project_queue1,current);
    }
    else if(x == 2)
    {
        DECLARE_WAITQUEUE(project_queue2,current);
    }
    else
    {
        DECLARE_WAITQUEUE(project_queue3,current);
    }       

    return 1;
}