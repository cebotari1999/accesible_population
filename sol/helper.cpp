#include <math.h>
#include <fstream>
#include<stdlib.h>
#include <algorithm>

#include "helper.h"
#include "accesible_population.h"

using namespace std;

// geoDistance computes geographical distance (lat1, lat1) and (lat2, lon2)
float geoDistance(float lat1, float lon1, float lat2, float lon2)
{
    float phi1 = (90.f - lat1) * DEGREE_TO_RADIANS;
    float phi2 = (90.f - lat2) * DEGREE_TO_RADIANS;

    float theta1 = lon1 * DEGREE_TO_RADIANS;
    float theta2 = lon2 * DEGREE_TO_RADIANS;

    float cs = sin(phi1) * sin(phi2) * cos(theta1 - theta2) + cos(phi1) * cos(phi2);
    if (cs > 1) {
        cs = 1;
    } else if (cs < -1) {
        cs = -1;
    }

    return 6371.f * acos(cs);

}

bool compareLatLon(cityInfo a, cityInfo b)
{
    if (a.lat != b.lat)
        return a.lat < b.lat;
 
    return (a.lon < b.lon);
}

bool compareIndex(cityInfo a, cityInfo b)
{
    return (a.i < b.i);
}
 

// sampleFileIO demos reading test files and writing output
void sampleFileIO(float kmRange, const char* fileIn, const char* fileOut)
{
    double time_spent = 0.0;

    clock_t begin = clock();

    string geon;
    float lat = 0, lon = 0;
    int pop = 0, N = 0;

    struct cityInfo *citiesInfo;
    
    citiesInfo = (struct cityInfo*) malloc(sizeof(struct cityInfo) * 10000000);

    ifstream ifs(fileIn);
    ofstream ofs(fileOut);

    // Se citesc datele din fisier si se salveaza in structura.
    // Asupra longitudinei si latitudinei se aplica niste operatii
    // matematice, necesare pentru calcularea distantei;
    while(ifs >> geon >> lat >> lon >> pop)
    {
        citiesInfo[N].i = N;
        citiesInfo[N].lat = (90.f - lat) * DEGREE_TO_RADIANS;;
        citiesInfo[N].lon = lon * DEGREE_TO_RADIANS;
        citiesInfo[N].pop = pop;
        citiesInfo[N].acc = pop;
        N++;
    }

    // Se sorteaza orasele dupa latitudine si longitudine.
    sort(citiesInfo, citiesInfo + N, compareLatLon);
    
    // Se calculeaza populatia accesibila pentru fiecare oras.
    processCityData(citiesInfo, N, kmRange);
    
    // Orasele sunt aduse la ordinea initiala.
    sort(citiesInfo, citiesInfo + N, compareIndex);

    // Se afiseaza populatia accesibila pentru fiecare oras.
    for (int i = 0; i < N; i++) {
        ofs<<citiesInfo[i].acc<<endl;
    }

    ifs.close();
    ofs.close();

    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds\n", time_spent);
}
