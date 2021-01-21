import java.io.*;
import java.util.*;
import java.math.*;

public class quadrant {
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
      int x = in.nextInt();
      int y = in.nextInt();
      if (x > 0 && y > 0) {
        out.println(1);
      } else if (x < 0 && y > 0) {
        out.println(2);
      } else if (x < 0 && y < 0) {
        out.println(3);
      } else {
        out.println(4);
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

