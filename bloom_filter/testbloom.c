#include <stdio.h>
#include "bloom_filter.h"

#define TEST_HEADER printf("\n=====================%s===================\n",__FUNCTION__)

void TestBloom(){
    TEST_HEADER;
    BloomFilter bf;
    BloomFilterInit(&bf);
    BloomFilterInsert(&bf,"hehe");
    BloomFilterInsert(&bf,"haha");
    int ret = BloomFilterIsExist(&bf,"hehe");
    printf("ret expected 1,actual %d\n",ret);
}
int main(){
    TestBloom();
    return 0;
}
