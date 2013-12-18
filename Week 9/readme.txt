For the homework we had to parallelize a lot of the code.

The idea of it was to section off the image into columns which is why I changwed 
the original for loop into 
for( px=(tID*(width/nthreads)); px<((tID+1)*(width/nthreads)); ++px )
and left the 2 inner loops for anti-aliasing and because we 
just wanted to split the image into columns for the threads

I also moved most of the declarations as global so it would be easier for 
the threads to access the information without scoping problems

I moved most of the code into a ThreadFunction and sent threads to do 
the functions job with pthread_create and sent the nthreads into the function

You want to base the sectioning off the number of threads used

You also want to store the image somewhere so I created a 2D array. The first 
index is for the width and the second index is for the height * 3. You want 
to multiply the height by 3 because the vector has 3 values corresponding 
to r g b values

Each component of the vector is represented by scaled_color[px][offset+n] where 
n is either 0,1,2 because it corresponds to the scaled_color variable that 
originally had 0,1,2. You are using an offset because each thread will have 
its own stack and will be performing the code based on those variables, offsetted 
by a certain amount based on what part of the image the threads are working on. 

When you want the threads to join together to produce the image, you would want 
to use the pthread_join function so they will hang until 
all of the threads are finished.

It is important to move any print statements into the main function as each thread 
will print the specified message if left in the thread function. You want to print 
based off the memory you allocated or in my case the global static array I just declared.

The modification made to the ray tracing program sped up the program around 4
times. It went from 45 seconds to about 10 seconds after running with 8
threads. The more threads, the more it will speed up and divide the work. 
