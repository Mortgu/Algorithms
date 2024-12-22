public class Node implements Comparable<Node> {
    private final String name;
    private int distance = Integer.MAX_VALUE;
    private Node previous = null;

    public Node(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getDistance() {
        return distance;
    }

    public void setDistance(int distance) {
        this.distance = distance;
    }

    public Node getPrevious() {
        return previous;
    }

    public void setPrevious(Node previous) {
        this.previous = previous;
    }

    @Override
    public int compareTo(Node other) {
        return Integer.compare(this.distance, other.distance);
    }

    @Override
    public String toString() {
        return name + " (" + distance + ")";
    }
}