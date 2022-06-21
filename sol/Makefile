all: gpu_sol

gpu_sol: helper.o
	nvcc -g -arch=sm_35 -rdc=true main.cpp helper.o accesible_population.o -o gpu_sol -O0

helper.o:
	nvcc -g helper.cpp -c -O0
	nvcc -g accesible_population.cu -c -O0

clean:
	rm -f gpu_sol *.o