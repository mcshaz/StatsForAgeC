// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STATSFORAGEC_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STATSFORAGEC_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STATSFORAGEC_EXPORTS
#define STATSFORAGEC_API __declspec(dllexport)
#else
#define STATSFORAGEC_API __declspec(dllimport)
#endif

// This class is exported from the StatsForAgeC.dll
class STATSFORAGEC_API CStatsForAgeC {
public:
	CStatsForAgeC(void);
	// TODO: add your methods here.
};

extern STATSFORAGEC_API int nStatsForAgeC;

STATSFORAGEC_API int fnStatsForAgeC(void);
