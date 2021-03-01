import subprocess
import sys

args = ['py', 'cpp_test.py']

print("[INFO] Running parallel tests with MPI_Isend/MPI_Irecv")
cpp_dyn = subprocess.Popen(args + ['isend'])
cpp_dyn.communicate()

print("[INFO] Running parallel tests with MPI_Scatter/MPI_Gather")
cpp_stat = subprocess.Popen(args + ['scatter'])
cpp_stat.communicate()

print("[INFO] Running sequential tests")
java = subprocess.Popen(args + ['sequential'])
java.communicate()
