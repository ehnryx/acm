import java.io.*;
import java.util.*;
import java.math.*;

public class C {
  public static void main(String[] args) {
    InputStream inputStream = System.in;
    OutputStream outputStream = System.out;
    InputReader in = new InputReader(inputStream);
    PrintWriter out = new PrintWriter(outputStream);
    // new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
    Solver solver = new Solver();
    int T = 1; //in.nextInt();
    for(int tt = 1; tt <= T; tt++) {
      solver.run_solver(in, out);
    }
    out.close();
  }

  static class Solver {
    public void run_solver(InputReader in, PrintWriter out) {
      int n = in.nextInt();
      int m = in.nextInt();
      int[] a = read_array(n, in);
      int[] b = read_array(n, in);
      int[] c = read_array(m, in);
      int[] cnt = new int[n + 1];
      boolean have = new boolean[n + 1];

      for(int i=0; i<n; i++) {
        cnt[a[i]] -= 1;
        cnt[b[i]] += 1;
        have[b[i]] = true;
      }

      for(int i=0; i<m; i++) {
        cnt[c[i]] -= 1;
      }

      boolean ok = have[c[m-1]];
      for(int i=1; i<=n; i++) {
        if(cnt[i] > 0) {
          ok = false;
          break;
        }
      }
    }

    int[] read_array(int n, InputReader in) {
      int[] a = new int[n];
      for(int i=0; i<n; i++) {
        a[i] = in.nextInt();
      }
      return a;
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

