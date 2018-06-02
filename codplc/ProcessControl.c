

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
	"115",
	"116",
	"117",
	"MBArm_R_ComMotorCMD",
	"119",
	"MBArm_R_EffluentMotroCMD",
	"121",
	"122",
	"123",
	"124",
	"125",
	"126",
	"127",
	"128",
	"129",


};

int16_t	const	 XYZ[][3u] = {
	{ 0, 0, 0 },
	{ 400 - 400, 0, 4400 },
	{ 400 - 400, 0, 1600 },
	{ 2050 - 400, 0, 4400 },
	{ 2050 - 400, 0, 1600 },
	{ 3700 - 400, 0, 4400 },
	{ 3700 - 400, 0, 1600 },
	{ 5350 - 400, 0, 4400 },
	{ 5350 - 400, 0, 1600 },
	{ 400 - 400, 1650, 4400 },
	{ 400 - 400, 1650, 1600 },
	{ 2050 - 400, 1650, 4400 },
	{ 2050 - 400, 1650, 1600 },
	{ 3700 - 400, 1650, 4400 },
	{ 3700 - 400, 1650, 1600 },
	{ 5350 - 400, 1650, 4400 },
	{ 5350 - 400, 1650, 1600 },
	{ 400 - 400, 3300, 4400 },
	{ 400 - 400, 3300, 1600 },
	{ 2050 - 400, 3300, 4400 },
	{ 2050 - 400, 3300, 1600 },
	{ 3700 - 400, 3300, 4400 },
	{ 3700 - 400, 3300, 1600 },
	{ 5350 - 400, 3300, 4400 },
	{ 5350 - 400, 3300, 1600 },
	{ 400 - 400, 4950, 4400 },
	{ 400 - 400, 4950, 1600 },
	{ 2050 - 400, 4950, 4400 },
	{ 2050 - 400, 4950, 1600 },
	{ 3700 - 400, 4950, 4400 },
	{ 3700 - 400, 4950, 1600 },
	{ 5350 - 400, 4950, 4400 },
	{ 5350 - 400, 4950, 1600 },
	{ 400 - 400, 6600, 4400 },
	{ 400 - 400, 6600, 1600 },
	{ 2050 - 400, 6600, 4400 },
	{ 2050 - 400, 6600, 1600 },
	{ 3700 - 400, 6600, 4400 },
	{ 3700 - 400, 6600, 1600 },
	{ 5350 - 400, 6600, 4400 },
	{ 5350 - 400, 6600, 1600 },
	{ 400 - 400, 8250, 4400 },
	{ 400 - 400, 8250, 1600 },
	{ 2050 - 400, 8250, 4400 },
	{ 2050 - 400, 8250, 1600 },
	{ 3700 - 400, 8250, 4400 },
	{ 3700 - 400, 8250, 1600 },
	{ 5350 - 400, 8250, 4400 },
	{ 5350 - 400, 8250, 1600 },





	{ 9850 - 400, 0, 4400 },
	{ 9850 - 400, 0, 1600 },
	{ 11500 - 400, 0, 4400 },
	{ 11500 - 400, 0, 1600 },
	{ 13150 - 400, 0, 4400 },
	{ 13150 - 400, 0, 1600 },
	{ 14800 - 400, 0, 4400 },
	{ 14800 - 400, 0, 1600 },
	{ 8200 - 400, 1650, 4400 },
	{ 8200 - 400, 1650, 1600 },
	{ 9850 - 400, 1650, 4400 },
	{ 9850 - 400, 1650, 1600 },
	{ 11500 - 400, 1650, 4400 },
	{ 11500 - 400, 1650, 1600 },
	{ 13150 - 400, 1650, 4400 },
	{ 13150 - 400, 1650, 1600 },
	{ 14800 - 400, 1650, 4400 },
	{ 14800 - 400, 1650, 1600 },
	{ 16450 - 400, 1650, 4400 },
	{ 16450 - 400, 1650, 1600 },
	{ 8200 - 400, 3300, 4400 },
	{ 8200 - 400, 3300, 1600 },
	{ 9850 - 400, 3300, 4400 },
	{ 9850 - 400, 3300, 1600 },
	{ 11500 - 400, 3300, 4400 },
	{ 11500 - 400, 3300, 1600 },
	{ 13150 - 400, 3300, 4400 },
	{ 13150 - 400, 3300, 1600 },
	{ 14800 - 400, 3300, 4400 },
	{ 14800 - 400, 3300, 1600 },
	{ 16450 - 400, 3300, 4400 },
	{ 16450 - 400, 3300, 1600 },
	{ 8200 - 400, 4950, 4400 },
	{ 8200 - 400, 4950, 1600 },
	{ 9850 - 400, 4950, 4400 },
	{ 9850 - 400, 4950, 1600 },
	{ 11500 - 400, 4950, 4400 },
	{ 11500 - 400, 4950, 1600 },
	{ 13150 - 400, 4950, 4400 },
	{ 13150 - 400, 4950, 1600 },
	{ 14800 - 400, 4950, 4400 },
	{ 14800 - 400, 4950, 1600 },
	{ 16450 - 400, 4950, 4400 },
	{ 16450 - 400, 4950, 1600 },
	{ 9850 - 400, 6600, 4400 },
	{ 9850 - 400, 6600, 1600 },
	{ 11500 - 400, 6600, 4400 },
	{ 11500 - 400, 6600, 1600 },
	{ 13150 - 400, 6600, 4400 },
	{ 13150 - 400, 6600, 1600 },
	{ 14800 - 400, 6600, 4400 },
	{ 14800 - 400, 6600, 1600 },



	{ 24850 - 400, 0, 4400 },
	{ 24850 - 400, 0, 1600 },
	{ 26500 - 400, 0, 4400 },
	{ 26500 - 400, 0, 1600 },
	{ 28150 - 400, 0, 4400 },
	{ 28150 - 400, 0, 1600 },
	{ 29800 - 400, 0, 4400 },
	{ 29800 - 400, 0, 1600 },
	{ 23200 - 400, 1650, 4400 },
	{ 23200 - 400, 1650, 1600 },
	{ 24850 - 400, 1650, 4400 },
	{ 24850 - 400, 1650, 1600 },
	{ 26500 - 400, 1650, 4400 },
	{ 26500 - 400, 1650, 1600 },
	{ 28150 - 400, 1650, 4400 },
	{ 28150 - 400, 1650, 1600 },
	{ 29800 - 400, 1650, 4400 },
	{ 29800 - 400, 1650, 1600 },
	{ 31450 - 400, 1650, 4400 },
	{ 31450 - 400, 1650, 1600 },
	{ 23200 - 400, 3300, 4400 },
	{ 23200 - 400, 3300, 1600 },
	{ 24850 - 400, 3300, 4400 },
	{ 24850 - 400, 3300, 1600 },
	{ 26500 - 400, 3300, 4400 },
	{ 26500 - 400, 3300, 1600 },
	{ 28150 - 400, 3300, 4400 },
	{ 28150 - 400, 3300, 1600 },
	{ 29800 - 400, 3300, 4400 },
	{ 29800 - 400, 3300, 1600 },
	{ 31450 - 400, 3300, 4400 },
	{ 31450 - 400, 3300, 1600 },
	{ 23200 - 400, 4950, 4400 },
	{ 23200 - 400, 4950, 1600 },
	{ 24850 - 400, 4950, 4400 },
	{ 24850 - 400, 4950, 1600 },
	{ 26500 - 400, 4950, 4400 },
	{ 26500 - 400, 4950, 1600 },
	{ 28150 - 400, 4950, 4400 },
	{ 28150 - 400, 4950, 1600 },
	{ 29800 - 400, 4950, 4400 },
	{ 29800 - 400, 4950, 1600 },
	{ 31450 - 400, 4950, 4400 },
	{ 31450 - 400, 4950, 1600 },
	{ 24850 - 400, 6600, 4400 },
	{ 24850 - 400, 6600, 1600 },
	{ 26500 - 400, 6600, 4400 },
	{ 26500 - 400, 6600, 1600 },
	{ 28150 - 400, 6600, 4400 },
	{ 28150 - 400, 6600, 1600 },
	{ 29800 - 400, 6600, 4400 },
	{ 29800 - 400, 6600, 1600 },


};
//struct	uTubeReagent	TubeReagent[TubeMax];

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
	case	ProNoWaterFirst:
		g_pBaseInterface->ptrFuncLogger("\r\n%s Ç°È±Òº£¡\r\n", s);
		break;
	case	ProNoWaterLast:
		g_pBaseInterface->ptrFuncLogger("\r\n%s ºóÈ±Òº£¡\r\n", s);
		break;
	case	ProNoWater:
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
}

_Bool	HoldingSingelWrite2(const	char *lpName, uint16_t	Data)
{
	if (g_pBaseInterface->ptrSetPntValueByName(lpName, Data, 2000u))
	{
		;
	}
	else
	{
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
		osDelay(100u);
		while ((RTStatus.Channel != Channel) && (i++ < 50u))
		{
			osDelay(300u);
			RTStatus.Channel = (enum enumType)HoldingSingelRead2(MBName[ArmBase+13u]);
		}
		if (i >= 50u)
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
	int16_t	PumpPosition = (int16_t)((ulPumpPosition + 1.0f) / 2.0096f);
	if (RTStatus.PumpPosition + PumpPosition > (21000 + 1.0f) / 2.0096f)
		PumpPosition = (int16_t)((21000 + 1.0f) / 2.0096f);
	else
		if (RTStatus.PumpPosition + PumpPosition < 0)
			PumpPosition = 0u;
		else
			PumpPosition += RTStatus.PumpPosition;
	if (abs(PumpPosition - RTStatus.PumpPosition) > PumpZero)
	{
		uint16_t	i = 0u;
		uint16_t	ValueStatus = 0u;

		uint16_t	ii = (abs(PumpPosition - RTStatus.PumpPosition)) / 20u + 20u;
		HoldingSingelWrite2(MBName[ArmBase+31u], PumpPosition);
		osDelay(500u);

		do{
			osDelay(300u);
			RTStatus.PumpPosition = HoldingSingelRead2(MBName[ArmBase+11u]);
		} while ((abs(PumpPosition - RTStatus.PumpPosition) > PumpZero) && (i++ < ii));
		
		osDelay(1000u);
		ValueStatus = HoldingSingelRead2(MBName[ArmBase+19u]);

		if (ValueStatus != 0xFFFFu)
		{
			for (uint8_t i = 0u; i < TypeMax; i++)
			{
				if (!((ValueStatus >> i) & 0x0001u))
				{
					RTStatus.Exist[i] = StatusBlank;
				}
			}
		}

		if (i > ii)
		{
			Err = ProPumpBlockingErr;
			return	Err;
		}
	}
	return Err;
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
		//g_pBaseInterface->ptrFuncLogger("Holding[28u] %d ", HoldingSingelRead2(MBName[ArmBase + 28u]));
		do
		{
			osDelay(300u);
		} while (HoldingSingelRead2(MBName[ArmBase + 28u]) && (i++ < (M_Type2+2000u) / 300u));
		//g_pBaseInterface->ptrFuncLogger("Holding[28u] %d ", HoldingSingelRead2(MBName[ArmBase + 28u]));
		//g_pBaseInterface->ptrFuncLogger("Holding[28u]i %d ", i);
		HoldingSingelWrite2(MBName[ArmBase + 38u], false);
		HoldingSingelWrite2(MBName[ArmBase + 35u], false);

		if (i >= M_Type2 / 50u)
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
			LocationZ = HoldingSingelRead2(MBName[ArmBase+9u]);
		}
		HoldingSingelWrite2(MBName[ArmBase+25u], XYZ[SerialNumbler][0u]);
		osDelay(300u); 
		HoldingSingelWrite2(MBName[ArmBase + 26u], XYZ[SerialNumbler][1u]);

		i = 0u;
		do{
			osDelay(300u);
		} while (((HoldingSingelRead2(MBName[ArmBase+5u]) != XYZ[SerialNumbler][0u]) ||
			(HoldingSingelRead2(MBName[ArmBase+7u]) != XYZ[SerialNumbler][1u])) &&
			(i++ < (abs(XYZ[SerialNumbler][0u] - LocationX) >
			abs(XYZ[SerialNumbler][1u] - LocationY) ?
			abs(XYZ[SerialNumbler][0u] - LocationX) :
			abs(XYZ[SerialNumbler][1u] - LocationY)) / 10u
			)
			);
		if (i >= (abs(XYZ[SerialNumbler][0u] - LocationX) >
			abs(XYZ[SerialNumbler][1u] - LocationY) ?
			abs(XYZ[SerialNumbler][0u] - LocationX) :
			abs(XYZ[SerialNumbler][1u] - LocationY)) / 10u
			)
		{
			Err = ProArmXErr;
			return	Err;
		}
	}
	if (HoldingSingelRead2(MBName[ArmBase+9u]) != XYZ[SerialNumbler][2u])
	{
		HoldingSingelWrite2(MBName[ArmBase+27u], XYZ[SerialNumbler][2u]);
		do{
			osDelay(100u);
		} while ((HoldingSingelRead2(MBName[ArmBase+9u]) != XYZ[SerialNumbler][2u]) && (i++ < abs(XYZ[SerialNumbler][2u] - LocationZ) / 10u));
		if (i >= abs(XYZ[SerialNumbler][2u] - LocationZ) / 10u)
		{
			Err = ProArmZErr;
			return	Err;
		}
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
	do
	{
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
		if( Channel )
			HoldingSingelWrite2( MBName[30u+30u], HoldingSingelRead2( MBName[30u+30u] ) | (0x01u << (Channel - 1u)) );
		else
			HoldingSingelWrite2( MBName[30u+30u], 0u );
	return	Err;
}
ProcessErr	ConcentrationRead(uint16_t	Channel)
{
	ProcessErr
		Err = ProNOErr;
		switch( Channel )
		{
		case 1u:
				RTStatus.Concentration[0u] = HoldingSingelRead2(MBName[30u + 31u]);
				break;
			case 2u:
				RTStatus.Concentration[1u] = HoldingSingelRead2(MBName[30u + 32u]);
				break;
			case 3u:
				RTStatus.Concentration[2u] = HoldingSingelRead2(MBName[30u + 33u]);
				break;
			case 4u:
				RTStatus.Concentration[3u] = HoldingSingelRead2(MBName[30u + 34u]);
				break;
			default:
				break;
		}
	return	Err;

}
ProcessErr	SignalCMDDeal(struct	uCMDs	CMDs)
{
	ProcessErr
		Err = ProNOErr;

	switch (CMDs.CMD)
	{
	case  CMDValve:
	{
		Err = ValveCTRL((enum enumType)CMDs.Control);
		break;
	}
	case	CMDPump:
	{
		Err = PumpCTRL(CMDs.Control);
		break;
	}
	case	CMDMotor:
	{
		Err = MotorCTRL(CMDs.Control);
		break;
	}
	case CMDXYZ:
	{
		Err = RBootARMMove(CMDs.Control);
		break;
	}
	case	CMDDLY:
	{
		osDelay(CMDs.Control);
		break;
	}
	case	CMDEFF:
	{
		Err = EffluentDeal(CMDs.Control);
		break;
	}
	case	CMDLED:
	{
		Err = Spectropho(CMDs.Control);
		break;
	}
	case	CMDCOV:
	{
		Err = ConcentrationRead(CMDs.Control);
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
#define Retry	30u

	struct uCMDs ExsitErrInit[] =
	{
		{ CMDValve, Type1 },
		{ CMDMotor, 10000u },
		{ CMDPump, 0 },
		{ CMDDLY, 1000u },
		{ CMDValve, TypeSet },
	};
	struct uCMDs ExsitErr[] =
	{
		{ CMDPump, (int16_t)(1000 / 2.0096f + 0.5f) },
		{ CMDDLY, 300u },
	};
	struct uCMDs ExsitErrEnd[] =
	{
		{ CMDValve, Type1 },
		{ CMDPump, -20000 },
		{ CMDMotor, 10000u },
		{ CMDDLY, 2000u },
		{ CMDValve, TypeSet },
	};


	uint8_t t = 0u;
	if (!RTStatus.Exist[RTStatus.Channel])
	{

		for (uint8_t i = 0u; i < sizeof(ExsitErrInit) / sizeof(ExsitErrInit[0u]); i++)
		{
			Err = SignalCMDDeal(ExsitErrInit[i]);
			if (Err != ProNOErr)	return	Err;
		}

		for (uint8_t j = 0u; j < Retry; j++)
		{
			uint16_t ValueStatus = 0u;
			ValueStatus = HoldingSingelRead2(MBName[ArmBase+19u]);
			if (ValueStatus != 0xFFFFu)
			{
				if ((ValueStatus >> RTStatus.Channel) & 0x0001u)
				{
					if ( ++t >= 3u )
						RTStatus.Exist[RTStatus.Channel] = StatusNonblank;
				}
				else
				{
					RTStatus.Exist[RTStatus.Channel] = StatusBlank;
					t = 0u;
				}
			}				

			if (RTStatus.Exist[RTStatus.Channel])
			{
				for (uint8_t i = 0u; i < sizeof(ExsitErrEnd) / sizeof(ExsitErrEnd[0u]); i++)
					Err = SignalCMDDeal(ExsitErrEnd[i]);
				return	Err;
			}

			for (uint8_t i = 0u; i < sizeof(ExsitErr) / sizeof(ExsitErr[0u]); i++)
			{
				Err = SignalCMDDeal(ExsitErr[i]);
				if (Err != ProNOErr)	return	Err;
			}

			if (RTStatus.PumpPosition >= (20000 + 1.0f) / 2.0096f)
				for (uint8_t i = 0u; i < sizeof(ExsitErrEnd) / sizeof(ExsitErrEnd[0u]); i++)
				{
					Err = SignalCMDDeal(ExsitErrEnd[i]);
					if (Err != ProNOErr)	return	Err;
				}
		}
		for (uint8_t i = 0u; i < sizeof(ExsitErrEnd) / sizeof(ExsitErrEnd[0u]); i++)
			Err = SignalCMDDeal(ExsitErrEnd[i]);
		Err = ProReagentErr;
		return	Err;

	}

	return	Err;
}


ProcessErr	ProcessDeal(struct	uCMDs * CMDs, uint8_t	CMDsLenth)
{
	ProcessErr
		Err = ProNOErr;
	for (uint8_t ix = 0u; ix < CMDsLenth; ix++)
	{
		Err = SignalCMDDeal(CMDs[ix]);

		if (CMDs[ix].CMD == CMDPump)
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
				if (!RTStatus.Exist[RTStatus.Channel])
					ix -= 1u;
				Err = ExsitErrDeal(RTStatus.Channel);
				break;
			}
			default:
				break;
			}
		}
		if (Err != ProNOErr)
			return	Err;
	}
	return	Err;
}


















