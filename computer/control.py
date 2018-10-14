import bluetooth
import sys, pygame
from pygame.locals import *
pygame.init()

print "Searching for device..."
print ""
device = -1
while 1:
    print "doing pass"
    nearby_devices = bluetooth.discover_devices()
    for i in nearby_devices:
        if bluetooth.lookup_name( i ) == "NORMAL":
            device = i
            print "found!"
    if device != -1:
        break
print bluetooth.lookup_name(device), " has been located"
sock = bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((device, 1))
pygame.init()
size = width, height = 320, 240

pygame.display.set_mode(size)

keys = pygame.key.get_pressed()

state = ["s", "s"]

while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == KEYDOWN:
            if event.key == K_w:
                state[0] = "f"
            if event.key == K_s:
                state[0] = "b"
            if event.key == K_e:
                state[1] = "f"
            if event.key == K_d:
                state[1] = "b"
            if event.key == K_SPACE:
                sock.send("9")
        elif event.type == KEYUP:
            if event.key == K_w:
                if state[0] == "f":
                    state[0] = "s"
            if event.key == K_s:
                if state[0] == "b":
                    state[0] = "s"
            if event.key == K_e:
                if state[1] == "f":
                    state[1] = "s"
            if event.key == K_d:
                if state[1] == "b":
                    state[1] = "s"
            if event.key == K_SPACE:
                sock.send("9")
    if state == ["s", "s"]:
        sock.send("0")
    elif state == ["s", "f"]:
        sock.send("1")
    elif state == ["s", "b"]:
        sock.send("2")
    elif state == ["f", "s"]:
        sock.send("3")
    elif state == ["f", "f"]:
        sock.send("4")
    elif state == ["f", "b"]:
        sock.send("5")
    elif state == ["b", "s"]:
        sock.send("6")
    elif state == ["b", "f"]:
        sock.send("7")
    elif state == ["b", "b"]:
        sock.send("8")




while 1:
    key = getkey()
    if key == keys.UP:
        sock.send("up")
    if key == "q":
        sock.close()
        break
