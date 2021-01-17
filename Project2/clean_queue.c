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
    int random_num1, random_num2;
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

    // write file
    pFile = fopen(file_gettid,"a+");

    while (1)
    {
        gettimeofday(&t2, NULL);

        // condition
        if(t2.tv_sec - t1.tv_sec >= 20)
            break;
        
        // content
        random_num1= (rand()%3)+1;
        random_num2= (rand()%3);
        sleep(random_num2);

        sprintf(str, "Wake up all processes in wait queue project2_queue_%d at time ...\n", random_num1);


        fprintf(pFile,"%s",str);

        // add wq
        syscall(323, random_num1);
        printf("1");
    }
    strcpy(str,  "Clean wait wait queue project2_queue_1\n");
    fprintf(pFile,"%s",str);
    syscall(323, 1);
    printf("2");
    
    strcpy(str,  "Clean wait wait queue project2_queue_2\n");
    fprintf(pFile,"%s",str);
    syscall(323, 2);
    printf("3");
    
    strcpy(str,  "Clean wait wait queue project2_queue_3\n");
    fprintf(pFile,"%s",str);
    syscall(323, 3);
    printf("4");
    
    fclose(pFile);
    printf("process %d completes!\n", ttid);
}