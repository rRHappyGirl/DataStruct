#include <stdio.h>
#include <stdlib.h>

#include "seqstack.h"
void SeqStackInit(SeqStack* stack){
	if(stack == NULL){
		return;
	}
	stack->size = 0;
	stack->capacity = 1000;
	stack->data = (SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType));
	return;
}

void SeqStackDestroy(SeqStack* stack){
	free(stack->data);
	stack->size = 0;
	stack->capacity = 0;
}

void SeqStackReSize(SeqStack* stack){
	if(stack == NULL){
		return;
	}
	if(stack->size < stack->capacity){
		return;
	}
	//扩容策略可以按照自己的喜好来定
	stack->capacity = stack->capacity * 2 + 1;
	SeqStackType* new_ptr = (SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType));
	
	size_t i = 0;
	for(i = 0; i < stack->size;i++){
		new_ptr[i] = stack->data[i];
	}
	free(stack->data);
	stack->data = new_ptr;
	return;
}

void SeqStackPush(SeqStack* stack , SeqStackType value){
	if(stack == NULL){
		//非法输入
		return;
	}
	if(stack->size >= stack->capacity){
		//扩容
		SeqStackReSize(stack);
	}
	stack->data[stack->size] = value;
	stack->size++;
	return;
}

void SeqStackPop(SeqStack* stack){
	if(stack == NULL){
		//非法输入
		return;
	}
	if(stack->size == 0){
		//空栈
		return;
	}
	stack->size--;
	return;
}

int  SeqStackTop(SeqStack* stack,SeqStackType* value){
	if(stack == NULL){
		return 0;
	}
	if(stack->size == 0){
		return 0;
	}
	*value = stack->data[stack->size-1];
	return 1;
}

void SeqStackAssgin(SeqStack* from,SeqStack* to){
    //为了保证to里面的内存能够足够的容纳from中的元素
    //就采用以下的策略：
    //1.释放to中的原有内存
    SeqStackDestroy(to);
    //2.根据from元素的个数，确定内存申请的大小
    //  给to重新申请一个足够的内存
    to->size = from->size;
    to->capacity = from->capacity;
    to->data = (SeqStackType*)malloc(to->capacity*sizeof(SeqStackType));
    //3.再进行数据的拷贝
    size_t i = 0;
    for(;i<from->size;i++){
        to->data[i] = from->data[i];
    }
    return;
}

//此函数仅用于迷宫问题中，用来调式
//通常意义下，栈是不允许进行遍历的
//但是如果是进行调式或者测试，这个是例外
//这里遍历仅用于测试
//之所以写这样一个函数遍历栈，是为了能够从入口到出口的顺序
//来打印栈中的内存
void SeqStackDebugPrint(SeqStack* stack,const char* msg){
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i<stack->size;i++){
        printf("(%d,%d)\n",stack->data[i].row,stack->data[i].col);
    }
    printf("\n");
}
/////////////////////////////////////////////////////////
//////以下为测试代码
////////////////////////////////////////////////////////
//#if 1
//#include <stdio.h>
//#define TEST_HEADER printf("\n========================%s=========================\n",__FUNCTION__) 
//
//void SeqStackPrintChar(SeqStack* stack,const char* msg){
//	printf("[%s]\n",msg);
//	size_t i = 0;
//	for(i=0;i<stack->size;i++){
//		printf("[%c] ",stack->data[i]);
//	}
//	printf("\n");
//}
//void TestInit(){
//	TEST_HEADER;
//	SeqStack stack;
//	SeqStackInit(&stack);
//	printf("size expected 0 , actual %d\n",stack.size);
//	printf("capacity expected 1000,actual %d\n",stack.capacity);
//
//}
//
//void TestDestroy(){
//	TEST_HEADER;
//	SeqStack stack;
//	SeqStackInit(&stack);
//	SeqStackDestroy(&stack);
//	printf("capacity expacted 0 ,actual %d\n",stack.capacity);
//}
//void TestPush(){
//	TEST_HEADER;
//	SeqStack stack;
//	SeqStackInit(&stack);
//	SeqStackPush(&stack , 'a');
//	SeqStackPush(&stack , 'b');
//	SeqStackPush(&stack , 'c');
//	SeqStackPush(&stack , 'd');
//
//	SeqStackPrintChar(&stack ,"入栈四个元素");
//}
//
//void TestPop(){
//	TEST_HEADER;
//	SeqStack stack;
//	SeqStackInit(&stack);
//	SeqStackPush(&stack , 'a');
//	SeqStackPush(&stack , 'b');
//	SeqStackPush(&stack , 'c');
//	SeqStackPush(&stack , 'd');
//
//	SeqStackPop(&stack);
//	SeqStackPop(&stack);
//	SeqStackPrintChar(&stack,"出栈两个元素");
//	SeqStackPop(&stack);
//	SeqStackPop(&stack);
//	SeqStackPrintChar(&stack,"再出栈两个元素");
//	SeqStackPop(&stack);
//	SeqStackPrintChar(&stack ,"尝试对空栈出栈");
//}
//void TestTop(){
//	TEST_HEADER;
//	SeqStack stack;
//	SeqStackInit(&stack);
//	SeqStackPush(&stack , 'a');
//	SeqStackPush(&stack , 'b');
//	SeqStackPush(&stack , 'c');
//	SeqStackPush(&stack , 'd');
//
//	SeqStackType value;
//	int ret = SeqStackTop(&stack , &value);
//	printf("ret expected 1,ctual %d\n",ret);
//	printf("value expected d,actual %c\n",value);
//}
//int main(){
//	TestInit();
//	TestDestroy();
//	TestPush();
//	TestPop();
//	TestTop();
//	return 0;
//}
//#endif 
