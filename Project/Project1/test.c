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

//�򵥽ṹ����뺯��
int TeacherEncode(stu_t *s, unsigned char **outData, int *outDataLen)
{
	ITCAST_INT ret = 0;

	ITCAST_ANYBUF *tmpAnyBuf = NULL;
	ITCAST_ANYBUF *headNode = NULL;
	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *outDataNode = NULL;

	unsigned char *out = NULL;
	int outLen = 0;

	//0. �ݴ��ж�
	if (NULL == s || NULL == outData || NULL == outDataLen)
	{
		printf("TeacherEncode parameter is invalid....\n");
		return -1;
	}

	//1. ����name

	//�Ƚ�char*תΪANYBUF����
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

	//2. ����age
	tmpNode = headNode;
	ret = DER_ItAsn1_WriteInteger(s->age, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed.. ret:%d\n", ret);
		goto err0;
	}

	//3. ����p
	tmpNode = tmpNode->next;
	ret = EncodeChar(s->p, strlen(s->p), &(tmpNode->next));
	if (0 != ret)
	{
		printf("EncodeChar failed.. ret:%d\n", ret);
		goto err0;
	}

	//4. ����pLen
	tmpNode = tmpNode->next;
	ret = DER_ItAsn1_WriteInteger(s->pLen, &(tmpNode->next));
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteInteger failed.. ret:%d\n", ret);
		goto err0;
	}

	//5. �����ṹ��
	ret = DER_ItAsn1_WriteSequence(headNode, &outDataNode); //3.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_WriteSequence failed.. ret:%d\n", ret);
		goto err0;
	}

	//6. ����
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

	//7. �ͷ��ڴ�
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
//�򵥽ṹ����뺯��
int TeacherDecode(unsigned char *inData, int inDataLen, stu_t **s)
{
	int ret = 0;

	ITCAST_ANYBUF *tmpNode = NULL;
	ITCAST_ANYBUF *headNode = NULL;
	ITCAST_ANYBUF *tmp = NULL;
	ITCAST_ANYBUF *tmpNodeName = NULL;
	ITCAST_ANYBUF *tmpNodeP = NULL;

	stu_t *pStu = NULL;

	//0. �ݴ��ж�
	if (NULL == inData || inDataLen <= 0 || NULL == s)
	{
		printf("TeacherDecode parameter is invalid\n");
		return -1;
	}

	//1. �����ṹ��
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

	//����ռ�
	pStu = malloc(sizeof(stu_t));
	if (NULL == pStu)
	{
		printf("malloc pStu failed....\n");
		ret = ITDER_MemoryErr;
		goto err0;
	}
	memset(pStu, 0, sizeof(stu_t));

	//2. ����name
	ret = DER_ItAsn1_ReadPrintableString(headNode, &tmpNodeName);	//3.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadPrintableString failed... ret:%d\n", ret);
		goto err0;
	}

	//��������
	memcpy(pStu->name, tmpNodeName->pData, tmpNodeName->dataLen);


	//3. ����age
	tmp = headNode->next;
	ret = DER_ItAsn1_ReadInteger(tmp, &pStu->age);
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadInteger failed... ret:%d\n", ret);
		goto err0;
	}

	//4. ����p
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadPrintableString(tmp, &tmpNodeP);	//4.free
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadPrintableString failed... ret:%d\n", ret);
		goto err0;
	}

	//����ռ�
	pStu->p = malloc(tmpNodeP->dataLen + 1);
	if (NULL == pStu->p)
	{
		printf("malloc pStu->p failed....\n");
		goto err0;
	}
	memset(pStu->p, 0, tmpNodeP->dataLen + 1);

	//��������
	memcpy(pStu->p, tmpNodeP->pData, tmpNodeP->dataLen);

	//5. ����pLen
	tmp = tmp->next;
	ret = DER_ItAsn1_ReadInteger(tmp, &pStu->pLen);
	if (0 != ret)
	{
		printf("DER_ItAsn1_ReadInteger failed... ret:%d\n", ret);
		goto err0;
	}

	//6. ����
	*s = pStu;

	//7. �ͷ��ڴ�
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
//�򵥽ṹ���ڴ��ͷź���
int TeacherFreeMem(stu_t **s)
{
	stu_t *pStu = NULL;
	//1. �ݴ��ж�
	if (NULL == s || NULL == *s)
	{
		printf("TeacherFreeMem parameter is invalid...\n");
		return -1;
	}

	pStu = *s;
	//2. �ж�(*s)->p
	if (NULL != pStu->p)
	{
		free(pStu->p);
	}

	//3. �ͷ�(*s)
	free(pStu);

	//4. NULL
	*s = NULL;

	return 0;
}

//�ļ���������
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

	//���뺯������
	unsigned char *outData = NULL;
	int outDataLen = 0;

	//����֮�󴫳�����
	stu_t *pStu = NULL;

	//����һ���ṹ�����, Ȼ������ʼ��
	stu_t s = {
		.name = "������",
		.age = 18,
		.p = "hello world",
		.pLen = 11
	};

	//1. ����
	ret = TeacherEncode(&s, &outData, &outDataLen);
	if (0 != ret)
	{
		printf("TeacherEncode failed.....\n");
		return 1;
	}

	printf("����ɹ�....\n");
	printf("outData: %s outDataLen:%d\n", outData, outDataLen);

	mywritefile(outData, outDataLen);


	//2. ����
	ret = TeacherDecode(outData, outDataLen, &pStu);
	if (0 != ret)
	{
		printf("TeacherDecode failed... ret: %d\n", ret);
		free(outData);
		return 1;
	}
	printf("����ɹ�....\n");

	//3. �ȽϽ��
	if ((s.age == pStu->age) && strcmp(s.name, pStu->name) == 0)
	{
		printf("�����ok....\n");
	}
	else
	{
		printf("�����failed....\n");
	}

	printf("name:%s age:%d p: %s pLen: %d\n", pStu->name, pStu->age, pStu->p, pStu->pLen);

	//4. �ͷ��ڴ�
	TeacherFreeMem(&pStu);

	printf("hello world\n");


	system("pause");
	return 0;
}