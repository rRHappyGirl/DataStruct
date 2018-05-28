#pragma once

typedef char SeqStackType;


typedef struct SeqStack {
	SeqStackType* data;
	size_t size;
	size_t capacity; //MAX_SIZE的替代品，data这段内存中能容纳的元素个数
}SeqStack;

void SeqStackInit(SeqStack* stack);

void SeqStackDestroy(SeqStack* stack);

void SeqStackPush(SeqStack* stack,SeqStackType value);

void SeqStackPop(SeqStack* stack);

int  SeqStackTop(SeqStack* stack ,SeqStackType* value);

void SeqStackPrintChar(SeqStack* stack,const char* smg);
