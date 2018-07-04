
#include "DEBUG.H"
#include "CodPLCInterface.h"

struct	uTaskSet	TaskSet[TubeMax];
/*
uint8_t	TubeNum;					//	水样试管号
//	uint8_t	SampleDosage;		//	水样剂量
uint8_t	ExperimentNum;				//	平行试验组数
uint8_t	MeasuringChlorine;			//	0 无须测氯		1 需要测氯
uint8_t	ConcentrationEstimate;		//	0 未知浓度		1 高浓度			2 低浓度
uint8_t	DissolutionTime;			//	0 不消解			1 消解时长15min	2 消解时长5min
uint8_t	ConcentrationMeasure;		//	0 不比色			1 比色分析浓度		2
*/
uint8_t	Listlv[50u] = { 0u };
uint8_t	Listyupan[50u] = { 0u };
uint8_t	Listbisegao[50u] = { 0u };
uint8_t	Listbisedi[50u] = { 0u };

#define	TubeUseBase	25u
#define	TubeUseMax	32u
#define TubeSampleMax 24u

extern	ProcessErr	ChlorineMeasuring(uint8_t *	SampleNumList, uint8_t Size);
extern	ProcessErr	ConcentrationEstimate(uint8_t * List, uint8_t Size);
extern	ProcessErr	ConcentrationEstimate(uint8_t * List, uint8_t Size);
void	TubeAnalyze(void)
{
	uint8_t	k, l = 0u;
	uint8_t	SumTube = 0u;
	uint8_t	Sum[3u] = { 0u };
	uint8_t	BatchHead[10u] = { 0u };
	uint8_t	BatchEnd[10u] = { 0u };
	uint8_t	SumTemp = 0u;							//	临时求和
	BatchHead[0u] = 0u;
	BatchEnd[0u] = 0u;
	/************************************************************/
	for (uint8_t i = 1u; i <= TubeSampleMax; i++)	//	模拟上位机设置
	{
		//TaskSet[i].MeasuringChlorine = 1u;
		TaskSet[i].ConcentrationEstimate = 2u;
		TaskSet[i].ConcentrationMeasure = 1u;
		TaskSet[i].ExperimentNum = 4u;
	}
	/************************************************************/
	/*单组水样所需的总试管数量不得超过TubeUseMax*/
	l = 0u;
	for (uint8_t i = 1u; i <= TubeSampleMax; i++)	//	计算所需试管量
	{
		SumTemp = 0u;
		if (TaskSet[i].MeasuringChlorine)			//	测氯
		{
			Sum[0u] ++;								//	总的测氯数量
			SumTemp++;
		}
		if (!TaskSet[i].ConcentrationEstimate)		//	浓度判定
		{
			Sum[1u] ++;								//	总的判定数量
			SumTemp++;
		}
		if (TaskSet[i].ConcentrationMeasure)		//	比色分析
		{
			Sum[2u] ++;								//	总的分析数量
			SumTemp += TaskSet[i].ExperimentNum;	//	平行试验组数
		}
		SumTube += SumTemp;							//	总的试管需求量
		
		if (SumTube <= TubeUseMax * l)				//	分批次
		{
			BatchEnd[l] = i;						//	单批次末端水样号
		}
		else
		{
			BatchHead[++l] = i;						//	单批次开头水样号
		}
	}		
	
	for (uint8_t i = 1; i <= l; i ++)				//	批次数
	{
		k = 0u;
		for (uint8_t j = BatchHead[i]; j <= BatchEnd[i]; j++)				//	当前批次处理
		{
			//	每批次都默认和保证所有试管都是干净的
			if (TaskSet[j].MeasuringChlorine)								//	测氯
			{
				RTStatus.TubeReagent[TubeUseBase + k].Useing = true;
				RTStatus.TubeReagent[TubeUseBase + k].SampleFrom = j;
				RTStatus.TubeReagent[TubeUseBase + k].Function = 1u;
				RTStatus.TubeReagent[TubeUseBase + k].NumWithInGroup = k;
				k++;
			}
			if (!TaskSet[j].ConcentrationEstimate)							//	预判浓度
			{
				RTStatus.TubeReagent[TubeUseBase + k].Useing = true;
				RTStatus.TubeReagent[TubeUseBase + k].SampleFrom = j;
				RTStatus.TubeReagent[TubeUseBase + k].Function = 2u;
				RTStatus.TubeReagent[TubeUseBase + k].NumWithInGroup = k;
				k++;
			}
			for (uint8_t x = 0u; x < TaskSet[j].ExperimentNum; x++)			//	测浓度
			{
				RTStatus.TubeReagent[TubeUseBase + k].Useing = true;
				RTStatus.TubeReagent[TubeUseBase + k].SampleFrom = j;
				if (TaskSet[j].ConcentrationEstimate == 1)					//	预判浓度
					RTStatus.TubeReagent[TubeUseBase + k].Function = 3u;	//	高浓度
				if (TaskSet[j].ConcentrationEstimate == 2)					//	预判浓度
					RTStatus.TubeReagent[TubeUseBase + k].Function = 4u;	//	低浓度
				RTStatus.TubeReagent[TubeUseBase + k].NumWithInGroup = k;
				k++;
			}
		}
		k = 0u;
		uint8_t	CountLv, CountYu, CountGao, CountDi = 0u;
		CountLv = CountYu = CountGao = CountDi = 0u;
		for (uint8_t j = 0; j < TubeUseMax; j++)							//	当前批次处理
		{
			switch (RTStatus.TubeReagent[TubeUseBase + j].Function)
			{
			case 1u:
				Listlv[CountLv++] = TubeUseBase + j;
				break;
			case 2u:
				Listyupan[CountYu++] = TubeUseBase + j;
				break;
			case 3u:
				Listbisegao[CountGao++] = TubeUseBase + j;
				break;
			case 4u:
				Listbisedi[CountDi++] = TubeUseBase + j;
				break;
			default:
				break;
			}
			k++;
		}

		/*ChlorineMeasuring(Listlv, CountLv);
		ConcentrationEstimate(Listyupan, CountYu);*/
		ConcentrationEstimate(Listbisedi, CountDi);
	}

}