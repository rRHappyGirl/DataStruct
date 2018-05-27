//线性探测法（闭散列）
#pragma once

#include <stddef.h>

#define HashMaxSize 1000

typedef enum{
    Empty,   //空状态
    Valid,   //有效状态
    Deleted
}Stat;

typedef int KeyType;
typedef int ValType;

//这个结构体表示哈希表中的一个元素
//这个元素中同时表示了健值对
typedef struct HashElem{
    KeyType key;
    ValType value;
    Stat stat;
}HashElem;

typedef size_t (*HashFunc)(KeyType key);

typedef struct HashTable{
    HashElem data[HashMaxSize];
    size_t size;
    HashFunc func;
}HashTable;

void HashInit(HashTable* ht,HashFunc hash_func);

void HashDestroy(HashTable* ht);

void HashInsert(HashTable* ht,KeyType key,ValType value);

int HashFind(HashTable* ht,KeyType key,ValType* value);

void HashRemove(HashTable* ht,KeyType key);
