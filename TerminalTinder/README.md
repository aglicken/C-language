Terminal Tinder - Alyssa Kelley & Anne Glickenhaus

This program is mainly written in C with a small amount of python, and its functionality is being a match maker. The user is asked initial questions about themselves, and then fills out a dating questionnaire which is all saved to a seperate file just for them, and their name is added to our database file with all of our members. We then use File I/O to parse through the database and each individual user's file, to find this current user's perfect match. Once a match is found, a heart animation pops up on the screan, and both users are emailed their corrensponding matches file. If no match is made, a sad animation is played and then they are informed of this news. If no match is made, their name will stay in the database for potential matches in the future. 

Files used: 

    questionnaire.h - This is the header file that all of the programs for intial setup use. It holds the Person struct which contains their answers.
    
    questionnaire.c - This program is the intial prompting of the user for their personal information such as name and email address, and their is a lot of error checking in the program to ensure that we have their information correct for when we reach out to them and make their portfolio.
    
    ask_dating_questions.c - This program is asking the actual dating questions. There are 10 questions all with multiple choice answers usually with 5 options. The users enters their choice as a numeric value indiciting which number choice their answer is. 
    
    make_files.c - This program takes the information saved in questionnaire.h that was gathered in questionnaire.c and ask_dating_questions.c and actually makes their dating file. The file is formated in the way of their personal information at the top, followed by their answer choices. This is the style of the file:
            Question
            # - Answer description
            New line
    
    make_match.h - This is the header file for making a match and holds that info in the Match struct. 
    
    make_match.c - This program goes through the total database file and parses through the names and then opens the individual portfolios to see who has a match with the current user. This also creates a file keeping track of who matches with who.
            
    made_match.py - This is the python script that is called if a match is made. The script is inflicted in the main C file and will display the animation and email the two users that were matched with one another.
    
    no_match_made.py - This is the python script that is called if a match is made. The script is inflicted in the main C file and will display the animation and inform the user that no match has been made at this time.

    Please Note: With the python graphics, if you do not click on the pop up window, the graphics with take a long time to appear. You need to click on the graphics window in order to avoid this delay, and the emails take about 30 seconds to finishing sending after the turtle window is closed. You will see print statements to standard out indicating when this is complete.

    call_python.c - This file is working with make_match.h to inflict the correct python command to run when a match is made, or at the end when no match can be made. 

    Makefile - This file takes care of creating all of the object files and linking them together since we are using multiple files in this project it is crucial to compile it a specific way. Pygame is a python install that we have, so we provided a line in the Makefile to pip install this for you with the command "make .env", and there is also the "make clean" command to remove the executable.