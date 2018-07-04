#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "BaseInterface.h"

typedef	uint8_t		ProcessErr;

#ifndef _Bool
#define _Bool bool
#endif


enum	enumType	//	����ͨ����
{
	TypeErr = 0u,
	Type1 = 1u,
	Type2,
	Type3,
	Type4,
	Type5,
	Type6,
	Type7,
	Type8,
	Type9,
	Type10,
	Type11,
	TypeMax,
};

enum	ProErr	//	���̴�����Ϣ
{
	ProNOErr = 0u,
	ProPumpBlockingErr,
	ProPumpRangeErr,
	ProPumpPositionErr,
	ProValveErr,
	ProCommonErr,
	ProNoFluid,
	ProArmXErr,
	ProArmYErr,
	ProArmZErr,
	ProReagentErr,
	ProMBReadErr,
	ProMBWriteErr,
	ProBusy,
	ProErrNoDef = 0xFFu,
};


////	��Ӧ����
extern	ProcessErr	ValveCTRL(enum enumType Channel);		//	ת���� //	1-10
extern	ProcessErr	PumpCTRL(int16_t	ulPumpPosition);	//	ע���	//	����˶���  
extern	ProcessErr	MotorCTRL(uint16_t ms);					//	������	���չ����ܺ����ʱʱ��
extern	ProcessErr	RBootARMMoveXYZ(uint16_t X, uint16_t Y, uint16_t Z);
extern	ProcessErr	EffluentDeal(uint16_t	Delayms);		//	��Һ�ſ�	//	Ŀǰû�мӹ���� ��������ʱ�ſ�
extern	ProcessErr	Spectropho(uint16_t	Channel);			//	��緢��LEDͨ��	//	0-4 0Ϊȫ��
extern	ProcessErr	ConcentrationRead(uint16_t	Channel);	//	���������ݻ�ȡ	//	1-4


#endif
