#pragma once

#include <stddef.h>

#define SeqListMaxSize 1000
typedef char SeqListType;

typedef struct SeqList{
    SeqListType data[SeqListMaxSize];
    size_t size;
}SeqList;

//初始化
void SeqListInit(SeqList* seqlist);

//尾插
void SeqListPushBack(SeqList* seqlist ,SeqListType value);

//尾删
void SeqListPopBack(SeqList* seqlist);

//头插
void SeqListPushFront(SeqList* seqlist,SeqListType value);

//头删
void SeqListPopFront(SeqList* seqlist);

//给指定位置插入元素
void SeqListInsert(SeqList* seqlist,size_t pos,SeqListType value);

//删除指定位置的元素
void SeqListErase(SeqList* seqlist,size_t pos);

//获取指定位置的值
int SeqListGet(SeqList* seqlist,size_t pos,SeqListType* value);

//给指定位置设置值
void SeqListSet(SeqList* seqlist,size_t pos,SeqListType value);

//找到某个元素的下标，返回下标
int SeqListFindPos(SeqList* seqlist,SeqListType value);

//删除顺序表中指定的值, 如果存在重复元素, 只删除第一个 
void SeqListRemove(SeqList* seqlist,SeqListType to_del);

//删除顺序表中所有相同的元素
void SeqListRemoveAll(SeqList* seqlist,SeqListType to_del);

//获取顺序表中元素的个数
int SeqListSize(SeqList* seqlist);

//顺序表判空,如果为空，返回1，否则返回0
int SeqListEmpty(SeqList* seqlist);

//冒泡排序
void SeqListBubbleSort(SeqList* seqlist);

//冒泡排序的扩展，可以指定升序，降序
//对Cmp比较函数作以下约定
//如果 a 和 b 满足比较规则，返回1，否则返回0
//满足比较规则具体值：
//如果是升序排序，a < b则称为满足比较规则
typedef int(*Cmp)(SeqListType a,SeqListType b);
void SeqListBubbleSortEx(SeqList* seqlist,Cmp cmp);

