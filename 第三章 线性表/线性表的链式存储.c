#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// ����ʹ�� OK ERROR ������������ int ���͵ĺ�������ֵ��ʹ�ɶ��Ը�ǿ����ֱ��
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 // ����ռ��ʼ������

typedef int Status; // Status �Ǻ��������ͣ���ֵ�Ǻ������״̬���룬�� OK ��
typedef int ElemType; // ElemType ���͸���ʵ������������������Ϊ int

// ��ʼ�����Ա����ʽ����ṹ
typedef struct Node
{
	ElemType data; // ������
	struct Node *next; // ָ����
}Node;
typedef struct Node *LinkList; // ����LinkList

// ��ʼ����ʽ���Ա�
Status InitList(LinkList *L) 
{ 
	*L = (LinkList)malloc(sizeof(Node)); // ����ͷ��㣬��ʹLָ���ͷ���
	if(!(*L)) // �洢����ʧ��(���������ܹ�)
		return ERROR;
	(*L)->next = NULL; // ָ����Ϊ��
	
	return OK;
}

// ��LΪ�ձ��򷵻�TRUE�����򷵻�FALSE
Status ListEmpty(LinkList L)
{ 
	if(L->next) // ���ͷ�ڵ��nextָ��ָ��Ĳ�ΪNULL����˵��������Ϊ�գ���֮Ϊ��
		return FALSE;
	else
		return TRUE;
}

// ��L����Ϊ�ձ�
Status ClearList(LinkList *L)
{ 
	LinkList p, q;
	p = (*L)->next; // pָ���һ�����
	while(p) // ������pָ����ΪNULL����û����β
	{
		q = p->next; // �Ͱ�q��ֵΪp����һ�����
		free(p); // ���ͷ�p
		p = q; // ���ð�q��ֵ��p
	}
	(*L)->next = NULL; // ͷ���ָ����Ϊ��
	
	return OK;
}

// ����L������Ԫ�ظ���
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; // pָ���һ�����
	while(p)                        
	{
		i ++;
		p = p->next; // ���ϱ���
	}
	return i; // ���ؽ�����
}

// ��L�е�i������Ԫ�ص�ֵ��ֵ��e����������1(OK)����i��Ԫ�ز����ڣ��򷵻�0(ERROR)
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p; // ����һָ��p
	p = L->next; // ��pָ������L�ĵ�һ�����
	j = 1; // jΪ������
	while (p && j < i) // p��ΪNULL �� ������j��û�е���iʱ��ѭ������
	{   
		p = p->next; // ��pָ����һ�����
		j ++;
	}
	
   /* ����ԭ����Ϊ if (!p || j > i) ������ԭ���߿�֤��j > i �Ĳ������������ɾȥ
	* ����whileѭ���������� pָ��NULL ���� j == i ������Ӧû�ҵ����ҵ�����״̬
    * �����ں���if�ж��У�����ֻҪ�ж� p�Ƿ�ָ��NULL ����֪�������Ƿ��ҵ���iλ���ϵ�ֵ
    * ��Ϊ j �����ֵҲ�������i
	*/ 
	if (!p) // ������pΪNULL�����������˱�β����û�ҵ�i
		return ERROR; // ��˵����i��Ԫ�ز����ڣ�����ERROR
	*e = p->data; // ����ѵ�i��Ԫ�ظ�ֵe
	
	return OK;
}

// ����L�е�1������e������Ԫ�ص�λ��������������Ԫ�ز����ڣ��򷵻�ֵΪ0
int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next; // ָ��pָ���һ�����
	while(p) // ��ָ��p��ΪNULL
	{
		i ++;
		if(p->data == e) // �ҵ�����������Ԫ��
			return i; // ����λ��
		p = p->next;
	}
	
	return 0;
}


// ��L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1
Status ListInsert(LinkList *L, int i, ElemType e)
{ 
	int j;
	LinkList p, s;
	p = *L;   
	j = 1;
	while (p && j < i) // Ѱ�ҵ�i�����
	{
		p = p->next;
		j ++;
	} 
	
	// ����ͬ��86�е���90��
	if (!p) 
		return ERROR; // λ��i������
	s = (LinkList)malloc(sizeof(Node)); // �����½��(C���Ա�׼����)
	s->data = e;  
	s->next = p->next; // ��p�ĺ�̽�㸳ֵ��s�ĺ�̽��
	p->next = s; // ��s��ֵ��p�ĺ�̽��
	
	return OK;
}

// ��L�е�i������Ԫ��ɾ����������ֵ��ֵ��e����������1(OK)������i��Ԫ�ز����ڣ��򷵻�0(ERROR)
Status ListDelete(LinkList *L, int i, ElemType *e) 
{ 
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next && j < i)
	{
		p = p->next;
		j ++;
	}
	if (!(p->next)) 
		return ERROR; // λ��i������
	q = p->next;
	p->next = q->next; // ��q�ĺ�̽�㸳ֵ��p�ĺ�̽��
	*e = q->data; // ��q����е����ݸ�ֵ��e
	free(q); // ��ϵͳ���մ˽�㣬�ͷ��ڴ�
	
	return OK;
}

// ���ζ�L��ÿ������Ԫ�����
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;
	while(p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n\n");
	
	return OK;
}

// �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��ͷ�巨��
void CreateListHead(LinkList *L, int n) 
{
	LinkList p;
	int i;
	srand(time(0)); // ��ʼ�����������
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL; // �Ƚ���һ����ͷ���ĵ�����
	for (i = 0;i < n;i ++) 
	{
		p = (LinkList)malloc(sizeof(Node)); // �����½��
		p->data = rand()%100 + 1; // �������1~100֮�������
		p->next = (*L)->next;    
		(*L)->next = p; // ���뵽��ͷ
	}
}

// �������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L��β�巨��
void CreateListTail(LinkList *L, int n) 
{
	LinkList p, r;
	int i;
	srand(time(0)); // ��ʼ�����������
	*L = (LinkList)malloc(sizeof(Node)); // LΪ�������Ա�
	r = *L; // rΪָ��β���Ľ��
	for (i = 0;i < n;i ++) 
	{
		p = (Node *)malloc(sizeof(Node)); // �����½��
		p->data = rand()%100 + 1; // �������1~100֮�������
		r->next = p; // ����β�ն˽���ָ��ָ���½��
		r = p; // ����ǰ���½�㶨��Ϊ��β�ն˽��
	}
	r->next = NULL; // ��ʾ��ǰ�������
}

int main()
{        
	// ����һ����ʽ��������Ա�L
	LinkList L;
	
	// ����һ�� ElemType(int) ���͵ı���e
	ElemType e;
	
	// ����һ�����溯������ֵ�� ElemType(int) ���͵ı���
	Status i;

	i = InitList(&L);
	printf("��ʼ�������Ա�ĳ���Ϊ%d\n\n", ListLength(L));
	
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);
	
	for(int j = 1;j <= 5;j ++)
		i = ListInsert(&L, 1, j);
	GetElem(L, 5, &e);
	printf("��L�ı�ͷ���β���1��5�󣺱�ͷԪ��Ϊ%d����βԪ��Ϊ%d�����Ա���Ϊ��%d\n\n",
		L->next->data, e, ListLength(L));
	
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L);
	
	i = ClearList(&L);
	printf("���L�����Ա���Ϊ%d\n\n", ListLength(L));
	i = ListEmpty(L);
	printf("���Ա��Ƿ�Ϊ�գ�(1Ϊ�գ�0Ϊ����)��%d\n\n", i);
	
	for(int j = 1;j <= 5;j ++)
		ListInsert(&L, j, j);
	GetElem(L, 5, &e);
	printf("��L�ı�β���β���1��5�󣺱�ͷԪ��Ϊ%d����βԪ��Ϊ%d�����Ա���Ϊ��%d\n\n",
		L->next->data, e, ListLength(L));
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L);
	
	ListInsert(&L, 1, 0);
	printf("��L�ı�ͷ����0��");
	printf("�������L��Ԫ�أ�");
	ListTraverse(L);
	
	GetElem(L, 3, &e);
	printf("��3��Ԫ�ص�ֵΪ��%d\n", e);
	
	ListDelete(&L, 4, &e); // ɾ����4������ 
	printf("ɾ����%d����Ԫ��ֵΪ��%d\n", 4, e);
	
	printf("�������L��Ԫ�أ�");
	ListTraverse(L);
	
	i = ClearList(&L);
	printf("���L�����Ա�ĳ���Ϊ%d\n\n", ListLength(L));
	CreateListHead(&L, 20);
	printf("�����������L��Ԫ��(ͷ�巨)��");
	ListTraverse(L); 
	
	i = ClearList(&L);
	printf("���L�����Ա�ĳ���Ϊ%d\n\n", ListLength(L));
	CreateListTail(&L, 20);
	printf("�����������L��Ԫ��(β�巨)��");
	ListTraverse(L); 
	
	return 0;
}

