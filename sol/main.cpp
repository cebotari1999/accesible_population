#include <iostream>
#include <stdlib.h>
#include <time.h> 
#include "helper.h"

int main(int argc, char** argv) {
    double time_spent = 0.0;

    DIE( argc == 1,
         "./accpop <kmrange1> <file1in> <file1out> ...");
    DIE( (argc - 1) % 3 != 0,
         "./accpop <kmrange1> <file1in> <file1out> ...");

    for(int argcID = 1; argcID < argc; argcID += 3) {
        float kmRange = atof(argv[argcID]);
        sampleFileIO(kmRange, argv[argcID + 1], argv[argcID + 2]);
    }
}
