import java.io.*;
import java.util.*;
import java.math.*;

public class hindex {
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
      List<Integer> citations = new ArrayList<>();
      for (int i = 0; i < n; i++) {
        citations.add(in.nextInt());
      }
      Collections.sort(citations, Collections.reverseOrder());

      int ans = 0;
      for (int h = 1; h <= n; h++) {
        if(citations.get(h - 1) >= h) {
          ans = h;
        }
      }
      out.println(ans);
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

