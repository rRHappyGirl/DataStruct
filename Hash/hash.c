#include "hash.h"

size_t HashFuncDefault(KeyType key){
    return key % HashMaxSize;
}

void HashInit(HashTable* ht,HashFunc hash_hunc){
    ht->size = 0;
    ht->func =hash_hunc;
    size_t i = 0;
    for(;i < HashMaxSize;i++){
        ht->data[i].stat = Empty;
    }
    return;
}

void HashDestroy(HashTable* ht){
    ht->size = 0;
    ht->func = NULL;
    size_t i = 0;
    for(;i < HashMaxSize;i++){
        ht->data[i].stat = Empty;
    }
    return;
}

void HashInsert(HashTable* ht,KeyType key,ValType value){
    if(ht == NULL){
        //非法输入
        return;
    }
    //1.判定哈希表是否能继续插入（根据负载因子来进行判定）
    //此处的负载因子为0.8
    if(ht->size >= 0.8 * HashMaxSize){
        //哈希表已经达到了负载因子的上线，插入失败
        return;
    }
    //2.根据key来计算offset
    size_t offset = ht->func(key);
    //3.从offset位置线性往后查找，找到第一个状态为Empty然后插入
    while(1){
        if(ht->data[offset].stat != Valid){
            //找到了一个位置
            ht->data[offset].stat = Valid;
            ht->data[offset].key = key;
            ht->data[offset].value = value;
            ++ht->size;
            return;
        }else if(ht->data[offset].stat == Valid && ht->data[offset].key == key){
            return;
        }else{
        ++offset;
        offset = offset >= HashMaxSize ? 0:offset;
        }
    }
    return;
    //4.如果此时发现key相同的元素，直接插入失败
    //5.++size
}


//思路：1.根据key算出offset
//2.从offset位置循环的进行查找，每次取到一个元素，用key去比较
//a)如果找到了key相同的元素，返回value，并且查找成功
//b)如果当前key不相等就继续往后找
//c)如果发现当前的元素是一个空元素，此时认为查找失败
int HashFind(HashTable* ht,KeyType key,ValType* value){
    if(ht == NULL){
        return 0;
    }
    size_t offset = ht->func(key);
    while(1){
        if(ht->data[offset].stat == Valid 
           && ht->data[offset].key == key){
            *value = ht->data[offset].value;
            return 1;
        }else if(ht->data[offset].stat == Empty){
            return 0;
        }else{
            ++offset;
            offset = offset >= HashMaxSize ? 0:offset;
        }
    }
    return 0;
}
void HashRemove(HashTable* ht,KeyType key){
    if(ht == NULL){
        return;
    }
    size_t offset = ht->func(key);
    while(1){
        if(ht->data[offset].stat == Valid
           && ht->data[offset].key == key){
            ht->data[offset].stat = Deleted;
            ht->size--;
            return;
        }else if(ht->data[offset].stat == Empty){
            return;
        }else{
            offset++;
            offset = offset >= HashMaxSize ? 0:offset;
        }
    }
    return;
}
/////////////////////////////////////////
//以下代码为测试代码
/////////////////////////////////////////
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n================%s================\n",__FUNCTION__)

void HashPrint(HashTable* ht,const char* msg){
    if(ht == NULL){
        return;
    }
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i < HashMaxSize;i++){
        if(ht->data[i].stat == Empty){
            continue;
        }
        printf("[%lu  %d:%d]",i,ht->data[i].key,ht->data[i].value);
    }
    printf("\n");
    return;
}
void TestInit(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    printf("size expected 0,actual %lu\n",ht.size);
    printf("func expected %p,actual %p\n",HashFuncDefault,ht.func);
}
void TestDestroy(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashDestroy(&ht);
    printf("size expected 0,actual %lu\n",ht.size);
    printf("func expected NULL,actual %p\n",ht.func);
}
void TestInsert(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,2);

    HashPrint(&ht,"插入四个元素");
}
void TestFind(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);
    ValType value;
    int ret = HashFind(&ht,1002,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected 12 ,actual %d\n",value);
}
void TestRemove(){
    TEST_HEADER;
    HashTable ht;
    HashInit(&ht,HashFuncDefault);
    HashInsert(&ht,1,1);
    HashInsert(&ht,1,10);
    HashInsert(&ht,2,2);
    HashInsert(&ht,1001,11);
    HashInsert(&ht,1002,12);

    HashRemove(&ht,2);

    ValType value;
    int ret = HashFind(&ht,1002,&value);
    printf("ret expected 1,actaul %d\n",ret);
    printf("value expected 12.actual %d\n",value);

    ret = HashFind(&ht,2,&value);
    printf("ret expected 0,actual %d\n",ret);
    return;
}
int main(){
    TestInit();
    TestDestroy();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
#endif
