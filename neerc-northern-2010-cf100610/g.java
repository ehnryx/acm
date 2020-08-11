import java.io.*;
import java.util.*;
import java.math.*;

public class g {
	static class Rat implements Comparable<Rat> {
		BigInteger n, d;
		public Rat() {}
		public Rat(long x) {
			this.n = BigInteger.valueOf(x);
			this.d = BigInteger.valueOf(1);
		}
		public Rat(BigInteger n, BigInteger d) {
			this.n = n;
			this.d = d;
			BigInteger g = this.n.gcd(this.d);
			this.n = this.n.divide(g);
			this.d = this.d.divide(g);
		}
		public Rat add(Rat o) {
			return new Rat(this.n.multiply(o.d).add(this.d.multiply(o.n)), this.d.multiply(o.d));
		}
		public Rat subtract(Rat o) {
			return new Rat(this.n.multiply(o.d).subtract(this.d.multiply(o.n)), this.d.multiply(o.d));
		}
		public Rat multiply(Rat o) {
			return new Rat(this.n.multiply(o.n), this.d.multiply(o.d));
		}
		public boolean lessThan(Rat o) {
			return this.n.multiply(o.d).compareTo(o.n.multiply(this.d)) == -1;
		}
		public boolean equals(Rat o) {
			return this.n.multiply(o.d).compareTo(o.n.multiply(this.d)) == 0;
		}
		public double print() {
			return n.doubleValue() / d.doubleValue();
		}
		public int compareTo(Rat o) {
			return this.n.multiply(o.d).compareTo(o.n.multiply(this.d));
		}
	}

	static class Collection {
		long sum;
		int amt;
		long a, b, c;
		Collection() {
			sum = 0;
			amt = 0;
			a = 0;
			b = 0;
			c = 0;
		}
		void insert(long p) {
			sum += p;
			amt += 1;
			a += 1;
			b -= 2*p;
			c += p*p;
		}
		void remove(long p) {
			sum -= p;
			amt -= 1;
			a -= 1;
			b += 2*p;
			c -= p*p;
		}
		Rat loc() {
			return new Rat(BigInteger.valueOf(sum), BigInteger.valueOf(amt));
		}
		Rat query() {
			Rat x = loc();
			return x.multiply(x).multiply(new Rat(a))
				.add(x.multiply(new Rat(b)))
				.add(new Rat(c));
		}
	}

	static class Minstore {
		Rat cur;
		ArrayList<Rat> values;
		public Minstore() {
			cur = new Rat((long) 1e18);
			values = new ArrayList<Rat>();
		}
		public void insert(Rat amt, Rat position) {
			if (amt.equals(cur)) {
				values.add(position);
			} else if (amt.lessThan(cur)) {
				cur = amt;
				values.clear();
				values.add(position);
			}
		}
	}

	static class Pair implements Comparable<Pair> {
		int first, second;
		public Pair(int a, int b) {
			this.first = a;
			this.second = b;
		}
		public int compareTo(Pair o) {
			if(first == o.first && second == o.second) return 0;
			if(first < o.first || (first == o.first && second < o.second)) return -1;
			else return 1;
		}
	}

	static final int N = 10000 + 1;
	static final int M = 100000 + 1;
	static ArrayList<ArrayList<Integer>> fac;
	static int[] cur = new int[N];

	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new FileReader("gadgets.in"));
		PrintWriter out = new PrintWriter("gadgets.out");
		Scanner sc = new Scanner(in);

		Minstore mst = new Minstore();
		int n = sc.nextInt();
		int m = sc.nextInt();
		fac = new ArrayList<>();
		for(int i=0; i<=n; i++) {
			fac.add(new ArrayList<>());
		}
		for(int i=1; i<=m; i++) {
			int x = sc.nextInt();
			int p = sc.nextInt();
			fac.get(p).add(x);
		}

		ArrayList<Pair> splits = new ArrayList<>();
		for(int i=1; i<=n; i++) {
			for(int j=0; j<fac.get(i).size()-1; j++) {
				splits.add(new Pair(fac.get(i).get(j) + fac.get(i).get(j+1), i));
			}
		}

		Collection coll = new Collection();
		for(int i=1; i<=n; i++) {
			coll.insert(fac.get(i).get(0));
		}
		mst.insert(coll.query(), coll.loc());

		Collections.sort(splits);
		for (Pair pp : splits) {
			int i = pp.second;
			coll.remove(fac.get(i).get(cur[i]));
			coll.insert(fac.get(i).get(++cur[i]));
			mst.insert(coll.query(), coll.loc());
		}

		out.printf("%d\n", mst.values.size());
		Collections.sort(mst.values);
		for (Rat x : mst.values) {
			out.printf("%.9f\n", x.print());
		}
		out.close();
	}
}
