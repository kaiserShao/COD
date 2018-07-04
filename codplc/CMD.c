/*!
 ** (C) COPYRIGHT 2018 青岛中特环保仪器有限公司 **
 * \file CMD.c
 *
 * \author kaiser
 * \date 2018/06/12
 *
 * 
 */
#include "DEBUG.H"

//************************************
// Method:    注射泵吸排液控制
// FullName:  PumpFluidControl
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: enum enumType TypeSet
// Parameter: int16_t Dosage
//************************************
ProcessErr	PumpFluidControl(enum	enumType	TypeSet, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	int16_t Value2 = 0u;
	if (Dosage > 0)
	{
		switch (TypeSet)
		{
		case Type1:
		{
			Value2 = Dosage / 8 + 600u;
			break;
		}
		case Type2:
		{
			Value2 = Dosage / 20 + 600u;
			break;
		}
		case Type3:
		{
			Value2 = Dosage / 5 + 600u;
			break;
		}
		case Type4:
		case Type5:
		{			
			Value2 = Dosage / 1 + 1500u;
			break;
		}
		case Type6:
		case Type7:
		{
			Value2 = Dosage / 4 + 1500u;
			break;
		}
		default:
			Value2 = 200u;
			break;
		}
	}
	else
		Value2 = 0u;
	Err = ProcessDeal(CMDValve, TypeSet);
	if (Err != ProNOErr)
		return Err;
	Err = ProcessDeal(CMDPump, Dosage);
	if (Err != ProNOErr)
		return Err;
	Err = ProcessDeal(CMDDLY, Value2);
	if (Err != ProNOErr)
		return Err;

	return	Err;
}
//************************************
// Method:    平衡注射泵气压
// FullName:  Decompress
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	Decompress(void)
{
	ProcessErr
		Err = ProNOErr;
	Err = ProcessDeal(CMDValve, Type10);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type1);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    排空公共管
// FullName:  EmptyingCommon
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t M_Type
//************************************
ProcessErr	EmptyingCommon(uint16_t M_Type)
{
	ProcessErr
		Err = ProNOErr;
	Err = ProcessDeal(CMDValve, Type1);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    排空注射泵
// FullName:  PumpEvacuation
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	PumpEvacuation(void)
{
	ProcessErr
		Err = ProNOErr;

	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = EmptyingCommon(M_Type2);
	if (Err != ProNOErr)
		return	Err;
	return Err;
}
//************************************
// Method:    清洗注射泵
// FullName:  PumpCleanOut
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	PumpCleanOut(void)
{
	ProcessErr
		Err = ProNOErr;
	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type3, 2000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type10, PumpPositionMax - 2000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    润洗注射泵
// FullName:  PumpRinse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: enum enumType TypeSet
//************************************
ProcessErr	PumpRinse(enum	enumType	TypeSet)
{
	ProcessErr
		Err = ProNOErr;
	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(TypeSet, 1000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type10, Full - 1000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    外部吸液润洗注射泵
// FullName:  PumpRinseType2
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Numbler
//************************************
ProcessErr	PumpRinseType2(uint16_t Numbler)
{
	ProcessErr
		Err = ProNOErr;
	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDXYZ, Numbler * 2u - 1u);
	if (Err != ProNOErr)
		return Err;
	Err = PumpFluidControl(Type2, 1000);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDXYZ, Numbler * 2u);
	if (Err != ProNOErr)
		return Err;
	Err = PumpFluidControl(Type2, Full - 1000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type1, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    注液到试管
// FullName:  AddToTube
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Numbler
// Parameter: int16_t Dosage
//************************************
ProcessErr	AddToTube(uint16_t	Numbler, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	uint8_t Channel = RTStatus.Channel;
	Err = ProcessDeal(CMDXYZ, Numbler * 2u);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpFluidControl(Type2, -Dosage);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    从试管取液
// FullName:  TakeOutFromTube
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t SampleNum
// Parameter: int16_t Dosage
//************************************
ProcessErr	TakeOutFromTube(uint16_t	SampleNum, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	Err = ProcessDeal(CMDXYZ, SampleNum * 2u - 1u);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, Dosage);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDXYZ, SampleNum * 2u);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, 3000);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type1);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, -4000);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = Decompress();
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    空气搅拌
// FullName:  AIR_Stir
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Numbler
//************************************
ProcessErr	AIR_Stir(uint16_t	Numbler)
{
	ProcessErr
		Err = ProNOErr;

	if (Numbler == 0u)
		return Err;
	Err = ProcessDeal(CMDXYZ, Numbler * 2u - 1u);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type10);
	if (Err != ProNOErr)
		return	Err;

	return	Err;

}
//************************************
// Method:    试管清空
// FullName:  EffluentOut
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Numbler
//************************************
ProcessErr	EffluentOut(uint16_t	Numbler)
{
	ProcessErr
		Err = ProNOErr;

	if (Numbler == 0u)
	{
		return Err;
	}
	Err = ProcessDeal(CMDXYZ, Numbler * 2u - 1u);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDEFF, 25000);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    转移待比色液体
// FullName:  ColorimetricFlood
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Numbler
// Parameter: int16_t Dosage
//************************************
ProcessErr	ColorimetricFlood(uint16_t	Numbler, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	Err = ProcessDeal(CMDXYZ, Numbler * 2u - 1u);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type2);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, Dosage);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDXYZ, Numbler * 2u);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, 15000);
	if (Err != ProNOErr)
		return	Err;
	Err = Decompress();
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type9);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type10);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type1);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    比色管清空
// FullName:  ColorimetricOutClean
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	ColorimetricOutClean(void)
{
	ProcessErr
		Err = ProNOErr;
	Err = ProcessDeal(CMDValve, Type9);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, Full);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type1);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;	

	Err = ProcessDeal(CMDValve, Type3);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, 8000);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type9);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type10);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type10);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, Full);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDValve, Type1);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDPump, -PumpPositionMax);
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDMotor, M_Type2);
	if (Err != ProNOErr)
		return	Err;

	return	Err;
}
//************************************
// Method:    比色
// FullName:  Colorimetric
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Channel
//************************************
ProcessErr	Colorimetric(uint16_t	Channel)
{
	ProcessErr
		Err = ProNOErr;

	Err = ProcessDeal(CMDDLY, (Channel == 0 ? 500u : 10000u));
	if (Err != ProNOErr)
		return	Err;
	Err = ProcessDeal(CMDCOV, Full);
	if (Err != ProNOErr)
		return	Err;

	return	Err;

}








//************************************
// Method:    气泡搅拌混合
// FullName:  TubeMix
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * TubeList
// Parameter: uint8_t Size
//************************************
ProcessErr	TubeMix(uint8_t	* TubeList, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;

	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = AIR_Stir(TubeList[i]);
		if (Err != ProNOErr)
			return	Err;
	}

	return	Err;

}
//************************************
// Method:    批量试管清洗
// FullName:  TubeClean
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * TubeList
// Parameter: uint8_t Size
//************************************
ProcessErr	TubeClean(uint8_t	* TubeList, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;

	if (PumpEvacuation() != ProNOErr)
		return	Err;
	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = EffluentOut(TubeList[i]);
		if (Err != ProNOErr)
			return	Err;
		RTStatus.TubeReagent[TubeList[i]].Water = 0u;
		RTStatus.TubeReagent[TubeList[i]].LowLevel = 0u;
		RTStatus.TubeReagent[TubeList[i]].HighLevel = 0u;
		RTStatus.TubeReagent[TubeList[i]].AgNo3 = 0u;
		RTStatus.TubeReagent[TubeList[i]].KCrO = 0u;
		RTStatus.TubeReagent[TubeList[i]].Sum = 0u;
		RTStatus.TubeReagent[TubeList[i]].CleanCount = 1u;
		RTStatus.TubeReagent[TubeList[i]].ConcentrationValue = 0u;
		RTStatus.TubeReagent[TubeList[i]].ChloridionHL = StateUnknown;
		RTStatus.TubeReagent[TubeList[i]].ConcentrationHL = StateUnknown;
	}

	for (uint8_t i = 0u; i < Size; i++)
	{
		if (RTStatus.PumpPosition < (Clean + 1.0f) / 2.0096f)
		{
			if ((Size - i) * Clean > 20000u)
				Err = PumpFluidControl(Type3, 20000);
			else
				Err = PumpFluidControl(Type3, (Size - i) * Clean - (int16_t)(RTStatus.PumpPosition * 2.0096f + 2000));
			if (Err != ProNOErr)
				return	Err;
		}

		Err = AddToTube(TubeList[i], Clean);
		if (Err != ProNOErr)
			return	Err;

		RTStatus.TubeReagent[i].Water += Clean;

	}
	Err = PumpEvacuation();
	if (Err != ProNOErr)
		return	Err;
	Err = TubeMix(TubeList, Size);
	if (Err != ProNOErr)
		return	Err;

	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = EffluentOut(TubeList[i]);
		if (Err != ProNOErr)
			return	Err;
		RTStatus.TubeReagent[TubeList[i]].Water = 0u;
		RTStatus.TubeReagent[TubeList[i]].LowLevel = 0u;
		RTStatus.TubeReagent[TubeList[i]].HighLevel = 0u;
		RTStatus.TubeReagent[TubeList[i]].AgNo3 = 0u;
		RTStatus.TubeReagent[TubeList[i]].KCrO = 0u;
		RTStatus.TubeReagent[TubeList[i]].Sample = 0u;
		RTStatus.TubeReagent[TubeList[i]].Sum = 0u;
		RTStatus.TubeReagent[TubeList[i]].CleanCount = 2u;
		RTStatus.TubeReagent[TubeList[i]].ConcentrationValue = 0u;
		RTStatus.TubeReagent[TubeList[i]].ChloridionHL = StateUnknown;
		RTStatus.TubeReagent[TubeList[i]].ConcentrationHL = StateUnknown;
	}
	Err = ProcessDeal(CMDXYZ, TubeList[Size - 1] * 2u);
	if (Err != ProNOErr)
		return	Err;

	return	Err;

}
//************************************
// Method:    吸取预装试剂到试管
// FullName:  Preparation
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * TubeList
// Parameter: uint8_t Size
// Parameter: enum enumType TypeSet
// Parameter: int16_t Dosage
//************************************
ProcessErr	Preparation(uint8_t	* TubeList, uint8_t Size, enum enumType TypeSet, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.PumpPosition)
	{
		Err = PumpFluidControl(Type1, -PumpPositionMax);
		if (Err != ProNOErr)
			return	Err;
	}

	for (uint8_t i = 0u; i < Size; i++)
	{
		if (RTStatus.PumpPosition < (Dosage + 1.0f) / 2.0096f)
		{
			if ((Size - i) * Dosage > Full)
			{
				Err = PumpFluidControl(TypeSet, Full + 2000);
			}	
			else
			{
				Err = PumpFluidControl(TypeSet, (Size - i) * Dosage - (int16_t)(RTStatus.PumpPosition * 2.0096f) + 2000);
			}
			if (Err != ProNOErr)
				return	Err;
			switch (TypeSet)
			{
			case Type3:
			{
				Err = PumpFluidControl(Type1, -1000);
				if (Err != ProNOErr)
					return	Err;
				Err = EmptyingCommon(M_Type2);
				if (Err != ProNOErr)
					return	Err;
				break;
			}
			case Type4:
			{
				if (Err != ProNOErr)
					return	Err;
				Err = EmptyingCommon(M_Type10);
				Err = PumpFluidControl(Type1, -1000);
				Err = EmptyingCommon(M_Type2);
				if (Err != ProNOErr)
					return	Err;
				break;
			}
			case Type5:
			{
				if (Err != ProNOErr)
					return	Err;
				Err = EmptyingCommon(M_Type10);
				Err = PumpFluidControl(Type1, -1000);
				Err = EmptyingCommon(M_Type2);
				if (Err != ProNOErr)
					return	Err;
				break;
			}
			case Type6:
			{
				Err = PumpFluidControl(Type1, -1000);
				if (Err != ProNOErr)
					return	Err;
				Err = EmptyingCommon(M_Type2);
				if (Err != ProNOErr)
					return	Err;
				break;
			}
			case Type7:
			{
				Err = PumpFluidControl(Type1, -1000);
				if (Err != ProNOErr)
					return	Err;
				Err = EmptyingCommon(M_Type2);
				if (Err != ProNOErr)
					return	Err;
				break;
			}
			default:
				break;
			}
			Err = Decompress();
			if (Err != ProNOErr)
				return	Err;
		}

		Err = AddToTube(TubeList[i], Dosage);
		if (Err != ProNOErr)
			return	Err;
		switch (TypeSet)
		{
		case Type3:
		{
			RTStatus.TubeReagent[TubeList[i]].Water += Dosage;
			break;
		}
		case Type4:
		{
			Err = ProcessDeal(CMDMotor, M_Type2);
			if (Err != ProNOErr)
				return	Err;
			Err = ProcessDeal(CMDMotor, M_Type2);
			if (Err != ProNOErr)
				return	Err;
			RTStatus.TubeReagent[TubeList[i]].LowLevel += Dosage;
			break;
		}
		case Type5:
		{
			Err = ProcessDeal(CMDMotor, M_Type2);
			if (Err != ProNOErr)
				return	Err;
			Err = ProcessDeal(CMDMotor, M_Type2);
			if (Err != ProNOErr)
				return	Err;
			RTStatus.TubeReagent[TubeList[i]].HighLevel += Dosage;
			break;
		}
		case Type6:
		{
			Err = ProcessDeal(CMDMotor, M_Type2);
			if (Err != ProNOErr)
				return	Err;
			RTStatus.TubeReagent[TubeList[i]].AgNo3 += Dosage;
			break;
		}
		case Type7:
		{
			Err = ProcessDeal(CMDMotor, M_Type2);
			if (Err != ProNOErr)
				return	Err;
			RTStatus.TubeReagent[TubeList[i]].KCrO += Dosage;
			break;
		}
		default:
			break;
		}
	}
	Err = PumpEvacuation();
	if (Err != ProNOErr)
		return	Err;

	return	Err;

}
//************************************
// Method:    采集水样到试管
// FullName:  WaterSampleIn
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * TubeList
// Parameter: uint8_t Size
// Parameter: uint8_t SampleNum
// Parameter: int16_t Dosage
//************************************
ProcessErr	WaterSampleIn(uint8_t	* TubeList, uint8_t Size, uint8_t SampleNum, int16_t Dosage)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.PumpPosition)
	{
		Err = PumpFluidControl(Type1, -PumpPositionMax);
		if (Err != ProNOErr)
			return	Err;
	}

	for (uint8_t i = 0u; i < Size; i++)
	{
		if (RTStatus.PumpPosition < (Dosage + 1.0f) / 2.0096f)
		{
			if ((Size - i) * Dosage > Full-2000)
			{
				Err = TakeOutFromTube(SampleNum, Full-2000);
				RTStatus.TubeReagent[SampleNum].Sample -= Full-2000;
			}
			else
			{
				Err = TakeOutFromTube(SampleNum, (Size - i) * Dosage - (int16_t)(RTStatus.PumpPosition * 2.0096f) + 2000);
				RTStatus.TubeReagent[SampleNum].Sample -= ((Size - i) * Dosage - (int16_t)(RTStatus.PumpPosition * 2.0096f) + 2000);
			}
			if (Err != ProNOErr)
				return	Err;
			Err = Decompress();
			if (Err != ProNOErr)
				return	Err;
		}
		Err = AddToTube(TubeList[i], Dosage);
		if (Err != ProNOErr)
			return	Err;

		RTStatus.TubeReagent[i].Sample += Dosage;
	}
	Err = PumpEvacuation();
	if (Err != ProNOErr)
		return	Err;
	return	Err;

}
//************************************
// Method:    水样稀释
// FullName:  WaterSampleAttenuation
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t WaterSampleNumbler
// Parameter: uint8_t AttenuationNumbler
//************************************
ProcessErr	WaterSampleAttenuation(uint8_t	WaterSampleNumbler, uint8_t AttenuationNumbler)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.PumpPosition)
	{
		Err = PumpFluidControl(Type1, -Full);
		if (Err != ProNOErr)
			return	Err;
	}

	Err = PumpFluidControl(Type3, DosageType2 * 9 + 2000);
	if (Err != ProNOErr)
		return	Err;
	Err = Decompress();
	if (Err != ProNOErr)
		return	Err;
	Err = AddToTube(AttenuationNumbler, 18000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpEvacuation();
	RTStatus.TubeReagent[AttenuationNumbler].Water += 18000u;
	Err = TakeOutFromTube(WaterSampleNumbler, DosageType2 + 2000);
	if (Err != ProNOErr)
		return	Err;
	Err = AddToTube(AttenuationNumbler, DosageType2);
	if (Err != ProNOErr)
		return	Err;
	RTStatus.TubeReagent[WaterSampleNumbler].Sample -= DosageType2+2000;
	RTStatus.TubeReagent[AttenuationNumbler].Sample += DosageType2;
	Err = PumpEvacuation();
	if (Err != ProNOErr)
		return	Err;
	return	Err;

}
//************************************
// Method:    机械臂移动
// FullName:  RbootArmChange
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint16_t Numbler
//************************************
ProcessErr	RbootArmChange(uint16_t Numbler)
{
	ProcessErr
		Err = ProNOErr;
	Err = ProcessDeal(CMDXYZ, Numbler);
	if (Err != ProNOErr)
		return	Err;
	return	Err;
}









//************************************
// Method:    实时状态初始化
// FullName:  RTStatus_Init
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	RTStatus_Init(void)
{
	ProcessErr
		Err = ProNOErr;
	RTStatus.PumpPosition = HoldingSingelRead2(MBName[ArmBase + 11u]);
	for (uint8_t i = 0; i < TypeMax; i++)
	{
		RTStatus.Exist[i] = StatusNonblank;
		/*Err = PumpFluidIn((enum enumType)i, 1000);
		switch ((enum enumType)i)
		{
		case Type3:
		{
			PRINTErr("蒸馏水", Err);
			break;
		}
		case Type4:
		{
			PRINTErr("低量程预装试剂", Err);
			break;
		}
		case Type5:
		{
			PRINTErr("高量程预装试剂", Err);
			break;
		}
		case Type6:
		{
			PRINTErr("硝酸银试剂", Err);
			break;
		}
		case Type7:
		{
			PRINTErr("铬酸钾试剂", Err);
			break;
		}
		default:
			break;
		}
		PumpFluidOut(Type1, - Full);*/
	}
	return Err;
}

//	试管清洗
//Err = TubeClean(, );
//PRINTErr("试管清洗", Err);

//	打开分光光度计
//Err = ProcessDeal(, );
//PRINTErr("打开LED", Err);

//Err = WaterSampleAttenuation(, );

//Err = Preparation(, , , );
//PRINTErr("低浓度预装试剂分配", Err);


//************************************
// Method:    比色流程操作
// FullName:  ConcentrationMeasure
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * List
// Parameter: uint8_t Size
// Parameter: uint8_t LEDChannel
//************************************
ProcessErr	ConcentrationMeasure(uint8_t * List, uint8_t Size, uint8_t LEDChannel)
{
	ProcessErr
		Err = ProNOErr;
	Err = Colorimetric(1u);
	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = PumpCleanOut();
		PRINTErr("注射泵清洗", Err);
		Err = PumpCleanOut();
		PRINTErr("注射泵清洗", Err);
		Err = TakeOutFromTube(List[i], 2000);
		PRINTErr("试管中取液", Err);
		Err = PumpRinse(Type2);
		PRINTErr("注射泵润洗", Err);
		Err = ColorimetricFlood(List[i], 6000);
		PRINTErr("比色试样采集", Err);
		Err = Colorimetric(LEDChannel);
		PRINTErr("试样比色", Err);
		RTStatus.TubeReagent[List[i]].ConcentrationValue = RTStatus.Concentration[1u];
		g_pBaseInterface->ptrFuncLogger("%d号浓度值为%d\r\n", List[i], RTStatus.Concentration[0u]);
		Err = ColorimetricOutClean();
		PRINTErr("比色试样抽空清洗", Err);

	}
	Err = Colorimetric(0u);
	return Err;
}

//************************************
// Method:    测氯流程操作
// FullName:  ChlorineMeasuring
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t SampleNum
// Parameter: uint8_t * List
// Parameter: uint8_t Size
//************************************
ProcessErr	ChlorineMeasuring(uint8_t *	List, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;
	Err = PumpEvacuation();
	//Err = PumpCleanOut();
	//PRINTErr("注射泵清洗", Err);
	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = PumpCleanOut();
		PRINTErr("注射泵清洗", Err);

		Err = PumpRinseType2(RTStatus.TubeReagent[List[i]].SampleFrom);
		PRINTErr("注射泵润洗", Err);

		Err = WaterSampleIn(&List[i], 1, RTStatus.TubeReagent[List[i]].SampleFrom, DosageType2 * 4);
		PRINTErr("水样采集", Err);
	}

	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpRinse(Type6);
	PRINTErr("注射泵润洗", Err);

	Err = Preparation(List, Size, Type6, DosageType6 * 4);
	PRINTErr("硝酸银溶液注入", Err);

	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpRinse(Type7);
	PRINTErr("注射泵润洗", Err);

	Err = Preparation(List, Size, Type7, DosageType7 * 4);
	PRINTErr("铬酸钾溶液注入", Err);

	Err = TubeMix(List, Size);
	PRINTErr("溶液混合", Err);
	
	Err = ConcentrationMeasure(List, Size, 1);
	g_pBaseInterface->ptrFuncLogger("\r\n测氯过程正常\r\n");
	return Err;

}

//************************************
// Method:    高低浓度流程操作
// FullName:  ConcentrationEstimate
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t SampleNum
// Parameter: uint8_t * List
// Parameter: uint8_t Size
//************************************
ProcessErr	ConcentrationEstimate(uint8_t * List, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;
	//g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度\r\n");
	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpRinse(Type4);
	PRINTErr("注射泵润洗", Err);
	Err = Preparation(List, Size, Type4, 666);
	PRINTErr("低浓度预装试剂分配", Err);
	PRINTErr("注射泵清洗", Err);
	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpRinse(Type4);
	PRINTErr("注射泵润洗", Err);
	Err = Preparation(List, Size, Type6, 333);
	PRINTErr("低浓度预装试剂分配", Err);
	PRINTErr("注射泵清洗", Err);
	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	Err = PumpRinse(Type4);
	PRINTErr("注射泵润洗", Err);
	Err = Preparation(List, Size, Type7, 4000);
	PRINTErr("低浓度预装试剂分配", Err);

	Err = PumpCleanOut();
	PRINTErr("注射泵清洗", Err);
	uint8_t	i = 0u;
	do
	{
		uint8_t	FromNum = RTStatus.TubeReagent[List[i]].SampleFrom;
		uint8_t	ListTemp[50u] = { 0u };
		uint8_t k = 0u;
		Err = PumpCleanOut();
		PRINTErr("注射泵清洗", Err);
		Err = PumpRinseType2(RTStatus.TubeReagent[List[i]].SampleFrom);
		PRINTErr("注射泵润洗", Err);
		do
		{
			ListTemp[k] = List[i+k];
			k++;
		} while ((RTStatus.TubeReagent[List[i + k]].SampleFrom == FromNum) && ((i + k) < Size));
		i += k;

		Err = WaterSampleIn(ListTemp, k, FromNum, DosageType2);
		PRINTErr("水样采集", Err);
	} while (i < Size); 

	Err = TubeMix(List, Size);
	PRINTErr("溶液混合", Err);

	Err = ConcentrationMeasure(List, Size, 1);
	return Err;
}

enum	enumCTRLCMD
{
	CMD_Pumpclean = 0,		//	清洗注射泵	No Parameter
	CMD_Chloridion,			//	测氯			uint8_t SampleNum, uint8_t * List, uint8_t Size,
	CMD_Attenuation,		//	稀释			uint8_t SampleNum, uint8_t AttenuationNumbler
	CMD_CompoundHigh,		//	配制高浓度样品	uint8_t * List, uint8_t Size,
	CMD_CompoundLow,		//	配制低浓度样品	uint8_t * List, uint8_t Size,
	CMD_Dissolution5,		//	加热消解5分钟	
	CMD_Dissolution15,		//	加热消解15分钟
	CMD_Colorimetric,		//	分光比色		uint8_t * List, uint8_t Size, uint8_t LEDChannel
	CMD_TubeClean,			//	试管清洗		uint8_t * List, uint8_t Size,
	CMD_LEDCTRL,			//	控制分光光度计	uint8_t LEDChannel
};
static	enum enumCTRLCMD CMD;
static	bool	Flag = false;

static	uint8_t SampleNum;
static	uint8_t * List;
static	uint8_t Size;
static	uint8_t AttenuationNumbler;
static	uint8_t LEDChannel;


//************************************
// Method:    接口函数
// FullName:  CMD_PumpcleanResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	CMD_PumpcleanResponse(void)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Pumpclean;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_ChloridionResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t uSampleNum
// Parameter: uint8_t * uList
// Parameter: uint8_t uSize
//************************************
ProcessErr	CMD_ChloridionResponse(uint8_t uSampleNum, uint8_t * uList, uint8_t uSize)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_AttenuationResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t uSampleNum
// Parameter: uint8_t uAttenuationNumbler
//************************************
ProcessErr	CMD_AttenuationResponse(uint8_t uSampleNum, uint8_t uAttenuationNumbler)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_CompoundHighResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * uList
// Parameter: uint8_t uSize
//************************************
ProcessErr	CMD_CompoundHighResponse(uint8_t * uList, uint8_t uSize)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_CompoundLowResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * uList
// Parameter: uint8_t uSize
//************************************
ProcessErr	CMD_CompoundLowResponse(uint8_t * uList, uint8_t uSize)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_Dissolution15Response
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	CMD_Dissolution15Response(void)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_ColorimetricResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * uList
// Parameter: uint8_t uSize
// Parameter: uint8_t uLEDChannel
//************************************
ProcessErr	CMD_ColorimetricResponse(uint8_t * uList, uint8_t uSize, uint8_t uLEDChannel)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_TubeCleanResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t * uList
// Parameter: uint8_t uSize
//************************************
ProcessErr	CMD_TubeCleanResponse(uint8_t * uList, uint8_t uSize)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}
//************************************
// Method:    接口函数
// FullName:  CMD_LEDCTRLResponse
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: uint8_t uLEDChannel
//************************************
ProcessErr	CMD_LEDCTRLResponse(uint8_t uLEDChannel)
{
	ProcessErr
		Err = ProNOErr;
	if (!Flag)
	{
		CMD = CMD_Chloridion;
		Flag = true;
	}
	else
	{
		Err = ProBusy;
	}
	return Err;
}


//************************************
// Method:    获取命令循环执行函数
// FullName:  Prowhile
// Access:    public 
// Returns:   ProcessErr
// Qualifier:
// Parameter: void
//************************************
ProcessErr	Prowhile(void)
{
	ProcessErr
		Err = ProNOErr;
	if (Flag)
	{
		switch (CMD)
		{
		case CMD_Pumpclean:
			Err = PumpCleanOut();
			PRINTErr("注射泵清洗", Err);
			break;
		case CMD_Chloridion:
			//Err = ChlorineMeasuring(SampleNum, List, Size);
			break;
		case CMD_Attenuation:
			Err = WaterSampleAttenuation(SampleNum, AttenuationNumbler);
			PRINTErr("水样稀释", Err);
			break;
		case CMD_CompoundHigh:
			Err = Preparation(List, Size, Type5, 5000);
			PRINTErr("高浓度预装试剂分配", Err);
			break;
		case CMD_CompoundLow:
			Err = Preparation(List, Size, Type4, 5000);
			PRINTErr("低浓度预装试剂分配", Err);
			break;
		case CMD_Dissolution5:
			//break;
		case CMD_Dissolution15:
			break;
		case CMD_LEDCTRL:
			Err = ProcessDeal(CMDLED, LEDChannel);
			PRINTErr("LED控制", Err);
			break;
		case CMD_Colorimetric:
			Err = ConcentrationMeasure(List, Size, LEDChannel);
			break;
		case CMD_TubeClean:
			Err = TubeClean(List, Size);
			PRINTErr("试管清洗", Err);
			break;
		default:
			break;
		}
		Flag = false;
	}
	osDelay(50u);
	return	Err;
}

//************************************
// Method:    非接口状态下流程测试函数
// FullName:  Processx
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void	ProcessAUTO(void)
{
	ProcessErr
		Err = ProNOErr;
	//Err = ChlorineMeasuring(SampleNum, List, Size);
	//Err = WaterSampleAttenuation(SampleNum, AttenuationNumbler);
	//Err = Preparation(List, Size, Type5, 5000);
	//Err = Preparation(List, Size, Type4, 5000);
	//Err = ProcessDeal(CMDLED, LEDChannel);
	//Err = ConcentrationMeasure(List, Size, LEDChannel);
	//Err = ProcessDeal(CMDLED, LEDChannel);
	//Err = TubeClean(List, Size);

	
	//Err = ChlorineMeasuring(ChlorineMeasuringSampleNum, ListChlorineMeasuring, 1);
	//Err = Preparation(ListPreparation, Size, Type5, 3);
	//
	//Err = ProcessDeal(CMDLED, 1);

	//Err = ConcentrationMeasure(ListConcentrationMeasure, 3, LEDChannel);
	//Err = TubeClean(ListTubeClean, 7);
	//Err = ProcessDeal(CMDLED, 0);

	//uint8_t	SampleNum = 4u;
	//uint8_t	List0[1u] = { 28 };
	//uint8_t	List1[6u] = { 25, 26, 27, 29, 30, 31 };
	//uint8_t	List2[3u] = { 29, 30, 31 };
	//uint8_t	List3[3u] = { 34, 35, 36 };
	//Err = Prowhile();
	RTStatus_Init();
	Err = RbootArmChange(0u);
	Err = PumpEvacuation();
//	PRINTErr("注射泵排空", Err);
//	PRINTErr("注射泵排空", Err);
//	PRINTErr("注射泵排空", Err);
//
//	PRINTErr("测氯开始", Err);
//	PRINTErr("测氯开始", Err);
//	PRINTErr("测氯开始", Err);
//	osDelay(2000);
//	Err = ProcessDeal(CMDLED, 1u);
//	PRINTErr("打开LED", Err);
//	PRINTErr("打开LED", Err);
//	PRINTErr("打开LED", Err);
//
//	//Err = PumpCleanOut();
//	//PRINTErr("注射泵清洗", Err);
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//
//	Err = PumpRinseType2(SampleNum);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//
//	Err = WaterSampleIn(List0, 1u, SampleNum, DosageType2 * 4);
//	PRINTErr("水样采集", Err);
//	PRINTErr("水样采集", Err);
//	PRINTErr("水样采集", Err);
//
//	//Err = PumpCleanOut();
//	//PRINTErr("注射泵清洗", Err);
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	Err = PumpRinse(Type6);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//
//	Err = Preparation(List0, 1u, Type6, DosageType6 * 4);
//	PRINTErr("硫酸银溶液注入", Err);
//	PRINTErr("硫酸银溶液注入", Err);
//	PRINTErr("硫酸银溶液注入", Err);
//
//	//Err = PumpCleanOut();
//	//PRINTErr("注射泵清洗", Err);
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	Err = PumpRinse(Type7);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//
//	Err = Preparation(List0, 1u, Type7, DosageType7 * 4);
//	PRINTErr("铬酸钾溶液注入", Err);
//	PRINTErr("铬酸钾溶液注入", Err);
//	PRINTErr("铬酸钾溶液注入", Err);
//
//	Err = TubeMix(List0, 1u);
//	PRINTErr("溶液混合", Err);
//	PRINTErr("溶液混合", Err);
//	PRINTErr("溶液混合", Err);
//	//Err = RbootArmChange(0u);
//	for (uint8_t i = 0u; i < 1u; i++)
//	{
//		//Err = PumpCleanOut();
//		//PRINTErr("注射泵清洗", Err);
//		Err = PumpCleanOut();
//		PRINTErr("注射泵清洗", Err);
//		PRINTErr("注射泵清洗", Err);
//		PRINTErr("注射泵清洗", Err);
//		Err = PumpRinseType2(List0[i]);
//		PRINTErr("注射泵润洗", Err);
//		PRINTErr("注射泵润洗", Err);
//		PRINTErr("注射泵润洗", Err);
//
//		Err = ColorimetricFlood(List0[i], 2500u * 3);
//		PRINTErr("比色试样采集", Err);
//		PRINTErr("比色试样采集", Err);
//		PRINTErr("比色试样采集", Err);
//		Err = Colorimetric(1);
//		PRINTErr("试样比色", Err);
//		PRINTErr("试样比色", Err);
//		PRINTErr("试样比色", Err);
//		g_pBaseInterface->ptrFuncLogger("浓度值为%d\r\n", RTStatus.Concentration[0u]);
//		Err = ColorimetricOutClean();
//		PRINTErr("比色试样抽空清洗", Err);
//		PRINTErr("比色试样抽空清洗", Err);
//		PRINTErr("比色试样抽空清洗", Err);
//	}
//	g_pBaseInterface->ptrFuncLogger("\r\n测氯过程正常\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n测氯过程正常\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n测氯过程正常\r\n");
//
//	Err = TubeClean(List0, 1u);
//	PRINTErr("试管清洗", Err);
//	PRINTErr("试管清洗", Err);
//	PRINTErr("试管清洗", Err);
////Err = EffluentOut(List3[0]);
////Err = EffluentOut(List3[1]);
////Err = EffluentOut(List3[2]);
//
//	g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度\r\n");
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	Err = PumpRinse(Type4);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//
//	Err = Preparation(List2, 3u, Type4, 5000);
//	PRINTErr("低浓度预装试剂分配", Err);
//	PRINTErr("低浓度预装试剂分配", Err);
//	PRINTErr("低浓度预装试剂分配", Err);
//
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	Err = PumpCleanOut();
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	PRINTErr("注射泵清洗", Err);
//	Err = PumpRinseType2(SampleNum);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//	PRINTErr("注射泵润洗", Err);
//
//	Err = WaterSampleIn(List2, 3u, 4u, DosageType2);
//	PRINTErr("水样采集", Err);
//	PRINTErr("水样采集", Err);
//	PRINTErr("水样采集", Err);
//	Err = TubeMix(List2, 3u);
//	PRINTErr("溶液混合", Err);
//	PRINTErr("溶液混合", Err);
//	PRINTErr("溶液混合", Err);
//
//	for (uint8_t i = 0u; i < 3u; i++)
//	{
//		Err = PumpCleanOut();
//		PRINTErr("注射泵清洗", Err);
//		Err = PumpCleanOut();
//		PRINTErr("注射泵清洗", Err);
//		PRINTErr("注射泵清洗", Err);
//		PRINTErr("注射泵清洗", Err);
//		Err = PumpRinseType2(List2[i]);
//		PRINTErr("注射泵润洗", Err);
//		PRINTErr("注射泵润洗", Err);
//		PRINTErr("注射泵润洗", Err);
//		Err = ColorimetricFlood(List2[i], 2500u * 2);
//		PRINTErr("比色试样采集", Err);
//		PRINTErr("比色试样采集", Err);
//		PRINTErr("比色试样采集", Err);
//		Err = Colorimetric(1);
//		PRINTErr("试样比色", Err);
//		PRINTErr("试样比色", Err);
//		PRINTErr("试样比色", Err);
//		g_pBaseInterface->ptrFuncLogger("浓度值为%d\r\n", RTStatus.Concentration[0u]);
//		g_pBaseInterface->ptrFuncLogger("浓度值为%d\r\n", RTStatus.Concentration[0u]);
//		g_pBaseInterface->ptrFuncLogger("浓度值为%d\r\n", RTStatus.Concentration[0u]);
//		Err = ColorimetricOutClean();
//		PRINTErr("比色试样抽空清洗", Err);
//		PRINTErr("比色试样抽空清洗", Err);
//		PRINTErr("比色试样抽空清洗", Err);
//	}
//	g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度结束\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度结束\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n分辨高低浓度结束\r\n");
//	Err = TubeClean(List2, 3u);
//	PRINTErr("试管清洗", Err);
//	PRINTErr("试管清洗", Err);
//	PRINTErr("试管清洗", Err);
//
//	g_pBaseInterface->ptrFuncLogger("\r\n水样稀释\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n水样稀释\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n水样稀释\r\n");
//
//	Err = WaterSampleAttenuation(SampleNum, List3[0u]);
//	PRINTErr("水样稀释1", Err);
//	PRINTErr("水样稀释1", Err);
//	PRINTErr("水样稀释1", Err);
//	Err = WaterSampleAttenuation(SampleNum, List3[1u]);
//	PRINTErr("水样稀释2", Err);
//	PRINTErr("水样稀释2", Err);
//	PRINTErr("水样稀释2", Err);
//	Err = WaterSampleAttenuation(SampleNum, List3[2u]);
//	PRINTErr("水样稀释3", Err);
//	PRINTErr("水样稀释3", Err);
//	PRINTErr("水样稀释3", Err);
//
//	Err = TubeClean(List3, 3u);
//	PRINTErr("试管清洗", Err);
//	PRINTErr("试管清洗", Err);
//	PRINTErr("试管清洗", Err);
//
//	Err = RbootArmChange(0u);
//	PRINTErr("机械臂归位", Err);
//	PRINTErr("机械臂归位", Err);

}

/** (C) COPYRIGHT 2018 青岛中特环保仪器有限公司 **/

