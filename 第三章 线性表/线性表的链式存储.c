#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// 书中使用 OK ERROR 等文字来代替 int 类型的函数返回值，使可读性更强，更直观
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 // 储存空间初始分配量

typedef int Status; // Status 是函数的类型，其值是函数结果状态代码，如 OK 等
typedef int ElemType; // ElemType 类型根据实际情况而定，这里假设为 int

// 初始化线性表的链式储存结构
typedef struct Node
{
	ElemType data; // 数据域
	struct Node *next; // 指针域
}Node;
typedef struct Node *LinkList; // 定义LinkList

// 初始化链式线性表
Status InitList(LinkList *L) 
{ 
	*L = (LinkList)malloc(sizeof(Node)); // 产生头结点，并使L指向此头结点
	if(!(*L)) // 存储分配失败(基本不可能哈)
		return ERROR;
	(*L)->next = NULL; // 指针域为空
	
	return OK;
}

// 若L为空表，则返回TRUE，否则返回FALSE
Status ListEmpty(LinkList L)
{ 
	if(L->next) // 如果头节点的next指针指向的不为NULL，则说明此链表不为空，反之为空
		return FALSE;
	else
		return TRUE;
}

// 将L重置为空表
Status ClearList(LinkList *L)
{ 
	LinkList p, q;
	p = (*L)->next; // p指向第一个结点
	while(p) // 如果结点p指针域不为NULL，即没到表尾
	{
		q = p->next; // 就把q赋值为p的下一个结点
		free(p); // 再释放p
		p = q; // 再让把q赋值给p
	}
	(*L)->next = NULL; // 头结点指针域为空
	
	return OK;
}

// 返回L中数据元素个数
int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next; // p指向第一个结点
	while(p)                        
	{
		i ++;
		p = p->next; // 不断遍历
	}
	return i; // 返回结点个数
}

// 将L中第i个数据元素的值赋值给e，函数返回1(OK)，第i个元素不存在，则返回0(ERROR)
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j;
	LinkList p; // 声明一指针p
	p = L->next; // 让p指向链表L的第一个结点
	j = 1; // j为计数器
	while (p && j < i) // p不为NULL 且 计数器j还没有等于i时，循环继续
	{   
		p = p->next; // 让p指向下一个结点
		j ++;
	}
	
   /* 这里原代码为 if (!p || j > i) ，经向原作者考证，j > i 的部分无意义可以删去
	* 跳出while循环的条件是 p指向NULL 或者 j == i ，即对应没找到和找到两种状态
    * 所以在后续if判断中，我们只要判断 p是否指向NULL 即可知道我们是否找到了i位置上的值
    * 因为 j 的最大值也不会大于i
	*/ 
	if (!p) // 如果结点p为NULL，即遍历到了表尾还是没找到i
		return ERROR; // 就说明第i个元素不存在，返回ERROR
	*e = p->data; // 否则把第i个元素赋值e
	
	return OK;
}

// 返回L中第1个等于e的数据元素的位序，若这样的数据元素不存在，则返回值为0
int LocateElem(LinkList L, ElemType e)
{
	int i = 0;
	LinkList p = L->next; // 指针p指向第一个结点
	while(p) // 若指针p不为NULL
	{
		i ++;
		if(p->data == e) // 找到这样的数据元素
			return i; // 返回位序
		p = p->next;
	}
	
	return 0;
}


// 在L中第i个位置之前插入新的数据元素e，L的长度加1
Status ListInsert(LinkList *L, int i, ElemType e)
{ 
	int j;
	LinkList p, s;
	p = *L;   
	j = 1;
	while (p && j < i) // 寻找第i个结点
	{
		p = p->next;
		j ++;
	} 
	
	// 这里同第86行到第90行
	if (!p) 
		return ERROR; // 位置i不存在
	s = (LinkList)malloc(sizeof(Node)); // 生成新结点(C语言标准函数)
	s->data = e;  
	s->next = p->next; // 将p的后继结点赋值给s的后继结点
	p->next = s; // 将s赋值给p的后继结点
	
	return OK;
}

// 将L中第i个数据元素删除，并将其值赋值给e，函数返回1(OK)，若第i个元素不存在，则返回0(ERROR)
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
		return ERROR; // 位置i不存在
	q = p->next;
	p->next = q->next; // 将q的后继结点赋值给p的后继结点
	*e = q->data; // 将q结点中的数据赋值给e
	free(q); // 让系统回收此结点，释放内存
	
	return OK;
}

// 依次对L的每个数据元素输出
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

// 随机产生n个元素的值，建立带表头结点的单链线性表L（头插法）
void CreateListHead(LinkList *L, int n) 
{
	LinkList p;
	int i;
	srand(time(0)); // 初始化随机数种子
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL; // 先建立一个带头结点的单链表
	for (i = 0;i < n;i ++) 
	{
		p = (LinkList)malloc(sizeof(Node)); // 生成新结点
		p->data = rand()%100 + 1; // 随机生成1~100之间的数字
		p->next = (*L)->next;    
		(*L)->next = p; // 插入到表头
	}
}

// 随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法）
void CreateListTail(LinkList *L, int n) 
{
	LinkList p, r;
	int i;
	srand(time(0)); // 初始化随机数种子
	*L = (LinkList)malloc(sizeof(Node)); // L为整个线性表
	r = *L; // r为指向尾部的结点
	for (i = 0;i < n;i ++) 
	{
		p = (Node *)malloc(sizeof(Node)); // 生成新结点
		p->data = rand()%100 + 1; // 随机生成1~100之间的数字
		r->next = p; // 将表尾终端结点的指针指向新结点
		r = p; // 将当前的新结点定义为表尾终端结点
	}
	r->next = NULL; // 表示当前链表结束
}

int main()
{        
	// 声明一个链式储存的线性表L
	LinkList L;
	
	// 声明一个 ElemType(int) 类型的变量e
	ElemType e;
	
	// 声明一个储存函数返回值的 ElemType(int) 类型的变量
	Status i;

	i = InitList(&L);
	printf("初始化后线性表的长度为%d\n\n", ListLength(L));
	
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);
	
	for(int j = 1;j <= 5;j ++)
		i = ListInsert(&L, 1, j);
	GetElem(L, 5, &e);
	printf("在L的表头依次插入1～5后：表头元素为%d，表尾元素为%d，线性表长度为：%d\n\n",
		L->next->data, e, ListLength(L));
	
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);
	
	printf("依次输出L的元素：");
	ListTraverse(L);
	
	i = ClearList(&L);
	printf("清空L后：线性表长度为%d\n\n", ListLength(L));
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);
	
	for(int j = 1;j <= 5;j ++)
		ListInsert(&L, j, j);
	GetElem(L, 5, &e);
	printf("在L的表尾依次插入1～5后：表头元素为%d，表尾元素为%d，线性表长度为：%d\n\n",
		L->next->data, e, ListLength(L));
	
	printf("依次输出L的元素：");
	ListTraverse(L);
	
	ListInsert(&L, 1, 0);
	printf("在L的表头插入0后");
	printf("依次输出L的元素：");
	ListTraverse(L);
	
	GetElem(L, 3, &e);
	printf("第3个元素的值为：%d\n", e);
	
	ListDelete(&L, 4, &e); // 删除第4个数据 
	printf("删除第%d个的元素值为：%d\n", 4, e);
	
	printf("依次输出L的元素：");
	ListTraverse(L);
	
	i = ClearList(&L);
	printf("清空L后，线性表的长度为%d\n\n", ListLength(L));
	CreateListHead(&L, 20);
	printf("整体随机创建L的元素(头插法)：");
	ListTraverse(L); 
	
	i = ClearList(&L);
	printf("清空L后，线性表的长度为%d\n\n", ListLength(L));
	CreateListTail(&L, 20);
	printf("整体随机创建L的元素(尾插法)：");
	ListTraverse(L); 
	
	return 0;
}

