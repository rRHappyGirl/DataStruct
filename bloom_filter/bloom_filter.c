#include "bloom_filter.h"
#include "hash_func.h"
#include <stdlib.h>

#define BitmapMaxSize 10000

void BloomFilterInit(BloomFilter* bf){
    if(bf == NULL){
        return;
    }
    BitmapInit(&bf->bm,BitmapMaxSize);
    bf->bloom_hash[0] = SDBMHash;
    bf->bloom_hash[1] = BKDRHash;
    return;
}

void BloomFilterDestroy(BloomFilter* bf){
    if(bf == NULL){
        return;
    }
    bf->bloom_hash[0] = NULL;
    bf->bloom_hash[1] = NULL;
    BitmapDestroy(&bf->bm);
    return;
}

void BloomFilterInsert(BloomFilter* bf,const char* str){
    if(bf == NULL || str == NULL){
        return;
    }
    size_t i = 0;
    for(;i < BloomHashCount;++i){
        size_t hash = bf->bloom_hash[i](str) % BitmapMaxSize;
        BitmapSet(&bf->bm,hash);
    }
    return;
}

int BloomFilterIsExist(BloomFilter* bf,const char* str){
    if(bf == NULL || str == NULL){
        return 0;
    }
    size_t i = 0;
    for(;i < BloomHashCount;++i){
        uint64_t hash = bf->bloom_hash[i](str) % BitmapMaxSize;
        int ret = BitmapTest(&bf->bm,hash);
        if(ret == 0){
            return 0;
        }
    }
    return 1;
}
