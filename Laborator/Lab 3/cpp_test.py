import subprocess
import sys

tests = [
    # (N1, 	N2, 	no_processes)
    (1000, 	1000, 	2),
    (1000, 	1000, 	4),
    (1000, 	1000, 	6),
    (1000, 	1000, 	8),
    (1000, 	1000, 	16),
    (10, 	100000,	2),
    (10, 	100000,	4),
    (10, 	100000,	6),
    (10, 	100000,	8),
    (10, 	100000,	16)
]

if __name__ == '__main__':
    if len(sys.argv) < 2:
        exit(f"Usage: {argv[0]} sequential|scatter|isend")
    
    run_tests = {}

    for test in tests:
        if sys.argv[1] == "sequential":
            if run_tests.get((test[0], test[1])):
                continue
            else:
                run_tests[(test[0], test[1])] = "da"

        args = ['py', 'cpp_multiple_run.py', 'report.xlsx',
    	    str(test[0]), str(test[1]), '5', sys.argv[1]] + ([str(test[2])] if sys.argv[1] != "sequential" else [])
    	    
        print(f"[INFO] Running test... N={test[0]:<8}, M={test[1]:<8}" + (f", on p={test[2]:<2} processes" if sys.argv[1] != "sequential" else ""))
        proc = 	subprocess.Popen(args)
        proc.communicate()
