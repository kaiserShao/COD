
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

//	�û�����
struct uTaskSet
{
	uint8_t	TubeNum;					//	ˮ���Թܺ�
		//	uint8_t	SampleDosage;		//	ˮ������
	uint8_t	ExperimentNum;				//	ƽ����������
	uint8_t	MeasuringChlorine;			//	0 �������		1 ��Ҫ����
	uint8_t	ConcentrationEstimate;		//	0 δ֪Ũ��		1 ��Ũ��			2 ��Ũ��
	uint8_t	DissolutionTime;			//	0 ������			1 ����ʱ��15min	2 ����ʱ��5min
	uint8_t	ConcentrationMeasure;		//	0 ����ɫ			1 ��ɫ����Ũ��		2

};

extern	struct	uTaskSet	TaskSet[TubeMax];
extern	void	ProcessAUTO(void);
#endif
