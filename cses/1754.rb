gets
$<.map{|x|
  a,b = x.split.map(&:to_i)
  puts (a+b) % 3 > 0 || a > 2*b || b > 2*a ? "NO" : "YES"
}
