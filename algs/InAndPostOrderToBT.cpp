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
#include <vector>
#include <map>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
    void doConstruct(map<int, int> &inMap, vector<int> &postorder, TreeNode *result, int index, int start, int end) {
		cout << "inside construct: " << result->val << "," << index << "," << start << "," << end << endl;
        int i = end;
        while( i >= start && inMap[postorder[i]] > index ) {
            i--;
        }
        if( inMap[postorder[end]] > index ) {
            //right child
            result->right = new TreeNode(postorder[end]);
            if( i < end-1 ) {
                doConstruct(inMap, postorder, result->right, inMap[postorder[end]], i+1, end-1);
            }
        }
        if( i >= start ) {
            //left child
            result->left = new TreeNode(postorder[i]);
			if( i > start ) doConstruct(inMap, postorder, result->left, inMap[postorder[i]], start, i-1);
        }
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        map<int, int> inMap;
        int index = 0;
        for( vector<int>::iterator it = inorder.begin(); it != inorder.end(); ++it ) {
            inMap[*it] = index++;
        }
        int len = postorder.size();
        if( len == 0 ) return NULL;
        TreeNode *result = new TreeNode(postorder[len-1]);
        index = inMap[postorder[len-1]];
        doConstruct( inMap, postorder, result, index, 0, len-2 );
        return result;
    }
};
int main() {
	Solution solution;
	int tmp[] = {1,3,2};
	vector<int> inorder (tmp, tmp+3);
	int tmp1[] = {3,2,1};
	vector<int> postorder (tmp1, tmp1+3);
	TreeNode *result = solution.buildTree(inorder, postorder);
	cout << result->val << endl;
	if( result->left != NULL ) cout << "left: " << result->left->val << endl;
	if( result->right != NULL ) cout << "right: " << result->right->val << endl;
	result = result->right;
	if( result->left != NULL ) cout << "two left: " << result->left->val << endl;
	if( result->right != NULL ) cout << "two right: " << result->right->val << endl;
	return 1;
}
