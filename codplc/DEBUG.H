
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "BaseInterface.h"
typedef	uint8_t		ProcessErr;
#ifndef _Bool
#define _Bool bool
#endif

void	osDelay(int nDelay);
extern	_Bool	HoldingSingelWrite2(const	char *lpName, uint16_t	Data);
extern	uint16_t	HoldingSingelRead2(const	char *lpName);
extern	const	char * MBName[];
extern	void	PRINTErr(char *s, ProcessErr Err);

#define	SPECTROPHOTOMETRY 0x01u
#define	ARMRBOOT		0x02u
#define	DISSOLVE		0x03u
#define Retry			30u
#define	TubeMax			180u
#define	PumpPositionMax	22000
#define	Full			20000
#define	ArmBase			70u
#define	SpeBase			30u
#define	PumpZero		2
#define	Clean			7000
#define	DosageType2 	2000
#define	DosageType4		5000
#define	DosageType5 	5000
#define	DosageType6 	500
#define	DosageType7 	200

#define	MBRetry			4
#define	M_Type1			3000u
#define	M_Type2			8000u
#define	M_Type10		10000u



enum	enumStatus	//	公共管状态 空/非空
{
	StatusBlank = 0u,
	StatusNonblank,
	StatusMax,
};

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


enum	enumTubeState	//	试剂量程 未知/高/低
{
	StateUnknown,
	StateHigh,
	StateLow,
};

struct	uTubeReagent	//	试管状态
{

	uint8_t	Useing;					//	是否正在使用

	uint8_t	SampleFrom;				//	水样源
	uint8_t	Function;				//	功能	// 1 测氯 2 
	uint8_t	NumWithInGroup;			//	组内编号

	int16_t	Water;					//	各种试剂的量
	int16_t	LowLevel;
	int16_t	HighLevel;
	int16_t	AgNo3;
	int16_t	KCrO;
	int16_t	Sample;
	int16_t	Sum;					//	试剂总量

	uint8_t	CleanCount;				//	清洗次数

	enum	enumTubeState	ChloridionHL;		//	氯离子浓度高低
	enum	enumTubeState	ConcentrationHL;	//	待测液浓度高低

	int16_t	ConcentrationValue;					//	浓度值

};
struct	uRTStatus			//	实时状态
{
	enum	enumStatus	Exist[TypeMax];	//	试剂是否存在
	enum	enumStatus	Common;			//	公共管状态
	enum	enumType	Channel;		//	转换阀当前通道（当前试剂）
	uint16_t	HeatRealTemp;			//	消解器实时温度
	uint16_t	PumpPosition;			//	注射泵实时位置
	uint16_t	RbootArmPosition[3u];	//	机械臂实时位置
	uint16_t	Concentration[4u];		//	浓度值实时数据（暂时不使用）
	struct	uTubeReagent	TubeReagent[TubeMax];
};
extern	struct	uRTStatus	RTStatus;	//	仪器运行的实时状态

struct uResult			//	最终结果 
{
	uint8_t	Useing;					//	是否正在使用

	uint8_t	SampleFrom;				//	水样源
	uint8_t	Function;				//	功能
	uint8_t	NumWithInGroup;			//	组内编号

	enum	enumTubeState	ChloridionHL;		//	氯离子浓度高低
	enum	enumTubeState	ConcentrationHL;	//	待测液浓度高低

	int16_t	ConcentrationValue;					//	浓度值
};
enum	enumCommand
{
	CMDValve = 1u,
	CMDPump,
	CMDMotor,
	CMDXYZ,
	CMDEFF,
	CMDLED,
	CMDCOV,
	CMDDLY,
};

struct	uCMDs
{
	enum enumCommand	CMD;
	int16_t	Control;
};

extern	ProcessErr	ProcessDeal(enum enumCommand CMD, int16_t Value);

#endif


