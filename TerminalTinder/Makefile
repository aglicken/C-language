CC = gcc
CFLAGS = -std=c11 -g

.env: requirements.txt
	pip3 install -r requirements.txt 

terminal_tinder.exe: questionnaire.c ask_dating_questions.c make_files.c Terminal_Tinder_main.c
	$(CC) $(CFLAGS) -o terminal_tinder.exe questionnaire.c ask_dating_questions.c make_files.c make_match.c call_python.c Terminal_Tinder_main.c

memcheckTT.exe: terminal_tinder.exe
	valgrind --leak-check=yes --track-origins=yes ./terminal_tinder.exe

clean:
	rm *.exe


