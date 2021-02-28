#Disclaimer - about this project

Direct access to the repository: https://github.com/mrlreable/reverse-line-server

About this repository:
	- it contains a basic TCP server-client model written in C programming language
	- the server and client side should be run in separate terminals
	- currently I have no Linux on my laptop so I created 2 versions:
		- the master branch: is based on the winsock library, the main.c file is the server basically, client.c is the client,
				     and contains a Makefile to build the 2 .c files (in cmd: \.mingw32-makefile.exe)
		- linux_version branch: I could not test it since the reasons above, but the code itself is no different (just in few
					function names and libraries), the files are the mainx.c (server), clientx.c (client), Makefilex