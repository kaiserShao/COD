
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
	ptrLoggerDllDef		ptrFuncLogger;//��־�ӿں���
	ptrGetPntValueByNameDef ptrGetPntValueByName;//���ݲ�����ƻ�ȡ���ֵ
	ptrSetPntValueByNameDef ptrSetPntValueByName;//���ݲ���������ò��ֵ
}SBaseInterface;//�ýṹ����λ�������߼���

typedef bool(*ptrReturnFuncDef)();
typedef struct 
{
	ptrReturnFuncDef  ptrDoBeforeWhile;//����whileѭ��֮ǰִ�еĺ���
	ptrReturnFuncDef  ptrDoWhile;//����while֮��ѭ��֮ǰִ�еĺ���
	ptrReturnFuncDef  ptrDoAfterWhile;//�Ƴ�while֮��ѭ��֮ǰִ�еĺ���
}SReturnInterface;//�߼��ⷵ����Ҫ��λ�����Ƶĺ���ָ��

void LOG_FORMAT_INFO_EX(const char * szFormat, ...);//�߼��ⲻ��ʹ��
bool GetPntValueByName(const char *pPntName, int *pValue);//�߼��ⲻ��ʹ��
bool SetPntValueByName(const char *pPntName, int nValue, int nExceedTime);//�߼��ⲻ��ʹ��
extern ptrLoggerDllDef LOG_INFO_EX;//�߼��ⲻ��ʹ��
extern SBaseInterface g_stBaseInterface;//�߼��ⲻ��ʹ��
extern SBaseInterface *g_pBaseInterface;
#ifdef __cplusplus
}
#endif
#endif