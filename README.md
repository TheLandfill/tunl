# TU Numerical Library

This library exists mainly for TUACM students to get a working project under
their belt to help bridge the gap between theory and practice, so if you need
performance critical code, you're probably better off using another library.

# Setting Up

1.	[Set up a github account](https://git-scm.com/book/en/v2/GitHub-Account-Setup-and-Configuration).
1.	[Fork this repository](https://guides.github.com/activities/forking/).
1.	[Follow the instructions on setting up for C/C++ development](https://tuacm.com/blog/c-language/compilers-and-ides/#which-ide-to-use).
1.	There are some differences between Windows and Mac/Linux, so the next step
	will cover both cases. Everything will be done in the terminal.
	-	On Windows, open the Ubuntu or Debian App (probably Ubuntu) and run the
		commands
		```bash
			$ ln -s /mnt/c/Users/[user] ~/win-home
			$ mkdir -p ~/win-home/dev/
			$ cd ~/win-home/dev/
		```
		where [user] is your username on your Windows computer. We're just
		creating a directory where you can put your projects that should be easy
		to access from both your terminal and on Windows.
	-	On Linux/Mac, open the Terminal or Terminal Emulator and run the
		commands
		```bash
			$ mkdir -p ~/dev/
			$ cd ~/dev/
		```
	Then type the following command on Windows, MacOS, or Linux.
	```bash
		$ git clone https://github.com/[github username]/tunl.git
	```
	For example, I would type
	```bash
		$ git clone https://github.com/TheLandfill/tunl.git
	```
	since my username is TheLandfill and someone with the username `password` would
	type
	```bash
		$ git clone https://github.com/password/tunl.git
	```
1.  You should now have downloaded the project and are ready to work on it. If
	you're on Windows, you'll find the project files in the directory
	C:\Users\[user]\dev\tunl\ on Windows and you'll find them in
	~/win-home/dev/tunl/ in the Terminal App (probably Ubuntu). If you're on Mac
	or Linux, then they'll be in ~/dev/tunl, a.k.a. /home/[user]/dev/tunl.
