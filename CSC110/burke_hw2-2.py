#Richard Burke
#9/17/18
#Programming in Python
#HW 2-2

#initialize
i = 0
NUM_DAYS = 9
total = 0

#loop through for each day, getting score and add sum
while (i < NUM_DAYS):
    score = int(input("Enter score: "))
    total += score
    i+=1

#calulate result
result = total / NUM_DAYS

#print out result
print("You average score for three weeks is:", result)
