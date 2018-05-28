#include "hash.h"
#include <stdlib.h>

size_t HashFuncDefualt(KeyType key){
    return key % HashMaxSize;
}

HashElem* CreateElem(KeyType key,ValType value){
    HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void DestroyElem(HashElem* node){
    free(node);
}

void HashInit(HashTable* ht,HashFunc hash_func){
    if(ht == NULL){
        return;
    }
    ht->size = 0;
    ht->func = hash_func;
    size_t i = 0;
    for(;i < HashMaxSize;i++){
        ht->data[i] = NULL;
    }
    return;
}

void HashDestroy(HashTable* ht){
    if(ht == NULL){
        return;
    }
    ht->size = 0;
    ht->func = NULL;
    //遍历所有链表，进行释放操作
    size_t i = 0;
    for(;i < HashMaxSize;i++){
        HashElem* cur = ht->data[i];
        while(cur != NULL){
            HashElem* next = cur->next;
            DestroyElem(cur);
            cur = next;
        }
    }
    return;
}

//int HashBucketFind(HashElem* head,KeyType to_find){
//    if(head == NULL){
//        return 0;
//    }
//    HashElem* cur = head;
//    while(cur != NULL){
//        if(cur->key == to_find){
//            return 1;
//        }else{
//            cur = cur->next;
//        }
//    }
//    return 0;
//}
HashElem* HashBucketFind(HashElem* head,KeyType to_find){
    if(head == NULL){
        return NULL;
    }
    HashElem* cur = head;
    for(;cur != NULL;cur = cur->next){
        if(to_find == cur->key){
            break;
        }
    }
    return cur == NULL ? NULL:cur;
}
void HashInsert(HashTable* ht ,KeyType key,ValType value){
    if(ht == NULL){
        return;
    }
    size_t offset = ht->func(key);
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret != NULL){
        //存在与key值一样的元素，插入失败
        return;
    }
    //采用头插方式
    HashElem* new_node = CreateElem(key,value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    ++ht->size;
    return;
}

int HashFind(HashTable* ht,KeyType key,ValType* value){
    if(ht == NULL){
        return 0;
    }
    size_t offset = ht->func(key);
    HashElem* ret = HashBucketFind(ht->data[offset],key);
    if(ret == NULL){
        //没找到
        return 0;
    }
    *value = ret->value;
    return 1;
}

int HashBucketFindEx(HashElem* head,KeyType to_find,HashElem** pre_node,
                     HashElem** cur_node){
    if(head == NULL){
        return 0;
    }
    HashElem* cur = head;
    HashElem* pre = NULL;
    for(;cur != NULL;pre=cur,cur=cur->next){
        if(to_find == cur->key){
            break;
        }
    }
    if(cur == NULL){
        return 0;
    }
    *pre_node = pre;
    *cur_node = cur;
    return 1;
}
void HashRemove(HashTable* ht,KeyType key){
    if(ht == NULL){
        return;
    }
    if(ht->size == 0){
        return;
    }
    size_t offset = ht->func(key);
    HashElem* pre = NULL;
    HashElem* cur = NULL;
    int ret = HashBucketFindEx(ht->data[offset],key,&pre,&cur);
    if(ret == 0){
        //没找到
        return;
    }
    if(pre == NULL){
        //删除头节点
        ht->data[offset] = cur->next;
    }else{
        pre->next = cur->next;
    }
    DestroyElem(cur);
    --ht->size;
    return;
}

//////////////////////////////////////////////////////
//以下为测试代码
//////////////////////////////////////////////////////
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n===============================%s===========================\n",__FUNCTION__)

void HashPrint(HashTable* ht,const char* msg){
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i<HashMaxSize;i++){
        if(ht->data[i] == NULL){
            continue;
        }
        printf("%lu  ",i);
        HashElem* cur = ht->data[i];
        for(;cur != NULL;cur=cur->next){
            printf("[%d : %d]  ",cur->key,cur->value);
        }
        printf("\n");
    }
}
void TestInsert(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefualt);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);

    HashPrint(&ht,"插入五个元素");
}
void TestFind(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefualt);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);

    ValType value;
    int ret = HashFind(&ht,1,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected 1,actaul %d\n",value);
}

void TestRemove(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefualt);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);

    HashRemove(&ht,1);
    HashPrint(&ht,"删除key为1的值");
}
int main(){
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
#endif
