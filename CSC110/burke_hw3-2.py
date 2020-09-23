#Richard Burke
#9/24/18
#Homework 3 -Python Lists, part 2

#get number of 10yo's
numKids = int(input("How many heights are in the original list? "))

#prepare height list
hList = []
#loop for numKids asking the height of each 10yo, thereafter append height to hList
#if statement is to avoid illogical inputs
i = 0
while(i < numKids):
    height = int(input("Enter height: "))
    if (height <= 0):
        print("Enter in a value higher than zero")
    else:
        hList.append(height)
        i+=1

#loop through list for every 3rd element after the 1st element (like in the example)
#appends to the sample list
i = 0
sample = []
while(i < numKids):
    sample.append(hList[i])
    i+=3

#printout list
print("The sampled list is:\n" + str(sample))
