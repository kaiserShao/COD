
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"
//#include "cmsis_os.h"
#include "BaseInterface.h"
//#include "MBM.H"
//extern	uint16_t	usRegHoldingBuf1[];
//extern	uint16_t	usRegHoldingBuf2[];
//extern	uint16_t	usRegHoldingBuf3[];
typedef	uint8_t		ProcessErr;
#ifndef _Bool
#define _Bool bool
#endif
void osDelay(int nDelay);
//extern	eMBErrorCode	HoldingSingelWrite1( uint16_t  Numbler, uint16_t	Data );
//extern	uint16_t	HoldingSingelRead1( uint16_t  Numbler );
extern	_Bool	HoldingSingelWrite2(const	char *lpName, uint16_t	Data);
extern	uint16_t	HoldingSingelRead2(const	char *lpName);
//extern	eMBErrorCode	HoldingSingelWrite3( uint16_t  Numbler, uint16_t	Data );
//extern	uint16_t	HoldingSingelRead3( uint16_t  Numbler );
extern	const	char * MBName[];

extern	void	PRINTErr(char *s, ProcessErr Err);

extern	void	Processx();
#define	SPECTROPHOTOMETRY 0x01u
#define	ARMRBOOT 0x02u
#define	DISSOLVE 0x03u

#define	TubeMax	180u
#define	Full	23000
#define	ArmBase 70u
#define	PumpZero	2
#define	Clean	7000
#define	DosageType2 	2000
#define	DosageType4		5000
#define	DosageType5 	5000
#define	DosageType6 	500
#define	DosageType7 	200

#define	M_Type1		3000u
#define	M_Type2		8000u
#define	M_Type10	10000u


enum	enumStatus
{
	StatusBlank = 0u,
	StatusNonblank,
	StatusMax,
};

enum	enumType
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

enum	ProErr
{
	ProNOErr = 0u,
	ProPumpBlockingErr,
	ProPumpRangeErr,
	ProPumpPositionErr,
	ProValveErr,
	ProCommonErr,
	ProNoWater,
	ProNoWaterFirst,
	ProNoWaterLast,
	ProArmXErr,
	ProArmYErr,
	ProArmZErr,
	ProReagentErr,
	ProErrNoDef = 0xFFu,
};


enum	enumTubeState
{
	StateUnknown,
	StateHigh,
	StateLow,
};

struct	uTubeReagent
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
	//bool	TubeMix;
	//bool	HeatTime;
	//bool	DataValid;
};
//extern	struct	uTubeReagent	TubeReagent[TubeMax];

struct	uRTStatus
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
extern	struct	uRTStatus RTStatus;

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

extern	ProcessErr	ProcessDeal(struct	uCMDs * CMDs, uint8_t CMDsLenth);


#endif


