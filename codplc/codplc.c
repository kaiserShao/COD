
#include "codplc.h"
#include <stdio.h>
#include "stdbool.h"
#include "BaseInterface.h"
#include "Debug.H"

uint8_t	SampleNum = 4u;
uint8_t	List0ChlorineMeasuring[1u] = { 28u };
uint8_t	List1ConcentrationMeasure[3u] = { 29u, 30u, 31u };
uint8_t	List2Preparation[3u] = { 29u, 30u, 31u };
uint8_t	List3WaterSampleAttenuation[3u] = { 34u, 35u, 36u };
uint8_t	List4TubeClean[7u] = { 28u, 29u, 30u, 31u, 34u, 35u, 36u };

SBaseInterface *g_pBaseInterface;

bool	DoBeforeWhile()
{
	int nValue = 0;
	g_pBaseInterface->ptrFuncLogger("DoBeforeWhile\n");
	nValue = HoldingSingelRead2(MBName[ArmBase + 0u]);
	osDelay(2000u);
	return true;
}
extern	void	TubeAnalyze(void);
bool	DoWhile()
{
	//g_pBaseInterface->ptrFuncLogger("DoWhile\n");
	int nValue = 0;

	//	Debug();
	ProcessAUTO();
	TubeAnalyze();
	while (1)
	{
		osDelay(1000);
	}
	return true;
}
bool	DoAfterWhile()
{
	g_pBaseInterface->ptrFuncLogger("DoAfterWhile\n");	
	return true;
}

void	InitPLCInterface(SBaseInterface *pBaseInterface, SReturnInterface *pReturnInterface)
{
	g_pBaseInterface = pBaseInterface;
	pReturnInterface->ptrDoBeforeWhile = DoBeforeWhile;
	pReturnInterface->ptrDoWhile = DoWhile;
	pReturnInterface->ptrDoAfterWhile = DoAfterWhile;
}