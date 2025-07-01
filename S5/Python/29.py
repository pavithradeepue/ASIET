#recursive power fuction
def power(x,y):
	return 1 if y == 0 else x*power(x,y-1)
print(power(2,3))
