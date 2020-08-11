import re

def leading_zero(s):
	nums = re.findall(r"[0-9]+", s)
	for num in nums:
		if len(num) > 1 and num[0] == "0":
			return True
	return False

if __name__ == "__main__":
	n = input()
	for i in range(n):
		s = raw_input()
		flag = False
		for j in range(10):
			if str(j) not in s:
				s1 = s.replace("?", str(j))
				if not leading_zero(s1):
					lhs, rhs = s1.split("=")
					if eval(lhs) == eval(rhs):
						print j
						flag = True
						break
		if not flag:
			print -1
