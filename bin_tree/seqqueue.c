#include <stdio.h>
#include <stdlib.h>
#include "seqqueue.h"

void SeqQueueInit(SeqQueue* q){
	if(q == NULL){
		//非法输入
		return;
	}
	q->size = 0;
	q->head = 0;
	q->tail = 0;
	return;
}

void SeqQueueDestroy(SeqQueue* q){
	if(q ==	NULL){
		return;
	}
	q->size = 0;
	q->head = 0;
	q->tail = 0;
	return;
}

void SeqQueuePush(SeqQueue* q,SeqQueueType value){
	if(q ==	NULL){
		return;
	}
	if(q->size >= SeqQueueMaxSize){
		//队列满了
		return;
	}
	q->data[q->tail] = value;
	q->tail++;
	if(q->tail >= SeqQueueMaxSize){
		q->tail = 0;
	}
	q->size++;
	return;
}

void SeqQueuePop(SeqQueue* q){
	if(q == NULL){
		//非法输入
		return;
	}
	if(q->size == 0){
		//空队列
		return;
	}
	q->head++;
	if(q->head >= SeqQueueMaxSize){
		q->head = 0;
	}
	q->size--;
	return;
}

int SeqQueueFront(SeqQueue* q,SeqQueueType* value){
	if(q == NULL){
		//非法输入
		return 0;
	}
	if(q->size == 0){
		//空队列
		return 0;
	}
	*value = q->data[q->head];
	return 1;
}



/////////////////////////////////////////////////
//以下为测试代码
////////////////////////////////////////////////

#include <stdio.h>
#define TEST_HEADER printf("\n==========================%s==========================\n",__FUNCTION__)

void SeqQueuePrintChar(SeqQueue* q,const char* msg){
	printf("[%s]\n",msg);
	size_t i =q-> head;
	for(i=q->head;i<q->tail;i++){
		printf("[%c] ",q->data[i]);
	}
	printf("\n");
}

//void TestQueue(){
//	TEST_HEADER;
//	SeqQueue queue;
//	SeqQueueInit(&queue);
//	SeqQueuePush(&queue,'a');
//	SeqQueuePush(&queue,'b');
//	SeqQueuePush(&queue,'c');
//	SeqQueuePush(&queue,'d');
//	SeqQueuePrintChar(&queue ,"入队列四个元素");
//
//	SeqQueueType value;
//	int ret = 0;
//	ret = SeqQueueFront(&queue,&value);
//	printf("ret expeted 1,actual %d\n",ret);
//	printf("value expected a,actual %c\n",value);
//
//	SeqQueuePop(&queue);
//	SeqQueuePop(&queue);
//	SeqQueuePrintChar(&queue,"出队列两个元素");
//	SeqQueuePop(&queue);
//	SeqQueuePop(&queue);
//	SeqQueuePrintChar(&queue,"再出队列两个元素");

//	SeqQueueType value;
//	int ret = 0;
//	ret = SeqQueueFront(&queue,&value);
//	printf("ret expeted 1,actual %d\n",ret);
//	printf("value expected a,actual %c\n",value);
//}

//int main(){
//	TestQueue();
//	return 0;
//}
