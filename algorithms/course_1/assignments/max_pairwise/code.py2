def solution(numbers):
	bigger = min(numbers[0], numbers[1])
	biggest= max(numbers[0], numbers[1])
	for i in xrange(2, len(numbers)):
		if numbers[i] >= biggest:
			bigger = biggest
			biggest = numbers[i]
		elif numbers[i] >= bigger:
			bigger = numbers[i]
	return biggest * bigger

size = int(raw_input())

numbers = [int(x) for x in raw_input().split()]

print solution(numbers)
