// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ANTHROSTATALINK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ANTHROSTATALINK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#include "stplugin.h"
#ifndef _stata_testlib_retint
#define _stata_testlib_retint 999
#endif
STDLL stata_call(int argc, char *argv[]);

STDLL stata_testlib(int argc);
