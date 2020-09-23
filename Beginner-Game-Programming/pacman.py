""" pacman.py
    a drawn pacman, nothing else
    Richard Burke
"""

import pygame
import math

def draw(background):

    pygame.draw.line(background, (255, 0, 0), (5, 100), (100, 100))

    pygame.draw.arc(background, (0, 0, 0), ((5, 100), (100, 100)), 0, math.pi*3/2, 5)
    
