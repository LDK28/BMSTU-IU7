import pygame
import os

WIDTH = 840
HEIGHT = 500
FPS = 60  # frame per second

# colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

pygame.init()
gameWindow = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Cool guy")
clock = pygame.time.Clock()

pygame.mixer.music.load('Forest Whisper.wav')  # background soundtrack
pygame.mixer.music.set_volume(0.4)
pygame.mixer.music.play(loops=-1)

# hero's coordinates
x = 0
y = HEIGHT // 2

# setting assets' folders
game_folder = os.path.dirname(__file__)
img_folder = os.path.join(game_folder, 'img')

bg = pygame.image.load(os.path.join(img_folder, 'bg.png'))

leftGround = pygame.image.load(os.path.join(img_folder, 'grassHalfLeft.png'))
midGroung = pygame.image.load(os.path.join(img_folder, 'grassHalfMid.png'))
rightGroung = pygame.image.load(os.path.join(img_folder, 'grassHalfRight.png'))
groundWidth = midGroung.get_width()

ladderMid = pygame.image.load(os.path.join(img_folder, 'ladder_mid.png'))
ladderTop = pygame.image.load(os.path.join(img_folder, 'ladder_top.png'))

Jossy = [pygame.image.load(os.path.join(img_folder, 'snakeLava.png')),
         pygame.image.load(os.path.join(img_folder, 'snakeLava_ani.png'))]
jCount = 0

message = pygame.image.load(os.path.join(img_folder, 'message.png'))
message = pygame.transform.scale(message, (message.get_width() // 3, message.get_height() // 5))
message.set_colorkey(WHITE)
text1 = pygame.font.SysFont('Calibri', 10).render("Hey buddy!", 1, BLACK)
text2 = pygame.font.SysFont('Calibri', 10).render("You can use this ladder to climb up.", 1, BLACK)
text3 = pygame.font.SysFont('Calibri', 10).render("Push <UP> near this one.", 1, BLACK)

doorMid = pygame.image.load(os.path.join(img_folder, 'door_openMid.png'))
doorTop = pygame.image.load(os.path.join(img_folder, 'door_openTop.png'))

gameComplete = pygame.image.load(os.path.join(img_folder, 'mission_complete.png'))
gameComplete.set_colorkey(WHITE)

gameOver = pygame.image.load(os.path.join(img_folder, 'gameover.png'))
gameOver.set_colorkey(WHITE)

# hero's images
man = [[pygame.image.load(os.path.join(img_folder, 'p1_walk01_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk02_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk03_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk04_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk05_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk06_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk07_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk08_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk09_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk10_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk11_l.png'))],

       [pygame.image.load(os.path.join(img_folder, 'p1_walk01_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk02_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk03_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk04_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk05_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk06_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk07_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk08_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk09_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk10_r.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_walk11_r.png'))],

       [pygame.image.load(os.path.join(img_folder, 'p1_front.png'))],

       [pygame.image.load(os.path.join(img_folder, 'p1_jump_l.png')),
        pygame.image.load(os.path.join(img_folder, 'p1_jump_r.png'))],

       [pygame.image.load(os.path.join(img_folder, 'alienGreen_climb1.png')),
        pygame.image.load(os.path.join(img_folder, 'alienGreen_climb2.png'))]]
manImage = 0
move = 0

running = True
while running:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            running = False

    gameWindow.blit(bg, (0, 0))

    gameWindow.blit(leftGround, (0, HEIGHT / 2 + 92))
    gameWindow.blit(midGroung, (groundWidth, HEIGHT / 2 + 92))
    gameWindow.blit(midGroung, (2 * groundWidth, HEIGHT / 2 + 92))
    gameWindow.blit(midGroung, (3 * groundWidth, HEIGHT / 2 + 92))
    gameWindow.blit(midGroung, (4 * groundWidth, HEIGHT / 2 + 92))
    gameWindow.blit(midGroung, (5 * groundWidth, HEIGHT / 2 + 92))
    gameWindow.blit(rightGroung, (6 * groundWidth, HEIGHT / 2 + 92))

    gameWindow.blit(leftGround, (6 * groundWidth, HEIGHT / 2 - 90))
    gameWindow.blit(midGroung, (7 * groundWidth, HEIGHT / 2 - 90))
    gameWindow.blit(midGroung, (8 * groundWidth, HEIGHT / 2 - 90))
    gameWindow.blit(midGroung, (9 * groundWidth, HEIGHT / 2 - 90))
    gameWindow.blit(midGroung, (10 * groundWidth, HEIGHT / 2 - 90))
    gameWindow.blit(rightGroung, (11 * groundWidth, HEIGHT / 2 - 90))

    gameWindow.blit(ladderMid, (410, HEIGHT / 2 + 22))
    gameWindow.blit(ladderMid, (410, HEIGHT / 2 - 35))
    gameWindow.blit(ladderTop, (410, HEIGHT / 2 - 90))

    gameWindow.blit(doorMid, (11 * groundWidth, HEIGHT / 2 - 160))
    gameWindow.blit(doorTop, (11 * groundWidth, HEIGHT / 2 - 160 - doorMid.get_height()))

    if jCount % FPS < FPS / 2:
        gameWindow.blit(Jossy[0], (300, HEIGHT // 2 - 54))
        jCount += 1
    else:
        gameWindow.blit(Jossy[1], (300, HEIGHT // 2 - 54))
        jCount += 1
    gameWindow.blit(message, (120, HEIGHT / 2 - 165))
    gameWindow.blit(text1, (160, HEIGHT / 2 - 145))
    gameWindow.blit(text2, (140, HEIGHT / 2 - 130))
    gameWindow.blit(text3, (150, HEIGHT / 2 - 115))

    gameWindow.blit(man[move][manImage], (x, y))

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]:
        if x > 0:
            x -= 3
        move = 0
        manImage += 1
        if manImage > 10:
            manImage = 0
    elif keys[pygame.K_RIGHT]:
        if x < WIDTH - 60:
            x += 3
            move = 1
            manImage += 1
            if manImage > 10:
                manImage = 0
    elif keys[pygame.K_UP]:
        if 380 < x < 430 and HEIGHT // 2 - 180 <= y <=  HEIGHT // 2:
            x = 410
            y -= 3
            move = 4
            manImage += 1
            if manImage > 1:
                manImage = 0
    elif keys[pygame.K_DOWN]:
        if 400 < x < 410 + ladderTop.get_width() and y < HEIGHT // 2:
            x = 410
            y += 3
            move = 4
            manImage = 1
    elif x == 410 and HEIGHT // 2 - 180 < y < HEIGHT // 2:
        move = 4
        manImage = 0
    else:
        move = 2
        manImage = 0

    if (x > 480 and y > HEIGHT // 2 - 180) or (y > HEIGHT // 2):
        y += 3
        move = 3
        manImage = 1

    if x < 360 and y < HEIGHT // 2:
        y += 3
        move = 3
        manImage = 0

    # hero on the ladder
    if HEIGHT // 2 - 180 < y < HEIGHT // 2:
        if x < 410:
            move = 3
            manImage = 0
            y += 3
        elif x > 410:
            move = 3
            manImage = 1
            y += 3

    if y > HEIGHT:
        gameWindow.blit(gameOver, (WIDTH // 2 - 250, HEIGHT // 2 - 250))
        if keys[pygame.K_RETURN]:
            x = 0
            y = HEIGHT // 2
    if WIDTH - 70 <= x <= WIDTH - 64:
        gameWindow.blit(gameComplete, (WIDTH // 2 - 320, HEIGHT // 2 - 200))
        x = WIDTH - 67
        if keys[pygame.K_RETURN]:
            x = 0
            y = HEIGHT // 2
    clock.tick(FPS)
    pygame.display.flip()

pygame.quit()
