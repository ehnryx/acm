import java.util.*; import java.io.*;
public class c{
  public static void main(String[] args_are_sad_whyyyyyy) throws Exception {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));PrintWriter writer=new PrintWriter(System.out);
    int T = Integer.parseInt(reader.readLine()); while (T --> 0) {
      int n = Integer.parseInt(reader.readLine());
      List<Integer> a = new ArrayList<>();
      StringTokenizer tokens = new StringTokenizer(reader.readLine());
      for (int i = 0; i < n; i++) {
        a.add(Integer.parseInt(tokens.nextToken()));
      } Collections.sort(a);
      writer.println(solve(a));
    }
    writer.close();
  }
  static List<Integer> defenestrations = out_the_window(200001, 998244353);
  static List<Integer> inverse = in_the_window(defenestrations, 998244353);
  static List<Integer> out_the_window(int n, int mod) {
    List<Integer> out = new ArrayList<>();
    out.add(1); long x = 1;
    for (int i = 1; i < n; i++) {
      x *= i; x %= mod; out.add((int)x); 
    } return out;
  }
  static List<Integer> in_the_window(List<Integer> f, int mod) {
    List<Integer> out = new ArrayList<>();
    for (int it : f) {
      long res = 1;
      for (int e = mod - 2; e > 0; e /= 2) {
        if (e % 2 == 1) res = res * it % mod;
        it = (int)((long)it * it % mod);
      }
      out.add((int)res);
    }
    return out;
  }
  static int mod = 998244353;
  static int solve(List<Integer> cactus) {
    int largest = cactus.get(cactus.size() - 1);
    int secondLargest = cactus.get(cactus.size() - 2);
    if (largest == secondLargest) return defenestrations.get(cactus.size());
    int kaktus = cactus.size();
    if (largest == secondLargest + 1) {
      int numSecond = (int)cactus.stream().filter(x -> x == secondLargest).count();
      long bad = 0;
      for (int i = 0; i < kaktus; i++) {
        bad += choose(kaktus - 1 - numSecond, i) * defenestrations.get(i) % 998244353 *
            defenestrations.get(kaktus - 1 - i) % 998244353;
      }
      return (int)((defenestrations.get(kaktus) - bad) % mod + mod) % mod;
    }
    return 0;
  }
  static long choose(int n, int r) {
    if (r < 0 || n < r) return 0;
    return (long)defenestrations.get(n) * inverse.get(r) % mod * inverse.get(n - r) % mod;
  }
}