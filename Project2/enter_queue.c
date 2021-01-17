#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/time.h>
#include <sys/syscall.h>
#include <string.h>
#define _GNU_SOURCE

void main()
{
    int random_num;
    int ttid, count;
    char str[300];
    memset(str, '\0', 300);
    FILE *pFile;

    struct timeval t1, t2;

    gettimeofday(&t1, NULL);
    ttid = syscall(SYS_gettid);
    count = 0;

    // get tid length
    int tid_len = 0;
    int ttid_tmp = ttid;
    while(ttid_tmp!=0)
    {
        ttid_tmp/=10;
        tid_len++;
    }
    
    // file name
    char tid[tid_len+1];
    memset(tid, '\0', tid_len+1);
    sprintf(tid, "%d", ttid);

    char file[]="file_";
    char file_gettid[tid_len+6];
    memset(file_gettid, '\0', tid_len+6);

    strcat(file_gettid, file);
    strcat(file_gettid, tid);

    // open file
    pFile = fopen(file_gettid,"a" );


    while (1)
    {
        gettimeofday(&t2, NULL);

        // condition
        if(t2.tv_sec - t1.tv_sec >= 10)
            break;
        
        // content
        random_num = (rand() % 3) + 1;
        sprintf(str, "process %d is added into wait queue project2_queue_%d the %d th time at time ...\n", ttid, random_num, count++);

        //write file
        fwrite(str,1,strlen(str),pFile);

        // add wq
        syscall(324, random_num);
    }
    fclose(pFile);
    printf("process %d completes!\n", ttid);
}