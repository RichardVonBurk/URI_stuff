#Richard Burke
#10/22/18
#Homework 6 - Analysis of Algorithms pt 2

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


def dualSort(list1, list2):
    for i in range(1, len(list1)):
        #save both respective elements
        #be sure to cast pop as int to be sure comparison is between int
        save = int(list1[i])
        save2 = list2[i]
        j = int(i)
        while j > 0 and int(list1[j - 1]) > save:
            # comparison
            list1[j] = int(list1[j - 1])
            list2[j] = list2[j - 1]
            j = j - 1
	    # swap
        list1[j] = save
        list2[j] = save2
    
    return list1, list2


def main():
    stateList, popList = getData()

    popList, stateList = dualSort(popList, stateList)

    for i in range(len(popList)):

        print(stateList[i], popList[i])

main()



