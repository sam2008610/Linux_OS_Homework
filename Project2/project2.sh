#!/bin/bash
gcc -o enter_queue enter_queue.c
gcc -o clean_queue clean_queue.c
./enter_queue &
echo "First enter_queue is running."
./enter_queue &
echo "Second enter_queue is running."
./enter_queue &
echo "Third enter_queue is running."
./clean_queue &
echo "Clean_queue is running."

wait
echo "Done"