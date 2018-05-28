//哈希桶（开散列）
#pragma once

#include <stddef.h>
#define HashMaxSize 1000

typedef int KeyType;
typedef int ValType;

//此结构相当于是链表的一个节点
typedef struct HashElem{
    KeyType key;
    ValType value;
    struct HashElem* next;
}HashElem;

typedef size_t (*HashFunc)(KeyType key);

typedef struct HashTable{
    HashElem* data[HashMaxSize];//不带头结点的链表
    size_t size;
    HashFunc func;
}HashTable;

void HashInit(HashTable* ht,HashFunc hash_func);

int HashFind(HashTable* ht,KeyType key,ValType* value);

void HashRemove(HashTable* ht ,KeyType key);
