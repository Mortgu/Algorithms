import java.util.*;

public class Dijkstra {
	
	public static void bfs(Map<Node, Map<Node, Integer>> graph, Node start) {
		// Prioritätswarteschlange für die Auswahl des Knotens mit der geringsten
		// Distanz
		PriorityQueue<Node> priorityQueue = new PriorityQueue<>(Comparator.comparingInt(node -> node.getDistance()));
		start.setDistance(0);
		priorityQueue.add(start);
		// Haupt-Schleife des Dijkstra-Algorithmus
		while (!priorityQueue.isEmpty()) {
			Node current = priorityQueue.poll();

			// Iteration über alle Nachbarn des aktuellen Knotens
			for (Map.Entry<Node, Integer> neighborEntry : graph.get(current).entrySet()) {
				Node neighbor = neighborEntry.getKey();
				int newDistance = current.getDistance() + neighborEntry.getValue();

				// Aktualisierung der Distanz, falls ein kürzerer Weg gefunden wurde
				if (newDistance < neighbor.getDistance()) {
					priorityQueue.remove(neighbor);
					neighbor.setDistance(newDistance);
					priorityQueue.add(neighbor);
				}
			}
		}
	}

	public static void main(String[] args) {
		Map<Node, Map<Node, Integer>> graph = new HashMap<>();

		Node nodeA = new Node("A");
		Node nodeB = new Node("B");
		Node nodeC = new Node("C");
		Node nodeD = new Node("D");
		Node nodeE = new Node("E");

		Node nodeF = new Node("F");
		Node nodeG = new Node("G");
		Node nodeH = new Node("H");
		Node nodeI = new Node("I");

		graph.put(nodeA, Map.of(nodeB, 1, nodeC, 1, nodeG, 1));
		graph.put(nodeB, Map.of(nodeD, 1));
		graph.put(nodeC, Map.of(nodeA, 1, nodeD, 1, nodeE, 1));
		graph.put(nodeD, Map.of(nodeG, 1));
		graph.put(nodeE, Map.of(nodeA, 1, nodeF, 1, nodeI, 1));
		graph.put(nodeF, Map.of(nodeC, 1, nodeD, 1, nodeE, 1, nodeH, 1));
		graph.put(nodeG, Map.of(nodeH, 1));
		graph.put(nodeH, Map.of(nodeD, 1, nodeI, 1));
		graph.put(nodeI, Map.of(nodeF, 1));

		bfs(graph, nodeA);

		System.out.println("Kürzeste Distanze vom Startknoten A:");
		for (Node node : graph.keySet()) {
			System.out.println(node.getName() + ": " + node.getDistance());
		}
	}

}

