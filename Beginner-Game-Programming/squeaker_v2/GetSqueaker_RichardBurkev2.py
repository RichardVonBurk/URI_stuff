"""
    Richard Burke
    4/25/16
    Get Squeakers! Game
"""

#import and initialize
import pygame
import random
pygame.init()
pygame.mixer.init()

def main():
    #display
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption("Get Squeakers!")

    #entities
    background = pygame.Surface(screen.get_size())      
    background = background.convert()
    background.fill((130, 165, 145))

   
    
        
    #Squeaker Class
    class Squeaker(pygame.sprite.Sprite):
        def __init__(self):
            pygame.sprite.Sprite.__init__(self)
            self.image = pygame.image.load("Squeaker.jpg")  
            self.rect = self.image.get_rect()                   
            self.rect.centerx = random.randint(0, screen.get_width())
            self.rect.centery = random.randint(0, screen.get_height())
            squeak = pygame.mixer.Sound("SqueakSound.ogg")

        def play_squeak(self):
            squeak.play()

        
            
            
    class CursorCircle(pygame.sprite.Sprite):
        def __init__(self):
            pygame.sprite.Sprite.__init__(self)
            self.image = pygame.Surface((40, 40))
            pygame.draw.circle(self.image, (255, 0, 0), (300, 300), 20, 0)
            self.rect = self.image.get_rect()

        def update(self):
            mouseXY = pygame.mouse.get_pos()
            self.rect.center = mouseXY


    #Spawn 10     
    squeakers = []
    for i in range(0, 10):
        if i < 10:
            squeakers.append(Squeaker())
            i+=1
                         
    
    
    allSqueakers = pygame.sprite.Group(squeakers)

    cursorCir = CursorCircle()
    allCursorCir = pygame.sprite.Group(cursorCir)

    
    #assign
    clock = pygame.time.Clock()
    keepGoing = True
    pygame.mouse.set_visible(False)
    #loop
    while keepGoing:
        #time
        clock.tick(30)

        
        #events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                keepGoing = False
            if pygame.sprite.spritecollide(cursorCir, squeakers, False):
                play = pygame.mixer.Sound("SqueakSound.ogg")
                play.play()
        
        
        #refresh
        screen.blit(background, (0,0))
        allSqueakers.clear(screen, background)
        allSqueakers.update()
        allSqueakers.draw(screen)
        allCursorCir.clear(screen, background)
        allCursorCir.update()
        allCursorCir.draw(screen)
              
        pygame.display.flip()

    pygame.quit()
    
if __name__ == "__main__":
    main()
