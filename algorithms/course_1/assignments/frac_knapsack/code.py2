import math

line = raw_input().strip().split()

N = int(line[0])
cap = float(line[1])

items = []

for _ in xrange(N):
	items.append(map(float, raw_input().split()))

def custcmp(x, y):
	_x = x[0]/x[1]
	_y = y[0]/y[1]
	
	if _x < _y:
		return 1
	if _x == _y:
		return 0
	if _x > _y:
		return -1

items = sorted(items, cmp=custcmp)

answer = 0.0
index = 0
while cap > 0 and index < N:
	cur = items[index]
	to_add = min(cur[1], cap)
	answer += to_add*(cur[0]/cur[1])
	cap -= to_add
	index+=1
print answer
