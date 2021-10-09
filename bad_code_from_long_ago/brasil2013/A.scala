object A extends App {
  @inline def tokenizeLine = new java.util.StringTokenizer(scala.io.StdIn.readLine);
  def readInts(n: Int) = {
    val tl = tokenizeLine; 
    Array.fill(n)(tl.nextToken.toInt);
  }

  val Array(a, b, c) = readInts(3);

  val ans = if (a == b && b == c) "*";
  else if (a == b) "C";
  else if (b == c) "A"; 
  else "B";

  println(ans);
}
