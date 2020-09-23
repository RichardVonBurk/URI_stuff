""" mathMagic.py
        Richard Burke
        1/24/16

    A first game to write, it performs a magic trick with math.
"""

print "I am a magic computer and I'm going to do a magic trick for you!"
print "Think of a number between 1 and 100."
print "(You might want to write all fo these steps down.)"

#var initialNumber is stored while var number is manipulated
initialNumber = raw_input("Type your number and I'll do the math with you:")
initialNumber = int(initialNumber)
number = initialNumber

print "You have chosen a wise number, friend. Prepare to be dazzled."
print "Multiply your number by 4."
raw_input("When you're ready, press a key...")


# math on the number
# (2(4n+12)+16)/8-n=5
#  (8n+40)/8-n=5
#  n+5-n=5
#  5=5

number = number*4
print "You should have gotten"
print number
print "Now add 12 to the result."
raw_input("When you're ready, press a key...")

number = number+12
print "You should have gotten"
print number
print "Double the new number."
raw_input("When you're ready, press a key...")

number = number*2
print "You should have gotten"
print number
print "Add 16."
raw_input("When you're ready, press a key...")

number = number+16
print "You should have gotten"
print number
print "Now divide that by 8, we're almost done!"
raw_input("When you're ready, press a key...")

number = number/8
print "You should have gotten"
print number
print "Now subtract your original number, and you'll get 5!!!"
raw_input("When you're ready, press a key...")

number = number - initialNumber
print "You should have gotten"
print number
#Dazzle them!
print "Thoust been dazzl'd *mic drop*"



