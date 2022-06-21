#include <fstream>
#include "accesible_population.h"
#include "helper.h"

__global__ void calculateAccesiblePopulation(float *lat, float *lon,
                                             int *pop, int *acc, 
                                             int N, int kmRange) {
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;
    float cs, dist;
    
    /**
     * Se calculeaza populatia accesibila pentru orasul i si 
     * orasele de la i + 1 la N. 
     * 
     * Prima data se caculeaza distranta dintre orase.
     * Daca distanta este mai mica de kmRange, la populatia
     * accesibila a orasului A se adauga populatia orasului
     * B si invers.
     * 
     * Daca distanta este mai mare de cat kmRande, for-ul inceteaza,
     * pentru ca coordonatele sunt sortate si pentru coordonatele ce 
     * ar urma distanta ar fi mai mare de cat kmRange.
     */

    for (int j = i + 1; j < N; j++) {
        cs = sin(lat[i]) * sin(lat[j]) * cos(lon[i] - lon[j]) 
            + cos(lat[i]) * cos(lat[j]);

        if (cs > 1) {
            cs = 1;
        } else if (cs < -1) {
            cs = -1;
        }

        dist =  6371.f * acos(cs);

        if (dist <= kmRange) {
            atomicAdd(&acc[i], pop[j]);
            atomicAdd(&acc[j], pop[i]);
        } else {
            break;
        }
    }
}


void processCityData(cityInfo *data, int N, int kmRange) {
    cudaSetDevice(0);
    

    float *device_lat, *device_lon, *host_lat, *host_lon;
    int *device_pop, *device_acc, *host_pop, *host_acc;

    host_lat = (float*) malloc(sizeof(float) * 10000000);
    host_lon = (float*) malloc(sizeof(float) * 10000000);
    host_pop = (int*) malloc(sizeof(int) * 10000000);
    host_acc = (int*) malloc(sizeof(int) * 10000000);

    cudaMallocManaged((void **)&device_lat, N * sizeof(float));
    cudaMallocManaged((void **)&device_lon, N * sizeof(float));
    cudaMallocManaged((void **)&device_pop, N * sizeof(int));
    cudaMallocManaged((void **)&device_acc, N * sizeof(int));

    /**
     * Se stocheaza latitudine, longitudinea si populatia in vectori.
     * Acestia vor fi folositi pentru calcularea distantei si a populatiei
     * pentru fiecare doua orase.
     */
    for (int i = 0; i < N; i++) {
        host_lat[i] = data[i].lat;
        host_lon[i] = data[i].lon;
        host_pop[i] = data[i].pop;
        host_acc[i] = data[i].acc;
        
    }

    cudaMemcpy(device_lat, host_lat, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_lon, host_lon, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_pop, host_pop, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_acc, host_acc, N * sizeof(int), cudaMemcpyHostToDevice);

    const size_t block_size = 100;
    size_t blocks_no = N / block_size;

    if (N % block_size)
    ++blocks_no;

    // Se calculeaza populatia accesibila pentru orase.
    calculateAccesiblePopulation<<<blocks_no, block_size>>>(device_lat, device_lon,
                                    device_pop, device_acc, N, kmRange);
    cudaDeviceSynchronize();

    cudaMemcpy(host_acc, device_acc, N *sizeof(int), cudaMemcpyDeviceToHost);
    
    // Se copiaza populatia accesibila pentru orase in structura.
    for (int i = 0; i < N; i++) {
        data[i].acc = host_acc[i];
    }

    free(host_lat);
    free(host_lon);
    free(host_pop);
    free(host_acc);

    cudaFree(device_lat);
    cudaFree(device_lon);
    cudaFree(device_pop);
    cudaFree(device_acc);
}

