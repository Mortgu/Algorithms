import java.util.*;

public class Dijkstra {

	public static void dijkstra(Map<Node, Map<Node, Integer>> graph, Node start) {
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

		graph.put(nodeA, Map.of(nodeB, 1, nodeC, 4, nodeD, 2));
		graph.put(nodeB, Map.of(nodeA, 1, nodeC, 2, nodeE, 5));
		graph.put(nodeC, Map.of(nodeA, 4, nodeB, 2, nodeD, 1, nodeE, 3));
		graph.put(nodeD, Map.of(nodeA, 2, nodeC, 1, nodeE, 1));
		graph.put(nodeE, Map.of(nodeB, 5, nodeC, 3, nodeD, 1));

		dijkstra(graph, nodeA);

		System.out.println("Kürzeste Distanze vom Startknoten A:");
		for (Node node : graph.keySet()) {
			System.out.println(node.getName() + ": " + node.getDistance());
		}
	}

}

