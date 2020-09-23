#Richard Burke
#9/24/18
#Homework 3 -Python Lists, part 1

#get number of cars that passed the sensor
numCars = int(input("How many cars passed the sensor? "))

#prepare list to store car speeds
carList = []
#loop for numCars asking the speed of each car, thereafter append speed to carList
#if statement is to avoid illogical inputs
i = 1
while(i <= numCars):
    speed = int(input("Enter speed for car " + str(i) + ": "))
    if (speed <= 0):
        print("Enter in a value higher than zero")
    else:
        carList.append(speed)
        i+=1

#prepare variables to store fastest & slowest
fastest = 0
slowest = 0
#loop through list while comparing elements to search for slowest and fastest, in linear time
for car in carList:
    if car > fastest:
        fastest = car
    if slowest == 0:
        slowest = car
    elif car < slowest:
        slowest = car

#calculate difference between fastest and slowest, then printout
diff = (fastest - slowest)
print("The difference in speed between the fastest car and the slowest car is ", diff, " mph")
