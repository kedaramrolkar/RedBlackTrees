This code is a implementation of Red-Black Tree as a part of class Assignment for ADS. 
Written by: Kedar Amrolkar   UFID:18418443	University of Florida

To compile the project, use the included Makefile i.e just run command
$ make         =>     This will create a executable named 'bbst' in the same folder.

You can use following command to clear compilation:
$ make cl	=>     This will delete the executable created above.

About executable bbst:
Run by: 
	$ ./bbst ~/testFolder/InitialSortedList.txt 			=> This will ask for commands via Std input-keyboard.
or	$ ./bbst ~/testFolder/InitialSortedList.txt < commands.txt      => This will directly print the output on screen
or	$ ./bbst ~/testFolder/InitialSortedList.txt < commands.txt > outputtest.txt 		=> This will send the output to file.

Any other parameters or command wont work. Only one parameter is expected.
