import pygame
import sys

# Initialize Pygame
pygame.init()

# Set up some constants
WIDTH, HEIGHT = 640, 480
BALL_RADIUS = 20
SPEED = 2

# Set up some colors
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# Create the game window
screen = pygame.display.set_mode((WIDTH, HEIGHT))

# Set up the ball's initial position and velocity
x, y = WIDTH // 2, HEIGHT // 2
vx, vy = SPEED, SPEED

# Game loop
while True:
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    # Move the ball
    x += vx
    y += vy

    # Bounce off edges
    if x - BALL_RADIUS < 0 or x + BALL_RADIUS > WIDTH:
        vx = -vx
    if y - BALL_RADIUS < 0 or y + BALL_RADIUS > HEIGHT:
        vy = -vy

    # Draw everything
    screen.fill(WHITE)
    pygame.draw.circle(screen, RED, (x, y), BALL_RADIUS)

    # Update the display
    pygame.display.flip()
    pygame.time.Clock().tick(60)