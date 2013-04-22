#include <iostream>
using namespace std;

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    TreeNode *doFlatten(TreeNode *root) {
		cout << "inside doFlatten: " << root->val << endl;
        if( root->left == NULL && root->right == NULL ) {
            return root;
        }
        TreeNode *ln = NULL, *rn = NULL;
        if( root->left != NULL ) {
            ln = doFlatten(root->left);
        }
        if( root->right != NULL ) {
            rn = doFlatten(root->right);
        }
        TreeNode *tl = root->left, *tr = root->right;
        TreeNode *result = NULL;
        if( ln != NULL ) {
            root->right = tl;
            tl->left = root;
            result = ln;
        }
        if( rn != NULL ) {
            if( result != NULL ) {
                result->right = tr;
                tr->left = result;
            }
            result = rn;
        }
        return result;
    }
    void flatten(TreeNode *root) {
        if( root == NULL ) return;
		cout << "inside flatten" << endl;
        doFlatten(root);
    }
};

int main() {
	TreeNode *root = new TreeNode(0);
	TreeNode *tmp = new TreeNode(1);
	root->right = tmp;
	tmp->left = root;
	Solution solution;
	solution.flatten(root);
	return 1;
}
