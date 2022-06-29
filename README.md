# Accesible population

For a list of cities the accessible population of each city is calculated. The accessible population of a city is represented by the population of cities that are at the maximum distance from the city.

 ## help.cpp

cityInfo structure is used to store information about cities:
- city id;
- latitude;
- longitude;
- population;
- accessible population;

The sampleFileIO function reads the data from the file and stores it in the array of cityInfo structures. Then the cities are sorted in in ascending order by latitude and longitude. The data is transmitted to calculate the accessible population. The cities are brought to their initial order and their accessible population is written in the output file.


## accesible_population.cu

The processCityData function allocates host and device vectors to store, latitude, longitude, population and accessible population for cities. Data from device vectors is processed by the calculateAccessiblePopulation function. The accessible population is copied in the structure that contains the data about the cities.

In the function calculatedAccesiblePopulation for city i it is calculated distance with cities between i + 1 and N. Thus for the first city with i = 0 the distance with all cities from 1 to N is calculated. For the second city with i = 1 , there is no need to calculate the distance between it and the first city, we did it before, we will calculate the distance between it and the cities from 2 to N. When the distance between 2 cities A and B is less than or equal to kmrange then we have accpopA + = popB, respectively accpopB + = popA.

When the distance between a city i and a city in the range i + 1 to N is greater than kmRange, the distances with the remaining cities will no longer be calculated, because they are sorted ascending by latitude and longitude and the distance will be bigger and bigger.

Checker output on Tesla A100 engine:
Executing tests on A100 with timeout: 18s 
The elapsed time is 1.140000 seconds 
The elapsed time is 0.090000 seconds 

The elapsed time is 0.330000 seconds 

The elapsed time is 0.380000 seconds

The elapsed time is 2.780000 seconds

B0 Passed .... 10p 

E1 Passed .... 20p 

M1 Passed .... 20p 

M2 Passed .... 20p 

H1 Passed .... 20p

Final score: 90/90


Checker output on my PC, I have GPU Nvidia Geforce 2060:

Executing tests on local with timeout: 200s

The elapsed time is 0.722000 seconds 

The elapsed time is 1.089000 seconds 

The elapsed time is 3.396000 seconds 

The elapsed time is 3.708000 seconds 

The elapsed time is 22.721000 seconds

B0 Passed .... 10p 

E1 Passed .... 20p 

M1 Passed .... 20p 

M2 Passed .... 20p 

H1 Passed .... 20p

Final score: 90/90


Tthe execution time increases as the number of data increases. Let's take as an example the input file B0.in which has almost 10000 lines and the file H1.in which has about 1000000 lines, the number of data has increased 100 times, and the execution time 30 times. I consider it a good result, because the execution time does not increase in the same rhythm with the number of data.

You can see the input files in folder test. Also you have a checker for linux in checker folder.

