#include <stdio.h>
#include <stdlib.h>
#include "LinkQueue.h"

LinkQueueNode* CreateNode(LinkQueueType value){
	LinkQueueNode* new_node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if(new_node == NULL){
		//申请内存失败
		printf("error\n");
		exit(-1);
	}
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}

void LinkQueueInit(LinkQueue* q){
	if(q == NULL){
		//非法输入
		return;
	}
	q->head = NULL;
	q->tail = NULL;
	return;
}

void LinkQueueDestroy(LinkQueue* q){
	if(q == NULL){
		return;
	}
	//循环释放链表结点
	LinkQueueNode* cur = q->head->next;
	while(cur!=NULL){
		LinkQueueNode* to_delete = cur;
		free(to_delete);
		cur = cur->next;
	}
	return;
}

void LinkQueuePush(LinkQueue* q,LinkQueueType value){
	if(q == NULL){
		return;
	}
	LinkQueueNode* new_node = CreateNode(value);
	if(q->head == NULL){
		//空队列
		q->head = q->tail = new_node;
	}
	//将新结点插入到尾指针之后，并更新尾指针
	q->tail->next = new_node;
	q->tail = new_node;
	q->tail->next = NULL;
	return;
}

void LinkQueuePop(LinkQueue* q){
	if(q == NULL){
		return;
	}
	if(q->head == NULL){
		//空队列
		return;
	}
	LinkQueueNode* cur = q->head;
	q->head = cur->next;
	free(cur);
	cur = NULL;
	return;
}

int LinkQueueFront(LinkQueue* q,LinkQueueType* value){
	if(q == NULL || value == NULL){
		return 0;
	}
	if(q->head == NULL){
		return 0;
	}
	*value = q->head->data;
	return 1;
}

///////////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////////
#define TEST_HEADER printf("\n===================================%s=================================\n",__FUNCTION__)

void LinkQueuePrintChar(LinkQueue* q,const char* msg){
	printf("[%s]\n",msg);
	LinkQueueNode* cur = q->head;
	for(;cur!=NULL;cur=cur->next){
		printf("[%c] ",cur->data);
	}
	printf("\n");
}
void TestLinkQueue(){
	TEST_HEADER;
	LinkQueue queue;
	LinkQueueInit(&queue);
	LinkQueuePush(&queue,'a');
	LinkQueuePush(&queue,'b');
	LinkQueuePush(&queue,'c');
	LinkQueuePush(&queue,'d');

	LinkQueuePrintChar(&queue,"入队列四个元素");

	LinkQueueType value;
	int ret = LinkQueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);

	LinkQueuePop(&queue);
	LinkQueuePop(&queue);
	LinkQueuePrintChar(&queue,"出队列两个元素");
	LinkQueuePop(&queue);
	LinkQueuePop(&queue);
	LinkQueuePrintChar(&queue,"再出队列两个元素");
	LinkQueuePop(&queue);
	LinkQueuePrintChar(&queue,"尝试对空队列出队列");

}

int main(){
	TestLinkQueue();
	return 0;
}








