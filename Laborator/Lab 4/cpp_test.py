import subprocess
import sys

tests = [
    # (NPolynomes, 	MaxDegree, 	NMonomes, 	no_threads)
      (10, 	        1000, 	    50,		    1),
      (10, 	        1000, 	    50,		    4),
      (10, 	        1000, 	    50,		    6),
      (10, 	        1000, 	    50,		    8),
      (5, 	        10000, 	    100,		1),
      (5, 	        10000, 	    100,		4),
      (5, 	        10000, 	    100,		6),
      (5, 	        10000, 	    100,		8),
]

if __name__ == '__main__':
    #if len(sys.argv) < 2: exit(f"Usage: {argv[0]}")

    for test in tests:
        args = ['py', 'cpp_multiple_run.py', 'report.xlsx',
    	    str(test[0]), str(test[1]), str(test[2]), '5'] +([str(test[3])] if test[3] > 1 else [])
    	    
        print(f"[INFO] Running test... N={test[0]:<8}, M={test[1]:<8}, n=m={test[2]:<2} on p={test[3]:<2} threads")
        proc = 	subprocess.Popen(args)
        proc.communicate()
