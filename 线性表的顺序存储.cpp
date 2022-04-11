#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 书中使用 OK ERROR 等文字来代替 int 类型的函数返回值，使可读性更强，更直观
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 // 储存空间初始分配量

typedef int Status; // Status 是函数的类型，其值是函数结果状态代码，如 OK 等
typedef int ElemType; // ElemType 类型根据实际情况而定，这里假设为 int

// 初始化线性表的顺序储存的结构体
typedef struct
{
	ElemType data[MAXSIZE]; // 数组储存数据元素，最大值为MAXSIZE
	int length; // 线性表当前长度
}SqList;

// 返回线性表长度
Status ListLength(SqList L)
{
	return L.length;
}

// 初始化顺序线性表
Status InitList(SqList *L) 
{ 
	L->length = 0;
	return OK;
}

// 将L中第i个数据元素的值赋值给e，函数返回1(OK)，若L长度为0或i位置不合法，则返回0(ERROR)
// 注意i是指位置，第1个位置的数组下标是从0开始
Status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i < 1 || i > L.length)
		return ERROR;
	*e = L.data[i - 1];
	return OK;
}

// 在L中第i个位置之前插入新的数据元素e，L的长度加1
Status ListInsert(SqList *L, int i, ElemType e)
{ 
	int k;
	if (L->length == MAXSIZE) // 顺序存储的线性表已满
		return ERROR;
	if (i < 1 || i > L->length + 1) // e的插入位置i不合法，e可以插在 1~L->length+1 的位置
		return ERROR;
	
	// 原代码中这里有一处判断插入位置是否是表尾，即判断插入位置i是否是 L->length + 1 的代码 
	// 但是这段代码可以将其删去，因为不必特判插入位置是否为表尾，不是表尾才执行for循环中内容
	// 因为若插入位置 i 为 L->length + 1，不满足for循环中判断条件，下面for循环中内容不会执行
	for(k = L->length - 1;k >= i - 1;k --) // 将要插入位置之后的数据元素向后移动一位
		L->data[k + 1] = L->data[k];

	// 将新元素插入特地空出来的位置，其实这里的值还是L->data[i-1]的值，只不过我们在L->data[i]中存储了它的值
	// 而L->data[i]的值已经在L->data[i + 1]中储存了，以此类推，我们空出来了L->data[i-1]的位置储存e
	L->data[i - 1] = e; 
	L->length ++; // 线性表长度加1
	
	return OK;
}

// 将L中第i个数据元素删除，并将它的值赋值给e，函数返回1(OK)，若L长度为0或i位置不合法，则返回0(ERROR)
Status ListDelete(SqList *L,int i,ElemType *e) 
{ 
	int k;
	if (L->length == 0) // 线性表为空
		return ERROR;
	if (i < 1 || i > L->length) // 删除位置不正确
		return ERROR;
	
	*e = L->data[i - 1];
	for(k = i;k < L->length;k ++) // 将删除位置后继元素前移
		L->data[k - 1] = L->data[k];

	L->length --; // 线性表的长度减1
	
	return OK;
}

// 若L为空表，则返回TRUE，否则返回FALSE
Status ListEmpty(SqList L)
{ 
	if(L.length == 0)
		return TRUE;
	else 
		return FALSE;
}

// 将L重置为空表
Status ClearList(SqList *L)
{ 
	L->length = 0;
	return OK;
}

// 依次对L的每个数据元素输出
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
	// 声明一个顺序存储的线性表L
	SqList L;
	
	// 声明一个 ElemType(int) 类型的变量e
	ElemType e;
	
	// 声明一个储存函数返回值的 ElemType(int) 类型的变量
	Status i;
	
	i = InitList(&L);
	printf("初始化线性表的长度为%d\n\n", L.length);
	
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);
	
	for(int j = 1;j <= 8;j ++)
		i = ListInsert(&L, 1, j);
	printf("在L的表头依次插入1～8后：表头元素为%d，表尾元素为%d，线性表长度为：%d\n\n", 
		L.data[0], L.data[7], L.length);
	
	printf("依次输出L的元素：");
	ListTraverse(L); 
	
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);

	i = ClearList(&L);
	printf("清空L后：线性表长度为%d\n\n", L.length);
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);
	
	printf("依次输出L的元素：");
	ListTraverse(L); 
	
	for(int j = 1;j <= 8;j ++)
		i = ListInsert(&L, j, j);
	printf("在L的表尾依次插入1～8后：表头元素为%d，表尾元素为%d，线性表长度为：%d\n\n", 
		L.data[0], L.data[7], L.length);
	
	printf("依次输出L的元素：");
	ListTraverse(L); 
	
	i = ListEmpty(L);
	printf("线性表是否为空？(1为空，0为不空)：%d\n\n", i);
	
	GetElem(L, 5, &e);
	printf("第5个元素的值为：%d\n\n", e);
	
	i = ListDelete(&L, 3, &e); // 删除第三个元素
	printf("删除的第%d个的元素值为：%d\n\n", 3, e);
	
	GetElem(L, 5, &e);
	printf("第5个元素的值为：%d\n\n", e);
	
	printf("依次输出L的元素：");
	ListTraverse(L); 
	
	return 0;
}
