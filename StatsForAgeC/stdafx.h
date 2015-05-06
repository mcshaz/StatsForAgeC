// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef __StatsForAgeC_stdafx_H_included
#define __StatsForAgeC_stdafx_H_included

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <stdexcept>

#ifdef STATSFORAGEC_EXPORTS
#define STATSFORAGE_API __declspec(dllexport) 
#else
#define STATSFORAGE_API __declspec(dllimport)  
#endif

// TODO: reference additional headers your program requires here
#endif