/**
 * Definition for binary tree
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public int sumNumbers(TreeNode root) {
        if( root == null ) return 0;
        int result = 0;
        Stack<TreeNode> s = new Stack<TreeNode>();
        TreeNode curNode;
        s.push(root);
        StringBuffer sb = new StringBuffer();
        HashSet<TreeNode> visited = new HashSet<TreeNode>();
        
        while( !s.empty() ) {
            curNode = s.pop();
            if( !visited.contains(curNode) ) {
                sb.append(curNode.val);
                visited.add(curNode);
            }
            
            if( curNode.left == null && curNode.right == null ) {
                //leaf node
                result += Integer.parseInt(sb.toString());
                sb.setLength(sb.length()-1);
            } else {
                boolean v = false;
                if( curNode.right != null && !visited.contains(curNode.right) ) {
                    s.push(curNode.right);
                    v = true;
                }
                if( curNode.left != null && !visited.contains(curNode.left) ) {
                    s.push(curNode.left);
                    v = true;
                }
                if( !v ) {
                    sb.setLength(sb.length()-1);
                }
            }
        }
        return result;
    }
}