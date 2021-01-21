import java.io.*;
import java.util.*;
import java.math.*;

public class bumped {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    // new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
    Solver solver = new Solver();
    solver.run_solver(in, out);
    out.close();
  }


  static class Solver {
    public void run_solver(InputReader in, PrintWriter out) {
      int n = in.nextInt();
      int m = in.nextInt();
      int f = in.nextInt();
      int s = in.nextInt();
      int t = in.nextInt();

      List<List<Edge>> adj = new ArrayList<>();
      for(int i=0; i<2*n; i++) {
        adj.add(new ArrayList<>());
      }

      for(int i=0; i<m; i++) {
        int a = in.nextInt();
        int b = in.nextInt();
        int c = in.nextInt();
        adj.get(a).add(new Edge(b, c));
        adj.get(b).add(new Edge(a, c));
        adj.get(a + n).add(new Edge(b + n, c));
        adj.get(b + n).add(new Edge(a + n, c));
      }

      for(int i=0; i<f; i++) {
        int a = in.nextInt();
        int b = in.nextInt();
        adj.get(a).add(new Edge(b + n, 0));
      }

      for(int i=0; i<n; i++) {
        adj.get(i).add(new Edge(i + n, 0));
      }

      long[] dist = new long[2*n];
      Arrays.fill(dist, -1);
      PriorityQueue<Edge> dijk = new PriorityQueue<>();
      dijk.add(new Edge(s, 0));
      while(!dijk.isEmpty()) {
        Edge cur = dijk.poll();
        if(dist[cur.u] != -1) continue;
        dist[cur.u] = cur.d;
        for(Edge e : adj.get(cur.u)) {
          if(dist[e.u] == -1) {
            dijk.add(new Edge(e.u, e.d + cur.d));
          }
        }
      }
      out.println(dist[t + n]);
    }

    class Edge implements Comparable<Edge> {
      int u;
      long d;
      Edge(int u, long d) {
        this.u = u;
        this.d = d;
      }
      public int compareTo(Edge o) {
        return Long.valueOf(d).compareTo(Long.valueOf(o.d));
      }
    }
  }

  static class InputReader {
    public BufferedReader reader;
    public StringTokenizer tokenizer;

    public InputReader(InputStream stream) {
      reader = new BufferedReader(new InputStreamReader(stream), 32768);
      tokenizer = null;
    }

    public String next() {
      while (tokenizer == null || !tokenizer.hasMoreTokens()) {
        try {
          tokenizer = new StringTokenizer(reader.readLine());
        } catch (IOException e) {
          throw new RuntimeException(e);
        }
      }
      return tokenizer.nextToken();
    }

    public int nextInt() {
      return Integer.parseInt(next());
    }

    public long nextLong() {
      return Long.parseLong(next());
    }

    public double nextDouble() {
      return Double.parseDouble(next());
    }

  }

}

