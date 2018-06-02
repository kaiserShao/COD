
#include "codplc.h"
#include <stdio.h>
#include "stdbool.h"
#include "BaseInterface.h"
#include "Debug.H"
#include "APPDEF.H"

SBaseInterface *g_pBaseInterface;




//int fputc(int ch, FILE *f)
//{
//    UART3_Send(ch);
//    return ch;
//}
//int	main( void )
//{
//	while(1u)
//	{
//		osDelay( 3000u );
//		printf( "+ " );

////		Err = eMBMRead ( 2u, 40001, 10u, usRegHoldingBuf2 );
//	}
//}

























bool	DoBeforeWhile()
{
	int nValue = 0;
	g_pBaseInterface->ptrFuncLogger("DoBeforeWhile\n");
//	BIOS_SWD_Init();
//	BIOS_USART3_Init();
//	osDelay( 1500u );	
//	Err = eMBMInit( MB_RTU,  115200u, MB_PAR_NONE );
//	ProcessCTRL_Init();
	//HoldingSingelWrite2(MBName[ArmBase+ 33u], 1);
	nValue = HoldingSingelRead2(MBName[ArmBase + 0u]);
	osDelay(2000u);
	return true;
}
bool	DoWhile()
{
	//g_pBaseInterface->ptrFuncLogger("DoWhile\n");
	int nValue = 0;

	//	Debug();
	Processx();
	//osDelay(5000);
	//nValue = HoldingSingelRead2(MBName[ArmBase+ 11u]);
	//g_pBaseInterface->ptrFuncLogger("value =  %d\n", nValue);
	//if (g_pBaseInterface->ptrGetPntValueByName(MBName[ArmBase+ 11u], &nValue))
	//{
	//	g_pBaseInterface->ptrFuncLogger("value =  %d\n", nValue);
	//}
	//else
	//{
	//	g_pBaseInterface->ptrFuncLogger("ptrGetPntValueByName   error\n");
	//}
	while (1)
	{
		osDelay(1000);
	}
	//if (g_pBaseInterface->ptrSetPntValueByName("MBArm_W_TargetX", 1000, 3000))
	//{
	//	g_pBaseInterface->ptrFuncLogger("ptrSetPntValueByName   success\n");
	//}
	//else
	//{
	//	g_pBaseInterface->ptrFuncLogger("ptrSetPntValueByName   error\n");
	//}
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