# TU Numerical Library

This library exists mainly for TUACM students to get a working project under
their belt to help bridge the gap between theory and practice, so if you need
performance critical code, you're probably better off using another library.

# Setting Up

1.	[Set up a github account](https://git-scm.com/book/en/v2/GitHub-Account-Setup-and-Configuration).
1.	[Fork this repository](https://guides.github.com/activities/forking/).
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
1.	[Follow the instructions on setting up for C/C++ development](https://tuacm.com/blog/c-language/compilers-and-ides/#which-ide-to-use).
	If you're on Windows and you followed the above steps, you can use the
	`~/win-home/dev/` path instead of the `/mnt/c/Users/[user]/dev/` path
	proposed in the article as they're the same. You pretty much just need to
	install a text editor. If you already have an IDE that you like, it will
	work. If not, then just install Visual Studio Code for now and use that as
	your IDE.
1.	Run the following command so that you can stay up to date with the main
	repository:
	```bash
		$ git remote add upstream https://github.com/TheLandfill/tunl.git
	```
	You should only ever need to use the upstream master branch, which you can
	get using
	```bash
		$ git checkout master
		$ git pull upstream master
	```
1.  You should now have downloaded the project and are ready to work on it. If
	you're on Windows, you'll find the project files in the directory
	C:\Users\[user]\dev\tunl\ on Windows and you'll find them in
	~/win-home/dev/tunl/ in the Terminal App (probably Ubuntu). If you're on Mac
	or Linux, then they'll be in ~/dev/tunl, a.k.a. /home/[user]/dev/tunl.

# Contributing to the Repository

We're going to follow the [git flow
model](https://guides.github.com/introduction/flow/), which consists of
1.	Make a new branch for the feature you're working on. For example, let's say
	you want to implement the Matrix class. In which case, you would create a
	branch called `matrix` and switch to it using:
	```bash
		$ git checkout -b matrix
	```
1.	Make the necessary additions, changes, and deletions to the files/code. Make
	sure to make a commit whenever you make a change that you would hate to have
	to reimplement if you delete it. Your commit messages should be descriptive
	enough for me to tell what you did. If you made a bunch of changes in a
	commit, create a file (call it commit-file.txt and put it in the `dev/tunl/`
	directory) and write out the commit message in the format:
	```text
		One-Line Summary

		1.	First change is going to be a long line so that I can show you how
			to write multiline descriptions
		2.	Second change
		3.	Third change
		...
	```
1.	Every so often, run the commands (I'm assuming you're on the branch
	`matrix`. If not, replace `matrix` with the name of the branch.)
	```bash
		$ git checkout master
		$ git pull upstream master
		$ git checkout matrix
		$ git merge master
	```
	to make sure you're as up to date as possible. You don't want to be twenty
	commits behind and have to incorporate a bunch of changes into your branch
	all at once. If all goes well, we won't get any merge conflicts and we can
	move onto the next step. If, however, we do get merge conflicts, then we'll
	have to fix them by editing the relevant files, as shown in [this
	article](https://opensource.com/article/20/4/git-merge-conflict).
1.	Once you've finished the feature and want to add it into the main
	repository (I'm assuming you're on the branch `matrix`. If not, replace
	`matrix` with the name of the branch.):
	1.	First, run the commands:
		```bash
			$ git checkout master
			$ git pull upstream master
			$ git checkout matrix
			$ git merge master
		```
	Note that merging `master` with your current branch was a recommendation in
	the previous step, but **merging `master` with your current branch is
	required at this point**. You must successfully merge `master` into your
	branch before a pull request will be accepted.
1.	Compile everything and run the tests to make sure everything is working.
1.	[Send a pull request from your fork](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork).
1.	We'll discuss what the changes you made did well and what needs to be fixed.
1.	Fix anything that needs to be fixed while continuing to keep your branch up
	to date with master by running the commands
	```bash
		$ git checkout master
		$ git pull upstream master
		$ git checkout matrix
		$ git merge master
	```
	and taking care of any merge conflicts.
1.	Compile everything and run the tests to make sure everything is working.
1.	Once everything is fixed, we'll merge it into master and you start working
	on a new feature.

# Contributing Rules

You can ask anyone else for help at any point in order to follow these
guidelines. If you break the rules, we won't merge your code into the main
repository.

-	**Give variables, files, functions, etc. a descriptive name.** Doing so will
	make the code easy to read and understand, which means less time spent
	trying to figure out what you meant.
	-	One letter names and abbreviations are only acceptable if they're
		common. For example, `num` as an abbreviation for "number" is fine, `i`,
		`j`, and `k` are fine for iteration variables in a loop, `x`, `y`, and
		`z` are fine if you're talking about Cartesian coordinates, etc.
	-	Context can also help you shorten the length of variable or function
		names. For example, `num_elements` is a descriptive name, but if you're
		implementing a mathematical formula, you can just use `n`.
	-	Do not give the variables long names unless you cannot make the name any
		shorter.
	-	In short, if I can't tell what a thing is just by looking at its name,
		you will need to change it.
-	If you get warnings or errors when you compile the program, fix them.
-	To keep a consistent coding style:
	-	All constants will be uppercase and in snake case (e.g. `TWO_THIRDS`).
	-	All variables and function names will be lowercase and in snake case
		(e.g. `distance_from_sun`, `area_of_circle`).
	-	All classes and structs will be capitalized and in snake case (e.g.
		`Simpson_Points`).
	-	Camel case (e.g. `areaOfCircle`) is banned.
-	Keep comments to the bare minimum. Your code should be self-documenting,
	meaning I should be able to read it and understand what's going on without
	comments.
