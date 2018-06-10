#pragma once
#include <stdlib.h>


typedef char LinkNodeType;

typedef struct LinkNode {
	LinkNodeType data;
	struct LinkNode* next;
}LinkNode;

//初始化链表
void  LinkListInit (LinkNode** node);

//创建结点
LinkNode* CreateNode(LinkNodeType value);

//销毁节点
void DestroyNode(LinkNode*);

//链表尾部插入一个元素
//**是因为当链表为空链表是需要修改头节点
void LinkListPushBack(LinkNode** head , LinkNodeType value);

//删除链表尾部元素
void LinkListPopBack(LinkNode** head );

//头插
void LinkListPushFront(LinkNode** head ,LinkNodeType value);
//头删
void LinkListPopFront(LinkNode** head );

//在Pos之后插入一个结点
void LinkListInsertAfter(LinkNode* head ,LinkNode* pos ,LinkNodeType value);
//在pos之前插入一个结点
void LinkListInsertBefore(LinkNode** head ,LinkNode* pos, LinkNodeType value);

//查找任意位置的节点
LinkNode* LinkListFind(LinkNode* head , LinkNodeType pos);

//删除指定位置的元素
void LinkListErase(LinkNode** head,LinkNode* pos);
//删除指定值的元素
void LinkListRemove(LinkNode** head,LinkNodeType value);
//指定值的所有元素都删掉
void LinkListRemoveAll(LinkNode** head ,LinkNodeType value);

//判空链表，如果为空，返回1，否则返回0
int LinkListEmpty(LinkNode* head);

//求链表的长度
int LinkListSize(LinkNode* head);


//逆置链表
void LinkListReverse(LinkNode** head);
void LinkListReverse2(LinkNode** head);

//约瑟夫环的实现
LinkNode* JosephCircle(LinkNode* head , int M);

//冒泡
void LinkListBubbleSort(LinkNode* head);


//合并两个有序链表
LinkNode* LinkListMerge(LinkNode* head1 , LinkNode* head2);

//查找中间元素
LinkNode* LinkListFindMidNode(LinkNode* head);


//查找倒数第k个结点
LinkNode* LinkListFindLastKNode(LinkNode* head , size_t K);

//删除倒数第K个结点
void LinkListEraseLastKNode(LinkNode** head , size_t K);

//判断链表是否带环,带环返回1
LinkNode* LinkListHasCycle(LinkNode* head);


//求环的长度
size_t LinkListCycleLen(LinkNode* head);


//求环的入口点
LinkNode* LinkListCycleEntry (LinkNode* head);

//不遍历链表删除单链表的非尾结点
void LinkListEraseNotLast(LinkNode** head,LinkNode* pos);

//逆序打印
void LinkListReversePrint(LinkNode* head);

//不遍历链表在一个结点前插入一个结点
void LinkListInsertBefore2(LinkNode* head , LinkNode* pos , LinkNodeType value);


//两个链表不带环，判断是否相交，求交点
LinkNode* LinkListHasCross(LinkNode* head1,LinkNode* head2 );
//可能带环的两个链表，判断是否相交，求交点
int LinkListHasCrossWithCycle(LinkNode* head1 ,LinkNode* head2);
LinkNode* LinkListHasCrossWithCyclePos(LinkNode* head1 ,LinkNode* head2);

//求交集
LinkNode* LinkListUnionSet(LinkNode* head1,LinkNode* head2);

//复杂链表的复制

