object E extends App {
	@inline def tokenizeLine = new java.util.StringTokenizer(scala.io.StdIn.readLine);
	def readInts(n: Int) = {
		val tl = tokenizeLine; 
		Array.fill(n)(tl.nextToken.toInt);
	}
    
    val Array(n, r) = readInts(2);
    val returned:Array[Int] = readInts(r);
    var dead = Array.fill(n)(1);
    for (i <- returned) dead(i-1) = 0;
    for (i <- 1 to n) if (dead(i-1) == 1) print(i + " ");
    print("\n");
}
