import java.io.*;
import java.util.*;

fun main() = output {
  val T = readInt();
  for (testnum in 1..T) {
    val (n, k) = readInts(2);
    val sb = StringBuilder();
    for (i in 0..n-1) {
      //sb.append(((i % k) + 'a'.toInt()).toChar());
      sb.append(((i % k) + 'a'.code).toChar());
    }
    println(sb);
  }
}

@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out

@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }

@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }
