#include <linux/init.h>//包含了模組的初始化的巨集定義及一些其他函式的初始化函式
#include <linux/module.h>//核心模組必備標頭檔案
#include <linux/mm.h>//// 記憶體管理相關標頭檔案，含有頁面大小定義和一些頁面釋放函式原型。
#include <linux/mm_types.h>//記憶體管理相關標頭檔案
#include <linux/sched.h>//程序排程相關標頭檔案
#include <linux/export.h>//必要的標頭檔案
#include<linux/wait.h>
#include<linux/kernel.h>
#include<linux/list.h>

static int __init queue_test(void)
{

    DECLARE_WAIT_QUEUE_HEAD(queue);
    DECLARE_WAITQUEUE(project_queue1,NULL);
    print("The wait queue is in %016llx",&project_queue1);
    add_wait_queue(&queue, &project_queue1);
    list_for_each(task_list *pos,queue->task_list){
        print("The wait queue is in %016llx",&pos);
    }

}
static void __exit v2p_exit(void)
{
	printk(KERN_INFO "Cleaning up.\n");
}
MODULE_LICENSE("GPL"); //許可證
module_init(queue_test);//核心入口函式
module_exit(queue_test);//核心出口函式