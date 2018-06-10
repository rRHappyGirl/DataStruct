#include <stdio.h>
#include <stdlib.h>

#include "linklist.h"


//创建一个结点
LinkNode* CreateNode(LinkNodeType value) {
	LinkNode* new_node = (LinkNode*) malloc (sizeof (LinkNode));
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}
//销毁结点
void DestroyNode(LinkNode* node) {
	free(node);
}

void LinkListPrintChar(LinkNode* head , const char* msg) {
	printf("[%s]\n",msg);
	LinkNode* cur = head;
	for(; cur != NULL;cur = cur->next) {
		printf("[%c|%p] ",cur->data , cur);
	}
	printf("\n");
}

//初始化链表
void  LinkListInit(LinkNode** head) {
	*head = NULL;
}


int LinkListSize(LinkNode* head) {
	if(head == NULL){
		//空链表
		return 0;
	}
	int count = 0;
	LinkNode* cur = head;
	while(cur != NULL) {
		cur = cur->next;
		count++;
	}
	return count;
}

LinkNode* LinkListFind(LinkNode* head , LinkNodeType pos) {
	if(head == NULL) {
		//空链表
		return NULL;
	}
	LinkNode* cur = head;
	while(cur != NULL) {
		if(cur->data == pos) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//尾插一个元素
void LinkListPushBack(LinkNode** head , LinkNodeType value) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		//为空链表
		*head = CreateNode(value);
		return;
	}
	//链表非空
	LinkNode* cur = *head;
	while(cur->next != NULL) {
		cur = cur->next;
	}
	LinkNode* new_node = CreateNode(value);
	cur->next = new_node;
	new_node->next = NULL;
}

//删除尾部元素
void LinkListPopBack(LinkNode** head) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		//空链表
		return;
	}
	if((*head)->next == NULL) {
		//只有一个元素

	DestroyNode(*head);
	*head == NULL;
		return;
	}
	LinkNode* cur = *head;
	LinkNode* pre = NULL;
	while(cur->next != NULL) {
		pre = cur;
		cur = cur->next;
	}
	LinkNode* to_delete = pre->next;
	pre->next == NULL;
	DestroyNode(to_delete);
	return;
}


void LinkListPushFront(LinkNode** head , LinkNodeType value) {
	if(head == NULL) {
		//非法输入
		return;
	}
	LinkNode* new_node = CreateNode(value);
	if(*head == NULL) {
		//空链表
		new_node->next = NULL;
		*head = new_node;
		return;
	}
	new_node->next = *head;
	*head = new_node;
	return;
}

void LinkListPopFront(LinkNode** head) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		// 空链表
		return;
	}
	LinkNode* to_delete = *head;
	*head = to_delete->next;
	DestroyNode(to_delete);
	return;
}

void LinkListInsertAfter(LinkNode* head, LinkNode* pos, LinkNodeType value) {
	if(head == NULL) {
		// 空链表
		return;
	}
	if(pos == NULL) {
		//pos 位置非法
		return;
	}
	LinkNode* new_node = CreateNode(value);
	new_node->next = pos->next;
	pos->next = new_node;
	return;
}
void LinkListInsertBefore(LinkNode** head, LinkNode* pos, LinkNodeType value) {
	if(head == NULL ||pos == NULL) {
		return;
	}
	if(*head == NULL) {
		return;
	}
	LinkNode* new_node = CreateNode(value);
	if(pos == (*head)) {
		new_node->next = *head;
		*head = new_node;
		return;
	}
	LinkNode* cur = *head;
	for(; cur != pos ; cur=cur->next) {
		if(cur->next == pos) {
			break;
		}
	}
	if(cur == NULL) {
		//pos不存在
		return;
	}
	new_node->next = cur->next;
	cur->next = new_node;
	return;
}
//不遍历链表在pos之前插入
void LinkListInsertBefore2(LinkNode* head ,LinkNode* pos ,LinkNodeType value) {
	if(head == NULL||pos == NULL) {
		//非法输入
		return;
	}
	LinkListInsertAfter(head , pos ,pos->data);
	pos->data = value;
	return;
}
//删除指定位置的元素
void LinkListErase(LinkNode** head ,LinkNode* pos) {
	if(head == NULL || pos == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		//空链表
		return;
	}
	if(pos == *head) {
		LinkListPopFront(&pos);
		return;
	}

	LinkNode* cur = *head;
	for(; cur != NULL;cur=cur->next) {
		if(cur->next == pos) {
			break;
		}
	}
	LinkNode* to_delete = cur->next;
	cur->next = pos->next;
	DestroyNode(to_delete);
	return;
}

//删除指定值的元素
void LinkListRemove(LinkNode** head, LinkNodeType value) {
	if(head == NULL) {
		return;
	}
	LinkNode* cur = *head;
	if((*head)->data == value) {
		LinkListPopFront(&cur);
		return;
	}
	for(;cur->next->next != NULL;cur=cur->next) {
		if(cur->next->data == value) {
			LinkNode* to_delete = cur->next;
			cur->next = to_delete->next;
			DestroyNode(to_delete);
			return;
		}
	}
	return;
}

//删除所有指定元素
void LinkListRemoveAll(LinkNode** head ,LinkNodeType value) {
	if(head == NULL) {
		return;
	}
	if(*head == NULL) {
		return;
	}
	while(1){
		LinkNode* cur = LinkListFind(*head,value);
		if(cur == NULL) {
			return;
		}
		LinkListErase(head,cur);
	}
}

//判空链表
int LinkListEmpty(LinkNode* head) {
	if(head == NULL) {
		return 1;
	}else {
		return 0;
	}
}

void Swap ( LinkNodeType* a , LinkNodeType* b ) {
	LinkNodeType tmp = *a;
	*a = *b;
	*b = tmp;
}
void LinkListBubbleSort(LinkNode* head) {
	if(head == NULL) {
		//空链表
		return;
	}
	if(head->next == NULL) {
		//只有一个元素
		return;
	}
	LinkNode* count = head;
	LinkNode* tail = NULL;
	for(;count != NULL;count = count->next){
		LinkNode* cur = head;
		while(cur->next != tail) {
			if(cur->data > cur->next->data) {
				Swap(&cur->data,&cur->next->data);
			}
			cur = cur->next;
		}
		tail = cur;
	}
}


LinkNode* LinkListMerge(LinkNode* head1 , LinkNode* head2) {
	if(head1 == NULL) {
		//空链表
		return head2;
	}
	if(head2 == NULL) {
		//空链表
		return head1;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	//用来指向链表的头结点和尾结点
	LinkNode* new_head = NULL;
	LinkNode* new_tail = NULL;

	while(cur1 != NULL && cur2 != NULL) {
		if(cur1->data < cur2->data) {
			if(new_tail == NULL){
				new_head = new_tail = cur1;
			}else{
				new_tail->next = cur1;
				new_tail = new_tail->next;
			}
			cur1 = cur1->next;
		}
		else {
			if(new_tail == NULL){
				new_head = new_tail = cur2;
			}else{
				new_tail->next = cur2;
				new_tail = new_tail->next;
			}
			cur2 = cur2->next;
		}
	}
	//有一方已经先到达末尾，需要把剩余的一方追加到链表后面
	if(cur1 != NULL) {
		new_tail->next = cur1;
	}else{
		new_tail->next = cur2;
	}
	return new_head;
}

LinkNode*  LinkListFindMidNode(LinkNode* head) {
	if(head == NULL ) {
		//空链表
		return NULL;
	}
	LinkNode* slow = head;
	LinkNode* fast = head;

	while(fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

LinkNode* LinkListFindLastKNode(LinkNode* head , size_t K) {
	if(head == NULL) {
		//空链表
		return NULL;
	}
	LinkNode* fast = head;
	LinkNode* slow = head;
	size_t i = 0;
	for(;i < K ;++i ) {
		if(fast == NULL) {
			//K的值超过了链表的长度
			return NULL;
		}
		fast = fast->next;
	}
	while(fast != NULL) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}


void LinkListEraseLastKNode(LinkNode** head , size_t K) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		//空链表
		return;
	}
	int len = LinkListSize(*head);
	if(K > len) {
		return;
	}
	if(K == len) {
		//要删除的为第一个结点
		LinkNode* to_delete = *head;
		*head = (*head)->next;
		DestroyNode(to_delete);
		return;
	}
	LinkNode* pre = *head;
	LinkNode* cur = *head;

	int i = 0;
	for(; i < K+1;++i) {
		cur = cur->next;
	}
	while(cur != NULL) {
		cur = cur->next;
		pre = pre->next;
	}
	LinkNode* to_delete = pre->next;
	pre->next = to_delete->next;
	DestroyNode(to_delete);
	return;
}

LinkNode* LinkListHasCycle(LinkNode* head) {
	if(head == NULL) {
		//空链表
		return NULL;
	}
	LinkNode* fast = head;
	LinkNode* slow = head;

	while(fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow) {
			return fast;
		}
	}
	return NULL;
}


size_t LinkListCycleLen(LinkNode* head) {
	if(head == NULL) {
		//空链表
		return 0;
	}
	LinkNode* meet_node = LinkListHasCycle(head);
	LinkNode* cur = meet_node->next;
	size_t len = 1;
	while(cur != meet_node) {
		cur = cur->next;
		++len;
	}
	return len;
}

LinkNode* LinkListCycleEntry(LinkNode* head) {
	if(head ==NULL) {
  	//空链表
		return NULL;
	}
	LinkNode* meet_node = LinkListHasCycle(head);
	if(meet_node == NULL) {
		return NULL;
	}

	LinkNode* cur1 = head;
	LinkNode* cur2 = meet_node;
	while(cur1 != cur2) {
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;
}

void LinkListReverse(LinkNode** head) {
	if(head ==NULL ) {
		//非法输入
		return;
	}
	if(*head == NULL){
		//空链表
		return;
	}
	if((*head)->next == NULL) {
		//只有一个元素
		return;
	}

	LinkNode* cur = (*head)->next;
	LinkNode* pre = *head;

	while(cur->next != NULL) {
		LinkNode* next = cur->next;
		//修改cur的next的指向
		cur->next = pre;
		//更新cur和next
		pre = cur;
		cur = next;
	}
	*head = pre;
}

void LinkListReverse2(LinkNode** head) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		//空链表
		return;
	}
	if((*head)->next == NULL) {
		//只有一个元素
		return;
	}
	LinkNode* cur = *head;
	while(cur->next != NULL) {
		LinkNode* to_delete = cur->next;
		//把这个结点删除掉
		cur->next = to_delete->next;
		//把这个刚刚删除的结点插入到链表的头部
		to_delete->next = *head;
		*head = to_delete;
	}
}


LinkNode* JosephCircle(LinkNode* head , int M) {
	if(head == NULL) {
		//空链表
		return NULL;
	}
	if(head->next == head) {
		//只有一个结点的环
		return head;
	}
	LinkNode* cur = head;
	while(cur->next != cur) {
		int i = 1;
		for(;i < M;++i) {
			cur = cur->next;
		}
		//cur指向的元素就是要被删掉的元素
		printf("%c\n",cur->data);
		cur->data = cur->next->data;
		LinkNode* to_delete = cur->next;
		cur->next = to_delete->next;
		DestroyNode(to_delete);
	}
	return cur;
}


void LinkListReversePrint(LinkNode* head) {
	if(head == NULL) {
		//空链表
		return;
	}else{
		LinkListReversePrint(head->next);
	}
	printf("[%c|%p] ",head->data,head);
}

void LinkListEraseNotLast(LinkNode** head,LinkNode* pos) {
	if(head == NULL) {
		//非法输入
		return;
	}
	if(*head == NULL) {
		//空链表
		return;
	}
	if((*head)->next == NULL) {
		//只有一个元素
		return;
	}
	LinkNode* cur = pos;
	cur->data = cur->next->data;
	LinkNode* to_delete = cur->next;
	cur->next = to_delete->next;
	DestroyNode(to_delete);
	
}

//判断是否相交，求交点（不带环）
LinkNode* LinkListHasCross(LinkNode* head1, LinkNode* head2) {
	if(head1 == NULL || head2 == NULL) {
		//空链表
		return NULL;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	int len1 = LinkListSize(head1);
	int len2 = LinkListSize(head2);
	int i = 0;
	if(len1 > len2 ){
		for(i = 0;i < len1 - len2;i++) {
			cur1 = cur1->next;
		}
	}else {
		for(i = 0;i < len2 - len1; i++) {
			cur2 = cur2->next;
		}
	}
	while(cur1 != NULL && cur2 != NULL) {
		if(cur1 == cur2 ) {
			return cur1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return NULL;

}
int  LinkListHasCross1(LinkNode* head1, LinkNode* head2) {
	if(head1 == NULL || head2 == NULL) {
		//空链表
		return 0;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	int len1 = LinkListSize(head1);
	int len2 = LinkListSize(head2);
	int i = 0;
	if(len1 > len2 ){
		for(i = 0;i < len1 - len2;i++) {
			cur1 = cur1->next;
		}
	}else {
		for(i = 0;i < len2 - len1; i++) {
			cur2 = cur2->next;
		}
	}
	while(cur1 != NULL && cur2 != NULL) {
		if(cur1 == cur2 ) {
			return 1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return 0;
}

int LinkListHasCrossWithCycle(LinkNode* head1 , LinkNode* head2) {
	if(head1 == NULL && head2 == NULL) {
		//空链表
		return 0;
	}
	//求连个链表的入口点
	LinkNode* entry1 = LinkListCycleEntry(head1);
	LinkNode* entry2 = LinkListCycleEntry(head2);
	//如果两个链表都不带环，则按照前面的方法判定
	if(entry1 == NULL && entry2 == NULL) {
		return LinkListHasCross1(head1 , head2);
	}
	//如果一个带环一个不带环，则不相交
	if((entry1 == NULL && entry2 != NULL)||(entry1 != NULL && entry2 == NULL)) {
		return 0;
	}
	//如果两个链表都带环
	//a）如果连个入口相同，说明相交，并且是环外相交
	if(entry1 == entry2) {
		return 1;
	}
	//b）如果从一个入口点出发，绕环一周，能到达第二个入口点说明也是相交，并且是环上相交
	LinkNode* cur = entry1->next;
	while(cur != entry1) {
		if(cur == entry2) {
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

LinkNode* LinkListHasCrossWithCyclePos(LinkNode* head1 , LinkNode* head2) {
	if(head1 == NULL && head2 == NULL) {
		return NULL;
	}
	//交点在环外
	LinkNode* entry1 = LinkListCycleEntry(head1);
	LinkNode* entry2 = LinkListCycleEntry(head2);
	if(entry1 == entry2) {
		LinkNode* cur1 = head1;
		LinkNode* cur2 = head2;
		size_t len1 = 0;
		size_t len2 = 0;
		for(cur1 = head1;cur1 != entry1;cur1 = cur1->next){
			len1++;
		}
		for(cur2 = head2 ;cur2 != entry2;cur2 = cur2->next){
			len2++;
		}
		if(len1 > len2) {
			int i = 0;
			for(i=0;i<len1-len2;i++){
				cur1 = cur1->next;
			}
			while(cur1 != NULL && cur2 != NULL) {
				if(cur1 == cur2) {
					return cur1;
				}
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
		}else {
			int i = 0;
			for(i=0;i<len2-len1;i++){
				cur2 = cur2->next;
			}
			while(cur1 != NULL && cur2 != NULL){
				if(cur1 == cur2) {
					return cur1;
				}
				cur1 = cur1->next;
			
				cur2 = cur2->next;
			}
		}
	}
	//环上相交
	if(entry1 != entry2){
	 	LinkNode* cur = entry1;
		for(;cur != entry2;cur = cur->next);
			return cur; 
	}
}

LinkNode* LinkListUnionSet(LinkNode* head1 , LinkNode* head2) {
	if(head1 == NULL || head2 == NULL) {
		return NULL;
	}
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	LinkNode* new_head = NULL;
	LinkNode* new_tail = NULL;
	while(cur1 != NULL && cur2 != NULL) {
		if(cur1->data < cur2->data){
			cur1 = cur1->next;
		}else if(cur1->data > cur2->data) {
			cur2 = cur2->next;
		}else {
			//两个相等
			if(new_head == NULL){
				new_head = new_tail = CreateNode(cur1->data);
			}else{
				new_tail->next = CreateNode(cur1->data);
				new_tail = new_tail->next;
			}
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
	}
	return new_head;
}

//复杂链表的复制
typedef struct ComplexNode{
	LinkNodeType data;
	struct ComplexNode* next;
	struct ComplexNode* random;
}ComplexNode;

ComplexNode* CreateComplexNode(LinkNodeType value){
	ComplexNode* new_node = (ComplexNode*)malloc(sizeof(ComplexNode));
	new_node->data = value;
	new_node->next = NULL;
	new_node->random = NULL;
	return new_node;
}

size_t Diff(ComplexNode* src , ComplexNode* dest){
	size_t offset = 0;
	while(src != NULL){
		if(src == dest){
			break;
		}
		++offset;
		src=src->next;
	}
	if(src==NULL){
		return (size_t)-1;
	}
	return offset;
}
ComplexNode* Step(ComplexNode* head ,size_t offset){
	ComplexNode* cur = head;
	size_t i = 0;

	while(1){
		if(cur == NULL){
			return NULL;
		}
		if(i>=offset){
			return cur;
		}
		++i;
		cur = cur->next;
	}
	return NULL;
}

ComplexNode* CopyComplexList(ComplexNode* head){
	if(head == NULL) {
		return NULL;
	}
	//先按照简单链表来进行复制
	ComplexNode* new_head = NULL;
	ComplexNode* new_tail = NULL;
	ComplexNode* cur = head;
	for(;cur != NULL;cur = cur->next){
		ComplexNode* new_node = CreateComplexNode(cur->data);
		if(new_head == NULL){
			new_head = new_tail = cur;
		}else {
			new_tail->next = new_node;
			new_tail = new_tail->next;
		}
	}
	//遍历旧链表，找到每个链表节点random指针相对与链表头部的偏移量
	//遍历新链表，根据偏移量，设置新链表的random
	ComplexNode* new_cur = new_head;
	for(cur = head;cur!=NULL;cur=cur->next,new_cur=new_cur->next){
		if(cur->random == NULL){
			new_cur->random = NULL;
			continue;
		}
		//通过Diff函数来计算两个节点的偏移量
		size_t offset = Diff(head ,cur->random);
		//通过Step函数，相当与求出从new_head出发，走了offset步，到达的位置是谁
		new_cur->random = Step(new_head,offset);
	}
	return new_head;
}
////////////////////////////////////////////////////
//以下为测试代码
///////////////////////////////////////////////////

#include <stdio.h>
#define TEST_HEADER printf("\n=====================%s====================\n",__FUNCTION__);


void TestInit() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
}

void TestFind() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode* pos = LinkListFind(head , 'c');
	LinkListPrintChar(head , "查找任意位置的元素");
	printf("pos expected c , actual %c\n",*pos);
}

void TestSize() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	int ret = LinkListSize(head);
	LinkListPrintChar(head , "求链表的长度");
	printf("ret excepcted 4,actual %d\n",ret);
}

void TestPushBack() {

	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkListPrintChar(head , "尾插一个元素");
}

void TestPopBack() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkListPopBack(&head);
	LinkListPrintChar(head , "尾删一个元素");

}

void TestPushFront() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkListPushFront(&head , 'x');
	LinkListPrintChar(head , "头插一个元素");

}

void TestPopFront() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkListPopFront(&head);
	LinkListPrintChar(head , "头删一个元素");

}

void TestInsertAfter() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	
	LinkNode* pos = head->next;
	LinkListInsertAfter(head ,pos,'x');
	LinkListPrintChar(head ,"在pos之后插入一个元素");

}

void TestInsertBefore() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode* pos = head->next;
	LinkListInsertBefore(&head ,pos,'x');
	LinkListPrintChar(head ,"在pos之前插入一个元素");

}

void TestInsertBefore2() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode* pos = head->next;
	LinkListInsertBefore2(head , pos,'x');
	LinkListPrintChar(head ,"不遍历在结点前插入一个结点");

}

void TestErase() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode* pos = head->next;
	LinkListErase(&head ,pos);
	LinkListPrintChar(head ,"删除指定位置的元素");
}

void TestRemove(){
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkListRemove(&head ,'b');
	LinkListPrintChar(head ,"删除指定元素的值");
}

void TestRemoveAll(){
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'b');

	LinkListRemoveAll(&head , 'b');
	LinkListPrintChar(head , "删除所有指定元素");

}

void TestEmpty() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');

	int ret = LinkListEmpty(head);
	printf("ret expected 0,actaul %d\n",ret);

}
void TestBubbleSort() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'e');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'a');

	LinkListBubbleSort(head);
	LinkListPrintChar(head , "冒泡排序");

}

void TestMerge() {
	TEST_HEADER;
	LinkNode* head1;
	LinkListInit(&head1);

	LinkListPushBack(&head1 , 'a');
	LinkListPushBack(&head1 , 'b');
	LinkListPushBack(&head1 , 'c');
	LinkListPushBack(&head1 , 'd');

	LinkNode* head2;
	LinkListInit(&head2);

	LinkListPushBack(&head2 , 'e');
	LinkListPushBack(&head2 , 'f');

	LinkNode* new_head = LinkListMerge(head1 , head2);
	LinkListPrintChar(new_head , "合并两个链表");

}

void TestMidNode() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode*  Mid = LinkListFindMidNode(head);
	LinkListPrintChar(head , "查找中间元素");
	printf("Mid expected b,actual %c\n",*Mid);

}

void TestFindLastKNode() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode* LastK = LinkListFindLastKNode(head , 2);
	LinkListPrintChar(head , "查找倒数第K个结点");
	printf("LastK expected c , actual %c\n",*LastK);
}

void TestEraseLastKNode() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkListEraseLastKNode(&head , 2);
	LinkListPrintChar(head , "删除倒数第K个结点");

}

void TestHasCycle() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'e');

	LinkNode* pos_t = LinkListFind(head , 'e');
	pos_t->next = head->next;

	LinkNode* ret = LinkListHasCycle(head);
	printf("ret expected e,actual %c\n",*ret);
	if(ret == NULL) {
		printf("链表无环\n");
	}else{
		printf("链表有环\n");
	}
}

void TestCycleLen() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');

	LinkNode* cur = head;
	while(cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = head->next;

	int ret = LinkListCycleLen(head);
	printf("ret expected 3,actual %d\n",ret);
}

void TestCycleEntry() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'e');

	LinkNode* pos_t = LinkListFind(head , 'e');
	pos_t->next = head->next;

	LinkNode* entry = LinkListCycleEntry(head);
	printf("entry expected b , actual %c\n",*entry);
}

void TestReverse() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'e');

	//LinkListReverse(&head);
	LinkListPrintChar(head , "逆置单链表");

}

void TestReverse2() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'e');

	LinkListReverse2(&head);
	LinkListPrintChar(head , "逆置链表");

}

void TestJosephCircle() {
	TEST_HEADER;
	LinkNode* a = CreateNode('a');
	LinkNode* b = CreateNode('b');
	LinkNode* c = CreateNode('c');
	LinkNode* d = CreateNode('d');
	LinkNode* e = CreateNode('e');
	LinkNode* f = CreateNode('f');
	LinkNode* g = CreateNode('g');
	LinkNode* h = CreateNode('h');

	a->next = b;
	b->next = c;
	c->next = d;
	d->next = e;
	e->next = f;
	f->next = g;
	g->next = h;
	h->next = a;

	LinkNode* survive = JosephCircle(a , 5);
	printf("survive is %c\n",survive->data);
}

void TestReversePrint() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'e');

	LinkListPrintChar(head , "逆序打印链表");
	LinkListReversePrint(head);

}

void TestEraseNotLast() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	LinkListPushBack(&head , 'a');
	LinkListPushBack(&head , 'b');
	LinkListPushBack(&head , 'c');
	LinkListPushBack(&head , 'd');
	LinkListPushBack(&head , 'e');

	LinkNode* pos_t = LinkListFind(head , 'c');
	LinkListEraseNotLast(&head , pos_t);
	LinkListPrintChar(head , "删除非尾结点");

}

void TestHasCross() {
	TEST_HEADER;
	LinkNode* head1;
	LinkListInit(&head1);

	LinkListPushBack(&head1 , 'a');
	LinkListPushBack(&head1 , 'b');
	LinkListPushBack(&head1 , 'c');
	LinkListPushBack(&head1 , 'd');
	LinkListPushBack(&head1 , 'e');

	LinkNode* head2;
	LinkListInit(&head2);

	LinkListPushBack(&head2 , 'a');
	LinkListPushBack(&head2 , 'b');
	LinkListPushBack(&head2 , 'c');

	LinkNode* node = LinkListFind(head2 , 'c');
	node->next = head1->next;
	LinkNode* new_node = LinkListHasCross(head1 , head2);
	printf("new_node ecpected b , actaul %c\n",*new_node);
}

void TestHasCrossWithCyle(){
	//两个链表都不带环
	TEST_HEADER;
	LinkNode* head1;
	LinkListInit(&head1);

	LinkListPushBack(&head1 , 'a');
	LinkListPushBack(&head1 , 'b');
	LinkListPushBack(&head1 , 'c');
	LinkListPushBack(&head1 , 'd');
	LinkListPushBack(&head1 , 'e');

	LinkNode* head2;
	LinkListInit(&head2);
	LinkListPushBack(&head1 , 'a');
	LinkListPushBack(&head1 , 'b');
	LinkListPushBack(&head1 , 'c');

	LinkNode* pos_c = LinkListFind(head2,'c');
	pos_c->next = head1->next;
	int ret1 = LinkListHasCrossWithCycle(head1 ,head2);
	printf("ret1 expected 1,actual %d\n",ret1);
	

}

void TestUnionSet(){
	TEST_HEADER;
	LinkNode* head1;
	LinkListInit(&head1);

	LinkListPushBack(&head1 , 'a');
	LinkListPushBack(&head1 , 'b');
	LinkListPushBack(&head1 , 'c');
	LinkListPushBack(&head1 , 'd');
	LinkListPushBack(&head1 , 'e');

	LinkNode* head2;
	LinkListInit(&head2);
	LinkListPushBack(&head2 , 'a');
	LinkListPushBack(&head2 , 'b');
	LinkListPushBack(&head2 , 'c');
	
	LinkNode* head = LinkListUnionSet(head1 ,head2);
	LinkListPrintChar(head,"两个已排序链表中相同的数");
}

void PrintComplexList(ComplexNode* head ,const char* msg){
	printf("[%s]\n",msg);
	ComplexNode* cur = head;
	for(;cur!=NULL;cur=cur->next){
		printf("[%c] ",cur->data);
	}
	printf("\n");
	for(cur=head;cur!=NULL;cur=cur->next){
		if(cur->random ==NULL){
			printf("[NULL]");
			continue;
		}
		printf("[%c] ",cur->random->data);
	}
	printf("\n");
}
void TestComplexListCopy(){
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);

	ComplexNode* a = CreateComplexNode('a');
	ComplexNode* b = CreateComplexNode('b');
	ComplexNode* c = CreateComplexNode('c');
	ComplexNode* d = CreateComplexNode('d');
	a->next = b;
	b->next = c;
	c->next = d;
	d->next = NULL;
	a->random = c;
	b->random = a;
	c->random = NULL;
	d->random = d;

	ComplexNode* new_head = CopyComplexList(a);
	PrintComplexList(new_head,"拷贝复杂链表");
}
int main() {
	TestInit();
	TestPushBack();
	TestSize();
	TestFind();
	TestBubbleSort();
	TestMerge();
	TestMidNode();
	TestFindLastKNode();
	TestEraseLastKNode();
	TestHasCycle();
	TestCycleLen();
	TestCycleEntry();
	TestReverse();
	TestReverse2();
	TestJosephCircle();
	TestReversePrint();
	TestEraseNotLast();
	TestPopBack();
	TestPushFront();
	TestPopFront();
	TestInsertAfter();
	TestInsertBefore();
	TestInsertBefore2();
	TestErase();
	TestRemove();
	TestRemoveAll();
	TestEmpty();
	TestHasCross();
	TestUnionSet();
	TestComplexListCopy();
	//TestHasCrossWithCycle();
	return 0;
}
