import java.util.Stack;

public class Main {
    
    private static class Pair {
        int n, m;
        Pair(int n, int m) {
            this.n = n;
            this.m = m;
        }
    }
    
    public static int iterative(int n, int m) {
        Stack<Pair> stack = new Stack<>();
        
        stack.push(new Pair(n, m));

        while (!stack.isEmpty()) {
            Pair pair = stack.pop();
            n = pair.n;
            m = pair.m;

            if (n == 0) {
                m += 1;

                if (!stack.isEmpty()) {
                    Pair previous = stack.pop();
                    stack.push(new Pair(previous.n, m));
                }
            } else if (m == 0) {
                stack.push(new Pair(n - 1, 1));
            } else {
                stack.push(new Pair(n - 1, -1));
                stack.push(new Pair(n, m - 1));
            }
        }
        return m;
    }

    public static void main(String[] args) {
       System.out.println("f(1, 2) = " + iterative(1, 2));
        System.out.println("f(2, 2) = " + iterative(2, 2));
        System.out.println("f(3, 2) = " + iterative(3, 2));
    }
}
