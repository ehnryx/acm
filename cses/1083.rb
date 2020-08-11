a = 0
(1..gets.to_i).map{|x|a^=x}
gets.split.map{|x|a^=x.to_i}
p a
