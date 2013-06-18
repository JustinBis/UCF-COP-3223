#######################
# Diaper Money        #
# By Justin Bisignano #
# COP 3223 Section 4  #
# 9/7/2012            #
#######################

# Constants
WEEKS_IN_MONTH = 4
OVERTIME_FACTOR = 1.5 # Overtime is 50% more than regular pay
OVERTIME_START = 40 # Hours until overtime pay is given

# Define Main Function
def main():
	# Get Inputs
	workedhours = int(input("How many hours do you work in a week?\n"))
	hourlypay = float(input("What is your hourly pay in dollars?\n"))
	grocerybill = float(input("What is your grocery bill for the month?\n"))
	utilitybill = float(input("What are your utility bills for the month?\n"))
	otherexpenses = float(input("What are your entertainment/other expenses for the month?\n"))
	rent = float(input("What is your rent for the month?\n"))
	
	# Do the Math
	totalexpenses = grocerybill+utilitybill+otherexpenses+rent
	if workedhours > OVERTIME_START:
		overtimehours = workedhours-OVERTIME_START
		totalpay = (OVERTIME_START*hourlypay + overtimehours*hourlypay*OVERTIME_FACTOR)*WEEKS_IN_MONTH
	else:
		totalpay = (workedhours*hourlypay)*WEEKS_IN_MONTH

	# Make the final decision
	if totalpay >= totalexpenses:
		print("Great, you can pay your rent!")
	if totalpay < totalexpenses:
		print("Sorry, you can't pay your rent.")
	
# Run Main
main()