#pragma once 

typedef char DLinkNodeType;

typedef struct DLinkNode{
	DLinkNodeType data;
	struct DLinkNode* prev;
	struct DLinkNode* next;
}DLinkNode;

//初始化
void DLinkListInit(DLinkNode** phead);

//查找
DLinkNode* DLinkListFind(DLinkNode* head  , DLinkNodeType to_find);

//尾插
void DLinkListPushBack(DLinkNode* head,DLinkNodeType value);

//尾删
void DLinkListPopBack(DLinkNode* head);

//头插
void DLinkListPushFront(DLinkNode* head,DLinkNodeType value);

//头删
void DLinkListPopFront(DLinkNode* head);

//在pos 之前插入一个元素
void DLinkListInsertFront(DLinkNode* head , DLinkNode* pos , DLinkNodeType value);

//在pos之后插入一个元素
void DLinkListInsertAfter(DLinkNode* head, DLinkNode* pos , DLinkNodeType value);

//删除to_delete位置的元素
void DLinkListErase(DLinkNode* head , DLinkNode* to_delete);

//删除delete_value值，按照值来删
void DLinkListRemove(DLinkNode* head , DLinkNodeType delete_value);
void DLinkListRemoveAll(DLinkNode* head);


//销毁双向链表
//因为要修改头指针使之指向空，不然销毁链表后head将变为野指针
void DestroyDLinkList(DLinkNode** phead);
//判空
int DLinkListEmpty(DLinkNode* head);

//求大小
size_t DLinkListSize(DLinkNode* head);
