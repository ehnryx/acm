n,b=gets.split.map{|x|x.to_f}
a=1
(1..b).map{|i|a*=(n-i+1)/(n+i)}
p a**2
