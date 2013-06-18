#######################
# Multiplication Game #
# By Justin Bisignano #
# COP 3223 Section 4  #
# 9/7/2012            #
#######################

# Module Import
import random

# Define main
def main():
	# Variables
	numcorrect = 0
	# User input
	while True: # Loop to check input and prevent division by 0 later
		numproblems = int(input("How many problems do you want?\n"))
		if numproblems<=0:
			print("Please enter some integer value above 0\n")
		else:
			break
	
	random.seed() # Seed the random number generator for later
	
	# Loop for numproblems
	for i in range(0,numproblems):
		num1 = random.randint(1,10)
		num2 = random.randint(1,10)
		
		print("What is ", num1, " x ", num2, "?", sep="")
		guess = int(input())
		answer = num1*num2
		
		if guess==answer:
			print("Correct!\n")
			numcorrect = numcorrect + 1
		else:
			print("Sorry, the answer is ", answer, ".\n", sep="")
	
	# Do some math
	percent = float((numcorrect/numproblems)*100)
	
	# Final Outputs
	print("You got ", "%.1f"%percent, "% of the problems right.", sep="")

# Run the main function
main()
