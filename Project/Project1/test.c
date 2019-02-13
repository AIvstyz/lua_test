#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "itcast_asn1_der.h"

typedef struct _stu_t
{
	char name[32];
	int age;
	char *p;
	int pLen;
}stu_t;

//简单结构体编码函数
int TeacherEncode(stu_t *s, unsigned char **outData, int *outDataLen)
{
	ITCAST_INT ret = 0;

	ITCAST_ANYBUF *tmpAnyBuf = NULL;
	ITCAST_ANYBUF *headNode = NULL;
	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *outDataNode = NULL;

	unsigned char *out = NULL;
	int outLen = 0;

	//0. 容错判断
	if (NULL == s || NULL == outData || NULL == outDataLen)
	{
		printf("TeacherEncode parameter is invalid....\n");
		return -1;
	}

	//1. 编码name

	//先将char*转为ANYBUF类型
	ret = DER_ITCAST_String_To_AnyBuf(&tmpAnyBuf, s->name, strlen(s->name));  //1.free
	if (0 != ret)
	{
		printf("DER_ITCAST_String_To_AnyBuf failed.. ret:%d\n", ret);
		goto err0;
	}

	ret = DER_ItAsn1_WritePrintableString(tmpAnyBuf, &headNode); //2.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_WritePrintableString failed.. ret:%d\n", ret);
		goto err0;
	}

	//2. 编码age
	tmpNode = headNode;
	ret = DER_ItAsn1_WriteInteger(s->age, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed.. ret:%d\n", ret);
		goto err0;
	}

	//3. 编码p
	tmpNode = tmpNode->next;
	ret = EncodeChar(s->p, strlen(s->p), &(tmpNode->next));
	if (0 != ret)
	{
		printf("EncodeChar failed.. ret:%d\n", ret);
		goto err0;
	}

	//4. 编码pLen
	tmpNode = tmpNode->next;
	ret = DER_ItAsn1_WriteInteger(s->pLen, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed.. ret:%d\n", ret);
		goto err0;
	}

	//5. 编码大结构体
	ret = DER_ItAsn1_WriteSequence(headNode, &outDataNode); //3.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteSequence failed.. ret:%d\n", ret);
		goto err0;
	}

	//6. 传出
	out = malloc(outDataNode->dataLen + 1);
	if (NULL == out)
	{
		printf("malloc failed...\n");
		ret = ITDER_MemoryErr;
		goto err0;
	}
	memset(out, 0, outDataNode->dataLen + 1);

	memcpy(out, outDataNode->pData, outDataNode->dataLen);
	outLen = outDataNode->dataLen;

	*outData = out;
	*outDataLen = outLen;

	//7. 释放内存
	if (NULL != tmpAnyBuf)
	{
		DER_ITCAST_FreeQueue(tmpAnyBuf);
	}

	if (NULL != headNode)
	{
		DER_ITCAST_FreeQueue(headNode);
	}

	if (NULL != outDataNode)
	{
		DER_ITCAST_FreeQueue(outDataNode);
	}

	return 0;

err0:
	if (NULL != tmpAnyBuf)
	{
		DER_ITCAST_FreeQueue(tmpAnyBuf);
	}

	if (NULL != headNode)
	{
		DER_ITCAST_FreeQueue(headNode);
	}

	if (NULL != outDataNode)
	{
		DER_ITCAST_FreeQueue(outDataNode);
	}

	return ret;
}
//简单结构体解码函数
int TeacherDecode(unsigned char *inData, int inDataLen, stu_t **s)
{
	int ret = 0;

	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *headNode = NULL;
	ITCAST_ANYBUF *tmp = NULL;
	ITCAST_ANYBUF *tmpNodeName = NULL;
	ITCAST_ANYBUF *tmpNodeP = NULL;

	stu_t *pStu = NULL;

	//0. 容错判断
	if (NULL == inData || inDataLen <= 0 || NULL == s)
	{
		printf("TeacherDecode parameter is invalid\n");
		return -1;
	}

	//1. 解码大结构体
	ret = DER_ITCAST_String_To_AnyBuf(&tmpNode, inData, inDataLen);	//1.free
	if (0 != ret)
	{
		printf("DER_ITCAST_String_To_AnyBuf failed.. ret:%d\n", ret);
		goto err0;
	}

	ret = DER_ItAsn1_ReadSequence(tmpNode, &headNode);	//2. free
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadSequence failed.. ret:%d\n", ret);
		goto err0;
	}

	//分配空间
	pStu = malloc(sizeof(stu_t));
	if (NULL == pStu)
	{
		printf("malloc pStu failed....\n");
		ret = ITDER_MemoryErr;
		goto err0;
	}
	memset(pStu, 0, sizeof(stu_t));

	//2. 解码name
	ret = DER_ItAsn1_ReadPrintableString(headNode, &tmpNodeName);	//3.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadPrintableString failed... ret:%d\n", ret);
		goto err0;
	}

	//拷贝数据
	memcpy(pStu->name, tmpNodeName->pData, tmpNodeName->dataLen);


	//3. 解码age
	tmp = headNode->next;
	ret = DER_ItAsn1_ReadInteger(tmp, &pStu->age);
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadInteger failed... ret:%d\n", ret);
		goto err0;
	}

	//4. 解码p
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadPrintableString(tmp, &tmpNodeP);	//4.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadPrintableString failed... ret:%d\n", ret);
		goto err0;
	}

	//分配空间
	pStu->p = malloc(tmpNodeP->dataLen + 1);
	if (NULL == pStu->p)
	{
		printf("malloc pStu->p failed....\n");
		goto err0;
	}
	memset(pStu->p, 0, tmpNodeP->dataLen + 1);

	//拷贝数据
	memcpy(pStu->p, tmpNodeP->pData, tmpNodeP->dataLen);

	//5. 解码pLen
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadInteger(tmp, &pStu->pLen);
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadInteger failed... ret:%d\n", ret);
		goto err0;
	}

	//6. 传出
	*s = pStu;

	//7. 释放内存
	if (NULL != tmpNode)
	{
		DER_ITCAST_FreeQueue(tmpNode);
	}
	if (NULL != headNode)
	{
		DER_ITCAST_FreeQueue(headNode);
	}
	if (NULL != tmpNodeName)
	{
		DER_ITCAST_FreeQueue(tmpNodeName);
	}
	if (NULL != tmpNodeP)
	{
		DER_ITCAST_FreeQueue(tmpNodeP);
	}


	return 0;
err0:

	if (NULL != tmpNode)
	{
		DER_ITCAST_FreeQueue(tmpNode);
	}
	if (NULL != headNode)
	{
		DER_ITCAST_FreeQueue(headNode);
	}
	if (NULL != tmpNodeName)
	{
		DER_ITCAST_FreeQueue(tmpNodeName);
	}
	if (NULL != tmpNodeP)
	{
		DER_ITCAST_FreeQueue(tmpNodeP);
	}
	return ret;
}
//简单结构体内存释放函数
int TeacherFreeMem(stu_t **s)
{
	stu_t *pStu = NULL;
	//1. 容错判断
	if (NULL == s || NULL == *s)
	{
		printf("TeacherFreeMem parameter is invalid...\n");
		return -1;
	}

	pStu = *s;
	//2. 判断(*s)->p
	if (NULL != pStu->p)
	{
		free(pStu->p);
	}

	//3. 释放(*s)
	free(pStu);

	//4. NULL
	*s = NULL;

	return 0;
}

//文件操作函数
int mywritefile(unsigned char *buf, int len)
{
	FILE *fp = NULL;
	fp = fopen("d:/teacher.ber", "wb+");
	if (fp == NULL)
	{
		printf("fopen file error \n");
		return -1;
	}
	fwrite(buf, 1, len, fp);
	fclose(fp);
	return 0;
}

int main(void)
{
	int ret = 0;

	//编码函数参数
	unsigned char *outData = NULL;
	int outDataLen = 0;

	//解码之后传出参数
	stu_t *pStu = NULL;

	//定义一个结构体变量, 然后做初始化
	stu_t s = {
		.name = "张三疯",
		.age = 18,
		.p = "hello world",
		.pLen = 11
	};

	//1. 编码
	ret = TeacherEncode(&s, &outData, &outDataLen);
	if (0 != ret)
	{
		printf("TeacherEncode failed.....\n");
		return 1;
	}

	printf("编码成功....\n");
	printf("outData: %s outDataLen:%d\n", outData, outDataLen);

	mywritefile(outData, outDataLen);


	//2. 解码
	ret = TeacherDecode(outData, outDataLen, &pStu);
	if (0 != ret)
	{
		printf("TeacherDecode failed... ret: %d\n", ret);
		free(outData);
		return 1;
	}
	printf("解码成功....\n");

	//3. 比较结果
	if ((s.age == pStu->age) && strcmp(s.name, pStu->name) == 0)
	{
		printf("编解码ok....\n");
	}
	else
	{
		printf("编解码failed....\n");
	}

	printf("name:%s age:%d p: %s pLen: %d\n", pStu->name, pStu->age, pStu->p, pStu->pLen);

	//4. 释放内存
	TeacherFreeMem(&pStu);

	printf("hello world\n");


	system("pause");
	return 0;
}