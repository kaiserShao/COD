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

#define	TubeMax				180u

enum	enumStatus	//	������״̬ ��/�ǿ�
{
	StatusBlank = 0u,
	StatusNonblank,
	StatusMax,
};

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

enum	enumTubeState	//	�Լ����� δ֪/��/��
{
	StateUnknown,
	StateHigh,
	StateLow,
};

struct	uTubeReagent	//	�Թܸ����Լ�״̬
{
	int16_t	Water;
	int16_t	LowLevel;
	int16_t	HighLevel;
	int16_t	AgNo3;
	int16_t	KCrO;
	int16_t	Sample;
	int16_t	Sum;
	int16_t	CleanCount;
	int16_t	ConcentrationValue;
	enum	enumTubeState	ChloridionHL;
	enum	enumTubeState	ConcentrationHL;

};

struct	uRTStatus			//	ʵʱ״̬
{
	enum	enumStatus	Exist[TypeMax];
	enum	enumStatus	Common;
	enum	enumType	Channel;
	uint16_t	HeatRealTemp;
	uint16_t	PumpPosition;
	uint16_t	RbootArmPosition[3u];
	uint16_t	Concentration[4u];
	struct	uTubeReagent	TubeReagent[TubeMax];
};
extern	struct	uRTStatus	RTStatus;


//	��Ӧ����
extern	ProcessErr	CMD_PumpcleanResponse(void);
extern	ProcessErr	CMD_ChloridionResponse(uint8_t uSampleNum, uint8_t * uList, uint8_t uSize);
extern	ProcessErr	CMD_AttenuationResponse(uint8_t uSampleNum, uint8_t uAttenuationNumbler);
extern	ProcessErr	CMD_CompoundHighResponse(uint8_t * uList, uint8_t uSize);
extern	ProcessErr	CMD_CompoundLowResponse(uint8_t * uList, uint8_t uSize);
extern	ProcessErr	CMD_Dissolution15Response(void);
extern	ProcessErr	CMD_ColorimetricResponse(uint8_t * uList, uint8_t uSize, uint8_t uLEDChannel);
extern	ProcessErr	CMD_TubeCleanResponse(uint8_t * uList, uint8_t uSize);
extern	ProcessErr	CMD_LEDCTRLResponse(uint8_t uLEDChannel);

#endif
