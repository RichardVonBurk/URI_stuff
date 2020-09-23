#Richard Burke
#10/8/18
#Homework 5 - Working with Files pt 2


def readFile():
    #reads file, name is given by constant
    #creates 3 lists
    #while reading, calculates percentages before appending to respective lists
    #returns the 3 lists
    READ_FILENAME = "cs-grads.csv"
    fileInstance = open(READ_FILENAME, 'r')

    yearList = []
    maleList = []
    femaleList = []

    fileInstance.readline()
    line = fileInstance.readline()

    while (line != ""):
        line = line.strip()
        year, total, male, female = line.split(",")

        malePercent = int(male) / int(total)
        femalePercent = int(female) / int(total)

        yearList.append(year)
        maleList.append(malePercent)
        femaleList.append(femalePercent)
        line = fileInstance.readline()

    fileInstance.close()
    return yearList, maleList, femaleList


def writeFile(yearList, maleList, femaleList):
    #writes a file, name is given by constant
    #iterates through the 3 lists with index i
    #each index is one line in resulting file
    WRITE_FILENAME = "pct-grads.csv"
    fileInstance = open(WRITE_FILENAME, 'w')

    i = 0
    while (i < len(yearList)):
        fileInstance.write(str(yearList[i]) + "," + str(maleList[i]) + "," + str(femaleList[i]) + "\n")
        i += 1
    fileInstance.close()

    #main
    #calls readFile, then writeFile
def main():
    yearList, maleList, femaleList = readFile()
    writeFile(yearList, maleList, femaleList)

main()
