#######################
# Diaper Money        #
# By Justin Bisignano #
# 8/29/2012           #
#######################

# Constants
DAYS_PER_MONTH = 30
CALS_PER_LB = 3500
CALSLOST_PER_BEER = 20
DOZEN = 12

# Get inputs
diapercost = float(input("What is the cost of a dozen diapers?\n"))
diapersperday = int(input("How many diapers does the baby go through a day?\n"))
beercost = float(input("What is the cost of a single beer?\n"))

# Calculations
diaperspend = diapercost/DOZEN*DAYS_PER_MONTH*diapersperday
fewerbeers = diaperspend//beercost
lbslost = fewerbeers*CALSLOST_PER_BEER/CALS_PER_LB

# Print outputs
print('You will spend $'+str(diaperspend),'on diapers in a month.')
print('You will drink',int(fewerbeers),'fewer beers in a month.')
print('As a result, you will loose',lbslost,'pounds in a month.')
