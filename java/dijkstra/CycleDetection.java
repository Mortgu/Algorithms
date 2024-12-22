import java.util.*;

public class CycleDetection {

    public static boolean hasCycle(Map<Integer, List<Integer>> graph) {
        Map<Integer, Integer> state = new HashMap<>(); 

        for (int node : graph.keySet()) {
            state.put(node, 0);
        }

        for (int node : graph.keySet()) {
            if (state.get(node) == 0) { 
                if (dfs(node, state, graph, new ArrayList<>())) {
                    return true;
                }
            }
        }
        return false;
    }

    private static boolean dfs(int node, Map<Integer, Integer> state, Map<Integer, List<Integer>> graph, List<Integer> path) {
        state.put(node, 1); 
        path.add(node);     

        for (int neighbor : graph.getOrDefault(node, new ArrayList<>())) {
            if (state.get(neighbor) == 1) { 
                path.add(neighbor);
                System.out.println("Cycle found: " + path);
                return true;
            }
            if (state.get(neighbor) == 0) { 
                if (dfs(neighbor, state, graph, path)) {
                    return true;
                }
            }
        }

        state.put(node, 2); 
        path.remove(path.size() - 1); 
        return false;
    }

    public static void main(String[] args) {
        Map<Integer, List<Integer>> graph = new HashMap<>();

        graph.put(0, Arrays.asList(1, 2, 3));
        graph.put(1, Arrays.asList());
        graph.put(2, Arrays.asList(3, 4));
        graph.put(3, Arrays.asList(2));
        graph.put(4, Arrays.asList(5));
        graph.put(5, Arrays.asList(6, 7));
        graph.put(6, Arrays.asList());
        graph.put(7, Arrays.asList(5));
        graph.put(8, Arrays.asList(7));

        if (hasCycle(graph)) {
            System.out.println("Graph contains a cycle.");
        } else {
            System.out.println("Graph does not contain a cycle.");
        }
    }
}