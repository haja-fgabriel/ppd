Command line arguments to input in Python script:
Java (single-threaded): 
  java Main <input_file> <kernel_input_file> [--log-to-socket]
  - where dynamic|static means choosing between dynamic and static memory allocation
    --log-to-socket should be provided, as the Python script receives the execution time through sockets
  - example:
      java Main data.txt kernel.txt --log-to-socket
	  
Java (multi-threaded): 
  java ParallelMain <input_file> <kernel_input_file> [--log-to-socket]
  - where dynamic|static means choosing between dynamic and static memory allocation
    --log-to-socket should be provided, as the Python script receives the execution time through sockets
  - example:
      java ParallelMain data.txt kernel.txt --log-to-socket
	  
Note:
- please generate random input and kernel data using the file generator provided in the C++ project