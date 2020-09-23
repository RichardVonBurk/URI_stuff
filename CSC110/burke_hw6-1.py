#Richard Burke
#10/22/18
#Homework 6 - Analysis of Algorithms


#The Program shows a side by side comparison of Linear Search and Binary Search
#The Linear Search in Worst case scenario is O(n)
#The Binary Search in Worst case scenario is O(logn)
#If the first element each search makes a comparison with is the target then they finish in constant time
#If the element, in this case for example, is the left-most in the list then linear search preforms better than binary.

def openFile():
    #prompts user to enter in the name of the data file
    #throws exception when invalid file name
    #opens file in reading mode
    
    validFile = False
    while (validFile == False):
        fileName = input("Enter the name of the data file: ")
        try:
            fileInstance = open(fileName, 'r')
            validFile = True
        except IOError:
            print("Invalid file name try again...")
    return fileInstance

def getData():
    #calls openFile()
    fileInstance = openFile()

    stateList = []
    popList = []

    line = fileInstance.readline()
    while (line != ""):
        line = line.strip()
        state, pop = line.split(",")
        stateList.append(state)
        popList.append(pop)
        line = fileInstance.readline()
    fileInstance.close()

    return stateList, popList

def getPopLinear(stateList, popList, state):
    #Linear search
    population = ""
    i = 0
    count = 0
    
    while(i < len(stateList)):
        count += 1
        
        if (stateList[i] == state):
            population = popList[i]
            i += (len(stateList) + 1)
        else:
            i += 1

    print("Linear Search: comps = " + str(count))
    return population
    


def getPopBinary(stateList, popList, state):
    #Binary search
    population = ""
    count = 0
    left = 0
    right = len(stateList)-1
    
    while (left <= right):
        count += 1
        #mid is the index being compared
        mid = (left + right) // 2

        #if found
        if (stateList[mid] == state):
            population = popList[mid]
            left += (right + 1)
        #else if ASCII code is higher, move right index
        elif (stateList[mid] >= state):
            right = mid - 1
        #else move left index
        else:
            left = mid + 1

    print("Binary Search: comps = " + str(count))
    return population


def main():
    stateList, popList = getData()

    state = input("Enter state abbreviation: ")

    getPopLinear(stateList, popList, state)
    population = getPopBinary(stateList, popList, state)

    if (population == ""):
        print("Invalid state abbreviation")
    else:
        print("The population of " + state + " is " + population)

main()



