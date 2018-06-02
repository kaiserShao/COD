
#include "DEBUG.H"

ProcessErr	PumpFluidIn(enum	enumType	TypeSet, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDValve, Type3 },
		{ CMDPump, 0 },
		{ CMDDLY, 2500 },
		{ CMDValve, Type1 },
		{ CMDPump, -1500 },
		{ CMDMotor, M_Type1 },
	};
	CMDs[0u].Control = TypeSet;
	RTStatus.PumpPosition = HoldingSingelRead2(MBName[ArmBase+11u]);
	CMDs[1u].Control = Dosage;
	switch (TypeSet)
	{
	case Type1:
	case Type4:
	case Type5:
	{
		CMDs[2u].Control = Dosage / 10 + 600u;
		break;
	}
	case Type2:
	{
		CMDs[2u].Control = Dosage / 20 + 600u;
		break;
	}
	case Type3:
	{
		CMDs[2u].Control = Dosage / 5 + 600u;
		break;
	}
	case Type6:
	case Type7:
	{
		CMDs[2u].Control = Dosage / 4 + 1500u;
		break;
	}
	default:
		CMDs[2u].Control = 500u;
		break;
	}
		
		
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}
ProcessErr	PumpFluidOut(enum	enumType	TypeSet, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDValve, Type3 },
		{ CMDPump, 0 },
		{ CMDMotor, M_Type1 },
	};
	CMDs[0u].Control = TypeSet;
	RTStatus.PumpPosition = HoldingSingelRead2(MBName[ArmBase+11u]);
	CMDs[1u].Control = Dosage;
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}

ProcessErr	PumpEvacuation(void)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDValve, Type1 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type1 },
	};
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}
ProcessErr	PumpCleanOut(void)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDValve, Type3 },
		{ CMDPump, 3000 },
		{ CMDDLY, 1000 },
		{ CMDValve, Type10 },
		{ CMDPump, 17000 },
		{ CMDDLY, 1000 },
		{ CMDValve, Type1 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type1 },
	};
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}

ProcessErr	PumpRinse(enum	enumType	TypeSet)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDValve, Type3 },
		{ CMDPump, 2000 },
		{ CMDDLY, 1000 },
		{ CMDValve, Type10 },
		{ CMDPump, 18000 },
		{ CMDDLY, 1000 },
		{ CMDValve, Type1 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type1 },
	};
	CMDs[0u].Control = TypeSet;
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}

ProcessErr	TubeFluidIn(uint16_t	Numbler, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDXYZ, 0 },
		{ CMDValve, Type2 },
		{ CMDPump, 0 },
		{ CMDMotor, M_Type1 },
		{ CMDMotor, M_Type1 },
	};
	CMDs[0u].Control = Numbler * 2u;
	CMDs[2u].Control = Dosage;

	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}
ProcessErr	TubeFluidOut(uint16_t	SampleNum, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDXYZ, 0 },
		{ CMDValve, Type2 },
		{ CMDPump, 0 },
		{ CMDXYZ, 0 },
		{ CMDPump, 3000 },
		{ CMDValve, Type1 },
		{ CMDPump, -3000 },
		{ CMDMotor, M_Type1 },
		{ CMDValve, Type2 },
		{ CMDPump, 3000 },
		{ CMDValve, Type1 },
		{ CMDPump, -4000 },
		{ CMDMotor, M_Type1 },
		{ CMDValve, Type10 },
		{ CMDMotor, M_Type1 },
		{ CMDValve, Type2 },
	};
	CMDs[0u].Control = SampleNum * 2u - 1u;
	CMDs[2u].Control = Dosage;
	CMDs[3u].Control = SampleNum * 2u;

	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}

ProcessErr	AIR_Stir(uint16_t	Numbler)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDXYZ, 0 },
		{ CMDValve, Type2 },
		{ CMDMotor, M_Type10 },
	};
	if (Numbler)
		CMDs[0u].Control = Numbler * 2u - 1u;
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;

}
ProcessErr	RbootArmChange(uint16_t	NumblerTrue)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDXYZ, 0 },
	};

	CMDs[0u].Control = NumblerTrue;

	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;

}
ProcessErr	EffluentOut(uint16_t	Numbler)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDXYZ, 0 },
		{ CMDValve, Type2 },
		{ CMDMotor, M_Type1 },
		{ CMDEFF, 30000 },
	};
	if (Numbler)
		CMDs[0u].Control = Numbler * 2u - 1u;
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}

ProcessErr	ColorimetricFlood(uint16_t	Numbler, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{

		{ CMDXYZ, 0 },
		{ CMDValve, Type2 },
		{ CMDPump, 0 },
		{ CMDXYZ, 0 },
		{ CMDPump, 10000 },
		{ CMDValve, Type9 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type10 },
		{ CMDMotor, M_Type10 },

	};
	CMDs[0u].Control = Numbler * 2u - 1u;
	CMDs[2u].Control = Dosage;
	CMDs[3u].Control = Numbler * 2u;

	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}
ProcessErr	ColorimetricOut(void)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{

		{ CMDValve, Type9 },
		{ CMDPump, 20000 },
		{ CMDValve, Type1 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type1 },
	};

	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}
ProcessErr	ColorimetricClean(void)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDValve, Type3 },
		{ CMDPump, 7000 },
		{ CMDValve, Type9 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type10 },
		{ CMDMotor, M_Type10 },
		{ CMDPump, 20000 },
		{ CMDValve, Type1 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type1 },
	};

	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;
}

ProcessErr	Colorimetric(uint16_t	Channel)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		{ CMDLED, 0u },
		{ CMDDLY, 10000u },
		{ CMDCOV, 0u },
	};
	CMDs[0u].Control = Channel;
	CMDs[2u].Control = Channel;
	if (Channel == 0u)
		CMDs[1u].Control = 500u;
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));


	return	Err;

}





ProcessErr	Debug(void)
{
	ProcessErr
		Err = ProNOErr;
	static	struct	uCMDs	CMDs[] =
	{
		//			{ CMDValve, Type1		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type2		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type3		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		{ CMDValve, Type2 },
		{ CMDPump, -Full },
		{ CMDMotor, M_Type10 },
		//			{ CMDValve, Type5		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type6		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type7		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type8		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type9		},											
		//			{ CMDMotor,	M_Type10	},											
		//			{ CMDMotor,	M_Type10	},																			
		//			{ CMDValve, Type10		},											
		//			{ CMDMotor,	M_Type10	},											
	};
	Err = ProcessDeal(CMDs, sizeof(CMDs) / sizeof(CMDs[0u]));
	return	Err;

}






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
ProcessErr	TubeClean(uint8_t	* TubeList, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;
	if (RTStatus.PumpPosition > PumpZero)
	{
		Err = PumpFluidOut(Type1, -Full);
		if (Err != ProNOErr)
			return	Err;
	}
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
				Err = PumpFluidIn(Type3, 20000);
			else
				Err = PumpFluidIn(Type3, (Size - i) * Clean - (int16_t)(RTStatus.PumpPosition * 2.0096f + 2000));
			if (Err != ProNOErr)
				return	Err;
		}

		Err = TubeFluidIn(TubeList[i], -Clean);
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
	return	Err;

}
ProcessErr	Preparation(uint8_t	* TubeList, uint8_t Size, enum enumType TypeSet, int16_t	Dosage)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.PumpPosition)
	{
		Err = PumpFluidOut(Type1, -Full);
		if (Err != ProNOErr)
			return	Err;
	}

	for (uint8_t i = 0u; i < Size; i++)
	{
		if (RTStatus.PumpPosition < (Dosage + 1.0f) / 2.0096f)
		{
			if ((Size - i) * Dosage > 20000u)
				Err = PumpFluidIn(TypeSet, 20000);
			else
				Err = PumpFluidIn(TypeSet, (Size - i) * Dosage - (int16_t)(RTStatus.PumpPosition * 2.0096f + 2000));
			if (Err != ProNOErr)
				return	Err;
		}
		Err = TubeFluidIn(TubeList[i], -Dosage);
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
			RTStatus.TubeReagent[TubeList[i]].LowLevel += Dosage;
			break;
		}
		case Type5:
		{
			RTStatus.TubeReagent[TubeList[i]].HighLevel += Dosage;
			break;
		}
		case Type6:
		{
			RTStatus.TubeReagent[TubeList[i]].AgNo3 += Dosage;
			break;
		}
		case Type7:
		{
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
ProcessErr	WaterSampleIn(uint8_t	* TubeList, uint8_t Size, uint8_t SampleNum, int16_t Dosage)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.PumpPosition)
	{
		Err = PumpFluidOut(Type1, -Full);
		if (Err != ProNOErr)
			return	Err;
	}

	for (uint8_t i = 0u; i < Size; i++)
	{
		if (RTStatus.PumpPosition < (Dosage + 1.0f) / 2.0096f)
		{
			if ((Size - i) * Dosage > 20000)
			{
				Err = TubeFluidOut(SampleNum, 20000);
				RTStatus.TubeReagent[SampleNum].Sample -= 20000;
			}
			else
			{
				Err = TubeFluidOut(SampleNum, (Size - i) * Dosage - (int16_t)(RTStatus.PumpPosition * 2.0096f + 2000));
				RTStatus.TubeReagent[SampleNum].Sample -= ((Size - i) * Dosage - (int16_t)(RTStatus.PumpPosition * 2.0096f + 2000));
			}
			if (Err != ProNOErr)
				return	Err;
		}
		Err = TubeFluidIn(TubeList[i], -Dosage);
		if (Err != ProNOErr)
			return	Err;

		RTStatus.TubeReagent[i].Sample += Dosage;
	}
	Err = PumpEvacuation();
	if (Err != ProNOErr)
		return	Err;
	return	Err;

}

ProcessErr	WaterSampleAttenuation(uint8_t	WaterSampleNumbler, uint8_t AttenuationNumbler)
{
	ProcessErr
		Err = ProNOErr;

	if (RTStatus.PumpPosition)
	{
		Err = PumpFluidOut(Type1, -Full);
		if (Err != ProNOErr)
			return	Err;
	}




	Err = PumpFluidIn(Type3, Full - DosageType2 + 2000);
	if (Err != ProNOErr)
		return	Err;
	Err = TubeFluidIn(AttenuationNumbler, -18000);
	if (Err != ProNOErr)
		return	Err;
	Err = PumpEvacuation();
	RTStatus.TubeReagent[AttenuationNumbler].Water += 18000u;
	Err = PumpFluidIn(Type2, DosageType2 + 2000);
	if (Err != ProNOErr)
		return	Err;
	Err = TubeFluidIn(AttenuationNumbler, DosageType2);
	if (Err != ProNOErr)
		return	Err;
	RTStatus.TubeReagent[WaterSampleNumbler].Sample -= DosageType2;
	RTStatus.TubeReagent[AttenuationNumbler].Sample += DosageType2;
	Err = PumpEvacuation();
	if (Err != ProNOErr)
		return	Err;
	return	Err;

}













ProcessErr	RTStatus_Init(void)
{
	ProcessErr
		Err = ProNOErr;

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


ProcessErr	ChlorineMeasuring(uint8_t SampleNum, uint8_t * List, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;
	Err = PumpEvacuation();
	PRINTErr("ע����ſ�", Err);

	PRINTErr("���ȿ�ʼ", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = TubeFluidOut(SampleNum, 2000);
	PRINTErr("�Թ���ȡҺ", Err);
	Err = PumpRinse(Type2);
	PRINTErr("ע�����ϴ", Err);

	Err = WaterSampleIn(List, Size, SampleNum, DosageType2 * 1);
	PRINTErr("ˮ���ɼ�", Err);

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
	for (uint8_t i = 0u; i < Size; i++)
	{
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = TubeFluidOut(List[i], 2000);
		PRINTErr("�Թ���ȡҺ", Err);
		Err = PumpRinse(Type2);
		PRINTErr("ע�����ϴ", Err);

		Err = ColorimetricFlood(List[i], 2500u * 3);
		PRINTErr("��ɫ�����ɼ�", Err);
		Err = Colorimetric(1);
		PRINTErr("������ɫ", Err);
		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
		Err = ColorimetricOut();
		PRINTErr("��ɫ�������", Err);
		Err = ColorimetricClean();
		PRINTErr("��ɫ����ϴ", Err);
	}
	g_pBaseInterface->ptrFuncLogger("\r\n���ȹ�������\r\n");
	return Err;

}
ProcessErr	ConcentrationEstimate(uint8_t SampleNum, uint8_t * List, uint8_t Size)
{
	ProcessErr
		Err = ProNOErr;
	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ��\r\n");
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type4);
	PRINTErr("ע�����ϴ", Err);

	Err = Preparation(List, Size, Type4, 5000);
	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = TubeFluidOut(SampleNum, 2000);
	PRINTErr("�Թ���ȡҺ", Err);
	Err = PumpRinse(Type2);
	PRINTErr("ע�����ϴ", Err);

	Err = WaterSampleIn(List, Size, SampleNum, DosageType2);
	PRINTErr("ˮ���ɼ�", Err);
	Err = TubeMix(List, 6u);
	PRINTErr("��Һ���", Err);

	return Err;
}
ProcessErr	ConcentrationMeasure(uint8_t * List, uint8_t Size)
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
		Err = TubeFluidOut(List[i], 2000);
		PRINTErr("�Թ���ȡҺ", Err);
		Err = PumpRinse(Type2);
		PRINTErr("ע�����ϴ", Err);
		Err = ColorimetricFlood(List[i], 6000);
		PRINTErr("��ɫ�����ɼ�", Err);
		Err = Colorimetric(1u);
		PRINTErr("������ɫ", Err);
		RTStatus.TubeReagent[List[i]].ConcentrationValue = RTStatus.Concentration[1u];
		g_pBaseInterface->ptrFuncLogger("%d��Ũ��ֵΪ%d\r\n", List[i], RTStatus.Concentration[0u]);
		Err = ColorimetricOut();
		PRINTErr("��ɫ�������", Err);
		Err = ColorimetricClean();
		PRINTErr("��ɫ����ϴ", Err);
	}
	Err = Colorimetric(0u);
	return Err;
}
//Err = TubeClean(List1, 3u);
//PRINTErr("�Թ���ϴ", Err);

void	Processx(void)
{
	ProcessErr
		Err = ProNOErr;
	uint8_t	SampleNum = 4u;
	uint8_t	List0[1u] = { 28 };
	uint8_t	List1[6u] = { 25, 26, 27, 29, 30, 31 };
	uint8_t	List2[3u] = { 29, 30, 31 };
	uint8_t	List3[3u] = { 34, 35, 36 };

	RTStatus_Init();
	Err = RbootArmChange(0u);
	Err = PumpEvacuation();
	PRINTErr("ע����ſ�", Err);

	PRINTErr("���ȿ�ʼ", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = TubeFluidOut(SampleNum, 2000);
	PRINTErr("�Թ���ȡҺ", Err);
	Err = PumpRinse(Type2);
	PRINTErr("ע�����ϴ", Err);

	Err = WaterSampleIn(List0, 1u, SampleNum, DosageType2 * 1);
	PRINTErr("ˮ���ɼ�", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type6);
	PRINTErr("ע�����ϴ", Err);

	Err = Preparation(List0, 1u, Type6, DosageType6 * 4);
	PRINTErr("��������Һע��", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type7);
	PRINTErr("ע�����ϴ", Err);

	Err = Preparation(List0, 1u, Type7, DosageType7 * 4);
	PRINTErr("�������Һע��", Err);

	Err = TubeMix(List0, 1u);
	PRINTErr("��Һ���", Err);
	for (uint8_t i = 0u; i < 1u; i++)
	{
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = TubeFluidOut(List1[i], 2000);
		PRINTErr("�Թ���ȡҺ", Err);
		Err = PumpRinse(Type2);
		PRINTErr("ע�����ϴ", Err);

		Err = ColorimetricFlood(List1[i], 2500u * 3);
		PRINTErr("��ɫ�����ɼ�", Err);
		Err = Colorimetric(1);
		PRINTErr("������ɫ", Err);
		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
		Err = ColorimetricOut();
		PRINTErr("��ɫ�������", Err);
		Err = ColorimetricClean();
		PRINTErr("��ɫ����ϴ", Err);
	}
	g_pBaseInterface->ptrFuncLogger("\r\n���ȹ�������\r\n");

	Err = TubeClean(List0, 1u);
	PRINTErr("�Թ���ϴ", Err);

	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ��\r\n");
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpRinse(Type4);
	PRINTErr("ע�����ϴ", Err);

	Err = Preparation(List2, 3u, Type4, 5000);
	PRINTErr("��Ũ��Ԥװ�Լ�����", Err);

	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = PumpCleanOut();
	PRINTErr("ע�����ϴ", Err);
	Err = TubeFluidOut(SampleNum, 2000);
	PRINTErr("�Թ���ȡҺ", Err);
	Err = PumpRinse(Type2);
	PRINTErr("ע�����ϴ", Err);

	Err = WaterSampleIn(List2, 3u, 4u, DosageType2);
	PRINTErr("ˮ���ɼ�", Err);
	Err = TubeMix(List1, 6u);
	PRINTErr("��Һ���", Err);


	for (uint8_t i = 0u; i < 3u; i++)
	{
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = PumpCleanOut();
		PRINTErr("ע�����ϴ", Err);
		Err = TubeFluidOut(List2[i], 2000);
		PRINTErr("�Թ���ȡҺ", Err);
		Err = PumpRinse(Type2);
		PRINTErr("ע�����ϴ", Err);
		Err = ColorimetricFlood(List2[0], 2500u * 2);
		PRINTErr("��ɫ�����ɼ�", Err);
		Err = Colorimetric(1);
		PRINTErr("������ɫ", Err);
		g_pBaseInterface->ptrFuncLogger("Ũ��ֵΪ%d\r\n", RTStatus.Concentration[0u]);
		Err = ColorimetricOut();
		PRINTErr("��ɫ�������", Err);
		Err = ColorimetricClean();
		PRINTErr("��ɫ����ϴ", Err);
	}
	g_pBaseInterface->ptrFuncLogger("\r\n�ֱ�ߵ�Ũ�Ƚ���\r\n");
	Err = TubeClean(List2, 3u);
	PRINTErr("�Թ���ϴ", Err);

	g_pBaseInterface->ptrFuncLogger("\r\nˮ��ϡ��\r\n");

	Err = WaterSampleAttenuation(SampleNum, List3[0u]);
	PRINTErr("ˮ��ϡ��1", Err);
	Err = WaterSampleAttenuation(SampleNum, List3[1u]);
	PRINTErr("ˮ��ϡ��2", Err);
	Err = WaterSampleAttenuation(SampleNum, List3[2u]);
	PRINTErr("ˮ��ϡ��3", Err);

	Err = TubeClean(List3, 3u);
	PRINTErr("�Թ���ϴ", Err);

	Err = RbootArmChange(0u);
	PRINTErr("��е�۹�λ", Err);

}
enum	enumCTRLCMD
{
	CMD_Pumpclean = 0,		//	��ϴע���
	CMD_Chloridion,			//	����
	CMD_Attenuation,		//	ϡ��
	CMD_CompoundHigh,		//	���Ƹ�Ũ����Ʒ
	CMD_CompoundLow,		//	���Ƶ�Ũ����Ʒ
	CMD_Dissolution5,		//	��������5����
	CMD_Dissolution15,		//	��������15����
	CMD_Colorimetric,		//	�ֹ��ɫ
};
ProcessErr	TaskCTRL(void)
{
	ProcessErr
		Err = ProNOErr;


	return	Err;
}


//void	__Task_ProcessControl( const void * P_arg )
//{
//	ProcessErr 
//	Err = ProNOErr;
//	RTStatus_Init();
//	
////	Debug();
//	Processx();

//	for(;;)
//	{
//		if( Err != ProNOErr )
//			while( 1u )	osDelay( 1000u );	
//		osDelay( 1000u );
//	}
//}
//osThreadDef( __Task_ProcessControl, osPriorityNormal, 1u, 0  );
//void	ProcessCTRL_Init( void )
//{
//	osThreadCreate( osThread( __Task_ProcessControl ), NULL );
//}

