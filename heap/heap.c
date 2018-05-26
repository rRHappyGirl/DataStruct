#include <stdio.h>
#include <string.h>
#include "heap.h"

//小堆
int Less(HeapType a,HeapType b){
    return a<b?1:0;
}
//大堆
int Greater(HeapType a, HeapType b){
    return a>b?1:0;
}


void HeapInit(Heap* heap,Compare cmp){
    if(heap == NULL){
        //非法输入
        return;
    }
    heap->size = 0;
    heap->cmp = cmp;
    return;
}


void HeapDestory(Heap* heap){
    if(heap ==NULL){
        //非法输入
        return;
    }
    heap->size = 0;
    heap->cmp = NULL;
    return;
}
void Swap(HeapType* a,HeapType* b){
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void AdjustUp(Heap* heap,size_t index){
    size_t child = index;
    size_t parent = (child - 1)/2;
    while(child > 0){
        if(!heap->cmp(heap->data[parent],heap->data[child])){
            Swap(&heap->data[parent],&heap->data[child]);
        }else{
            //如果发现某一时刻child 与 parent 符合堆的比较要求
            //此时就可以停止上浮，因为上面的元素肯定也是满足堆的要求的
            break;
        }
        child = parent;
        parent = (child - 1)/2;
    }
    return;
}
void HeapInsert(Heap* heap,HeapType value){
    if(heap == NULL){
        //非法输入
        return;
    }
    if(heap->size >= HeapMaxSize){
        //堆满了
        return;
    }
    heap->data[heap->size++] = value;
    //对堆进行上浮式调整
    //调整的起始位置是size - 1
    AdjustUp(heap,heap->size - 1);
    return;
}

int HeapRoot(Heap* heap,HeapType* value){
    if(heap == NULL){
        //非法输入
        return 0;
    }
    if(heap->size == 0){
        //空堆
        return 0;
    }
    *value = heap->data[0];
    return 1;
}

void AdjustDown(Heap* heap,size_t index){
    if(heap == NULL){
        return;
    }
    size_t parent = index;
    size_t child = 2 * parent + 1;
    while(child < heap->size){
        if(child + 1 < heap->size && heap->cmp(heap->data[child+1],heap->data[child])){
            //如果右子树存在，并且右子树比左子树更符合“堆的要求”
            //假设我们是小堆，就要求说：
            //如果右子树比左子树小，那么就让child指向右子树
            child = child + 1;
        }
        //child就指向了左右子树中更小的那个元素
        if(heap->cmp(heap->data[child],heap->data[parent])){
            Swap(&heap->data[parent],&heap->data[child]);
        }else{
            break;
        }
        parent = child;
        child = 2 * parent + 1;
    }
    return;
}
void HeapErase(Heap* heap){
    if(heap == NULL){
        //非法输入
        return;
    }
    if(heap->size == 0){
        //空堆
        return;
    }
    //交换堆顶元素与最后一个元素
    Swap(&heap->data[0],&heap->data[heap->size - 1]);
    //size--
    heap->size--;
    //调整堆
    //从根结点出发，进行下沉式调整
    AdjustDown(heap,0);
    return;
}

void HeapCreate(Heap* heap,HeapType arry[],size_t size){
    if(heap == NULL){
        return;
    }
    //遍历arry数组，将数组中的元素插入到堆中
    size_t i = 0;
    for(;i<size;i++){
        HeapInsert(heap,arry[i]);
    }
    return;
}
//假设我们要进行升序排序，我们要建立一个大堆
void HeapSort(HeapType arryp[],size_t size){
    //把这个数组构建成一个堆
    Heap heap;
    HeapInit(&heap,Greater);
    HeapCreate(&heap,arryp,size);
    //循环的对堆进行删除操作
    while(heap.size > 0){
        HeapErase(&heap);
    }
    //循环结束之后堆排序就完成了
    memcpy(arryp,heap.data,size*sizeof(HeapType));
    return;
}
////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////
#if 1
#define TEST_HEADER printf("\n=================%s===================\n",__FUNCTION__)
void HeapPrintChar(Heap* heap,const char* msg){
    printf("[%s]\n",msg);
    size_t i = 0;
    for(;i<heap->size;i++){
        printf("%c ",heap->data[i]);
    }
    printf("\n");
}

void TestInit(){
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    printf("size is expected 0,actual is %lu\n",heap.size);
}

void TestInsert(){
  TEST_HEADER;
  Heap heap;
  HeapInit(&heap,Greater);
  HeapInsert(&heap,'a');
  HeapInsert(&heap,'c');
  HeapInsert(&heap,'d');
  HeapInsert(&heap,'b');
  HeapInsert(&heap,'e');
  HeapPrintChar(&heap,"给堆中插入5个元素");
}

void TestRoot(){
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'e');
    HeapType value;
    int ret = HeapRoot(&heap,&value);
    printf("ret expected 1,actual %d\n",ret);
    printf("value expected e,actual %c\n",value);
}
void TestErase(){
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap,Greater);
    HeapInsert(&heap,'a');
    HeapInsert(&heap,'c');
    HeapInsert(&heap,'d');
    HeapInsert(&heap,'b');
    HeapInsert(&heap,'e');
    HeapErase(&heap);
    HeapPrintChar(&heap,"删除堆顶元素");
}
void TestSort(){
    TEST_HEADER;
    HeapType array[] = {'a','d','e','b','c'};
    HeapSort(array,sizeof(array)/sizeof(array[0]));
    size_t i = 0;
    for(;i<sizeof(array)/sizeof(array[0]);i++){
        printf("%c ",array[i]);
    }
    printf("\n");
}
int main(){
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
    TestSort();
    return 0;
}
#endif
