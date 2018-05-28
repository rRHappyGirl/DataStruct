#include <stdio.h>
#include "seqlist.h"

void SeqListInit(SeqList* seqlist){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    seqlist->size = 0;
    return;
}

void SeqListPushBack(SeqList* seqlist,SeqListType value){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(seqlist->size == SeqListMaxSize){
        //顺序表满
        return;
    }
    seqlist->data[seqlist->size] = value;
    seqlist->size++;
    return;
}

void SeqListPopBack(SeqList* seqlist){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(seqlist->size == 0){
        //空顺序表
        return;
    }
    seqlist->size--;
        return;
}

void SeqListPushFront(SeqList* seqlist,SeqListType value){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(seqlist->size == SeqListMaxSize){
        //顺序表满
        return;
    }
    seqlist->size++;
    size_t i = seqlist->size-1;
    for(;i>0;i--){
        seqlist->data[i] = seqlist->data[i-1];
    }
    seqlist->data[0] = value;
    return;
}

void SeqListPopFront(SeqList* seqlist){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(seqlist->size == 0){
        //空顺序表
        return;
    }
    size_t i = 0;
    for(;i<seqlist->size;i++){
        seqlist->data[i] = seqlist->data[i+1];
    }
    seqlist->size--;
    return;
}

void SeqListInsert(SeqList* seqlist,size_t pos,SeqListType value){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(seqlist->size == SeqListMaxSize){
        //顺序表满
        return;
    }
    seqlist->size++;
    size_t i = seqlist->size-1;
    for(;i>pos;i--){
        seqlist->data[i] = seqlist->data[i-1];
    }
    seqlist->data[pos] = value;
    return;
}

void SeqListErase(SeqList* seqlist,size_t pos){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(seqlist->size == 0){
        //空顺序表
        return;
    }
    size_t i = pos;
    for(;i<seqlist->size;i++){
        seqlist->data[i] = seqlist->data[i+1];
    }
    seqlist->size--;
    return;
}

int SeqListGet(SeqList* seqlist,size_t pos,SeqListType* value){
    if(seqlist == NULL){
        //非法输入
        return 0;
    }
    if(pos >= seqlist->size){
        //非法输入
        return 0;
    }
    *value = seqlist->data[pos];
    return 1;
}

void SeqListSet(SeqList* seqlist,size_t pos,SeqListType value){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    if(pos >= seqlist->size){
        //非法位置
        return;
    }
    seqlist->data[pos] = value;
    return;
}

int SeqListFindPos(SeqList* seqlist,SeqListType value){
    if(seqlist == NULL){
        //非法输入
        return 0;
    }
    size_t i = 0;
    for(;i<seqlist->size;i++){
        if(seqlist->data[i] == value){
            return i;
        }
    }
    return -1;
}

void SeqListRemove(SeqList* seqlist,SeqListType to_del){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    size_t pos = SeqListFindPos(seqlist,to_del);
    if(pos ==(size_t) -1){
        //没找到
        return;
    }
    SeqListErase(seqlist,pos);
    return;
}

void SeqListRemoveAll(SeqList* seqlist,SeqListType to_del){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    while(1){
        size_t pos = SeqListFindPos(seqlist,to_del);
            if(pos == (size_t) -1){
                break;
            }
        SeqListErase(seqlist,pos);
    }
    return;
}

int SeqListSize(SeqList* seqlist){
    if(seqlist == NULL){
        //非法输入
        return 0;
    }
    return seqlist->size;
}

int SeqListEmpty(SeqList* seqlist){
    if(seqlist == NULL){
        //非法输入
        return -1;
    }
    if(seqlist->size == 0){
        return 1;
    }
    return 0;
}

void swap(SeqListType* a,SeqListType* b){
    SeqListType tmp = *a;
    *a = *b;
    *b = tmp;
}
void SeqListBubbleSort(SeqList* seqlist){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    size_t count = 0;
    for(;count<seqlist->size;count++){
        size_t i = 0;
        for(i=0;i<seqlist->size - count - 1;i++){
            if(seqlist->data[i]>seqlist->data[i+1]){
                swap(&seqlist->data[i],&seqlist->data[i+1]);
            }
        }
    }
    return;
}

void SeqListBubbleSortEx(SeqList* seqlist,Cmp cmp){
    if(seqlist == NULL){
        //非法输入
        return;
    }
    size_t count = 0;
    for(;count<seqlist->size;count++){
        size_t cur = 0;
        for(cur=0;cur<seqlist->size - count - 1;cur++){
            if(!cmp(seqlist->data[cur],seqlist->data[cur+1])){
                swap(&seqlist->data[cur],&seqlist->data[cur+1]);

          }
        }
    }
    return;
}
///////////////////////////////
//以下为测试代码
////////////////////////////////
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n====================%s==================\n",__FUNCTION__)

void SeqListPrintChar(SeqList* seqlist,const char* msg){
    if(seqlist == NULL){
        return;
    }
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i<seqlist->size;i++){
        printf("%c ",seqlist->data[i]);
    }
    printf("\n");
}
void TestInit(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    printf("seqlist.size expected 0,actual %lu\n",seqlist.size);
}

void TestPushBack(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPrintChar(&seqlist,"尾插四个元素");
}

void TestPopBack(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPopBack(&seqlist);
    SeqListPrintChar(&seqlist,"尾删元素d");
    SeqListPopBack(&seqlist);
    SeqListPrintChar(&seqlist,"尾删元素c");
}

void TestPushFront(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPushFront(&seqlist,'x');
    SeqListPrintChar(&seqlist,"头插元素x");
}

void TestPopFront(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListPopFront(&seqlist);
    SeqListPrintChar(&seqlist,"头删元素a");
}

void TestInsert(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListInsert(&seqlist,1,'x');
    SeqListPrintChar(&seqlist,"在位置1插入x");
}

void TestErase(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListErase(&seqlist,1);
    SeqListPrintChar(&seqlist,"删除位置1的元素b");
}
void TestGet(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListType value;
    int ret = SeqListGet(&seqlist,1,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected b,actual %c\n",value);
}
void TestSet(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListSet(&seqlist,1,'x');
    SeqListPrintChar(&seqlist,"位置1设置为x");
}

void TestFindPos(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    int ret = SeqListFindPos(&seqlist,'b');
    printf("ret expected 1,actual %d\n",ret);

}
void TestRemove(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    SeqListRemove(&seqlist,'b');
    SeqListPrintChar(&seqlist,"删除元素b");
}
void TestRemoveAll(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');
    SeqListPushBack(&seqlist,'b');

    SeqListRemoveAll(&seqlist,'b');
    SeqListPrintChar(&seqlist,"删除所有b元素");
}
void TestSize(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'c');
    SeqListPushBack(&seqlist,'d');

    int ret = SeqListSize(&seqlist);
    printf("ret expected 4,actual %d\n",ret);
}
void TestEmpty(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');

    int ret = SeqListEmpty(&seqlist);
    printf("ret expected 0,actual %d\n",ret);
}

void TestBubbleSort(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'d');
    SeqListPushBack(&seqlist,'c');

    SeqListBubbleSort(&seqlist);
    SeqListPrintChar(&seqlist,"冒泡排序");
}
//降序
int Less(SeqListType a,SeqListType b){
    return a < b ? 1 : 0;
}
//升序
int Greater(SeqListType a,SeqListType b){
    return a > b ? 1 : 0;
}
void TestBubbleSortEx(){
    TEST_HEADER;
    SeqList seqlist;
    SeqListInit(&seqlist);
    SeqListPushBack(&seqlist,'a');
    SeqListPushBack(&seqlist,'b');
    SeqListPushBack(&seqlist,'d');
    SeqListPushBack(&seqlist,'c');

    SeqListBubbleSortEx(&seqlist,Greater);
    SeqListPrintChar(&seqlist,"升序冒泡");
}
int main(){
    TestInit();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestInsert();
    TestErase();
    TestGet();
    TestSet();
    TestFindPos();
    TestRemove();
    TestRemoveAll();
    TestSize();
    TestEmpty();
    TestBubbleSort();
    TestBubbleSortEx();
    return 0;
}
#endif
