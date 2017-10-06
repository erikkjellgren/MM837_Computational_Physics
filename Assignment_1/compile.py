import os
import subprocess

libflags = "-O3"
programflags = "-O3  -fopenmp"

os.chdir("forces")
bashCommand = "g++ "+libflags+" -fopenmp -c forces.cc -o forces.o"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

os.chdir("../integrators")
bashCommand = "g++ "+libflags+" -c integrators.cc -o integrators.o"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

os.chdir("../properties")
bashCommand = "g++ "+libflags+" -c printresults.cc -o printresults.o"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

os.chdir("..")
bashCommand = "mpicxx "+programflags+" Program.cc forces/forces.o integrators/integrators.o properties/printresults.o -o Program.run"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

