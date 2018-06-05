#pragma once 
#include <stdint.h>

//#define uint64_t BitmapType

typedef struct Bitmap{
    uint64_t* data;
    uint64_t capacity;//位图最多能容纳多少位
}Bitmap;

//初始化
void BitmapInit(Bitmap* bm,uint64_t capacity);

//销毁
void BitmapDestroy(Bitmap* bm);

//给某一位设置为1
void BitmapSet(Bitmap* bm ,uint64_t index);
//给某一位设置为0
void BitmapUnset(Bitmap* bm,uint64_t index);
//给所有位设置为1
void BitmapFill(Bitmap* bm);
//给所有位设置为0
void BitmapClear(Bitmap* bm);
//测试某一位是否为1
int BitmapTest(Bitmap* bm,uint64_t index);

