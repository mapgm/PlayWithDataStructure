#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// ����ʹ�� OK ERROR ������������ int ���͵ĺ�������ֵ��ʹ�ɶ��Ը�ǿ����ֱ��
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 // ����ռ��ʼ������

typedef int Status; // Status �Ǻ��������ͣ���ֵ�Ǻ������״̬���룬�� OK ��
typedef int ElemType; // ElemType ���͸���ʵ������������������Ϊ int

// ��ʼ�����Ա��˳�򴢴�Ľṹ��
typedef struct
{
	ElemType data[MAXSIZE]; // ���鴢������Ԫ�أ����ֵΪMAXSIZE
	int length; // ���Ա�ǰ����
}SqList;

// �������Ա���
Status ListLength(SqList L)
{
	return L.length;
}

// ��ʼ��˳�����Ա�
Status InitList(SqList *L) 
{ 
	L->length = 0;
	return OK;
}

// ��L�е�i������Ԫ�ص�ֵ��ֵ��e����������1(OK)����L����Ϊ0��iλ�ò��Ϸ����򷵻�0(ERROR)
// ע��i��ָλ�ã���1��λ�õ������±��Ǵ�0��ʼ
Status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i < 1 || i > L.length)
		return ERROR;
	*e = L.data[i - 1];
	return OK;
}

// ��L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1
Status ListInsert(SqList *L, int i, ElemType e)
{ 
	int k;
	if (L->length == MAXSIZE) // ˳��洢�����Ա�����
		return ERROR;
	if (i < 1 || i > L->length + 1) // e�Ĳ���λ��i���Ϸ���e���Բ��� 1~L->length+1 ��λ��
		return ERROR;
	
	// ԭ������������һ���жϲ���λ���Ƿ��Ǳ�β�����жϲ���λ��i�Ƿ��� L->length + 1 �Ĵ��� 
	// ������δ�����Խ���ɾȥ����Ϊ�������в���λ���Ƿ�Ϊ��β�����Ǳ�β��ִ��forѭ��������
	// ��Ϊ������λ�� i Ϊ L->length + 1��������forѭ�����ж�����������forѭ�������ݲ���ִ��
	for(k = L->length - 1;k >= i - 1;k --) // ��Ҫ����λ��֮�������Ԫ������ƶ�һλ
		L->data[k + 1] = L->data[k];

	// ����Ԫ�ز����صؿճ�����λ�ã���ʵ�����ֵ����L->data[i-1]��ֵ��ֻ����������L->data[i]�д洢������ֵ
	// ��L->data[i]��ֵ�Ѿ���L->data[i + 1]�д����ˣ��Դ����ƣ����ǿճ�����L->data[i-1]��λ�ô���e
	L->data[i - 1] = e; 
	L->length ++; // ���Ա��ȼ�1
	
	return OK;
}

// ��L�е�i������Ԫ��ɾ������������ֵ��ֵ��e����������1(OK)����L����Ϊ0��iλ�ò��Ϸ����򷵻�0(ERROR)
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
	int k;
	if (L->length == 0) // ���Ա�Ϊ��
		return ERROR;
	if (i < 1 || i > L->length) // ɾ��λ�ò���ȷ
		return ERROR;
	
	*e = L->data[i - 1];
	for(k = i;k < L->length;k ++) // ��ɾ��λ�ú��Ԫ��ǰ��
		L->data[k - 1] = L->data[k];

	L->length --; // ���Ա�ĳ��ȼ�1
	
	return OK;
}

// ��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
Status ListEmpty(SqList L)
{ 
	if(L.length == 0)
		return TRUE;
	else 
		return FALSE;
}

// ��L����Ϊ�ձ�
Status ClearList(SqList *L)
{ 
	L->length = 0;
	return OK;
}

// ���ζ�L��ÿ������Ԫ�����
Status ListTraverse(SqList L)
{
	int i;
	for(i = 0;i < L.length;i ++)
		printf("%d ", L.data[i]);
	printf("\n\n");
	
	return OK;
}

int main()
{
	// ����һ��˳��洢�����Ա�L
	SqList L;
	
	// ����һ�� ElemType(int) ���͵ı���e
	ElemType e;
	
	// ����һ�����溯������ֵ�� ElemType(int) ���͵ı���
	Status i;
	
	i = InitList(&L);
	printf("��ʼ�����Ա�ĳ���Ϊ%d\n\n", L.length);
	
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);
	
	for(int j = 1;j <= 8;j ++)
		i = ListInsert(&L, 1, j);
	printf("��L�ı�ͷ���β���1��8�󣺱�ͷԪ��Ϊ%d����βԪ��Ϊ%d�����Ա���Ϊ��%d\n\n", 
		L.data[0], L.data[7], L.length);
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L); 
	
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);

	i = ClearList(&L);
	printf("���L�����Ա���Ϊ%d\n\n", L.length);
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L); 
	
	for(int j = 1;j <= 8;j ++)
		i = ListInsert(&L, j, j);
	printf("��L�ı�β���β���1��8�󣺱�ͷԪ��Ϊ%d����βԪ��Ϊ%d�����Ա���Ϊ��%d\n\n", 
		L.data[0], L.data[7], L.length);
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L); 
	
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);
	
	GetElem(L, 5, &e);
	printf("��5��Ԫ�ص�ֵΪ��%d\n\n", e);
	
	i = ListDelete(&L, 3, &e); // ɾ��������Ԫ��
	printf("ɾ���ĵ�%d����Ԫ��ֵΪ��%d\n\n", 3, e);
	
	GetElem(L, 5, &e);
	printf("��5��Ԫ�ص�ֵΪ��%d\n\n", e);
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L); 
	
	return 0;
}
