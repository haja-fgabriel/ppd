Command line arguments to input in Python script:
C++ (single-threaded):
  PixelTransformation.exe dynamic|static <input_file> <kernel_input_file> [--log-to-socket]
  - where dynamic|static means choosing between dynamic and static memory allocation
    --log-to-socket should be provided, as the Python script receives the execution time through sockets
  - example:
      PixelTransformation.exe dynamic data.txt kernel.txt --log-to-socket

C++ (multi-threaded):
  ParallelPixelTransformation.exe dynamic|static <num_threads> <input_file> [--log-to-socket] 
  - both optional arguments are aforementioned
  - example:
      ParallelPixelTransformation.exe dynamic 8 data.txt kernel.txt --log-to-socket
	  
Note:
- please generate random input and kernel data using the file generator provided in the C++ project