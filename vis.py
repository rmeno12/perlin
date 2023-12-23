from matplotlib import pyplot as plt
import sys

data = sys.stdin.read()
print(data)
f = lambda s: s != '' and s != '\n' and s[0] != '#'
data = [float(l) for l in data.split('\n') if f(l)]
print(data)
plt.plot(data)
plt.show()