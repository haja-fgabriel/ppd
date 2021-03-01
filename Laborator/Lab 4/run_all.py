import subprocess
import sys

args = ['py', 'cpp_test.py']

print("[INFO] Running C++")
cpp_dyn = subprocess.Popen(args)
cpp_dyn.communicate()

#print("[INFO] Running C++ tests with dynamic allocation")
#cpp_stat = subprocess.Popen(args + ['dynamic'])
#cpp_stat.communicate()
#
#print("[INFO] Running Java tests (with dynamic allocation)")
#java = subprocess.Popen(['py', 'java_test.py'])
#java.communicate()
