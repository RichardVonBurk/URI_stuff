""" madLib.py

    Richard Burke
    2/20/16

    This program manipulates lists.

    Enduser enters the parts of speech requested and the program will
    insert them into a mad lib.
"""
#Set up a list which gets the words later get inserted as the enduser inputs them.
wordList = [
    ]

#Incoming words!
adjec = raw_input("Please enter an adjective:")
wordList.append(adjec)
noun = raw_input("Please enter a singular noun:")
wordList.append(noun)
pstVerb = raw_input("Please enter a past tense verb:")
wordList.append(pstVerb)

#WHO LIVES IN A PINEAPPLE UNDER THE SEA?! (this whole thing is based on a scene from Spongebob)
print "I'll tell you a little story called 'The", wordList[0], wordList[1],"'."
print "Once there was a(n)", wordList[0], wordList[1],"."
print "The", wordList[1], "was soo", wordList[0],","
print "that everyone", wordList[2], "!"
print "The End."

#Not sure if you prefer us to use the %s () over the method I used?
#I assume if it were really long it would be the more logical choice.
