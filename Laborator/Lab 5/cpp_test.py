import subprocess
import sys

tests = [
    # (NPolynomes, 	MaxDegree, 	NMonomes, 	no_threads, no_reading_threads)
      (10, 	        1000, 	    50,		    1,          2),
      (10, 	        1000, 	    50,		    1,          3),
      (10, 	        1000, 	    50,		    4,          2),
      (10, 	        1000, 	    50,		    4,          3),
      (10, 	        1000, 	    50,		    6,          2),
      (10, 	        1000, 	    50,		    6,          3),
      (10, 	        1000, 	    50,		    8,          2),
      (10, 	        1000, 	    50,		    8,          3),
      (5, 	        10000, 	    100,		1,          2),
      (5, 	        10000, 	    100,		1,          3),
      (5, 	        10000, 	    100,		4,          2),
      (5, 	        10000, 	    100,		4,          3),
      (5, 	        10000, 	    100,		6,          2),
      (5, 	        10000, 	    100,		6,          3),
      (5, 	        10000, 	    100,		8,          2),
      (5, 	        10000, 	    100,		8,          3),
]

if __name__ == '__main__':
    #if len(sys.argv) < 2: exit(f"Usage: {argv[0]}")

    for test in tests:
        args = ['py', 'cpp_multiple_run.py', 'report.xlsx',
    	    str(test[0]), str(test[1]), str(test[2]), '5'] + ([str(test[3]), str(test[4])] if test[3] > 1 else [])
    	    
        print(f"[INFO] Running test... N={test[0]:<8}, M={test[1]:<8}, n=m={test[2]:<2} on p={test[3]:<2} threads")
        proc = 	subprocess.Popen(args)
        proc.communicate()
