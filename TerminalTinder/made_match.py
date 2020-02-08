from turtle import *
import argparse
import time
import os
import pygame
import subprocess
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.image import MIMEImage
from email.message import EmailMessage
from email.utils import make_msgid
import mimetypes
from email import encoders
import smtplib

def main():

	setup(750, 750)

	parser = argparse.ArgumentParser(description='Usage: python3 '
                                     'heart.py <Person #1> '
                                     '<Person #2>')

	parser.add_argument('person1', type=str,
                        help='Person #1 Name')

	parser.add_argument('person2', type=str,
                        help='Person #2 Name')

	parser.add_argument('person1_email', type=str,
                        help='Person #1 Email Address')

	parser.add_argument('person2_email', type=str,
                        help='Person #2 Email Address')

	parser.add_argument('person1_filename', type=str,
                        help='Person #1 Dating File Name')

	parser.add_argument('person2_filename', type=str,
                        help='Person #2 Dating File Name')

	args = parser.parse_args()

	person1 = args.person1

	person2 = args.person2

	email_to_1 = args.person1_email
	email_to_2 = args.person2_email

	base_path = os.path.abspath(os.path.dirname(__file__))

	path_to_heart_gif = os.path.join(base_path, 'heart_gif')

	path_to_love_song = os.path.join(base_path, 'songs/trimmed_love_shack.mp3')

	filename1 = os.path.join(base_path, args.person1_filename)
	filename2 = os.path.join(base_path, args.person2_filename)

	play_the_song(path_to_love_song)
	
	draw_background(path_to_heart_gif)

	draw_the_names(person1, person2)

	send_email(person1, person2, email_to_1, filename2)  # this emails name1 name2's file (filename2)
	send_email(person2, person1, email_to_2, filename1)  # this emails name2 name1's file (filename1)

	exitonclick()


def curvemove(speed_level):
    speed(speed_level)
    for i in range(200):
        right(1)
        forward(1)


def draw_background(path_to_heart_gif):

	for times_played in range(6):

		for picture_num in range(38)[1:]:
			picture = path_to_heart_gif+'/'+'heart'+str(picture_num)+'.png'
			bgpic(picture)
			update()

	bgpic(path_to_heart_gif+'/compressed_heart.png')
	update()


def draw_the_names(person1, person2):

	intro = "Match has been made!"
	print_saying = person1+' matches with '+person2

	penup()
	goto(0,200)
	color("white")
	pensize(5)
	write(intro, font = ("SignPainter", 70, "bold", 'italic',
		  'underline'), align="center")
	goto(0,-10)
	pensize(3)
	color("black")
	write(print_saying, font = ("Courier", 25, "bold",
	      'italic'), align="center")
	penup()
	goto(500,500)
	done()


def play_the_song(path_to_love_song):

	pygame.init()
	pygame.mixer.init()
	pygame.mixer.music.load(path_to_love_song)
	pygame.mixer.music.play()
	pygame.event.wait()


def send_email(name_1, name_2, email_to, filename):

    email_address = 'terminal.tinder@gmail.com'
    filename_logo = 'terminal_tinder_logo.jpg'
    logo_data = open(filename_logo, 'rb')

    # email_address_password = os.environ[str('TT_EMAIL_PASS')]
    email_address_password = "CIS330password!" # NOT SECURE -- CHANGE TO LINE ABOVE

    email_contents_subject = ("You have a match! - Terminal Tinder")

    email_contents_body = ("Congrats " + name_1 + "!\n"
    	"\nYou have made a match using Terminal Tinder!\n"
    	"\nYour perfect match is "+name_2+" and we have attached their dating portfolio to this email for you."
    	"\nWe hope that you and your match have great success, and wish you both nothing but the best!\n"
    	"\nPlease feel free to use Terminal Tinder anytime to match with even more people.\n"
    	"\nKindest, \n"
    	"\nAlyssa and Anne - Founders of Terminal Tinder\n")

    msg = MIMEMultipart()
    msg['From'] = email_address
    msg['Subject'] = email_contents_subject

    msg.attach(MIMEText(email_contents_body, 'plain'))

    attachment = open(filename, 'rb')

    # Allows us to upload the attachment
    part = MIMEBase('application', 'octet-stream')
    part.set_payload((attachment).read())
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', "attachment; filename= " +
                    filename)
    msg.attach(part)

    # ----------------- for logo -------------------------------
    # image = MIMEImage(logo_data, name=os.path.basename(filename_logo))
    # msg.attach(image)

    image = MIMEBase('application', 'octet-stream')
    image.set_payload((logo_data).read())
    encoders.encode_base64(image)
    image.add_header('Content-Disposition', "attachment; filename= " +
                    filename_logo)
    msg.attach(image)

    # ----------------------------------------------------------

    text = msg.as_string()
    server = smtplib.SMTP('smtp.gmail.com', 587)
    server.starttls()
    server.login(email_address, email_address_password)


    receiver_email_address = email_to
    msg['To'] = receiver_email_address
    server.sendmail(email_address, receiver_email_address, text)
    print ("The dating portfolio for {} has successfully been sent "
           "to {}".format(name_2, name_1))

    server.close()


if __name__ == '__main__':
    main()
