

#include "DEBUG.H"
#include "BaseInterface.h"
#include <math.h>
#include "windows.h"

struct	uRTStatus RTStatus;

const	char * MBName[ArmBase+130u] =
{
	"MBHeat_R_Count",
	"MBHeat_R_HardwareVersion",
	"MBHeat_R_CompileTimeY",
	"MBHeat_R_CompileTimeM&D",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"MBHeat_W_DissolutionCTRL",
	"MBHeat_R_DissolutionState",
	"MBHeat_W_SetTemperature",
	"MBHeat_R_RealTemperature",
	"19",
	"MBHeat_W_AutoCoverCMD",
	"MBHeat_R_AutoCoverState",
	"22",
	"23",
	"24",
	"25",
	"26",
	"27",
	"28",
	"29",
	"MBSpe_R_Count",
	"MBSpe_R_HardwareVersion",
	"MBSpe_R_CompileTimeY",
	"MBSpe_R_CompileTimeM&D",
	"34",
	"MBSpe_R_ADDataChhnnel1",
	"MBSpe_R_ADDataChhnnel2",
	"MBSpe_R_ADDataChhnnel3",
	"MBSpe_R_ADDataChhnnel4",
	"39",
	"MBSpe_W_CalibrationChange",
	"MBSpe_W_CalibrationChannel",
	"MBSpe_W_LEDIntensitySet",
	"MBSpe_W_ADDataWater",
	"MBSpe_W_Concentration0",
	"MBSpe_W_OriginalData0",
	"MBSpe_W_Concentration1",
	"MBSpe_W_OriginalData1",
	"MBSpe_W_Concentration2",
	"MBSpe_W_OriginalData2",
	"MBSpe_W_Concentration3",
	"MBSpe_W_OriginalData3",
	"MBSpe_W_Concentration4",
	"MBSpe_W_OriginalData4",
	"MBSpe_W_Concentration5",
	"MBSpe_W_OriginalData5",
	"MBSpe_W_Concentration6",
	"MBSpe_W_OriginalData6",
	"58",
	"59",
	"MBSpe_W_ChannelSelect",
	"MBSpe_R_ConcentrationChannel1",
	"MBSpe_R_ConcentrationChannel2",
	"MBSpe_R_ConcentrationChannel3",
	"MBSpe_R_ConcentrationChannel4",
	"65",
	"66",
	"67",
	"68",
	"69",
	"MBArm_R_Count",
	"MBArm_R_HardwareVersion",
	"MBArm_R_CompileTimeY",
	"MBArm_R_CompileTimeM&D",
	"74",
	"MBArm_R_CurrentX",
	"MBArm_R_MotorStateX",
	"MBArm_R_CurrentY",
	"MBArm_R_MotorStateY",
	"MBArm_R_CurrentZ",
	"MBArm_R_MotorStateZ",
	"MBArm_R_CurrentPump",
	"MBArm_R_PumpState",
	"MBArm_R_CurrentCovChannel",
	"MBArm_R_CurrentCovState",
	"MBArm_R_Solenoid1State",
	"MBArm_R_Solenoid2State",
	"MBArm_R_AutoCoverState",
	"MBArm_R_ComState",
	"MBArm_R_liquidState",
	"90",
	"MBArm_R_EffluentState",
	"92",
	"93",
	"94",
	"MBArm_W_TargetX",
	"MBArm_W_TargetY",
	"MBArm_W_TargetZ",
	"MBArm_R_Motor",
	"99",
	"MBArm_R_Effluent",
	"MBArm_W_TargetPump",
	"102",
	"MBArm_W_TargetConversion",
	"104",
	"MBArm_W_Solenoid1CMD",
	"MBArm_W_Solenoid2CMD",
	"MBArm_W_AutoCoverCMD",
	"MBArm_W_ComMotorCMD",
	"MBArm_W_ComMotorMode",
	"MBArm_W_EffluentMotroCMD",
	"MBArm_W_EffluentSolenoidCMD",
	"112",
	"113",
	"114",

};

const	int16_t	XYZ[][3u] = {
	{ 0, 0, 0 },
	{ (400 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (400 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (2050 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (3700 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (3700 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (5350 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (5350 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (400 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (400 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (2050 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (3700 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (3700 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (5350 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (5350 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (400 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (400 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (2050 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (3700 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (3700 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (5350 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (5350 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (400 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (400 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (2050 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (3700 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (3700 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (5350 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (5350 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (400 - 400) * 1.6,	6600 * 1.575, 1600 * 1.60 },
	{ (400 - 400) * 1.6,	6600 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	6600 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	6600 * 1.575, 1600 * 1.60 },
	{ (3700 - 400) * 1.6,	6600 * 1.575, 4400 * 1.60 },
	{ (3700 - 400) * 1.6,	6600 * 1.575, 1600 * 1.60 },
	{ (5350 - 400) * 1.6,	6600 * 1.575, 4400 * 1.60 },
	{ (5350 - 400) * 1.6,	6600 * 1.575, 1600 * 1.60 },
	{ (400 - 400) * 1.6,	8250 * 1.575, 4400 * 1.60 },
	{ (400 - 400) * 1.6,	8250 * 1.575, 1600 * 1.60 },
	{ (2050 - 400) * 1.6,	8250 * 1.575, 4400 * 1.60 },
	{ (2050 - 400) * 1.6,	8250 * 1.575, 1600 * 1.60 },
	{ (3700 - 400) * 1.6,	8250 * 1.575, 4400 * 1.60 },
	{ (3700 - 400) * 1.6,	8250 * 1.575, 1600 * 1.60 },
	{ (5350 - 400) * 1.6,	8250 * 1.575, 4400 * 1.60 },
	{ (5350 - 400) * 1.6,	8250 * 1.575, 1600 * 1.60 },




	{ (9850 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (9850 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (11500 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (11500 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (13150 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (13150 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (14800 - 400) * 1.6,	0 * 1.575, 4400 * 1.60 },
	{ (14800 - 400) * 1.6,	0 * 1.575, 1600 * 1.60 },
	{ (8200 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (8200 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (9850 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (9850 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (11500 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (11500 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (13150 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (13150 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (14800 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (14800 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (16450 - 400) * 1.6,	1650 * 1.575, 4400 * 1.60 },
	{ (16450 - 400) * 1.6,	1650 * 1.575, 1600 * 1.60 },
	{ (8200 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (8200 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (9850 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (9850 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (11500 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (11500 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (13150 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (13150 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (14800 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (14800 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (16450 - 400) * 1.6,	3300 * 1.575, 4400 * 1.60 },
	{ (16450 - 400) * 1.6,	3300 * 1.575, 1600 * 1.60 },
	{ (8200 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (8200 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (9850 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (9850 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (11500 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (11500 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (13150 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (13150 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (14800 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (14800 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (16450 - 400) * 1.6,	4950 * 1.575, 4400 * 1.60 },
	{ (16450 - 400) * 1.6,	4950 * 1.575, 1600 * 1.60 },
	{ (8200 - 400) * 1.6,   6600 * 1.575, 4400 * 1.60 },
	{ (8200 - 400) * 1.6,   6600 * 1.575, 1600 * 1.60 },
	{ (9850 - 400) * 1.6,   6600 * 1.575, 4400 * 1.60 },
	{ (9850 - 400) * 1.6,   6600 * 1.575, 1600 * 1.60 },
	{ (11500 - 400) * 1.6,  6600 * 1.575, 4400 * 1.60 },
	{ (11500 - 400) * 1.6,  6600 * 1.575, 1600 * 1.60 },
	{ (13150 - 400) * 1.6,  6600 * 1.575, 4400 * 1.60 },
	{ (13150 - 400) * 1.6,  6600 * 1.575, 1600 * 1.60 },
	{ (14800 - 400) * 1.6,  6600 * 1.575, 4400 * 1.60 },
	{ (14800 - 400) * 1.6,  6600 * 1.575, 1600 * 1.60 },
	{ (16450 - 400) * 1.6,  6600 * 1.575, 4400 * 1.60 },
	{ (16450 - 400) * 1.6,  6600 * 1.575, 1600 * 1.60 },
	{ (9850 - 400) * 1.6,   8250 * 1.575, 4400 * 1.60 },
	{ (9850 - 400) * 1.6,   8250 * 1.575, 1600 * 1.60 },
	{ (11500 - 400) * 1.6,  8250 * 1.575, 4400 * 1.60 },
	{ (11500 - 400) * 1.6,  8250 * 1.575, 1600 * 1.60 },
	{ (13150 - 400) * 1.6,  8250 * 1.575, 4400 * 1.60 },
	{ (13150 - 400) * 1.6,  8250 * 1.575, 1600 * 1.60 },
	{ (14800 - 400) * 1.6,  8250 * 1.575, 4400 * 1.60 },
	{ (14800 - 400) * 1.6,  8250 * 1.575, 1600 * 1.60 },



	{ (24850 - 400) * 1.6, 0 * 1.575, 4400 * 1.60 },
	{ (24850 - 400) * 1.6, 0 * 1.575, 1600 * 1.60 },
	{ (26500 - 400) * 1.6, 0 * 1.575, 4400 * 1.60 },
	{ (26500 - 400) * 1.6, 0 * 1.575, 1600 * 1.60 },
	{ (28150 - 400) * 1.6, 0 * 1.575, 4400 * 1.60 },
	{ (28150 - 400) * 1.6, 0 * 1.575, 1600 * 1.60 },
	{ (29800 - 400) * 1.6, 0 * 1.575, 4400 * 1.60 },
	{ (29800 - 400) * 1.6, 0 * 1.575, 1600 * 1.60 },
	{ (23200 - 400) * 1.6, 1650 * 1.575, 4400 * 1.60 },
	{ (23200 - 400) * 1.6, 1650 * 1.575, 1600 * 1.60 },
	{ (24850 - 400) * 1.6, 1650 * 1.575, 4400 * 1.60 },
	{ (24850 - 400) * 1.6, 1650 * 1.575, 1600 * 1.60 },
	{ (26500 - 400) * 1.6, 1650 * 1.575, 4400 * 1.60 },
	{ (26500 - 400) * 1.6, 1650 * 1.575, 1600 * 1.60 },
	{ (28150 - 400) * 1.6, 1650 * 1.575, 4400 * 1.60 },
	{ (28150 - 400) * 1.6, 1650 * 1.575, 1600 * 1.60 },
	{ (29800 - 400) * 1.6, 1650 * 1.575, 4400 * 1.60 },
	{ (29800 - 400) * 1.6, 1650 * 1.575, 1600 * 1.60 },
	{ (31450 - 400) * 1.6, 1650 * 1.575, 4400 * 1.60 },
	{ (31450 - 400) * 1.6, 1650 * 1.575, 1600 * 1.60 },
	{ (23200 - 400) * 1.6, 3300 * 1.575, 4400 * 1.60 },
	{ (23200 - 400) * 1.6, 3300 * 1.575, 1600 * 1.60 },
	{ (24850 - 400) * 1.6, 3300 * 1.575, 4400 * 1.60 },
	{ (24850 - 400) * 1.6, 3300 * 1.575, 1600 * 1.60 },
	{ (26500 - 400) * 1.6, 3300 * 1.575, 4400 * 1.60 },
	{ (26500 - 400) * 1.6, 3300 * 1.575, 1600 * 1.60 },
	{ (28150 - 400) * 1.6, 3300 * 1.575, 4400 * 1.60 },
	{ (28150 - 400) * 1.6, 3300 * 1.575, 1600 * 1.60 },
	{ (29800 - 400) * 1.6, 3300 * 1.575, 4400 * 1.60 },
	{ (29800 - 400) * 1.6, 3300 * 1.575, 1600 * 1.60 },
	{ (31450 - 400) * 1.6, 3300 * 1.575, 4400 * 1.60 },
	{ (31450 - 400) * 1.6, 3300 * 1.575, 1600 * 1.60 },
	{ (23200 - 400) * 1.6, 4950 * 1.575, 4400 * 1.60 },
	{ (23200 - 400) * 1.6, 4950 * 1.575, 1600 * 1.60 },
	{ (24850 - 400) * 1.6, 4950 * 1.575, 4400 * 1.60 },
	{ (24850 - 400) * 1.6, 4950 * 1.575, 1600 * 1.60 },
	{ (26500 - 400) * 1.6, 4950 * 1.575, 4400 * 1.60 },
	{ (26500 - 400) * 1.6, 4950 * 1.575, 1600 * 1.60 },
	{ (28150 - 400) * 1.6, 4950 * 1.575, 4400 * 1.60 },
	{ (28150 - 400) * 1.6, 4950 * 1.575, 1600 * 1.60 },
	{ (29800 - 400) * 1.6, 4950 * 1.575, 4400 * 1.60 },
	{ (29800 - 400) * 1.6, 4950 * 1.575, 1600 * 1.60 },
	{ (31450 - 400) * 1.6, 4950 * 1.575, 4400 * 1.60 },
	{ (31450 - 400) * 1.6, 4950 * 1.575, 1600 * 1.60 },
	{ (23200 - 400) * 1.6, 6600 * 1.575, 4400 * 1.60 },
	{ (23200 - 400) * 1.6, 6600 * 1.575, 1600 * 1.60 },
	{ (24850 - 400) * 1.6, 6600 * 1.575, 4400 * 1.60 },
	{ (24850 - 400) * 1.6, 6600 * 1.575, 1600 * 1.60 },
	{ (26500 - 400) * 1.6, 6600 * 1.575, 4400 * 1.60 },
	{ (26500 - 400) * 1.6, 6600 * 1.575, 1600 * 1.60 },
	{ (28150 - 400) * 1.6, 6600 * 1.575, 4400 * 1.60 },
	{ (28150 - 400) * 1.6, 6600 * 1.575, 1600 * 1.60 },
	{ (29800 - 400) * 1.6, 6600 * 1.575, 4400 * 1.60 },
	{ (29800 - 400) * 1.6, 6600 * 1.575, 1600 * 1.60 },
	{ (31450 - 400) * 1.6, 6600 * 1.575, 4400 * 1.60 },
	{ (31450 - 400) * 1.6, 6600 * 1.575, 1600 * 1.60 },
	{ (24850 - 400) * 1.6, 8250 * 1.575, 4400 * 1.60 },
	{ (24850 - 400) * 1.6, 8250 * 1.575, 1600 * 1.60 },
	{ (26500 - 400) * 1.6, 8250 * 1.575, 4400 * 1.60 },
	{ (26500 - 400) * 1.6, 8250 * 1.575, 1600 * 1.60 },
	{ (28150 - 400) * 1.6, 8250 * 1.575, 4400 * 1.60 },
	{ (28150 - 400) * 1.6, 8250 * 1.575, 1600 * 1.60 },
	{ (29800 - 400) * 1.6, 8250 * 1.575, 4400 * 1.60 },
	{ (29800 - 400) * 1.6, 8250 * 1.575, 1600 * 1.60 },

};


void osDelay(int nDelay)
{
	Sleep(nDelay);
}

void	PRINTErr(char *s, ProcessErr Err)
{

	switch (Err)
	{
	case	ProNOErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s Õý³££¡\r\n", s);
		break;
	case	ProPumpBlockingErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s ±Ã´íÎó£¡\r\n", s);
		break;
	case	ProPumpRangeErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s ±ÃÁ¿³Ì´íÎó£¡\r\n", s);
		break;
	case	ProPumpPositionErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s ±ÃÎ»ÖÃ´íÎó£¡\r\n", s);
		break;
	case	ProValveErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s ×ª»»·§´íÎó£¡\r\n", s);
		break;
	case	ProCommonErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s ¹«¹²¹Ü´íÎó£¡\r\n", s);
		break;
	case	ProNoFluid:
		g_pBaseInterface->ptrFuncLogger("\r\n%s È±Òº£¡\r\n", s);
		break;
	case	ProArmXErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s »úÐµ±ÛX·½Ïò´íÎó£¡\r\n", s);
		break;
	case	ProArmYErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s »úÐµ±ÛY·½Ïò´íÎó£¡\r\n", s);
		break;
	case	ProArmZErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s »úÐµ±ÛZ·½Ïò´íÎó£¡\r\n", s);
		break;
	case	ProReagentErr:
		g_pBaseInterface->ptrFuncLogger("\r\n%s Á¿³Ì´íÎó£¡\r\n", s);
		break;
	case	ProErrNoDef:
		g_pBaseInterface->ptrFuncLogger("\r\n%s Î´Öª´íÎó£¡\r\n", s);
		break;
	default:
		g_pBaseInterface->ptrFuncLogger("\r\n%s Î´Öª´íÎó2£¡\r\n", s);
		break;
	}
	//while (Err != ProNOErr)
	//{
	//	osDelay(3000);
	//}
}



_Bool	HoldingSingelWrite2(const	char *lpName, uint16_t	Data)
{
	if (g_pBaseInterface->ptrSetPntValueByName(lpName, Data, 2000u) == true)
	{
		;
	}
	else
	{
		for (uint8_t i = 0u; i < MBRetry; i++)
		{
			osDelay(2000u);
			if (g_pBaseInterface->ptrSetPntValueByName(lpName, Data, 2000u) == true)
				return	true;
		}
		g_pBaseInterface->ptrFuncLogger("HoldingSingelWrite2 Error %s", lpName);
		return false;
	}

	return	true;
}
uint16_t	HoldingSingelRead2(const	char *lpName)
{
	int nValue = 0;
	if (g_pBaseInterface->ptrGetPntValueByName(lpName, &nValue) == true)
	{
		return	nValue;
	}
	else
	{
		for (uint8_t i = 0u; i < MBRetry; i++)
		{
			osDelay(2000u);
			if (g_pBaseInterface->ptrGetPntValueByName(lpName, &nValue) == true)
				return	nValue;
		}

		g_pBaseInterface->ptrFuncLogger("HoldingSingelRead2 Error %s", lpName);
		return	0xFFFFu;
	}
	return	0xFFFFu;
}

ProcessErr	ValveCTRL(enum enumType Channel)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.Channel != Channel)
	{
		uint8_t	i = 0u;
		HoldingSingelWrite2(MBName[ArmBase+33u], Channel);
		do{
			osDelay(300u);
			RTStatus.Channel = (enum enumType)HoldingSingelRead2(MBName[ArmBase+13u]);
		}while ((RTStatus.Channel != Channel) && (i++ < 30u));

		if (i >= 30u)
		{
			Err = ProValveErr;
			return	Err;
		}
		else
			RTStatus.Channel = (enum enumType)HoldingSingelRead2(MBName[ArmBase+13u]);
	}
	return Err;
}

ProcessErr	PumpCTRL(int16_t	ulPumpPosition)
{

	ProcessErr
		Err = ProNOErr;
	uint16_t	ValueStatus = 0u;
	uint16_t	i = 0u;
	uint16_t	ii = 0u;
	uint16_t	Common = 0u;
	uint16_t	j = 0u;
	uint16_t	t = 0u;
	bool	COMCheck;
	int16_t	PumpPosition = (int16_t)((ulPumpPosition + 1.0f) / 2.0096f);
	int16_t	RTPumpPosition = HoldingSingelRead2(MBName[ArmBase + 11u]);
	if (RTPumpPosition != 0xFFFF )
	{
		RTStatus.PumpPosition = RTPumpPosition;
	}
	else
	{
		return ProMBReadErr;
	}
	if (RTStatus.PumpPosition + PumpPosition > (PumpPositionMax + 1.0f) / 2.0096f)
	{
		PumpPosition = (int16_t)((PumpPositionMax + 1.0f) / 2.0096f);
	}
	else if (RTStatus.PumpPosition + PumpPosition <= PumpZero)
	{
		PumpPosition = 0u;
	}
	else
	{
		PumpPosition += RTStatus.PumpPosition;
	}

	if (abs(PumpPosition - RTStatus.PumpPosition) <= PumpZero)
		return	ProNOErr;
	COMCheck = false;
	ValueStatus = 0u;
	i = 0u;
	ii = (abs(PumpPosition - RTStatus.PumpPosition)) / 20u + 20u;
	Common = 0u;
	j = 0u;
	t = 0u;
	HoldingSingelWrite2(MBName[ArmBase+31u], PumpPosition);
	osDelay(500u);
	if (PumpPosition > PumpZero)
	{
		COMCheck = true;
		ii *= 6u;
	}
	do {
		if (COMCheck)
		{
			t++;
			Common = HoldingSingelRead2(MBName[ArmBase + 18u]);
			if (Common == 0u)
			{
				j++;
			}
			else
			{
				j = 0u;
			}

			osDelay(50u);
		}
		else
		{
			osDelay(300u);
		}
		if (t % 10 == 0u)
		{
			RTStatus.PumpPosition = HoldingSingelRead2(MBName[ArmBase+11u]);
		}
	} while ((abs(PumpPosition - RTStatus.PumpPosition) > PumpZero) && (i++ < ii));

	if (i > ii)
	{
		Err = ProPumpBlockingErr;
	}
	if (COMCheck == true)
	{
		if (j > 10u)
		{
			RTStatus.Exist[RTStatus.Channel] = RTStatus.Common = StatusBlank;
		}
		else
		{
			RTStatus.Exist[RTStatus.Channel] = RTStatus.Common = StatusNonblank;
		}
		COMCheck = false;
	}

	
	return	Err;
}

ProcessErr	MotorCTRL(uint16_t ms)
{
	ProcessErr
		Err = ProNOErr;
	uint16_t	i = 0u;
	switch (ms)
	{
	case	M_Type1:
	case	M_Type2:
	{
		
		HoldingSingelWrite2(MBName[ArmBase + 39u], M_Type1);
		HoldingSingelWrite2(MBName[ArmBase + 35u], true);
		HoldingSingelWrite2(MBName[ArmBase + 38u], true);
		osDelay(700u);
		do
		{
			osDelay(300u);
		} while (HoldingSingelRead2(MBName[ArmBase + 28u]) && (i++ < (M_Type2+10000u) / 300u));
		HoldingSingelWrite2(MBName[ArmBase + 38u], false);
		HoldingSingelWrite2(MBName[ArmBase + 35u], false);

		if (i >= (M_Type2 + 10000u) / 300u)
			return	ProCommonErr;
		break;
	}
	case	M_Type10:
	{
		HoldingSingelWrite2(MBName[ArmBase + 39u], M_Type2);
		HoldingSingelWrite2(MBName[ArmBase + 35u], true);
		HoldingSingelWrite2(MBName[ArmBase + 38u], true);
		osDelay(700u);
		do
		{
			osDelay(300u);
		}while (HoldingSingelRead2(MBName[ArmBase + 28u]) && (i++ < M_Type10 / 300u * 2));

		HoldingSingelWrite2(MBName[ArmBase + 38u], false);
		HoldingSingelWrite2(MBName[ArmBase + 35u], false);

		if (i >= M_Type10 / 300u * 2u)
			return	ProCommonErr;
		break;
	}
	default:
		break;
	}

	return	Err;
}
ProcessErr	RBootARMMoveXYZ(uint16_t	X, uint16_t	Y, uint16_t	Z )
{
	uint16_t	i = 0u;
	uint16_t	LocationX = HoldingSingelRead2(MBName[ArmBase + 5u]);
	uint16_t	LocationY = HoldingSingelRead2(MBName[ArmBase + 7u]);
	uint16_t	LocationZ = HoldingSingelRead2(MBName[ArmBase + 9u]);
	ProcessErr
		Err = ProNOErr;
	i = 0u;
	if ((LocationX != X) || (LocationY != Y))
	{
		if ((LocationZ != 0))
		{
			HoldingSingelWrite2(MBName[ArmBase + 27u], 0u);
			do{
				osDelay(300u);
			} while ((HoldingSingelRead2(MBName[ArmBase + 9u]) != 0u) && (i++ < abs(0 - LocationZ) / 10u));
			if (i >= abs(0 - LocationZ) / 10u)
			{
				Err = ProArmZErr;
				return	Err;
			}
			LocationZ = RTStatus.RbootArmPosition[2u] = HoldingSingelRead2(MBName[ArmBase + 9u]);
		}
		HoldingSingelWrite2(MBName[ArmBase + 25u], X);
		HoldingSingelWrite2(MBName[ArmBase + 26u], Y);

		i = 0u;
		uint16_t	X;
		uint16_t	Y;
		do{
			osDelay(300u);
			X = HoldingSingelRead2(MBName[ArmBase + 5u]);
			Y = HoldingSingelRead2(MBName[ArmBase + 7u]);
		} while (
			((X != X) || (Y != Y))
			&& (i++ <
			(
			abs(X - LocationX) > abs(Y - LocationY) ?
			abs(X - LocationX) : abs(Y - LocationY)
			) / 10u
			)
			);
		if (i >=
			(
			abs(X - LocationX) > abs(Y - LocationY) ?
			abs(X - LocationX) : abs(Y - LocationY)
			) / 10u
			)
		{
			Err = ProArmXErr;
			return	Err;
		}
		LocationX = RTStatus.RbootArmPosition[0u] = HoldingSingelRead2(MBName[ArmBase + 5u]);
		LocationY = RTStatus.RbootArmPosition[1u] = HoldingSingelRead2(MBName[ArmBase + 7u]);
	}
	if (HoldingSingelRead2(MBName[ArmBase + 9u]) != Z)
	{
		HoldingSingelWrite2(MBName[ArmBase + 27u], Z);
		do{
			osDelay(300u);
		} while ((HoldingSingelRead2(MBName[ArmBase + 9u]) != Z) && (i++ < abs(Z - LocationZ) / 10u));
		if (i >= abs(Z - LocationZ) / 10u)
		{
			Err = ProArmZErr;
			return	Err;
		}
		LocationZ = RTStatus.RbootArmPosition[2u] = HoldingSingelRead2(MBName[ArmBase + 9u]);
	}
	return	Err;
}

ProcessErr	RBootARMMove(uint16_t	SerialNumbler)
{
	uint16_t	i = 0u;
	uint16_t	LocationX = HoldingSingelRead2(MBName[ArmBase+5u]);
	uint16_t	LocationY = HoldingSingelRead2(MBName[ArmBase+7u]);
	uint16_t	LocationZ = HoldingSingelRead2(MBName[ArmBase+9u]);
	ProcessErr
		Err = ProNOErr;
	i = 0u;
	if ((LocationX != XYZ[SerialNumbler][0u]) || (LocationY != XYZ[SerialNumbler][1u]))
	{
		if ((LocationZ != 0))
		{
			HoldingSingelWrite2(MBName[ArmBase+27u], 0u);
			do{
				osDelay(300u);
			} while ((HoldingSingelRead2(MBName[ArmBase+9u]) != 0u) && (i++ < abs(0 - LocationZ) / 10u));
			if (i >= abs(0 - LocationZ) / 10u)
			{
				Err = ProArmZErr;
				return	Err;
			}
			LocationZ = RTStatus.RbootArmPosition[2u] = HoldingSingelRead2(MBName[ArmBase + 9u]);
		}
		HoldingSingelWrite2(MBName[ArmBase + 25u], XYZ[SerialNumbler][0u]);
		HoldingSingelWrite2(MBName[ArmBase + 26u], XYZ[SerialNumbler][1u]);

		i = 0u;
		uint16_t	X;
		uint16_t	Y;
		do{
			osDelay(300u);
			X = HoldingSingelRead2(MBName[ArmBase + 5u]);
			Y = HoldingSingelRead2(MBName[ArmBase + 7u]);
		} while (
					( (X != XYZ[SerialNumbler][0u]) || (Y != XYZ[SerialNumbler][1u]))	
				&& ( i++ <  
					 (
						abs(XYZ[SerialNumbler][0u] - LocationX) > abs(XYZ[SerialNumbler][1u] - LocationY) ?
						abs(XYZ[SerialNumbler][0u] - LocationX) : abs(XYZ[SerialNumbler][1u] - LocationY)
					  ) / 10u
					)
				);
		if ( i >= 
				(
					abs(XYZ[SerialNumbler][0u] - LocationX) > abs(XYZ[SerialNumbler][1u] - LocationY) ?
					abs(XYZ[SerialNumbler][0u] - LocationX) :abs(XYZ[SerialNumbler][1u] - LocationY)
				) / 10u
			)
		{
			Err = ProArmXErr;
			return	Err;
		}
		LocationX = RTStatus.RbootArmPosition[0u] = HoldingSingelRead2(MBName[ArmBase + 5u]);
		LocationY = RTStatus.RbootArmPosition[1u] = HoldingSingelRead2(MBName[ArmBase + 7u]);
	}
	if (HoldingSingelRead2(MBName[ArmBase+9u]) != XYZ[SerialNumbler][2u])
	{
		HoldingSingelWrite2(MBName[ArmBase+27u], XYZ[SerialNumbler][2u]);
		do{
			osDelay(300u);
		} while ((HoldingSingelRead2(MBName[ArmBase+9u]) != XYZ[SerialNumbler][2u]) && (i++ < abs(XYZ[SerialNumbler][2u] - LocationZ) / 10u));
		if (i >= abs(XYZ[SerialNumbler][2u] - LocationZ) / 10u)
		{
			Err = ProArmZErr;
			return	Err;
		}
		LocationZ = RTStatus.RbootArmPosition[2u] = HoldingSingelRead2(MBName[ArmBase + 9u]);
	}
	return	Err;
}

ProcessErr	EffluentDeal(uint16_t	Delayms)
{
	ProcessErr
		Err = ProNOErr;
	uint8_t	i = 0u;
	HoldingSingelWrite2(MBName[ArmBase + 41u], 15000);
	HoldingSingelWrite2(MBName[ArmBase + 40u], true);
	HoldingSingelWrite2(MBName[ArmBase + 36u], true);
	osDelay(700u);
	do{
		osDelay(300u);
	} while (HoldingSingelRead2(MBName[ArmBase + 30u]) && (i++ < (Delayms + 299u) / 300u));

	HoldingSingelWrite2(MBName[ArmBase + 40u], false);
	HoldingSingelWrite2(MBName[ArmBase + 36u], false);
	if (i >= (Delayms + 99u) / 300u)
		return	ProCommonErr;

	return	Err;

}

ProcessErr	Spectropho(uint16_t	Channel)
{
	ProcessErr
		Err = ProNOErr;

	if (Channel)
		HoldingSingelWrite2(MBName[SpeBase + 30u], HoldingSingelRead2(MBName[SpeBase + 30u]) | (0x01u << (Channel - 1u)));
	else
		HoldingSingelWrite2(MBName[SpeBase + 30u], 0u);

	return	Err;
}
ProcessErr	ConcentrationRead(uint16_t	Channel)
{
	ProcessErr
		Err = ProNOErr;
	switch (Channel)
	{
	case 1u:	
		RTStatus.Concentration[0u] = HoldingSingelRead2(MBName[SpeBase + 31u]);
		break;
	case 2u:
		RTStatus.Concentration[1u] = HoldingSingelRead2(MBName[SpeBase + 32u]);
		break;
	case 3u:
		RTStatus.Concentration[2u] = HoldingSingelRead2(MBName[SpeBase + 33u]);
		break;
	case 4u:
		RTStatus.Concentration[3u] = HoldingSingelRead2(MBName[SpeBase + 34u]);
		break;
	default:
		break;
	}
	return	Err;
}
ProcessErr	SignalCMDDeal(enum enumCommand CMD, int16_t Value)
{
	ProcessErr
		Err = ProNOErr;

	switch (CMD)
	{
	case  CMDValve:
	{
		Err = ValveCTRL((enum enumType)Value);
		break;
	}
	case	CMDPump:
	{
		Err = PumpCTRL(Value);
		break;
	}
	case	CMDMotor:
	{
		Err = MotorCTRL(Value);
		break;
	}
	case CMDXYZ:
	{
		Err = RBootARMMove(Value);
		break;
	}
	case	CMDDLY:
	{
		osDelay(Value);
		break;
	}
	case	CMDEFF:
	{
		Err = EffluentDeal(Value);
		break;
	}
	case	CMDLED:
	{
		Err = Spectropho(Value);
		break;
	}
	case	CMDCOV:
	{
		Err = ConcentrationRead(Value);
		break;
	}
	default:
		break;
	}
	return	Err;
}



ProcessErr	ExsitErrDeal(enum	enumType	TypeSet)
{
	ProcessErr
		Err = ProNOErr;

	uint8_t t = 0u;
	if (!RTStatus.Exist[RTStatus.Channel])
	{
		g_pBaseInterface->ptrFuncLogger("%dÍ¨µÀÈ±Òº£¬ÕýÔÚ»Ö¸´...",RTStatus.Channel);
		//	ÅÅ¿Õ×¢Éä±Ã 	
		Err = SignalCMDDeal(CMDValve, Type1);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDMotor, 10000u);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDPump, 0);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDDLY, 1000u);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDValve, TypeSet);
		if (Err != ProNOErr)
			return	Err;

		for (uint8_t j = 0u; j < Retry; j++)
		{
			g_pBaseInterface->ptrFuncLogger("ÖØÊÔ´ÎÊý %d", j );
			//	Ñ­»·¼ì²â
			Err = SignalCMDDeal(CMDPump, (int16_t)((1000 + 1.0f) / 2.0096f));
			if (Err != ProNOErr)
				return	Err;
			Err = SignalCMDDeal(CMDDLY, 300u);
			if (Err != ProNOErr)
				return	Err;
			if (HoldingSingelRead2(MBName[ArmBase + 18u]) == 1u)
			{
				t++;
			}
			else
			{
				t = 0u;
			}

			if (t >= 3u)
			{
				RTStatus.Common = StatusNonblank;
			}
			else
			{
				RTStatus.Common = StatusBlank;
			}

			RTStatus.Exist[RTStatus.Channel] = RTStatus.Common;	

			if (( RTStatus.Exist[RTStatus.Channel] == StatusNonblank)
			||  ( RTStatus.PumpPosition >= PumpPositionMax / 2.0096f + 1.0f)
			   )
			{
				Err = SignalCMDDeal(CMDValve, Type1);
				if (Err != ProNOErr)
					return	Err;
				Err = SignalCMDDeal(CMDPump, -PumpPositionMax);
				if (Err != ProNOErr)
					return	Err;
				Err = SignalCMDDeal(CMDMotor, M_Type10);
				if (Err != ProNOErr)
					return	Err;
				Err = SignalCMDDeal(CMDDLY, 2000u);
				if (Err != ProNOErr)
					return	Err;
				Err = SignalCMDDeal(CMDValve, TypeSet);
				if (Err != ProNOErr)
					return	Err;
				if (RTStatus.Exist[RTStatus.Channel] == StatusNonblank)
					return	ProNOErr;
			}
		}
		Err = SignalCMDDeal(CMDValve, Type1);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDPump, -PumpPositionMax);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDMotor, M_Type10);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDDLY, 2000u);
		if (Err != ProNOErr)
			return	Err;
		Err = SignalCMDDeal(CMDValve, TypeSet);
		if (Err != ProNOErr)
			return	Err;
		Err = ProReagentErr;
		return	Err;

	}

	return	Err;
}


ProcessErr	ProcessDeal(enum enumCommand CMD, int16_t Value)
{
	ProcessErr
		Err = ProNOErr;

	Err = SignalCMDDeal(CMD, Value);

	if (CMD == CMDPump)
	{
		switch (RTStatus.Channel)
		{
		case	Type1:
		case	Type2:
		case	Type8:
		case	Type9:
		case	Type10:
		{
			break;
		}
		case	Type3:
		case	Type4:
		case	Type5:
		case	Type6:
		case	Type7:
		{
			if (RTStatus.Exist[RTStatus.Channel] == StatusBlank)
			{
				Err = ExsitErrDeal(RTStatus.Channel);
				if (Err == ProNOErr)
				{
					Err = SignalCMDDeal(CMD, Value);
					if (RTStatus.Exist[RTStatus.Channel] == StatusBlank)
						return	ProNoFluid;
				}
			}
			break;
		}
		default:
			break;
		}
	}
	return	Err;
}











