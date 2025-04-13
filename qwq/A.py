import math
x = 233
y = 666
alpha = math.atan(y / x)

print(int((1 + alpha) * math.hypot(x, y)))