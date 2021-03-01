import subprocess
import sys

tests = [
    # (N, 	M, 		n=m, 	no_threads)
    (10, 	10, 	3, 		2),
    (1000, 	1000, 	5, 		1),
    (1000, 	1000, 	5, 		2),
    (1000, 	1000, 	5, 		4),
    (1000, 	1000, 	5, 		8),
    (1000, 	1000, 	5, 		16),
    (10, 	10000, 	5, 		1),
    (10, 	10000, 	5, 		2),
    (10, 	10000, 	5, 		4),
    (10, 	10000, 	5, 		8),
    (10, 	10000, 	5, 		16),
    (10000, 10, 	5, 		1),
    (10000, 10, 	5, 		2),
    (10000, 10, 	5, 		4),
    (10000, 10, 	5, 		8),
    (10000, 10, 	5, 		16)
]

if __name__ == '__main__':
    if len(sys.argv) < 1:
        exit(f"Usage: {sys.argv[0]}")

    for test in tests:
        args = ['py', 'java_multiple_run.py', 'report.xlsx',
    	    str(test[0]), str(test[1]), str(test[2]), '5', str(test[3])]
    	    
        print(f"[INFO] Running test... N={test[0]:<8}, M={test[1]:<8}, n=m={test[2]:<2} on p={test[3]:<2} threads")
        proc = 	subprocess.Popen(args)
        proc.communicate()
