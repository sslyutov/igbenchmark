/*!\brief benchmark test of bubble sort using different number of threads
* \file igbenchmark.cpp
* \date January 29, 2023
* \author Sergey Slyutov
*/

#include "igbenchmark.h"

#include <time.h>

#include <stdlib.h>

#include <iostream>

#include <thread>

void sort(int * parr, const unsigned int arrc, int threadindex)
{
	bool bcompleted = false;
	unsigned int iterations = 0;

	time_t tmsortbegin = time(NULL);

	unsigned int sorted = 0;

	int reportcounter = 0;

	while (!bcompleted)
	{
		bcompleted = true;
		
		iterations++;

		for (unsigned int i = 0; i < arrc-1; i++) {
			if (parr[i] > parr[i + 1]) {
				int tmp = parr[i];
				parr[i] = parr[i + 1];
				parr[i + 1] = tmp;
				bcompleted = false;
				sorted++;
			}
		}
	
		if (reportcounter == 0) {
			reportcounter = 10000;
			if (threadindex == -1) { // -1 main thread
				std::cout << "cycle clusters(each cluster 10000 passes): " << iterations << "; pairs sorted per this cycle: " << sorted;
				std::cout << "; time passed: " << time(NULL) - tmsortbegin << " secs" << std::endl;
			}
		}
		reportcounter--;

	}

	time_t tmsortend = time(NULL);

	if (threadindex == -1) { // -1 main thread
		std::cout << "total sorting time is: " << tmsortend - tmsortbegin << " secs" << std::endl;
	}
}


typedef struct _BENCHMARK {
	// number of threads
	unsigned int threadCount;
	
	// size of array in elements
	unsigned int arraysize;

	_BENCHMARK() { 
			m_array = NULL; // pointer to array to sort
	};
	
	int * m_array;

	bool init(){
		
		if (m_array != NULL)
			return false;

		time_t tmstart = time(NULL);
		std::cout << "init started at " << tmstart << std::endl;

		m_array = new int[arraysize];
		srand(10); // need to initialize the same sequence of random integers
		
		for (int i = 0; i < arraysize; i++) {
			m_array[i] = rand();
		}

		time_t tmend = time(NULL);
		std::cout << "array initialized " << tmend << " array was generated in "<< tmend - tmstart << " msec" << std::endl;

		return true;
	};

	bool terminate() { 
		if (m_array == NULL)
			return false;
		delete m_array;
		m_array = NULL;
	};
};

IGBENCHMARKAPI HBENCHMARK initBenchmark(const unsigned int thc, const unsigned int arrsize )
{
	_BENCHMARK * pbm = new _BENCHMARK();

	pbm->threadCount = thc;

	pbm->arraysize = arrsize;

	pbm->init();

	for (int i = 0; i < pbm->threadCount; i++) {
		std::thread * thread = new std::thread(sort, pbm->m_array, pbm->arraysize, i);
		
	}

	sort(pbm->m_array, pbm->arraysize, -1);

	return HBENCHMARK(pbm);
}

IGBENCHMARKAPI bool releaseBenckmark(HBENCHMARK hbm)
{ 
	delete (_BENCHMARK*)hbm;
	return false; 
}

IGBENCHMARKAPI bool terminateBenchmark(HBENCHMARK hbm)
{
	((_BENCHMARK*)hbm)->terminate();

	return false;
};
