/*!\brief benchmark test of bubble sort using different number of threads
* \file igbenchmark.h
* \date January 29, 2023
* \author Sergey Slyutov
*/

#ifndef _IGBENCHMARK_H

#define _IGBENCHMARK_H

/*! type of API functions desclaration for client and library*/
#ifdef _WIN32

	#if defined(IGBENCHMARK_EXPORTS) // inside DLL

		#define IGBENCHMARKAPI   __declspec(dllexport)

	#else // outside DLL

		#define IGBENCHMARKAPI   __declspec(dllimport)

	#endif  // SS_EXPORT

#else //_WIN32

	/*!\brief export calling convention for MacOs. redundant due to it is a default configuration for mac*/
	#define IGBENCHMARKAPI extern __attribute__((visibility("default")))
 
#endif //none _WIN32


typedef long long HBENCHMARK;

IGBENCHMARKAPI HBENCHMARK initBenchmark(const unsigned int thc, const unsigned int arrsize );

IGBENCHMARKAPI bool releaseBenckmark(HBENCHMARK);

IGBENCHMARKAPI bool terminateBenchmark(HBENCHMARK);


#endif //_IGBENCHMARK_H