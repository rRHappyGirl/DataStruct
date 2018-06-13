#include <stdio.h>
#include "seqstack.h"


typedef struct MinStack{
	SeqStack stack;//结构体变量
}MinStack;

void MinStackInit(MinStack* min_stack){
	if(min_stack == NULL){
		return;
	}
	SeqStackInit(&min_stack->stack);
}

void MinStackPush(MinStack* min_stack,SeqStackType value){
	if(min_stack == NULL){
		//非法输入
		return;
	}
	SeqStackType min = value;
	SeqStackType top;
	int ret = SeqStackTop(&min_stack->stack,&top);
	if(ret == 0){
		//当前是空栈
		return;
	}else {
		//如果是非空
		min = top < value ? top:value;
	}
	//先插入value,再插入min，才能保证栈顶为最小值
	SeqStackPush(&min_stack->stack,value);
	SeqStackPush(&min_stack->stack,min);
	return;
}

void MinStackPop(MinStack* min_stack){
	if(min_stack == NULL){
		//非法输入
		return;
	}
	SeqStackPop(&min_stack->stack);
	SeqStackPop(&min_stack->stack);
}

int MinStackTop(MinStack* min_stack,SeqStackType* value){
	if(min_stack == NULL || value == NULL){
		//非法输入
		return 0;
	}
	return SeqStackTop(&min_stack->stack,value);
}

//////////////////////////////////////////////////////////////////
//以下为测试代码
/////////////////////////////////////////////////////////////////
#include <stdio.h>
#define TEST_HEADER printf("\n====================================%s===================================\n",__FUNCTION__)

void TestMinStack(){
	TEST_HEADER;
	MinStack min_stack;
	MinStackInit(&min_stack);
	MinStackPush(&min_stack,'a');
	MinStackPush(&min_stack,'b');
	MinStackPush(&min_stack,'c');
	MinStackPush(&min_stack,'d');

	SeqStackType value;
	int ret;
	ret = MinStackTop(&min_stack,&value);
	printf("ret expected 1,actual %d\n",ret);
	printf("value expected a,actual %c\n",value);

}

int main(){
	TestMinStack();
	return 0;
}
