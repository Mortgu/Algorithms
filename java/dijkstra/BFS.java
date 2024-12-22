import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Queue;

public class BFS {

    public static int[] bfs(boolean[][] graph, int start) {
        Queue<Integer> queue = new PriorityQueue<>();
        queue.add(start);
        boolean[] visited = new boolean[graph.length];
        visited[start] = true;
        int[] distances = new int[graph.length]; 

        while (!queue.isEmpty()) {
            System.out.println("Visited nodes: " + Arrays.toString(visited));
            System.out.println("Distances: " + Arrays.toString(distances));
            int node = queue.remove();
            System.out.println("Removing node " + node + " from the queue...");

            for (int i = 1; i < graph[node].length; i++) {
                if (graph[node][i] && !visited[i]) {
                    visited[i] = true;
                    distances[i] = distances[node] + 1;
                    queue.add(i);
                    System.out.println("Visiting node " + i + ", setting its distance to " + distances[i] + " and adding it to the queue");
                }
            }
        }

        System.out.println("No more nodes in the queue. Distances: " + Arrays.toString(distances));
        return distances;
    }
}