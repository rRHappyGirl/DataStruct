#include <stdio.h>
#include <stdlib.h>
#include "seqstack.h"

typedef struct QueueBy2Stack{
	SeqStack input;
	SeqStack output;
}QueueBy2Stack;

void QueueInit(QueueBy2Stack* q){
	if(q == NULL){
		return;
	}
	SeqStackInit(&q->input);
	SeqStackInit(&q->output);
}

void QueuePush(QueueBy2Stack* q,SeqStackType value){
	if(q == NULL){
		//非法输入
		return;
	}
	//先把所有的output元素倒腾到input中
	while(1){
		SeqStackType top;
		int ret = SeqStackTop(&q->output,&top);
		if(ret == 0){
			break;
		}
		SeqStackPop(&q->output);
		SeqStackPush(&q->input,top);
	}
	//把新元素value插入到input中
	SeqStackPush(&q->input,value);
	return;
}

void QueuePop(QueueBy2Stack* q){
	if(q == NULL){
		return;
	}
	//把input中的元素倒腾到output中
	while(1){
		SeqStackType top;
		int ret = SeqStackTop(&q->input,&top);
		if(ret == 0){
			break;
		}
		SeqStackPop(&q->input);
		SeqStackPush(&q->output,top);
	}
	//把output的栈顶元素出栈
	SeqStackPop(&q->output);
	return;
}

int QueueFront(QueueBy2Stack* q,SeqStackType* value){
	if(q == NULL || value == NULL){
		return 0;
	}
	//将input中的元素倒腾到output中
	while(1){
		SeqStackType top;
		int ret = SeqStackTop(&q->input,&top);
		if(ret == 0){
			break;
		}
		SeqStackPop(&q->input);
		SeqStackPush(&q->output,top);
	}
	return SeqStackTop(&q->output,value);
}


///////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////
#include <stdio.h>
#define TEST_HEADER printf("\n=============================%s============================\n",__FUNCTION__)

void TestQueueBy2Stack(){
	TEST_HEADER;
	QueueBy2Stack queue;
	QueueInit(&queue);
	QueuePush(&queue,'a');
	QueuePush(&queue,'b');
	QueuePush(&queue,'c');
	QueuePush(&queue,'d');

	SeqStackType value;
	int ret;
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);
	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected b,actual %c\n",value);
	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected c,actual %c\n",value);
	QueuePop(&queue);
	ret = QueueFront(&queue,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected d,actual %c\n",value);
	QueuePop(&queue);
}

int main(){
	TestQueueBy2Stack();
	return 0;
}




