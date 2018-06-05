#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
uint64_t GetSize(uint64_t capacity){
    uint64_t size = capacity / (sizeof(uint64_t) * 8) + 1;
    return size;
}

void BitmapInit(Bitmap* bm,uint64_t capacity){
    if(bm == NULL){
        //非法输入
        return;
    }
    //capacity表示该位图中能容纳的最大数字
    //比如capacity = 100，2个元素
    //capacity = 200,4个元素
    //capacity = 300,5个元素
    //capacity = N,N/(sizeof(uint64_t) * 8) +1;
    bm->capacity = capacity;
    //size是我们申请内存时对应数组元素的个数
    uint64_t size = capacity/(sizeof(uint64_t) * 8) + 1;
    bm->data = (uint64_t*)malloc(sizeof(uint64_t) * size);
    memset(bm->data,0,sizeof(uint64_t)*size);
    return;
}

void BitmapDestroy(Bitmap* bm){
    if(bm == NULL){
        return;
    }
    bm->capacity = 0;
    free(bm->data);
    return;
}

void GetOffset(uint64_t index,uint64_t* n,uint64_t* offset){
    *n = index / (sizeof(uint64_t) * 8);
    *offset = index % (sizeof(uint64_t) * 8);
    return;
}
int BitmapTest(Bitmap* bm,uint64_t index){
    if(bm == NULL || index >= bm->capacity){
        //非法输入
        return 0;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    uint64_t ret = bm->data[n] & (0x1ul << offset);
    return ret > 0 ? 1 : 0;
}

void BitmapSet(Bitmap* bm,uint64_t index){
    if(bm == NULL){
        return;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    bm->data[n] = (0x1ul << offset);
    return;
}

void BitmapUnset(Bitmap* bm,uint64_t index){
    if(bm == NULL){
        return;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    bm->data[n] = ~(0x1ul << offset);
    return;
}

void BitmapFill(Bitmap* bm){
    if(bm == NULL){
        return;
    }
    uint64_t size = GetSize(bm->capacity);
    memset(bm->data,0xff,sizeof(uint64_t) * size);
    return;
}

void BitmapClear(Bitmap* bm){
    if(bm == NULL){
        return;
    }
    uint64_t size = GetSize(bm->capacity);
    memset(bm->data,0x0,sizeof(uint64_t) * size);
    return;
}

