# accesible_population


Fisierul help.cpp

Structura cityInfo, este folosita pentru a stoca informatiile despre orase: - id-ul orasului; - latitudine; - longitudine; - populatie; - populatia accesibila;

In functia sampleFileIO se citest datele din fisier si se stocheaza in structura cityInfo. Apoi orasele sunt sortate crescator dupa latitudine si longitudine. Datele sunt transmise pentru a calcula populatia accesibila. Orasele sunt aduse la ordinea lor initiala si se scrie in fisierul de output populatia accesibila a acestora.

Fisierul accesible_population.cu

In functia processCityData se aloca vectori host si device pentru a stoca, latitudinea, longitudinea, populatia si populatia accesibila pentru orase. Datele din vectorii device sunt procesate de functia calculateAccesiblePopulation. Populatia accesibila este copiata in structura ce contine datele despre orase.

In functia calculateAccesiblePopulation pentru orasul i se calculeaza dintre orasul i si toate orasele de la i + 1 la N. Astfel pentru primul oras cu i = 0 se calculeaza distanta cu toate orasele de la 1 la N. Pentru al doilea oras cu i = 1, nu e nevoie sa calculam care e distanta dintre el si primul oras, am facut-o anterior, vom calcula distanta dintre el si orasele de la 3 la N.

Atunci cand se ajunge ca distanta dintre un oras i si un oras din intervalul i + 1 la N este mai mare de cat kmRange, nu se vor mai calcula distantele cu orasele ramase, pentru ca ele sunt sortate crescator dupa latitudine si longitudine si distanta va fi din ce in ce mai mare.

Checker output on Tesla A100 engine: \\
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

Executing tests on local with timeout: 200s T
he elapsed time is 0.722000 seconds 
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

Se observa ca timpul de executie creste pe masura ce creste si numarul de date. Sa luam ca exemplu fisierul de input B0.in care are aproape 10000 de linii si fiesul H1.in care are aproximativ 1000000, numarul de date a cresut de 100 de ori, iar durata de exutie de 30 de ori. Consider ca este un rezultat bun, pentru ca durata de executie nu creste in acelasi ritm cu numarul de date.

Timpii de executie de pe cluster sunt de 10 ori mai mici, pe A100.
