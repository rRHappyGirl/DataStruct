#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "dblinklist.h"


DLinkNode* CreateDLinkNode(DLinkNodeType value) {
	DLinkNode* new_node = (DLinkNode*) malloc(sizeof(DLinkNode));
	new_node->data = value;
	new_node->prev = new_node;
	new_node->next = new_node;
	return new_node;
}

void DestroyDLinkNode(DLinkNode* node) {
	free(node);
}

void DLinkListInit(DLinkNode** phead) {
	if(*phead == NULL) {
		//非法输入
		return;
	}
	*phead = CreateDLinkNode(0);
}

void DLinkListPushBack(DLinkNode* head , DLinkNodeType value) {
	if(head == NULL) {
		//非法输入
		return;
	}
	DLinkNode* new_node = CreateDLinkNode(value);
	DLinkNode* tail = head->prev;
	head->prev = new_node;
	new_node->next = head;

	new_node->prev = tail;
	tail->next = new_node;
	return;
}

void DLinkListPopBack(DLinkNode* head) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(head->next == head) {
		//空链表
		return;
	}
	DLinkNode* to_delete = head->prev;
	DLinkNode* prev = to_delete->prev;

	head->prev = prev;
	prev->next = head;
	DestroyDLinkNode(to_delete);
	return;
}

void DLinkListPushFront(DLinkNode* head , DLinkNodeType value) {
	if(head == NULL) {
		//非法输入
		return;
	}
	DLinkNode* new_node = CreateDLinkNode(value);
	DLinkNode* next_node = head->next;

	head->next = new_node;
	new_node->prev = head;

	new_node->next = next_node;
	next_node->prev = new_node;
	return;
}

void DLinkListPopFront(DLinkNode* head) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(head->next == head) {
		//空链表
		return;
	}
	DLinkNode* to_delete = head->next;
	DLinkNode* next_node = to_delete->next;

	head->next = next_node;
	next_node->prev = head;
	DestroyDLinkNode(to_delete);
	return;
}

DLinkNode* DLinkListFind(DLinkNode* head , DLinkNodeType to_find) {
	if(head == NULL) {
		//非法输入
		 return NULL;
	}
	if(head->next == head) {
		return NULL;
	}
	DLinkNode* cur = head->next;
	for(;cur != head ; cur = cur->next) {
		if(cur->data == to_find) {
			return cur;
		}
	}
	return NULL;
}



void DLinkListInsertFront(DLinkNode* head , DLinkNode* pos , DLinkNodeType value) {
	if(head == NULL || pos == NULL) {
		//非法输入
		return;
	}
	DLinkNode* new_node = CreateDLinkNode(value);
	DLinkNode* prev = pos->prev;
	prev->next = new_node;
	new_node->prev = prev;

	new_node->next = pos;
	pos->prev = new_node;
	return;
}

void DLinkListInsertAfter(DLinkNode* head , DLinkNode* pos , DLinkNodeType value) {
	if(head == NULL || pos == NULL) {
		return;
	}
	DLinkNode* new_node = CreateDLinkNode(value);
	DLinkNode* next = pos->next;

	pos->next = new_node;
	new_node->prev = pos;

	new_node->next = next;
	next->prev = new_node;
	return;
}

void DLinkListErase(DLinkNode* head ,DLinkNode* to_delete) {
	if(head == NULL || to_delete == NULL) {
		return;
	}
	if(head->next == head) {
		return;
	}
	DLinkNode* prev = to_delete->prev;
	DLinkNode* next = to_delete->next;

	prev->next = next;
	next->prev = prev;
	return;
}

void DLinkListRemove(DLinkNode* head , DLinkNodeType delete_value) {
	if(head == NULL) {
		return;
	}
	DLinkNode* delete = DLinkListFind(head , delete_value);

	DLinkListErase(head , delete);
	return;

}

//void DLinkListRemoveAll(DLinkNode* head){
//	if(head == NULL){
//		return;
//	}
//	DLinkNode* cur = head;
//	while(cur->next!=head){
//		DLinkListPopFront(head);
//	}
//	return;
//}

void DestroyDLinkList(DLinkNode** phead) {
	if(phead == NULL) {
		return;
	}
	DLinkNode* cur = (*phead)->next;
	while(cur != (*phead)) {
		DLinkNode* next = cur->next;
		DestroyDLinkNode(cur);
		cur = next;
	}
	DestroyDLinkNode(*phead);
	*phead = NULL;
	return;
}

int  DLinkListEmpty(DLinkNode* head){
	if(head == NULL){
		//非法输入
		return 0;
	}
	if(head->next == head){
		//空链表
		return 1;
	}
	else{
		return 0;
	}
}

size_t DLinkListSize(DLinkNode* head){
	if(head == NULL){
		return 0;
	}
	if(head->next == head){
		return 0;
	}
	size_t count = 0;
	DLinkNode* cur = head;
	for(;cur->next != head;cur=cur->next){
		count++;
	}
	return count;
}

/////////////////////////////////////////////////////////
//以下为测试代码
/////////////////////////////////////////////////////////

#include <stdio.h>
#define TEST_HEADER printf("\n==========================%s============================\n",__FUNCTION__)


void DLinkListPrintChar(DLinkNode* head , const char* msg){
	printf("[%s]\n",msg);
	DLinkNode* cur1 = head->next;
	for(;cur1 != head;cur1=cur1->next) {
		printf("[%c|%p] ",cur1->data,cur1);
	}
	printf("\n");
	DLinkNode* cur2 = head->prev;
	for(;cur2 != head;cur2=cur2->prev) {
		printf("[%c|%p] ",cur2->data,cur2);
	}
	printf("\n");
}

void TestInit() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	printf("head expcted not NULL ,actual %p\n",head);
	printf("data expcted 0 , actual %d\n",head->data);
}

void TestPushBack() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');
	
	DLinkListPrintChar(head , "尾插四个元素");
}

void TestPopBack(){
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');
	DLinkListPrintChar(head , "尾插四个元素");

	DLinkListPopBack(head);
	DLinkListPopBack(head);
	DLinkListPrintChar(head , "尾删两个元素");

	DLinkListPopBack(head);
	DLinkListPopBack(head);
	DLinkListPrintChar(head , "再尾删两个元素");

	DLinkListPopBack(head);
	DLinkListPrintChar(head , "尝试对空链表删除");

}

void TestPushFront() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');
	DLinkListPrintChar(head , "尾插四个元素");

	DLinkListPushFront(head , 'x');
	DLinkListPrintChar(head , "头插元素x");

}

void TestPopFront() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPrintChar(head , "尾插两个元素");

	DLinkListPopFront(head);
	DLinkListPrintChar(head , "头删一个元素");

	DLinkListPopFront(head);
	DLinkListPrintChar(head , "再头删一个元素");

	DLinkListPopFront(head);
	DLinkListPrintChar(head , "尝试对空链表删除");
	
}
void TestFind() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');

	DLinkNode* pos_x = DLinkListFind(head, 'x');
	printf("pos_x ecpected NULL ,actual %p\n",pos_x);
	DLinkNode* pos_c = DLinkListFind(head , 'c');
	DLinkNode* poss = head->next->next;
	printf("pos_b expected %p , actual %p\n",poss->next , pos_c);
	printf("pos_b expcted %c,actual %c\n",head->next->next->next->data,pos_c->data);
}
void TestInsertFront(){
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');

	DLinkNode* pos = DLinkListFind(head , 'b');
	DLinkListInsertFront(head , pos , 'x');
	DLinkListPrintChar(head, "在 b 之前插入 x ");

}
void TestInsertAfter() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');

	DLinkNode* pos = DLinkListFind(head , 'b');
	DLinkListInsertAfter(head , pos,'x');
	DLinkListPrintChar(head, "在b之后插入x");

}
void TestErase() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');

	DLinkNode* pos = DLinkListFind(head , 'b');
	DLinkListErase(head , pos);
	DLinkListPrintChar(head , "删除pos位置的元素");

}

void TestRemove() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');

	DLinkListRemove(head ,'b');
	DLinkListPrintChar(head , "删除元素b");

}

//void TestRemoveAll(){
//	TEST_HEADER;
//	DLinkNode* head;
//	DLinkListInit(&head);
//	DLinkListPushBack(head , 'a');
//	DLinkListPushBack(head , 'b');
//	DLinkListPushBack(head , 'c');
//	DLinkListPushBack(head , 'd');
//	DLinkListPushBack(head , 'b');
//
//	DLinkListRemoveAll(head);
//	DLinkListPrintChar(head , "删除所有元素b");
//}

void TestDestroyDLinkList() {
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPushBack(head , 'c');
	DLinkListPushBack(head , 'd');

	DestroyDLinkList(&head);
}

void TestEmpty(){
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');
	DLinkListPrintChar(head , "插入两个元素");

	int ret1 = DLinkListEmpty(head);
	printf("ret1 ecpected 0,actual %d\n",ret1);
	DLinkListPopFront(head);
	DLinkListPopFront(head);
	DLinkListPrintChar(head,"删除两个元素");
	int ret2 = DLinkListEmpty(head);
	printf("ret2 expected 1,actual %d\n",ret2);
}
void TestSize(){
	TEST_HEADER;
	DLinkNode* head;
	DLinkListInit(&head);
	DLinkListPushBack(head , 'a');
	DLinkListPushBack(head , 'b');

	size_t ret = DLinkListSize(head);
	printf("ret ecpected 2,actual %d\n",ret);

	DLinkListPopFront(head);
	DLinkListPopFront(head);
	size_t ret1 = DLinkListSize(head);
	printf("ret1 expected 0,actual %d\n",ret1);
}
int main() {
	TestInit();
	TestPushBack();
	TestPopBack();
	TestPushFront();
	TestPopFront();
	TestFind();
	TestInsertFront();
	TestInsertAfter();
	TestErase();
	TestRemove();
	TestDestroyDLinkList();
	TestEmpty();
	TestSize();
//	TestRemoveAll();
	return 0;
}






