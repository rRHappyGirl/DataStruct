#pragma once

typedef char TreeNodeType;
//使用孩子表示法来表示一棵树
typedef struct TreeNode {
	TreeNodeType data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

//对于链表来说，使用链表的头节点指针来表示一个链表
//对于二叉树来说，使用跟结点的指针来表示一棵树

void TreeInit(TreeNode** pRoot);

void TreePreOrder(TreeNode* root);

void TreeInOrder(TreeNode* root);

void TreePostOrder(TreeNode* root);

void TreeLevelOrder(TreeNode* root);

//输入一个数组（数组中的每个元素就是树上的结点），根据数组的内容
//构建出一颗树，数组中元素的内容符合树的先序遍历结果（包含所有空结点）
TreeNode* TreeCreate(TreeNodeType arry[],size_t size,char null_node);
