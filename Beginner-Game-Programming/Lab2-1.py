""" silent_auction.py
    Richard Burke

    Program allows enduser to bid on items.
"""

import random

# Create a list of items

items = ["Baby Groot", "Forcefield dog", "Scaring Companion"]
bids = [0, 0, 0]

# Find out what the user wants to bid on.
print "You can bid on the following items: "
for item in items:
    print item


# Allow enduser to add to list


listAdd = raw_input("You can add one item. \nWhat item are you adding to the list?")

items.append(listAdd)


# Display updated list

print "You can bid on the following items: "
for item in items:
    print item



bid_item = raw_input("\nWhat do you wish to bid on? ")

# Randomly generate and amount to offer from 1 to 100
offer = random.randint(1, 100)
print "\nYou bid %d credits on the %s." %(offer, bid_item)

# Change the bid for the item.
index = items.index(bid_item)


# Print the result
print "\nThe high bid for %s is now %d credits." %(items[index], offer)
