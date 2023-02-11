class hack:
    def __init__(self, s):
        self.val = s
    def __add__(self, o):
        return hack(self.val + o.val + "+")
    def __sub__(self, o):
        return hack(self.val + o.val + "-")
    def __mul__(self, o):
        return hack(self.val + o.val + "*")
    def __truediv__(self, o):
        return hack(self.val + o.val + "/")

alphabet = "QWERTYIUOPASDFGHJKLZXCVBNM"
assert len(alphabet) == 26
for c in alphabet:
    exec(f"{c} = hack(\"{c}\")")

print(eval(input()).val)
