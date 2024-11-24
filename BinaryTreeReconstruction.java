// TreeNode class definition
class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;

    TreeNode(int x) {
        val = x;
    }
}

public class BinaryTreeReconstruction {

    // Method to reconstruct binary tree from preorder and inorder traversal
    public TreeNode buildTreeFromPreIn(int[] preorder, int[] inorder) {
        return buildTreeFromPreIn(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1);
    }

    private TreeNode buildTreeFromPreIn(int[] preorder, int preStart, int preEnd, int[] inorder, int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) return null;

        TreeNode root = new TreeNode(preorder[preStart]);
        int inRoot = inStart;
        while (inorder[inRoot] != root.val) inRoot++;

        int leftTreeSize = inRoot - inStart;
        root.left = buildTreeFromPreIn(preorder, preStart + 1, preStart + leftTreeSize, inorder, inStart, inRoot - 1);
        root.right = buildTreeFromPreIn(preorder, preStart + leftTreeSize + 1, preEnd, inorder, inRoot + 1, inEnd);

        return root;
    }

    // Method to reconstruct binary tree from inorder and postorder traversal
    public TreeNode buildTreeFromInPost(int[] inorder, int[] postorder) {
        return buildTreeFromInPost(inorder, 0, inorder.length - 1, postorder, 0, postorder.length - 1);
    }

    private TreeNode buildTreeFromInPost(int[] inorder, int inStart, int inEnd, int[] postorder, int postStart, int postEnd) {
        if (inStart > inEnd || postStart > postEnd) return null;

        TreeNode root = new TreeNode(postorder[postEnd]);
        int inRoot = inStart;
        while (inorder[inRoot] != root.val) inRoot++;

        int leftTreeSize = inRoot - inStart;
        root.left = buildTreeFromInPost(inorder, inStart, inRoot - 1, postorder, postStart, postStart + leftTreeSize - 1);
        root.right = buildTreeFromInPost(inorder, inRoot + 1, inEnd, postorder, postStart + leftTreeSize, postEnd - 1);

        return root;
    }

    // Method to reconstruct binary search tree from preorder traversal
    public TreeNode buildBSTFromPreorder(int[] preorder) {
        return buildBSTFromPreorder(preorder, Integer.MIN_VALUE, Integer.MAX_VALUE, new int[]{0});
    }

    private TreeNode buildBSTFromPreorder(int[] preorder, int min, int max, int[] index) {
        if (index[0] >= preorder.length) return null;

        int val = preorder[index[0]];
        if (val < min || val > max) return null;

        TreeNode root = new TreeNode(val);
        index[0]++;
        root.left = buildBSTFromPreorder(preorder, min, val, index);
        root.right = buildBSTFromPreorder(preorder, val, max, index);

        return root;
    }

    public static void main(String[] args) {
        BinaryTreeReconstruction reconstruction = new BinaryTreeReconstruction();

        int[] preorder = {3, 9, 20, 15, 7};
        int[] inorder = {9, 3, 15, 20, 7};
        TreeNode root1 = reconstruction.buildTreeFromPreIn(preorder, inorder);

        int[] postorder = {9, 15, 7, 20, 3};
        TreeNode root2 = reconstruction.buildTreeFromInPost(inorder, postorder);

        int[] bstPreorder = {8, 5, 1, 7, 10, 12};
        TreeNode root3 = reconstruction.buildBSTFromPreorder(bstPreorder);
    }
}