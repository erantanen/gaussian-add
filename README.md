Some backstory
--------------

There’s a popular story that Gauss, mathematician extraordinaire, had a lazy teacher. The so-called educator wanted to keep the kids busy so he could take a nap; he asked the class to add the numbers 1 to 100.

**Reference**: http://betterexplained.com/articles/techniques-for-adding-the-numbers-1-to-100/

Compiling
---------

Using GCC version 4.8.1 you may execute the following:
```
gcc -pthread -o gauss-add add_list_1_forloop.c
```

Executing
---------

To execute the program you can use the following arguments:
 - **-h**: outputs the help text
 - **-s**: starting number
 - **-e**: ending number

Example:
```
./gauss-add -s 1001 -e 10000000
```

Expected output:
```
Threads: 1000
Sum: 50000004499500

A shortened version of the result: "(number of lines) * (initial sum) = total sum"
4999500 * 10001001 = 50000004499500
```