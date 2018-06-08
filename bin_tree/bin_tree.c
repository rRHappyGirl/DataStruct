#include <stdio.h>
#include <stdlib.h>
#include "bin_tree.h"
#include "seqqueue.h"

TreeNode* CreateTreeNode(TreeNodeType value){
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	new_node->data = value;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

void TreeDestroy(TreeNode* node){
	free(node);
}

void TreeInit(TreeNode** pRoot){
	if(pRoot == NULL){
		//非法输入
		return;
	}
	*pRoot = NULL;
	return;
}

void TreePreOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//先访问根结点，访问即打印
	printf("%c ",root->data);
	//然后递归的遍历左子树
	TreePreOrder(root->lchild);
	//最后在递归的遍历右子树
	TreePreOrder(root->rchild);
	return;
}

void TreeInOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//先递归的遍历左子树
	TreeInOrder(root->lchild);
	//再访问根结点
	printf("%c ",root->data);
	//最后递归的遍历右子树
	TreeInOrder(root->rchild);
	return;
}

void TreePostOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//先递归的遍历左子树
	TreePostOrder(root->lchild);
	//再递归的遍历右子树
	TreePostOrder(root->rchild);
	//最后访问根结点
	printf("%c ",root->data);
	return;
}

void TreeLevelOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	SeqQueue queue;
	SeqQueueInit(&queue);
	SeqQueuePush(&queue,root);
	while(1){
		SeqQueueType front;
		int ret = SeqQueueFront(&queue,&front);
		if(ret == 0){
			//如果队列取队首元素失败，说明队列为空
			//如果队列为空就说明遍历结束了
			break;
		}
		//访问树中的元素，打印当前值
		printf("%c ",front->data);
		//把当前队首元素出队列
		SeqQueuePop(&queue);
		//把当前元素的左右子树入队列
	
		if(front->lchild != NULL){
			SeqQueuePush(&queue,front->lchild);
		}
		if(front->rchild != NULL){
			SeqQueuePush(&queue,front->rchild);
		}
	}
	return;
}

TreeNode* _TreeCreate(TreeNodeType arry[],size_t size,size_t* index,TreeNodeType null_node){
	if(index == NULL){
		//非法输入
		return NULL;
	}
	if(*index >= size){
		return NULL;
	}
	if(arry[*index] == null_node){
		return NULL;
	}
	TreeNode* new_node = CreateTreeNode(arry[*index]);
	++(*index);
	new_node->lchild = _TreeCreate(arry,size,index,null_node);
	++(*index);
	new_node->rchild = _TreeCreate(arry,size,index,null_node);
	return new_node;
}

TreeNode* TreeCreate(TreeNodeType arry[],size_t size,char null_node){
	//表示当前取数组中的那个元素
	size_t index = 0;
	return _TreeCreate(arry,size,&index,null_node);
}

TreeNode* TreeClone(TreeNode* root){
	if(root == NULL){
		//空树
		return NULL;
	}
	//按照先序方式来遍历
	TreeNode* new_node = CreateTreeNode(root->data);
	new_node->lchild = TreeClone(root->lchild);
	new_node->rchild = TreeClone(root->rchild);
	return new_node;
}
//////////////////////////////////////
//以下为测试代码
/////////////////////////////////////
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n=============================%s===========================\n",__FUNCTION__)

void TestInit(){
	TEST_HEADER;
	TreeNode* root;
	TreeInit(&root);
	printf("root expected NULL,actual %p\n",root);
}

void TestPreOrder(){
	TEST_HEADER;
	TreeNode* a = CreateTreeNode('a');
	TreeNode* b = CreateTreeNode('b');
	TreeNode* c = CreateTreeNode('c');
	TreeNode* d = CreateTreeNode('d');
	TreeNode* e = CreateTreeNode('e');
	TreeNode* f = CreateTreeNode('f');
	TreeNode* g = CreateTreeNode('g');

	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	printf("前序遍历结果：");
	TreePreOrder(a);
	printf("\n");
}
void TestInOrder(){
	TEST_HEADER;
	TreeNode* a = CreateTreeNode('a');
	TreeNode* b = CreateTreeNode('b');
	TreeNode* c = CreateTreeNode('c');
	TreeNode* d = CreateTreeNode('d');
	TreeNode* e = CreateTreeNode('e');
	TreeNode* f = CreateTreeNode('f');
	TreeNode* g = CreateTreeNode('g');

	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	printf("中序遍历结果：");
	TreeInOrder(a);
	printf("\n");
}
void TestPostOrder(){
	TEST_HEADER;
	TreeNode* a = CreateTreeNode('a');
	TreeNode* b = CreateTreeNode('b');
	TreeNode* c = CreateTreeNode('c');
	TreeNode* d = CreateTreeNode('d');
	TreeNode* e = CreateTreeNode('e');
	TreeNode* f = CreateTreeNode('f');
	TreeNode* g = CreateTreeNode('g');

	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	printf("后序遍历结果：");
	TreePostOrder(a);
	printf("\n");
}
void TestLevelOrder(){
	TEST_HEADER;
	TreeNode* a = CreateTreeNode('a');
	TreeNode* b = CreateTreeNode('b');
	TreeNode* c = CreateTreeNode('c');
	TreeNode* d = CreateTreeNode('d');
	TreeNode* e = CreateTreeNode('e');
	TreeNode* f = CreateTreeNode('f');
	TreeNode* g = CreateTreeNode('g');

	a->lchild = b;
	a->rchild = c;
	b->lchild = d;
	b->rchild = e;
	e->lchild = g;
	c->rchild = f;
	printf("层序遍历结果：");
	TreeLevelOrder(a);
	printf("\n");
}

void TestCreate(){
	TEST_HEADER;
	TreeNodeType arry[] = "abd##eg###c#f##";
	TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');

	printf("\n先序遍历：");
	TreePreOrder(root);
	printf("\n中序遍历：");
	TreeInOrder(root);
	printf("\n后序遍历：");
	TreePostOrder(root);
	printf("\n层序遍历：");
	TreeLevelOrder(root);
	printf("\n");
}
void TestClone(){
	TEST_HEADER;
	TreeNodeType arry[] = "abd##eg###c#f##";
	TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');

	TreeNode* new_node = TreeClone(root);
	printf("\n先序遍历：");
	TreePreOrder(root);
	printf("\n中序遍历：");
	TreeInOrder(root);
	printf("\n后序遍历：");
	TreePostOrder(root);
	printf("\n层序遍历：");
	TreeLevelOrder(root);
	printf("\n");
}
int main(){
	TestInit();
	TestPreOrder();
	TestInOrder();
	TestPostOrder();
	TestLevelOrder();
	TestCreate();
	TestClone();
	return 0;
}
#endif
