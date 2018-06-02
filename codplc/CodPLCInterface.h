
#ifndef __CodPLCInterface_H__
#define __CodPLCInterface_H__

#ifdef __cplusplus
extern "C"{
#endif 
#include "BaseInterface.h"
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif	

	DLL_EXPORT void	InitPLCInterface(SBaseInterface *pBaseInterface, SReturnInterface *pReturnInterface);
	

#ifdef __cplusplus
}
#endif
#endif