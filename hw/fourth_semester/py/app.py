import math
import random

def primeTest(m, k=20):
	if m in [2, 3, 5, 7, 11, 13, 17, 19]:
		return True
	elif (m % 2 == 0 | m < 20):
		return False
	
	t = m - 1; s = 0
	while t % 2 == 0:
		t /= 2; s += 1
	t = int(t)
	
	for j in range(k):
		b = random.randrange(2, m-1)
		#print("b = ", b)
		#print(type(b), type(t), type(m))
		x = pow(b, t, m)
		#print((x - 1) % m)
		if ((x-1) % m ==  0 or (x+1) % m == 0):
			continue
		
		i = 0
		while i < s:
			x = pow(x, 2, m)
			i += 1
			if (x-1) % m == 0:
				return False
			elif (x+1) % m == 0:
				break
		
		if (i == s and (x-1) % m != 0):
			#print("Code 2")
			return False
	#print("Code 3")
	return True 	
	

def main():
	m = int(input("Input the number: "))
	if primeTest(m):
		print("m - простое число")
	else: 
		print("m - составное число")
			
	

if __name__ == "__main__":
	main()
