n = gets.to_i
puts 1 < n && n < 4 ? "NO SOLUTION" :
([*(1..n)].select(&:even?) + [*(1..n)].select(&:odd?))*?\s
