# Project README file

This is **PR1-Multithreading** Readme file.
Last updated - 15-02-2018

## Project Description
Project #1 :- Multithread client-server implementation for static data sharing using network programming in C and custom Getfile protocol

- Summary :- Implementation of this project can be divided into 3 stages
	_Stage 1 - Echo!_ - first practice stage to get client and server to talk to each other
	References for echo implementation:
		a. Project readme document incl. sample source code and linux socket tutorial
		b. Beej's guide on network programming

	_Stage 2 - Share_ - second practice stage to get client to receive content from server
	References for transfer file implementation:
		a. Project readme document
		b. File transfer example on Stackoverflow

	_Stage 3 - API and Multithread implementation_ - get server to interact with multiple clients
	References for getfile api implementation:
		a. Project readme document
		b. Piazza threads#142, 200, 240, 249, 279,
		c. Tutorial on function pointers and void pointers 
	References for multithread implementation:
		a. Pthread creation and termination example on computing.Ilnl.gov
		b. Piazza thread#463 on steque
		c. Classroom lecture on Pthreads (they are awesome!)


- Any additional observations -
	- This is my first experience with serious C-programming and socket programming in linux environment - these two being at the core of this project. I have spent major portion of my time learning - concepts in C programming, network programming, gcc, gdb, make and to some extent git setup.
	- For project setup I have used Ubuntu 16.4 in Virtualbox on Macbook. I found this to be easiest to setup project environment and instructions shared on Piazza really helped. I did not face any issues.
	- I have thoroughly enjoyed working on this project and I wish I had some more time.
	- If I have to do this project again, I will invest more time on callbacks and parallel programming
	- I will revisit this project later in the semester to work on the core areas where I couldn't give needed time - parallel programming using pthreads.

## Known Bugs/Issues/Limitations

__Please tell us what you know doesn't work in this submission__
Below is the summary of bugs/issues/limitations at the time of latest submission till date
1. echoclient - client is not able to print server response
2. gfclient - memory leak issues
3. gfserver - buffer overflow issues
4. gfclient_mt - memory leak issues

## References
Why C has Pointers? (http://duramecho.com/ComputerInformation/WhyCPointers.html)
-- good article for those who have never done serious C programming before (like me)
Void Pointers (https://www.geeksforgeeks.org/void-pointer-c/)
-- helped in gflib implementation. Originally shared by fellow student Kimberly Sibol in Piazza thread #220
Pthread concepts and design considerations (https://computing.llnl.gov/tutorials/pthreads/#Designing)
-- helped understand basics of parallel programming
Besides, multiple piazza threads on issues and discussion around project implementation and challenges has been quite valuable


__Please include references to any external materials that you used in your project__

**Note** - if you prefer, you may submit a PDF version of this readme file.  Simply create a file called **readme-student.pdf** in the same directory.  When you submit, one or the other (or both) of these files will be submitted.  This is entirely optional.
