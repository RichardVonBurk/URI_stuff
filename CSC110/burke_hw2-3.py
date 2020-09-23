#Richard Burke
#9/17/18
#Programming in Python
#HW 2-3

#initialize
i = 0
NUM_DAYS = 7
highest = 0

#loop through for each day, comparing highest to each input
while (i < NUM_DAYS):
    numBugs = int(input("Enter score: "))
    if numBugs > highest:
        highest = numBugs
    i+=1

#print highest
print("The highest number of bugs collected this week is", highest)
