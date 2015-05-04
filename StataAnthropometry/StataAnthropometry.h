// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STATAANTHROPOMETRY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STATAANTHROPOMETRY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef STATAANTHROPOMETRY_EXPORTS
#define STATAANTHROPOMETRY_API __declspec(dllexport)
#else
#define STATAANTHROPOMETRY_API __declspec(dllimport)
#endif

// This class is exported from the StataAnthropometry.dll
class STATAANTHROPOMETRY_API CStataAnthropometry {
public:
	CStataAnthropometry(void);
	// TODO: add your methods here.
};

extern STATAANTHROPOMETRY_API int nStataAnthropometry;

STATAANTHROPOMETRY_API int fnStataAnthropometry(void);
