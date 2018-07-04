/*!
 ** (C) COPYRIGHT 2018 �ൺ���ػ����������޹�˾ **
 * \file CMD.c
 *
 * \author kaiser
 * \date 2018/06/12
 *
 * 
 */
#include "DEBUG.H"

//************************************
// Method:    ע�������Һ����
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
// Method:    ƽ��ע�����ѹ
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
// Method:    �ſչ�����
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
// Method:    �ſ�ע���
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
// Method:    ��ϴע���
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
// Method:    ��ϴע���
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
// Method:    �ⲿ��Һ��ϴע���
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
// Method:    עҺ���Թ�
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
// Method:    ���Թ�ȡҺ
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
// Method:    ��������
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
// Method:    �Թ����
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
// Method:    ת�ƴ���ɫҺ��
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
// Method:    ��ɫ�����
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
// Method:    ��ɫ
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
// Method:    ���ݽ�����
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
// Method:    �����Թ���ϴ
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
// Method:    ��ȡԤװ�Լ����Թ�
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
// Method:    �ɼ�ˮ�����Թ�
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
// Method:    ˮ��ϡ��
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
// Method:    ��е���ƶ�
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
// Method:    ʵʱ״̬��ʼ��
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
			PRINTErr("����ˮ", Err);
			break;
		}
		case Type4:
		{
			PRINTErr("������Ԥװ�Լ�", Err);
			break;
		}
		case Type5:
		{
			PRINTErr("������Ԥװ�Լ�", Err);
			break;
		}
		case Type6:
		{
			PRINTErr("�������Լ�", Err);
			break;
		}
		case Type7:
		{
			PRINTErr("������Լ�", Err);
			break;
		}
		default:
			break;
		}
		PumpFluidOut(Type1, - Full);*/
	}
	return Err;
}

//	�Թ���ϴ
//Err = TubeClean(, );
//PRINTErr("�Թ���ϴ", Err);

//	�򿪷ֹ��ȼ�
//Err = ProcessDeal(, );
//PRINTErr("��LED", Err);

//Err = WaterSampleAttenuation(, );

//Err = Preparation(, , , );
//PRINTErr("��Ũ��Ԥװ�Լ�����", Err);


//************************************
// Method:    ��ɫ���̲���
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
		PRINTErr("ע�����ϴ", Err);
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = TakeOutFromTube(List[i], 2000);
		PRINTErr("�Թ���ȡҺ", Err);
		Err = PumpRinse(Type2);
		PRINTErr("ע�����ϴ", Err);
		Err = ColorimetricFlood(List[i], 6000);
		PRINTErr("��ɫ�����ɼ�", Err);
		Err = Colorimetric(LEDChannel);
		PRINTErr("������ɫ", Err);
		RTStatus.TubeReagent[List[i]].ConcentrationValue = RTStatus.Concentration[1u];
		g_pBaseInterface->ptrFuncLogger("%d��Ũ��ֵΪ%d\r\n", List[i], RTStatus.Concentration[0u]);
		Err = ColorimetricOutClean();
		PRINTErr("��ɫ���������ϴ", Err);

	}
	Err = Colorimetric(0u);
	return Err;
}

//************************************
// Method:    �������̲���
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
	//PRINTErr("ע�����ϴ", Err);
	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);

		Err = PumpRinseType2(RTStatus.TubeReagent[List[i]].SampleFrom);
		PRINTErr("ע�����ϴ", Err);

		Err = WaterSampleIn(&List[i], 1, RTStatus.TubeReagent[List[i]].SampleFrom, DosageType2 * 4);
		PRINTErr("ˮ���ɼ�", Err);
	}

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type6);
	PRINTErr("ע�����ϴ", Err);

	Err = Preparation(List, Size, Type6, DosageType6 * 4);
	PRINTErr("��������Һע��", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type7);
	PRINTErr("ע�����ϴ", Err);

	Err = Preparation(List, Size, Type7, DosageType7 * 4);
	PRINTErr("�������Һע��", Err);

	Err = TubeMix(List, Size);
	PRINTErr("��Һ���", Err);
	
	Err = ConcentrationMeasure(List, Size, 1);
	g_pBaseInterface->ptrFuncLogger("\r\n���ȹ�������\r\n");
	return Err;

}

//************************************
// Method:    �ߵ�Ũ�����̲���
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
	//g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ��\r\n");
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type4);
	PRINTErr("ע�����ϴ", Err);
	Err = Preparation(List, Size, Type4, 666);
	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type4);
	PRINTErr("ע�����ϴ", Err);
	Err = Preparation(List, Size, Type6, 333);
	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type4);
	PRINTErr("ע�����ϴ", Err);
	Err = Preparation(List, Size, Type7, 4000);
	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	uint8_t	i = 0u;
	do
	{
		uint8_t	FromNum = RTStatus.TubeReagent[List[i]].SampleFrom;
		uint8_t	ListTemp[50u] = { 0u };
		uint8_t k = 0u;
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = PumpRinseType2(RTStatus.TubeReagent[List[i]].SampleFrom);
		PRINTErr("ע�����ϴ", Err);
		do
		{
			ListTemp[k] = List[i+k];
			k++;
		} while ((RTStatus.TubeReagent[List[i + k]].SampleFrom == FromNum) && ((i + k) < Size));
		i += k;

		Err = WaterSampleIn(ListTemp, k, FromNum, DosageType2);
		PRINTErr("ˮ���ɼ�", Err);
	} while (i < Size); 

	Err = TubeMix(List, Size);
	PRINTErr("��Һ���", Err);

	Err = ConcentrationMeasure(List, Size, 1);
	return Err;
}

enum	enumCTRLCMD
{
	CMD_Pumpclean = 0,		//	��ϴע���	No Parameter
	CMD_Chloridion,			//	����			uint8_t SampleNum, uint8_t * List, uint8_t Size,
	CMD_Attenuation,		//	ϡ��			uint8_t SampleNum, uint8_t AttenuationNumbler
	CMD_CompoundHigh,		//	���Ƹ�Ũ����Ʒ	uint8_t * List, uint8_t Size,
	CMD_CompoundLow,		//	���Ƶ�Ũ����Ʒ	uint8_t * List, uint8_t Size,
	CMD_Dissolution5,		//	��������5����	
	CMD_Dissolution15,		//	��������15����
	CMD_Colorimetric,		//	�ֹ��ɫ		uint8_t * List, uint8_t Size, uint8_t LEDChannel
	CMD_TubeClean,			//	�Թ���ϴ		uint8_t * List, uint8_t Size,
	CMD_LEDCTRL,			//	���Ʒֹ��ȼ�	uint8_t LEDChannel
};
static	enum enumCTRLCMD CMD;
static	bool	Flag = false;

static	uint8_t SampleNum;
static	uint8_t * List;
static	uint8_t Size;
static	uint8_t AttenuationNumbler;
static	uint8_t LEDChannel;


//************************************
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    �ӿں���
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
// Method:    ��ȡ����ѭ��ִ�к���
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
			PRINTErr("ע�����ϴ", Err);
			break;
		case CMD_Chloridion:
			//Err = ChlorineMeasuring(SampleNum, List, Size);
			break;
		case CMD_Attenuation:
			Err = WaterSampleAttenuation(SampleNum, AttenuationNumbler);
			PRINTErr("ˮ��ϡ��", Err);
			break;
		case CMD_CompoundHigh:
			Err = Preparation(List, Size, Type5, 5000);
			PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
			break;
		case CMD_CompoundLow:
			Err = Preparation(List, Size, Type4, 5000);
			PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
			break;
		case CMD_Dissolution5:
			//break;
		case CMD_Dissolution15:
			break;
		case CMD_LEDCTRL:
			Err = ProcessDeal(CMDLED, LEDChannel);
			PRINTErr("LED����", Err);
			break;
		case CMD_Colorimetric:
			Err = ConcentrationMeasure(List, Size, LEDChannel);
			break;
		case CMD_TubeClean:
			Err = TubeClean(List, Size);
			PRINTErr("�Թ���ϴ", Err);
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
// Method:    �ǽӿ�״̬�����̲��Ժ���
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
//	PRINTErr("ע����ſ�", Err);
//	PRINTErr("ע����ſ�", Err);
//	PRINTErr("ע����ſ�", Err);
//
//	PRINTErr("���ȿ�ʼ", Err);
//	PRINTErr("���ȿ�ʼ", Err);
//	PRINTErr("���ȿ�ʼ", Err);
//	osDelay(2000);
//	Err = ProcessDeal(CMDLED, 1u);
//	PRINTErr("��LED", Err);
//	PRINTErr("��LED", Err);
//	PRINTErr("��LED", Err);
//
//	//Err = PumpCleanOut();
//	//PRINTErr("ע�����ϴ", Err);
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//
//	Err = PumpRinseType2(SampleNum);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//
//	Err = WaterSampleIn(List0, 1u, SampleNum, DosageType2 * 4);
//	PRINTErr("ˮ���ɼ�", Err);
//	PRINTErr("ˮ���ɼ�", Err);
//	PRINTErr("ˮ���ɼ�", Err);
//
//	//Err = PumpCleanOut();
//	//PRINTErr("ע�����ϴ", Err);
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	Err = PumpRinse(Type6);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//
//	Err = Preparation(List0, 1u, Type6, DosageType6 * 4);
//	PRINTErr("��������Һע��", Err);
//	PRINTErr("��������Һע��", Err);
//	PRINTErr("��������Һע��", Err);
//
//	//Err = PumpCleanOut();
//	//PRINTErr("ע�����ϴ", Err);
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	Err = PumpRinse(Type7);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//
//	Err = Preparation(List0, 1u, Type7, DosageType7 * 4);
//	PRINTErr("�������Һע��", Err);
//	PRINTErr("�������Һע��", Err);
//	PRINTErr("�������Һע��", Err);
//
//	Err = TubeMix(List0, 1u);
//	PRINTErr("��Һ���", Err);
//	PRINTErr("��Һ���", Err);
//	PRINTErr("��Һ���", Err);
//	//Err = RbootArmChange(0u);
//	for (uint8_t i = 0u; i < 1u; i++)
//	{
//		//Err = PumpCleanOut();
//		//PRINTErr("ע�����ϴ", Err);
//		Err = PumpCleanOut();
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		Err = PumpRinseType2(List0[i]);
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//
//		Err = ColorimetricFlood(List0[i], 2500u * 3);
//		PRINTErr("��ɫ�����ɼ�", Err);
//		PRINTErr("��ɫ�����ɼ�", Err);
//		PRINTErr("��ɫ�����ɼ�", Err);
//		Err = Colorimetric(1);
//		PRINTErr("������ɫ", Err);
//		PRINTErr("������ɫ", Err);
//		PRINTErr("������ɫ", Err);
//		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
//		Err = ColorimetricOutClean();
//		PRINTErr("��ɫ���������ϴ", Err);
//		PRINTErr("��ɫ���������ϴ", Err);
//		PRINTErr("��ɫ���������ϴ", Err);
//	}
//	g_pBaseInterface->ptrFuncLogger("\r\n���ȹ�������\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n���ȹ�������\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n���ȹ�������\r\n");
//
//	Err = TubeClean(List0, 1u);
//	PRINTErr("�Թ���ϴ", Err);
//	PRINTErr("�Թ���ϴ", Err);
//	PRINTErr("�Թ���ϴ", Err);
////Err = EffluentOut(List3[0]);
////Err = EffluentOut(List3[1]);
////Err = EffluentOut(List3[2]);
//
//	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ��\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ��\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ��\r\n");
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	Err = PumpRinse(Type4);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//
//	Err = Preparation(List2, 3u, Type4, 5000);
//	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
//	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
//	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);
//
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	Err = PumpCleanOut();
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	Err = PumpRinseType2(SampleNum);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//	PRINTErr("ע�����ϴ", Err);
//
//	Err = WaterSampleIn(List2, 3u, 4u, DosageType2);
//	PRINTErr("ˮ���ɼ�", Err);
//	PRINTErr("ˮ���ɼ�", Err);
//	PRINTErr("ˮ���ɼ�", Err);
//	Err = TubeMix(List2, 3u);
//	PRINTErr("��Һ���", Err);
//	PRINTErr("��Һ���", Err);
//	PRINTErr("��Һ���", Err);
//
//	for (uint8_t i = 0u; i < 3u; i++)
//	{
//		Err = PumpCleanOut();
//		PRINTErr("ע�����ϴ", Err);
//		Err = PumpCleanOut();
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		Err = PumpRinseType2(List2[i]);
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		PRINTErr("ע�����ϴ", Err);
//		Err = ColorimetricFlood(List2[i], 2500u * 2);
//		PRINTErr("��ɫ�����ɼ�", Err);
//		PRINTErr("��ɫ�����ɼ�", Err);
//		PRINTErr("��ɫ�����ɼ�", Err);
//		Err = Colorimetric(1);
//		PRINTErr("������ɫ", Err);
//		PRINTErr("������ɫ", Err);
//		PRINTErr("������ɫ", Err);
//		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
//		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
//		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
//		Err = ColorimetricOutClean();
//		PRINTErr("��ɫ���������ϴ", Err);
//		PRINTErr("��ɫ���������ϴ", Err);
//		PRINTErr("��ɫ���������ϴ", Err);
//	}
//	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ�Ƚ���\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ�Ƚ���\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ�Ƚ���\r\n");
//	Err = TubeClean(List2, 3u);
//	PRINTErr("�Թ���ϴ", Err);
//	PRINTErr("�Թ���ϴ", Err);
//	PRINTErr("�Թ���ϴ", Err);
//
//	g_pBaseInterface->ptrFuncLogger("\r\nˮ��ϡ��\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\nˮ��ϡ��\r\n");
//	g_pBaseInterface->ptrFuncLogger("\r\nˮ��ϡ��\r\n");
//
//	Err = WaterSampleAttenuation(SampleNum, List3[0u]);
//	PRINTErr("ˮ��ϡ��1", Err);
//	PRINTErr("ˮ��ϡ��1", Err);
//	PRINTErr("ˮ��ϡ��1", Err);
//	Err = WaterSampleAttenuation(SampleNum, List3[1u]);
//	PRINTErr("ˮ��ϡ��2", Err);
//	PRINTErr("ˮ��ϡ��2", Err);
//	PRINTErr("ˮ��ϡ��2", Err);
//	Err = WaterSampleAttenuation(SampleNum, List3[2u]);
//	PRINTErr("ˮ��ϡ��3", Err);
//	PRINTErr("ˮ��ϡ��3", Err);
//	PRINTErr("ˮ��ϡ��3", Err);
//
//	Err = TubeClean(List3, 3u);
//	PRINTErr("�Թ���ϴ", Err);
//	PRINTErr("�Թ���ϴ", Err);
//	PRINTErr("�Թ���ϴ", Err);
//
//	Err = RbootArmChange(0u);
//	PRINTErr("��е�۹�λ", Err);
//	PRINTErr("��е�۹�λ", Err);

}

/** (C) COPYRIGHT 2018 �ൺ���ػ����������޹�˾ **/

