#include <linux/wait.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/sched.h>

#ifndef Queue_head_define
#define Queue_head_define
wait_queue_head_t project_queue1 = __WAIT_QUEUE_HEAD_INITIALIZER(project_queue1);
wait_queue_head_t project_queue2 = __WAIT_QUEUE_HEAD_INITIALIZER(project_queue2);
wait_queue_head_t project_queue3 = __WAIT_QUEUE_HEAD_INITIALIZER(project_queue3);
#else
extern wait_queue_head_t project_queue1 ;
extern wait_queue_head_t project_queue2 ;
extern wait_queue_head_t project_queue3 ;
#endif

asmlinkage int sys_enter_wait_queue(int x) {
    if(x == 1)
    {        
        DEFINE_WAIT(wait1);
        prepare_to_wait(&project_queue1, &wait1, TASK_INTERRUPTIBLE);
        schedule();
	}
    else if(x == 2)
    {
        DEFINE_WAIT(wait2);
        prepare_to_wait(&project_queue2, &wait2, TASK_INTERRUPTIBLE);
        schedule();
    }
    else
    {
        DEFINE_WAIT(wait3);
        prepare_to_wait(&project_queue3, &wait3, TASK_INTERRUPTIBLE);
        schedule();
    }       

    return 1;
}