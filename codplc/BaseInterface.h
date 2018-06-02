
#ifndef __BaseInterface_H__
#define __BaseInterface_H__
#ifdef __cplusplus
extern "C"{
#endif 

typedef		void(*ptrLoggerDllDef)(const char * szFormat, ...);
typedef     bool(*ptrGetPntValueByNameDef)(const char *pPntName, int *pValue);
typedef     bool(*ptrSetPntValueByNameDef)(const char *pPntName, int nValue,int nExceedTime);
typedef struct
{
	ptrLoggerDllDef		ptrFuncLogger;//日志接口函数
	ptrGetPntValueByNameDef ptrGetPntValueByName;//根据测点名称获取测点值
	ptrSetPntValueByNameDef ptrSetPntValueByName;//根据测点名称设置测点值
}SBaseInterface;//该结构由上位机传给逻辑库

typedef bool(*ptrReturnFuncDef)();
typedef struct 
{
	ptrReturnFuncDef  ptrDoBeforeWhile;//进入while循环之前执行的函数
	ptrReturnFuncDef  ptrDoWhile;//进入while之后循环之前执行的函数
	ptrReturnFuncDef  ptrDoAfterWhile;//推出while之后循环之前执行的函数
}SReturnInterface;//逻辑库返回需要上位机控制的函数指针

void LOG_FORMAT_INFO_EX(const char * szFormat, ...);//逻辑库不能使用
bool GetPntValueByName(const char *pPntName, int *pValue);//逻辑库不能使用
bool SetPntValueByName(const char *pPntName, int nValue, int nExceedTime);//逻辑库不能使用
extern ptrLoggerDllDef LOG_INFO_EX;//逻辑库不能使用
extern SBaseInterface g_stBaseInterface;//逻辑库不能使用
extern SBaseInterface *g_pBaseInterface;
#ifdef __cplusplus
}
#endif
#endif