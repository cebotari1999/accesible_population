#ifndef ACCPOP_HELPER_H
#define ACCPOP_HELPER_H
#include <stdio.h>

#define DEGREE_TO_RADIANS		0.01745329252f

struct cityInfo {
    int i;
    float lat;
    float lon;
    int pop;
    int acc;
};

float geoDistance(float lat1, float lon1, float lat2, float lon2);

void sampleFileIO(float kmRange, const char* fileIn, const char* fileOut);

bool compareLatLon(cityInfo a, cityInfo b);

bool compareIndex(cityInfo a, cityInfo b);

#define DIE(assertion, call_description)                    \
do {                                                        \
    if (assertion) {                                        \
            fprintf(stderr, "(%d): ",                       \
                            __LINE__);                      \
            perror(call_description);                       \
            exit(EXIT_FAILURE);                             \
    }                                                       \
} while(0);

#endif //ACCPOP_HELPER_H
