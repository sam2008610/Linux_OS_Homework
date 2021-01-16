#!/bin/bash
gcc -o enter_queue enter_queue.c
gcc -o clean_queue clean_queue.c
for(( i = 0; i < 4; i++ ))
do
{
	sleep 3;
    if(i<3)
    {
        ./enter_queue
    }
    else 
    {
        ./clean_queue
    }
}&
done