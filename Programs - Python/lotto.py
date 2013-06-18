#######################
# Arup's Lotto        #
# By Justin Bisignano #
# COP 3223 Section 4  #
# 9/7/2012            #
#######################

# Module Import
import random

# Define main
def main():
	# Variables outside loop
	RUNS = 1000000
	COST_PER_RUN = 1
	totalcost = RUNS*COST_PER_RUN # No need to increase a variable each run of the loop when we know the number of times to run and cost per run.
	onematched = 0
	twomatched = 0

	# Random Winning Lotto Numbers
	random.seed()
	lottoA = random.randint(1,30)
	lottoB = random.randint(31,60)
	
	for i in range(0,RUNS):
		# Buyer's Random Chosen Numbers
		buyerA = random.randint(1,30)
		buyerB = random.randint(31,60)
		
		if (buyerA==lottoA and buyerB==lottoB):
			twomatched = twomatched + 1
		elif buyerA==lottoA:
			onematched = onematched + 1
		elif buyerB==lottoB:
			onematched = onematched + 1
	
	# Do some math
	winnings = onematched*5 + twomatched*500	

	# Final Outputs
	print("You Matched 1 number", onematched, "times.")
	print("You Matched 2 numbers", twomatched, "times.")
	
	# Seperate outputs for winning, losses, and breaking even.
	if winnings<totalcost:
		lost = totalcost-winnings
		print("You lost $", lost, ".", sep = "")
	elif winnings>totalcost:
		won = winnings-totalcost
		print("Congratulations! You won $", won, ".", sep = "")
	elif winnings==totalcost:
		print("You broke even and neither won nor lost any money")

# Run the main function
main()
