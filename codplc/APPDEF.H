
#ifndef _APPDEF_H_
#define _APPDEF_H_

#include "stdbool.h"
//#include "stm32f10x.h"
//#include "cmsis_os.h"

extern	int	BIOS_Init( void );

extern	void	BIOS_USART3_Init( void );
extern	void	UART3_Send( uint8_t OutByte );
extern	void	BIOS_SWD_Init( void );



extern	void	ModbusPoll( const	void * parg );
extern	void	MODBUS_Init( uint8_t MBAddress );
extern	uint16_t	usRegInputBuf[];
extern	uint16_t	usRegHoldingBuf[];
extern	uint8_t		ucRegDiscBuf[];
extern	uint8_t		ucRegCoilsBuf[];


enum	ValveState
{
	StateOK,
	FrameErr,
	ParameterErr,
	OptocouplerErr,
	MotorIsBusy,
	TaskBeSuspended,
	UnknownErr,
};
struct	uDataPackGeneral
{
	uint8_t		FrameHead;
	uint8_t		Address;
	uint8_t		CTRLCommand;
	uint8_t		Data[2u];
	uint8_t		FrameEnd;
	uint8_t		CRCSum[2u];
	
};
struct	uDataPackFactory
{
	uint8_t		FrameHead;
	uint8_t		Address;
	uint8_t		CTRLCommand;
	uint8_t		Password[4u];
	uint8_t		Data[4u];
	uint8_t		FrameEnd;
	uint8_t		CRCSum[2u];
	
};
struct	uDataUnpack
{
	uint8_t		FrameHead;
	uint8_t		Address;
	uint8_t		AckState;
	uint8_t		Data[2u];
	uint8_t		FrameEnd;
	uint8_t		CRCSum[2u];
};


#define	AddrSet								0x00
#define	RS232BaudRateSet			0x01
#define	RS485BaudRateSet			0x02
#define	CANBaudRateSet				0x03
#define	SpeedMaxSet						0x07
#define	ChannelMaxSet					0x0A
#define	ResertSpeedSet				0x0B
#define	ResertDirSet					0x0C
#define	PowerOnRst						0x0E
#define	DestinationCan				0x10
	
#define	AddrQuery							0x20u
#define	RS232BaudRateQuery		0x21u
#define	RS485BaudRateQuery		0x22u
#define	CANBaudRateQuery			0x23u
#define	SpeedMaxQuery					0x27u
#define	ChannelMaxQuery				0x2Au
#define	ResertSpeedQuery			0x2Bu
#define	ResertDirQuery				0x2Cu
#define	PowerOnRstQuery				0x2Du
#define	DestinationCanQuery		0x30u
#define	ChannelCurrentQuery		0x3Eu
#define	VerisonQuery					0x3Fu
#define	StopReasonQuery				0x65u
#define	CurrentPositionQuery	0x66u
#define	ClearCurrentPosition	0x67u
#define	CurrentDIRQuery				0x68u


#define	AntiClockwiseRotation	0x41u
#define	ClockwiseRotation			0x42u
#define	ChannelSelectSet			0x44u
#define	ChannelResert					0x45u
#define	Braking								0x49u
#define	MotorState						0x4Au
#define	ResetInsertData				0xFFu


#define	PumpAddr							0x00u
#define	ValveAddr							0x01u

#define	FactoryPassword1			0xAAu
#define	FactoryPassword2			0xBBu
#define	FactoryPassword3			0xEEu
#define	FactoryPassword4			0xFFu
#define	FrameHeadValue				0xCCu
#define	FrameEndValue					0xDDu

#define	Baud9600							0x00u
#define	Baud19200							0x01u
#define	Baud38400							0x02u
#define	Baud57600							0x03u
#define	Baud115200						0x04u

#define	SpeedMax							0xC8u

#define	PowerUpRst						0x01u
extern	struct	uDataUnpack	DataUnpackValve;
extern	struct	uDataPackGeneral	ValveGeneral; 
extern	struct	uDataPackFactory	ValveFactory; 
extern	_Bool	DataDealUnpack( struct	uDataUnpack * DataUnpack );

extern	_Bool	RxUpToDate;
extern	uint16_t	VPState[2u];
extern	uint16_t	VPPosition[2u];

extern	void	Pump_Value_CTRL_Init( void );

extern	uint32_t	CoordinateSet[3u];
extern	uint32_t	CoordinatePosition[3u];
extern	uint8_t		Arm_Init( void );



extern	void	AoutCover_Control( _Bool	Newstate, _Bool	Direction );
extern	void	Beep_Control( _Bool	Newstate );
extern	void	Blender_Control( uint16_t Percent );
extern	void	SolenoidValve_Control( _Bool	Newstate );
extern	void	SolenoidValve_Control2( _Bool	Newstate );
extern	void	delay_us ( uint32_t us );



extern	void	ProcessCTRL_Init( void );
extern	void	__Task_RTStatus( void );















#endif


