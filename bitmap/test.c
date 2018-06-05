
#if 1
#include <stdio.h>
#include "bitmap.h"
#define TEST_HEADER printf("\n======================%s==================\n",__FUNCTION__)

void TestSet(){
    TEST_HEADER;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);
}
void TestUnset(){
    TEST_HEADER;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);

    BitmapUnset(&bm,50);
    ret = BitmapTest(&bm,50);
    printf("ret expected 0,actual %d\n",ret);
}

int main(){
    TestSet();
    TestUnset();
    return 0;
}
#endif
