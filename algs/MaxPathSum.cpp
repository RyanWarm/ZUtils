/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 #include <iostream>
 using namespace std;
 
 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    int maxPath(TreeNode *root, int *result) {
		if( root == NULL ) return 0;
		cout << "inside max path: " << root->val << ":" << *result << endl;
        if( root->left == NULL && root->right == NULL ) {
            if( root->val > *result ) *result = root->val;
			cout << "change result: " << *result << endl;
            return root->val;
        }
        int left = maxPath(root->left, result);
        int right = maxPath(root->right, result);
        int m = max(max(left, right), left+right+root->val);
        if( m > *result) *result = m;
        return max(left+root->val, right+root->val);
    }
    int maxPathSum(TreeNode *root) {
        if( root == NULL ) return 0;
        
		int *tmp = new int(-1);
        maxPath(root, tmp);
		cout << "return: " << *tmp << endl;
        return *tmp;
    }
};
int main() {
    TreeNode *root = new TreeNode(1);
	TreeNode *tmp = new TreeNode(2);
	root->left = tmp;
    Solution solution;
    int result = solution.maxPathSum(root);
	cout << "final return" << result << endl;
    cout << result << endl;
    return 1;
}
