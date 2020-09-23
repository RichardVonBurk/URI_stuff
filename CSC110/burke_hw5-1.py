#Richard Burke
#10/8/18
#Homework 5 - Working with Files pt 1

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
    #creates lists and then stores .csv file info as it is read
    #closes .csv file
    fileInstance = openFile()

    yearList = []
    totalList = []
    maleList = []
    femaleList = []

    #skip first line of .csv, then actually begin reading
    fileInstance.readline()
    line = fileInstance.readline()

    while (line != ""):
        line = line.strip()
        year, total, male, female = line.split(",")
        yearList.append(year)
        totalList.append(total)
        maleList.append(male)
        femaleList.append(female)
        line = fileInstance.readline()
    fileInstance.close()

    return yearList, totalList, maleList, femaleList


def getPercent():
    #prompts user to enter a percentage
    #throws exception if input isn't valid to be a float
    validPercent = False
    while (validPercent == False):
        try:
            percent = float(input("Enter percentage of female CS graduates: "))
            validPercent = True
        except ValueError:
            print("Invalid entry, try again...")
    return percent


def findYears(percent, yearList, totalList, maleList, femaleList):
    #searches the parallel lists by index i
    #calculates the female percentage as it compares to the user's input percentage
    #if found then appended to tempList
    tempList = []
    i = 0
    while (i < len(yearList)):
        if (percent < (int(femaleList[i]) / int(totalList[i]))):
            tempList.append(yearList[i])
        i += 1

    #check to see if tempList is empty
    if (len(tempList) > 0):
        print("The years when the percentage of female Computer Science graduates was higher than " + str(percent) + " are:")
        for year in tempList:
            print(year)
    else:
        print("There are no years when the percentage of female Computer Science graduates was higher than " + str(percent))
        
    #main
    #calls getData, then getPercent, then findYears
def main():
    yearList, totalList, maleList, femaleList = getData()
    percent = getPercent()
    findYears(percent, yearList, totalList, maleList, femaleList)
    
main()
