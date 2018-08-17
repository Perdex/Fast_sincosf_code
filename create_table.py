import math

n = 128

for i in range(n):
	if(i % 4 == 0):
		print ""
	print "%.16f, "%math.sin(i * math.pi * 2 / n),
	