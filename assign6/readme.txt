In the homework, I modified main.c and makefile to support multithreading.
We need to divide the task of rendering width*height pixels into nthreads subtasks.
I did so by let thread i only deal with x=i mod nthreads in the iteration of width.
So we need to create a structure for the argument of the thread funciton
which need to include nthreads and the thread number (i).
Upon further examining the code, the argument struct also need to have the scene passed in
since it is not a global variable.
Since threads do the subtasks parallel, we can't print per pixel anymore.
So I initiate a 3D array to store all the outputs of pixel rendering
and print them together after threads are joined.
We can see from make-log.txt that the real time is approximately user time / number of threads.
Parallelism makes this task significantly faster.
