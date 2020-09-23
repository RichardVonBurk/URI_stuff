# World Series Results

# Given a file with the World Series Champions since 1904
# Allow user to ask various questions about the results

def fileException():
    goodName = False
    while goodName == False:
        file = input("Enter in the file name: ")
        try:
            fileInstance = open(file, 'r')
            goodName = True
        except IOError:
            print("Invalid name, please try again...")
    return fileInstance

def yearException():
    goodYear = False
    while goodYear == False:
        try:
            yearInput = int(input("Enter in a year to search: "))
            yearInput = str(yearInput)
            goodYear = True
        except ValueError:
            print("Invalid number, please try again..")
    return yearInput
            

def getChamps():
    # This function will get the data from the data file - be sure to look at the format of the data in the
    # file and read each line as we did with the phone search program in class.
    # The function should return the list of years, the list of winners and the list of losers
    fileInstance = fileException()

    champList = []
    yearList = []
    loserList = []
    line = fileInstance.readline()
    
    while (line != ""):
        line = line.strip()
        year, champ, loser = line.split(",")
        yearList.append(year)
        champList.append(champ)        
        loserList.append(loser)
        line = fileInstance.readline()
    fileInstance.close()

    
    print("")
    print("This is where you will get the data from the data file")
    print("")
    # Make sure to return the correct information from this function
    return champList, yearList, loserList


def findWinnerAndLoser(year, yearList, champList, loserList):
    i = 0
    while i < len(yearList):
        if year == yearList[i]:
            return (champList[i], loserList[i])
        i = i + 1

def countWins(team, champList):
    i = 0
    count = 0
    while i < len(champList):
        if team == champList[i]:
            count = count + 1
        i = i + 1
    return count

def getChoice():
    # This function displays the menu of choices for the user
    # It reads in the user's choice and returns it as an integer
    print("")
    print("Make a selection from the following choices:")
    print("1 - Find the World Series Winner and Loser for a particular year")
    print("2 - Count how many times a team has won the World Series")
    print("3 - Write to an output file all teams that have won the World Series")
    print("4 - Find the team that has won the most World Series Championships")
    print("5 - Find the team that has lost the most World Series Championships")
    print("6 - Quit")
    choice = int(input("Enter your choice --> "))
    print("")
    return choice


def main():
    # Call the function to get the data from the data file and store the results in three lists
    champList, yearList, loserList = getChamps()
    try:
        choice = getChoice()
    except ValueError:
        print("Invalid input")
        choice = getChoice()
    while choice != 6:
        if choice == 1:
            year = yearException()
            try:
                champ, loser = findWinnerAndLoser(year, yearList, champList, loserList)
                print("The winner for ",year, " was ", champ, ".")
                print("The loser for ", year, "was ", loser, ".")
            except TypeError:
                print("Year not found")
            choice = getChoice()
        elif choice == 2:
            team = input("Enter the team name: ")
            count = countWins(team, champList)
            print(team, " won the World Series ", count, " times.")
            choice = getChoice()
        elif choice == 3:
            team = input("Enter the team name: ")
            # Call the function to create output file containing teams defeated by chosen team
            choice = getChoice()
        elif choice == 4:
            # Call the function to find the team that won the most championships
            print("XXX won the World Series the most at XXX times.")
            choice = getChoice()
        elif choice == 5:
            # Call the function to find the team that lost the most championships
            print("XXX lost the World Series the most at XXX times.")
            choice = getChoice()
        else:
            print("Error in your choice")
            choice = getChoice()
    print("Good-bye")
    
    
