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


enum	enumType	//	试样通道号
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

enum	ProErr	//	流程错误信息
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


////	响应函数
extern	ProcessErr	ValveCTRL(enum enumType Channel);		//	转换阀 //	1-10
extern	ProcessErr	PumpCTRL(int16_t	ulPumpPosition);	//	注射泵	//	相对运动量  
extern	ProcessErr	MotorCTRL(uint16_t ms);					//	空气泵	吹空公共管后的延时时间
extern	ProcessErr	RBootARMMoveXYZ(uint16_t X, uint16_t Y, uint16_t Z);
extern	ProcessErr	EffluentDeal(uint16_t	Delayms);		//	废液排空	//	目前没有加光电检测 所以是延时排空
extern	ProcessErr	Spectropho(uint16_t	Channel);			//	光电发射LED通道	//	0-4 0为全关
extern	ProcessErr	ConcentrationRead(uint16_t	Channel);	//	光电接收数据获取	//	1-4


#endif
