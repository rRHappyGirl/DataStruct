#include <stdio.h>
#include <stdlib.h>
#include "seqstack.h"
#define MAX_ROW 6
#define MAX_COL 6

typedef struct Maze {
	int map[MAX_ROW][MAX_COL];
}Maze;

void MazeInit(Maze* maze) {
	int map[MAX_ROW][MAX_COL] = {
		{0,1,0,0,0,0},
		{0,1,1,1,0,0},
		{0,1,0,1,0,0},
		{0,1,0,1,1,0},
		{0,1,1,0,0,0},
		{0,0,1,0,0,0},
	};
	int i = 0;
	for(i=0;i<MAX_ROW;i++){
		int j = 0;
		for(j=0;j<MAX_COL;j++){
			maze->map[i][j] = map[i][j];
		}
	}
	return;
}


void MazePrint(Maze* maze) {
	int i = 0;
	for(i=0;i<MAX_ROW;i++){
		int j = 0;
		for(j=0;j<MAX_COL;j++){
			printf("%2d ",maze->map[i][j]);
		}
		printf("\n");
	}
}
//////////////////////////////////////////////////////
//Round1使用递归的方式来解决迷宫问题（能否走出迷宫）
/////////////////////////////////////////////////////


//判断pt这个点是否能落脚
//如果能落脚，返回1，否则返回0

int CanStay(Maze* maze,Point pt){
	//1.如果这个点在地图外肯定不能落脚
	if(pt.row < 0 || pt.row >= MAX_ROW || pt.col < 0 || pt.col >=MAX_COL){
		return 0;
	}
	//2.如果pt在地图内的话，如果这个位置值是1，就能落脚，如果值是0,或者2就不能落脚
	int value = maze->map[pt.row][pt.col];
	if(value == 1){
		return 1;
	}
	return 0;
}
//标记
void Mark(Maze* maze , Point cur){
	maze->map[cur.row][cur.col] = 2;
}

//如果是出口，返回1，否则返回0
int IsEixt(Maze* maze ,Point cur,Point entry) {
	(void) maze;//消除警告
	//1.当前点是不是入口，如果是入口，那肯定不是出口
	if(cur.row == entry.row && cur.col == entry.col){
		return 0;
	}
	//2.如果点在地图的边界上说明是出口
	if(cur.row == 0 || cur.row == MAX_ROW - 1 || cur.col == 0 || cur.col == MAX_COL - 1){
		return 1;
	}
	return 0;
}

//每次走到下一个点都会递归的调用下面这个函数
void _GetPath(Maze* maze,Point cur,Point entry){
	printf("cur:(%d,%d)\n",cur.row,cur.col);
	//1.判定当前点是否能落脚
	if(!CanStay(maze,cur)){
		return;
	}
	//2.如果能落脚就给当前位置做标记
	Mark(maze,cur);
	//3.如果当前点是出口，说明找到了一条出路，探测就结束
	if(IsEixt(maze,cur,entry)){
		printf("找到了一条路径\n");
		return;
	}
	//4.如果当前点不是出口，就按照顺时针探测四个相邻点，
	// 递归的调用函数自身，递归时，更新cur点
	//（每次递归的时候，点都是下一次要走的点，这个点能不能走交给递归函数实现）
	Point up = cur;
	up.row -= 1;
	_GetPath(maze,up,entry);

	Point right = cur;
	right.col += 1;
	_GetPath(maze,right,entry);

	Point down = cur;
	down.row += 1;
	_GetPath(maze,down,entry);

	Point left = cur;
	left.col -= 1;
	_GetPath(maze,left,entry);
}

void GetPath(Maze* maze,Point entry){
	if(maze == NULL){
		return;
	}
	//使用下面的函数辅助我们完成递归
	_GetPath(maze,entry,entry);//第一个entry是当前走到的点，第二个entry是入口点
}

/////////////////////////////////////////////
//Round2非递归的方式来求解迷宫问题
/////////////////////////////////////////////

void GetPathByLoop(Maze* maze,Point entry){
	//1.创建一个栈，并且初始化，这个栈保存走过的路径
	SeqStack stack;
	SeqStackInit(&stack);
	//2.判定入口能不能落脚，如果不能说明参数非法
	if(!CanStay(maze,entry)){
		//入口点非法
		return;
	}
	//3.标记入口点，并且将入口点入栈
	Mark(maze,entry);
	SeqStackPush(&stack,entry);
	//4.进入循环，获取到当前的栈顶元素（栈顶元素一定是能落脚）
	while(1){
		Point cur;
		int ret = SeqStackTop(&stack,&cur);
		if(ret == 0){
			//栈为空说明回溯结束了
			return;
		}
	
	//5.判定这个点是不是出口，如果是出口直接函数返回
	if(IsEixt(maze,cur,entry)){
		printf("找到了一条出口\n");
		return;
	}
	//6.按照顺势针方向取相邻点，判定相邻点是否能落脚，如果能落脚就标记并且入栈，立刻进入下一轮循环
	Point up = cur;
	up.row -= 1;
	if(CanStay(maze , up)){
		Mark(maze,up);
		SeqStackPush(&stack,up);
		continue;
	}
	Point right = cur;
	right.col += 1;
	if(CanStay(maze,right)){
		Mark(maze,right);
		SeqStackPush(&stack,right);
		continue;
	}
	Point down = cur;
	down.row += 1;
	if(CanStay(maze,down)){
		Mark(maze,down);
		SeqStackPush(&stack,down);
		continue;
	}
	Point left = cur;
	left.col -= 1;
	if(CanStay(maze,left)){
		Mark(maze,down);
		SeqStackPush(&stack,left);
		continue;
	}
	//7.如果四个相邻的点都不能落脚，就出栈当前点，相当于进行回溯
	SeqStackPop(&stack);
	}
	return;
}


///////////////////////////////////////////////
//Round3 如果迷宫有多条路径，找到最短的一条
///////////////////////////////////////////////

void MazeInit2(Maze* maze){
    if(maze == NULL){
        return;
  }
    int map[MAX_ROW][MAX_COL] = {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
    };
    size_t i = 0;
    for(;i<MAX_ROW;i++){
        size_t j = 0;
        for(;j<MAX_COL;j++){
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}

void _GetShortPath(Maze* maze,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path){
    if(maze == NULL){
        return;
    }
    //1.判断当前点是否能落脚
    if(!CanStay(maze,cur)){
        return;
    }
    //2.如果能落脚，就对当前点进行标记，同时把当前点插入到cur_path
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //3.判断当前点是否是出口
    if(IsEixt(maze,cur,entry)){
        //a)如果是出口，说明找到了一条路径，拿当前路径与最短路径进行比较
        //如果当前路径比最短路径短，或者最短路径为空
        //就用当前路径代替最短路径
        printf("找到一条路径\n");
        if(cur_path->size < short_path->size || short_path->size == 0){
            printf("找到一条较短路径\n");
            SeqStackAssgin(cur_path,short_path);
        }
        //b)如果当前路径没有short_path短，就继续在找其他路径（进行回溯）
        //回溯之前要把cur_path栈顶元素出栈
        SeqStackPop(cur_path);
        return;
    }
    //4.如果当前点不是出口，按照顺时针方向继续探测相邻的四个方向
    Point up = cur;
    up.row -= 1;
    _GetShortPath(maze,up,entry,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _GetShortPath(maze,right,entry,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _GetShortPath(maze,down,entry,cur_path,short_path);

    Point left = cur;
    left.col -= 1;
    _GetShortPath(maze,left,entry,cur_path,short_path);

    //5.如果四个方向都探测过了，就可以进行出栈（指当前函数栈帧结束，
    //同时cur_path也要进行出栈），回溯到上一个点
    SeqStackPop(cur_path);
    return;
}
//找到所有路径然后从所有路径中筛选出最短的一条（递归 ）
void GetShortPath(Maze* maze,Point entry){
    if(maze == NULL){
        return;
    }
    //就像从一个数组中查找最小元素一样，定义一个最短路径short_path，保存最短路径
    SeqStack cur_path;//保存当前路径
    SeqStack short_path;//保存最短路径
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    _GetShortPath(maze,entry,entry,&cur_path,&short_path);
    SeqStackDebugPrint(&short_path,"最短路径");
}

/////////////////////////////////////////////////
//Round4针对一个复杂的迷宫，找出其中最短的一条路径
//这里的复杂不单单指有多个出口，还有可能带环
////////////////////////////////////////////////


void MazeInit3(Maze* maze){
    if(maze == NULL){
        return;
    }
    int map[MAX_ROW][MAX_COL] = {
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0},
    };
    size_t i = 0;
    for(;i<MAX_ROW;i++){
        size_t j = 0;
        for(;j<MAX_COL;j++){
            maze->map[i][j] = map[i][j];
        }
    }
    return;
}

int CanStayWithCycle(Maze* maze,Point cur,Point pre){
    if(maze == NULL){
        return 0;
    }
    //当前点是否在地图上
    if(cur.row < 0||cur.col > MAX_COL||cur.row < 0 || cur.row > MAX_ROW){
        return 0;
    }
    int cur_value = maze->map[cur.row][cur.col];
    //当前点是墙
    if(cur_value == 0){
        return 0;
    }
    //当前点是1，就可以以直接落脚
    if(cur_value == 1){
        return 1;
    }
    //当前点如果已经被标记，就比较当前点与pre的大小
    //a)cur_value 7,pre_value 5 能落脚
    //b)cur_value 6,pre_value 5 不能落脚
    //c)cur_value 5,pre_value 5 不能落脚
    //d)cur_value 4,pre_value 5 不能落脚
    //总结以上情况，当cur_value > pre_value+1时能落脚
    int pre_value = maze->map[pre.row][pre.col];
    if(cur_value > pre_value+1){
        return 1;
    }
    return 0;
}

void MarkWithCycle(Maze* maze,Point cur,Point pre){
    if(maze == NULL){
        return;
    }
    if(cur.row < 0 || cur.row >=MAX_ROW || cur.col < 0 || cur.col >= MAX_COL){
        return;
    }
    if(pre.row == -1 && pre.col == -1){
        maze->map[cur.row][cur.col] = 2;
        return;
    }
    int pre_value = maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col] = pre_value + 1;
    return;
}

void _GetShortPathWithCycle(Maze* maze,Point cur,Point pre,Point entry,SeqStack* cur_path,SeqStack* short_path){
    if(maze == NULL){
        return;
    }
    //判断当前点是否能落脚（判定规则变了）
    if(!CanStayWithCycle(maze,cur,pre)){
        return;
    }
    //如果能落脚，就将当前点标记并且插入到cur_path中,更新pre
    MarkWithCycle(maze,cur,pre);
    SeqStackPush(cur_path,cur);
    pre = cur;
    //判断是否是出口
    if(IsEixt(maze,cur,entry)){
        //如果是出口，要拿cur_path与short_path进行比较，
        //把比较短的路径保存到short_path中
        if(cur_path->size < short_path->size || short_path->size == 0){
            printf("找到了一条比较短的路径\n");
            SeqStackAssgin(cur_path,short_path);
        }
        //进行回溯，不管当前找到的这条路径是不是比较短的路径
        SeqStackPop(cur_path);
        return;
    }
    //如果不是出口，以当前为基准，顺时针探测四周
    Point up = cur;
    up.row -= 1;
    _GetShortPathWithCycle(maze,up,pre,entry,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _GetShortPathWithCycle(maze,right,pre,entry,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _GetShortPathWithCycle(maze,down,pre,entry,cur_path,short_path);

    Point left = cur;
    left.col -= 1;
    _GetShortPathWithCycle(maze,left,pre,entry,cur_path,short_path);

    //如果四个点都探测过了，进行回溯
    SeqStackPop(cur_path);
    return;
}

void GetShortPathWithCycle(Maze* maze,Point entry){
    SeqStack cur_path;
    SeqStack short_path;
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);
    Point pre = {-1,-1};
    _GetShortPathWithCycle(maze,entry,pre,entry,&cur_path,&short_path);
    SeqStackDebugPrint(&short_path,"最短路径为");
}
//////////////////////////////////////////////
//以下为测试代码
/////////////////////////////////////////////
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n=================================%s==================================\n",__FUNCTION__)

void TestInit(){
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	MazePrint(&maze);
}

void Test1(){
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	Point entry = {0,1};
	GetPath(&maze,entry);
	MazePrint(&maze);
}

void Test2(){
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	Point entry = {0,1};
	
	GetPathByLoop(&maze,entry);
	MazePrint(&maze);

}

void Test3(){
	TEST_HEADER;
	Maze maze;
	MazeInit2(&maze);
	Point entry = {0,1};
	
	GetShortPath(&maze,entry);
	MazePrint(&maze);

}

void Test4(){
	TEST_HEADER;
	Maze maze;
	MazeInit3(&maze);
	Point entry = {0,1};
	
	GetShortPathWithCycle(&maze,entry);
	MazePrint(&maze);

}
int main(){
	TestInit();
	Test1();
	Test2();
    Test3();
    Test4();
	return 0;
}


#endif




