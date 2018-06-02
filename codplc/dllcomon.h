
#ifndef __DllCommon_H__
#define __DllCommon_H__

#ifdef _WIN32
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif	

#endif	