#!/usr/bin/ruby
include Math

arr = readline().split().map(&:to_i)
dim = readline().split().map(&:to_i)

good = false
dim.permutation.each do |net|
	w, h = net
	arr.permutation.each do |it|
		a, b, c = it
		if 2*a + 2*b <= w and c + 2*a <= h
			good = true
		elsif 2*a + b + c <= w and c + 2*b <= h
			good = true
		elsif a + b <= w and 3*c + a + b <= h
			good = true
		elsif a + b + 2*c <= w and a + b + c <= h
			good = true
		end
	end
end

if good
	puts "Yes"
else
	puts "No"
end
