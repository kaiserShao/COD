
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
#include "stdint.h"
	DLL_EXPORT void	InitPLCInterface(SBaseInterface *pBaseInterface, SReturnInterface *pReturnInterface);
#ifdef __cplusplus
}

#endif
#define	TubeMax			180u

//	用户设置
struct uTaskSet
{
	uint8_t	TubeNum;					//	水样试管号
		//	uint8_t	SampleDosage;		//	水样剂量
	uint8_t	ExperimentNum;				//	平行试验组数
	uint8_t	MeasuringChlorine;			//	0 无须测氯		1 需要测氯
	uint8_t	ConcentrationEstimate;		//	0 未知浓度		1 高浓度			2 低浓度
	uint8_t	DissolutionTime;			//	0 不消解			1 消解时长15min	2 消解时长5min
	uint8_t	ConcentrationMeasure;		//	0 不比色			1 比色分析浓度		2

};

extern	struct	uTaskSet	TaskSet[TubeMax];
extern	void	ProcessAUTO(void);
#endif
