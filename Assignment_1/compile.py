import os
import subprocess

libflags = "-O3 -std=c++11"
programflags = "-O3 -std=c++11"

os.chdir("forces")
bashCommand = "g++ "+libflags+" -c forces.cc -o forces.o"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

os.chdir("../integrators")
bashCommand = "g++ "+libflags+" -c integrators.cc -o integrators.o"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

os.chdir("../properties")
bashCommand = "g++ "+libflags+" -c properties.cc -o properties.o"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

os.chdir("..")
bashCommand = "mpicxx "+programflags+" Program.cc forces/forces.o integrators/integrators.o properties/properties.o -o Program.run"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

