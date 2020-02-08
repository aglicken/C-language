from turtle import *
import argparse
import time
import os
import pygame
import subprocess


def main():

	setup(800, 800)

	base_path = os.path.abspath(os.path.dirname(__file__))

	path_to_crying_gif = os.path.join(base_path, 'crying_gif')

	path_to_lonely_song = os.path.join(base_path, 'songs/trimmed_lonely.mp3')

	play_the_song(path_to_lonely_song)
	
	draw_background(path_to_crying_gif)

	draw_message("fastest")

	exitonclick()


def draw_background(path_to_crying_gif):

	for times_playing in range(6):
		for picture_num in range(38)[1:]:
			picture = path_to_crying_gif+'/'+'crying'+str(picture_num)+'.png'
			bgpic(picture)
			update()

	bgpic(path_to_crying_gif+'/compressed_crying.png')
	update()


def draw_message(speed_level):

	penup()
	goto(0,-380)
	intro = "Sorry, no match was found."
	speed(speed_level)
	color("white")
	pensize(5)
	pendown()
	write(intro, font = ("SignPainter", 60, "bold", 'italic',
		  'underline'), align="center")
	penup()
	goto(500,500)
	done()


def play_the_song(path_to_lonely_song):

	pygame.init()
	pygame.mixer.init()
	pygame.mixer.music.load(path_to_lonely_song)
	pygame.mixer.music.play()
	pygame.event.wait()

if __name__ == '__main__':
    main()
