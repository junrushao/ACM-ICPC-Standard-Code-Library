import java.io.*;
import java.util.*;
import java.math.*;

class Node implements Comparable<Node> {
	int key;
	public int compareTo(Node o) {
		if (key != o.key) return key < o.key ? -1 : 1;
		return 0;
	}
	public boolean equals(Object o) { return false; }
	public String toString() { return ""; }
	public int hashCode() { return key; }
}

class MyComparator implements Comparator<Node> {
	public int compare(Node a, Node b) {
		if (a.key != b.key)
			return a.key < b.key ? -1 : 1;
		return 0;
	}
}

public class Main {

	public void solve() {
		PriorityQueue<Integer> Q = new PriorityQueue<Integer>();
		Q.offer(1); Q.poll(); Q.peek(); Q.size();

		HashMap<Node, Integer> dict = new HashMap<Node, Integer>();
		dict.entrySet(); dict.put(new Node(), 0); dict.containsKey(new Node());
		//Map.Entry e = (Map.Entry)it.next(); e.getValue(); e.getKey();

		HashSet<Node> h = new HashSet<Node>();
		h.contains(new Node()); h.add(new Node()); h.remove(new Node());

		Random rand = new Random();
		rand.nextInt(); rand.nextDouble();

		int temp = 0;
		BigInteger a = BigInteger.ZERO, b = new BigInteger("1"), c = BigInteger.valueOf(2);
		a.remainder(b); a.modPow(b, c); a.pow(temp); a.intValue();
		a.isProbablePrime(temp); // 1 - 1 / 2 ^ certainty
		a.nextProbablePrime();

		Arrays.asList(array);
		Arrays.sort(array, fromIndex, toIndex, comparator);
		Arrays.fill(array, fromIndex, toIndex, value);
		Arrays.binarySearch(array, key, comparator); // found ? index : -(insertPoint) - 1
		Arrays.equals(array, array2);
		Collection.toArray(arrayType[]);

		Collections.copy(dest, src);
		Collections.fill(collection, value);
		Collections.max(collection, comparator);
		Collections.replaceAll(list, oldValue, newValue);
		Collections.reverse(list);
		Collections.reverseOrder();
		Collections.rotate(list, distance); //  --------->
		Collections.shuffle(list); // random_shuffle

	}

	public void run() {
		tokenizer = null;
		reader = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(System.out);

		solve();

		out.close();
	}

	public static void main(String[] args) {
		new Main().run();
	}

	public StringTokenizer tokenizer;
	public BufferedReader reader;
	public PrintWriter out;

	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			}
			catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

}
