#pragma once
#include <stddef.h>

#define HeapMaxSize 1024
typedef char HeapType;

//如果a和b满足比较关系，返回1
//如果不满足比较关系，就返回0
//所谓的比较关系，对于小堆来说，就是a<b
//对于大堆来说，a>b
typedef int(*Compare)(HeapType a,HeapType b);

typedef struct Heap{
    HeapType data[HeapMaxSize];
    size_t size;
    Compare cmp;
}Heap;

//在对堆进行初始化时，决定堆是大堆还是小堆
void HeapInit(Heap* heap,Compare cmp);

//销毁
void HeapDestory(Heap* heap);

//往堆中插入元素
void HeapInsert(Heap* heap,HeapType value);

//取堆顶元素
int HeapRoot(Heap* heap,HeapType* value);

//删除堆顶元素
void HeapErase(Heap* heap);

//根据arry数组，构建一个堆，这个堆用heap来表示
void HeapCreate(Heap* heap,HeapType arry[],size_t size);

//实现堆排序
void HeapSort(HeapType arryp[],size_t size);

