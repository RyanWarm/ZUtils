/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubSymmetric(TreeNode *left, TreeNode *right) {
		if( left == NULL && right == NULL ) return true;
		else if( left != NULL && right != NULL) {
			if( left->val != right->val ) {
				return false;
			} else {
				return isSubSymmetric(left->left,right->right) && isSubSymmetric(left->right,right->left);
			}
		} else {
			return false;
		}
	}
    bool isSymmetric(TreeNode *root) {
		if( root == NULL ) return true;
		else return isSubSymmetric(root->left, root->right);
    }
};
