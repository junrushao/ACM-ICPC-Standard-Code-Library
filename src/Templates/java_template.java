import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	public void solve() {}
	public void run() {
		tokenizer = null; out = new PrintWriter(System.out);
		in = new BufferedReader(new InputStreamReader(System.in));
		solve();
		out.close();
	}
	public static void main(String[] args) {
		new Main().run();
	}
	public StringTokenizer tokenizer;
	public BufferedReader in;
	public PrintWriter out;
	public String next() {
		while (tokenizer == null || !tokenizer.hasMoreTokens()) {
			try { tokenizer = new StringTokenizer(in.readLine()); }
			catch (IOException e) { throw new RuntimeException(e); }
		} return tokenizer.nextToken();
	}
}