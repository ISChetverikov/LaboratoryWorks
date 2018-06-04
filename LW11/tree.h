#pragma once

typedef struct TreeNode {
	char * word;
	int count;

	int height;
	struct TreeNode * left;
	struct TreeNode * right;

} TreeNode;

// helpers
int GetHeight(TreeNode * p);
int GetFactor(TreeNode * p);
void FixHeight(TreeNode * p);

// AVL
TreeNode * CreateNode(char * key);
TreeNode * RotateLeft(TreeNode * p);
TreeNode * RotateRight(TreeNode * p);
TreeNode * Balance(TreeNode *);
TreeNode * Insert(TreeNode * p, char * key);
void FreeAvl(TreeNode * p);

// Task
int GetWordCount(TreeNode * p, unsigned char c);

// Traverses
void PrintDepth(TreeNode * p);
void PrintWidth(TreeNode * p);
void PrintReverse(TreeNode * p);