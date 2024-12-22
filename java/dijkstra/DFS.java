public class DFS {

    public static Node dfs(Node start, int target) {
        System.out.println("Visiting Node " + start.value);
        if (start.value == target) {
            System.out.println("Found the node we're looking for!");
            return start;
        }

        for (int i = 0; i < start.children.length; i++) {
            Node result = dfs(start.children[i], target);
            if (result != null) {
                return result;
            }
        }

        System.out.println("Went through all children of " + start.value + ", returning to it's parent.");
        return null;
    }
}

class Node {
    Node[] children;
    int value;
}