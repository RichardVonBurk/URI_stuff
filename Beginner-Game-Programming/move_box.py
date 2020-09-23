""" move_box.py
    illustrates basic motion
    in the IDEA/ALTER framework
    moves a rect across the screen
"""

# Initialize
import pygame
import random
pygame.init()

# Display
screen = pygame.display.set_mode((640, 480))
pygame.display.set_caption("move a box")

#Entities
#Make a green-gray background.
background = pygame.Surface(screen.get_size())
background = background.convert()
background.fill((130, 165, 145))

#Make a red box.
BOX_SIDE = 25
box = pygame.Surface((BOX_SIDE, BOX_SIDE))
box = pygame.image.load("katze.png")
box = box.convert()
#box.fill((255, 0, 0))

#Set variables so box will bounce diagonally downwards
box_x = 0
box_y = 0
dx = 1
dy = 10

#Setup Counters for timed events based on clock.tick(30) = 1 sec
GrowthAndColor = 0
SizeAndColor = 0
TeleportCounter = 0
ReverseCounter = 0

    #Assign
clock = pygame.time.Clock()
keepGoing = True

#pygame.time.set_timer(counter, 5000)
    #Loop
while keepGoing:

    

    #Time
    clock.tick(30)

    #Square Resets Size and random color change
    if SizeAndColor == random.randint(600, 1200):
        BOX_SIDE = 25
        box = pygame.Surface((BOX_SIDE, BOX_SIDE))
        box.fill((random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
        SizeAndColor = 0
    else:
        SizeAndColor += 1

    #Square increases Size and random color change
    if GrowthAndColor == 150:   #150 / 30 = 5 sec
        BOX_SIDE += 10
        box = pygame.Surface((BOX_SIDE, BOX_SIDE))
        box.fill((random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)))
        GrowthAndColor = 0
    else:
        GrowthAndColor += 1
    
    #Events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            keepGoing = False

    
    
    #when clockInterval = random(20,40) then reset box original size and random color
    
    
    #modify box value
    box_x += dx
    box_y += dy

    #Teleports Square
    if TeleportCounter == 200:
        box_x = random.randint(0, screen.get_width())
        box_y = random.randint(0, screen.get_height())
        TeleportCounter = 0
    else:
        TeleportCounter += 1

    #Switches Direction
    if ReverseCounter == 300:
        dx *= -1
        ReverseCounter = 0
    else:
        ReverseCounter += 1

    #check boundaries
    if box_x + BOX_SIDE > screen.get_width():
        dx *= -1
    elif box_x < 0:
        dx *= -1
    if box_y + BOX_SIDE > screen.get_height():
        dy *= -1
    elif box_y < 0:
        dy *= -1

    #Refresh screen
    screen.blit(background, (0, 0))
    screen.blit(box, (box_x, box_y))
    pygame.display.flip()

pygame.quit()
