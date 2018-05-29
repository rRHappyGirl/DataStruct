#include <stdio.h>

int _Count(int array[],int size){
    int cur1 = 0;
    int count = 1;
    int mid = size/2;
    for(;cur1 < size;cur1++){
        int cur1_value = array[cur1];
        int cur2 = cur1 + 1;
        for(;cur2 < size;cur2++){
            if(cur1_value == array[cur2]){
                count++;
            }
        }
        if(count > mid){
            return cur1_value;
        }else{
            count = 1;
        }
    }
    return 0;
}

int main(){
    int array[] = {1,2,3,2,2,2,5,4,2};
    int len = sizeof(array)/sizeof(array[0]);
    int ret = _Count(array,len);
    printf("ret is %d\n",ret);
    return 0;
}
