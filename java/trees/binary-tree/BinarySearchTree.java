public class BinarySearchTree {
    class SkipNode {
        int key;
        SkipNode left, right;

        public SkipNode(int item) {
            key = item;
            left = right = null;
        }
    }

    SkipNode root;

    BinarySearchTree() {
        root = null;
    }

    void insert(int key) {
        root = insertRec(root, key);
    }

    SkipNode insertRec(SkipNode root, int key) {
        // Time complexity: O(h), where h is the height of the tree
        if (root == null) {
            root = new SkipNode(key);
            return root;
        }

        if (key < root.key)
            root.left = insertRec(root.left, key);
        else if (key > root.key)
            root.right = insertRec(root.right, key);

        return root;
    }

    void deleteKey(int key) {
        root = deleteRec(root, key);
    }

    SkipNode deleteRec(SkipNode root, int key) {
        // Time complexity: O(h), where h is the height of the tree
        if (root == null) return root;

        if (key < root.key)
            root.left = deleteRec(root.left, key);
        else if (key > root.key)
            root.right = deleteRec(root.right, key);
        else {
            if (root.left == null)
                return root.right;
            else if (root.right == null)
                return root.left;

            root.key = minValue(root.right);
            root.right = deleteRec(root.right, root.key);
        }

        return root;
    }

    int minValue(SkipNode root) {
        // Time complexity: O(h), where h is the height of the tree
        int minv = root.key;
        while (root.left != null) {
            minv = root.left.key;
            root = root.left;
        }
        return minv;
    }

    void deleteKeyIterative(int key) {
        root = deleteIterative(root, key);
    }

    SkipNode deleteIterative(SkipNode root, int key) {
        // Time complexity: O(h), where h is the height of the tree
        SkipNode parent = null;
        SkipNode current = root;

        while (current != null && current.key != key) {
            parent = current;
            if (key < current.key)
                current = current.left;
            else
                current = current.right;
        }

        if (current == null) return root;

        if (current.left == null || current.right == null) {
            SkipNode newCurr;
            if (current.left == null)
                newCurr = current.right;
            else
                newCurr = current.left;

            if (parent == null)
                return newCurr;

            if (current == parent.left)
                parent.left = newCurr;
            else
                parent.right = newCurr;
        } else {
            SkipNode p = null;
            SkipNode temp;

            temp = current.right;
            while (temp.left != null) {
                p = temp;
                temp = temp.left;
            }

            if (p != null)
                p.left = temp.right;
            else
                current.right = temp.right;

            current.key = temp.key;
        }

        return root;
    }

    void inorder() {
        inorderRec(root);
    }

    void inorderRec(SkipNode root) {
        // Time complexity: O(n), where n is the number of nodes in the tree
        if (root != null) {
            inorderRec(root.left);
            System.out.print(root.key + " ");
            inorderRec(root.right);
        }
    }

    public static void main(String[] args) {
        BinarySearchTree tree = new BinarySearchTree();

        tree.insert(50);
        tree.insert(30);
        tree.insert(20);
        tree.insert(40);
        tree.insert(70);
        tree.insert(60);
        tree.insert(80);

        System.out.println("Inorder traversal of the given tree");
        tree.inorder();

        System.out.println("\n\nDelete 20");
        tree.deleteKey(20);
        System.out.println("Inorder traversal of the modified tree");
        tree.inorder();

        System.out.println("\n\nDelete 30");
        tree.deleteKey(30);
        System.out.println("Inorder traversal of the modified tree");
        tree.inorder();

        System.out.println("\n\nDelete 50");
        tree.deleteKey(50);
        System.out.println("Inorder traversal of the modified tree");
        tree.inorder();
    }
}