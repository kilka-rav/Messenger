# Messenger
Local Messenger, the main function of which is the transmission of memes. Project will be updated.
We use SFML library. Install https://www.sfml-dev.org/download.php
We use SSH for send and recieve message.
We use network for classications memes.
You have to:
	Linux
	SFML-library
	g++(14)
	SSH LIBRARY(9.0) (information: https://github.com/GELGOOG-STUTZER/ssh_attempt)
	Python(3.8)
	torch, torchvision
	
RUN:
Before start:
	You have to customize personal_settings:
		1) share SSH-keys with your friends
		2) create directory, for you and your friend
		3) change ip, and names 13-18 strings in ../inception/global_variables.hpp
START:
	in ../inception:
		g++ -c paint.cpp
		g++ paint.o -o paint -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lssh -lstdc++fs
		./paint

CAPABILITIES:
	share messages, memes, classication of memes.
Screenshots:
	
