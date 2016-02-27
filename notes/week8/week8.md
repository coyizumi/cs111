# Week 8

## Crypto basics

* Algorithms (E, D) are widely known
* Keys (KE, KD) shouldbe less widely distributed
* For this to be effective, the cyphertext should be the only info that's available to the world
* Plaintext is known only to the people with the keys (in an ideal world)

Algs well known, keys not well known

Ideally cyphertext appears random

Compress THEN encrypt, cannot compress random data

* Secret Key encryption
* Symmetric-key
* MOnoalphabetic substitution
* Vignere cipher
*Both are easy to break!
* Given the encryption key, easy to generate the decryption key
* Alternatively, use different (but similar) algs for encryption and decryption

Modern Encryption Algs

* DES (Data encryption  standard)
	* 56 bit keys
	* Same key is used to encrypt and decrypt
	* Keys used to be difficult to guess
		* Needed to try 2^55 on avg
		* Modern computer can try millions per second
		* For $250k, EFF build a machine that broke DES quickly
* Current algorithms (AES, Blowfish) use at least 128 bit keys
	* Adding one bit makes it twice as hard to guess
	* Must try 2^127 keys on avg
	* At 10^15 per second, this would require 1000 billion years
	* Modern encryption isn't usually broken by brute force

Unbreakable codes

*One time pad
	* Use a truly random key as long as the message to be encoded
	* XOR the message with the key a bit at a time
* Code is unbreakable because
	* Key could be anything
	* Without knowning key, message could be anything with the correct number of bits in it
* Difficulty: dist key is as hard as dist message
	* May be easier because of timing
* Difficulty: generating truly random bits

If used twice, is no longer unbreakable

Truly random bits

* Typical random number generators aren't really random
	* Look random, but
	* Totally repeatable
* Get randomness from the outside world
	* Timing intervals: key presses, network packets, etc
	* Use a few(low order) bits from each sample
* May use physical processes
	* Radioactive decay
	* Lava lamps!!
	* Webcams with lens cap on
* Cureent approcah: leaky diodes
	* Built into new intel x86 cpus

PUblic Key crypto

* Instead of a single shared secret, keys come in pairs
	* One key of each pair dist widely (public)
	* One key of each pair kept secret (private)
	* Keys are inversed of one another, but not identical
	* Encrytpion and decrytpion are the same algorithm
* Typically used for
	* Encrypting small amounts of data
	* Establishing a shared key between two users who mightnot know each other
* Currently the most popular method involves primes and exponentiaition
	* Difficult to crack unless large numbers can be factored
	* Very slow for large messages
* Other methods involve discrete logarithsma dna elliptical curves

RSA Alg

* Two large primes p,q
* Not shared, difficult to compute them
* PUblic key is published anc can be used by anyhone to send a message to the private key's owner
* Encryption same algo

One way funciton (HASH)

* Easy to computer one way, hard to reverse
	* Given formula for f9x), easy to evaluation y= h(x)
	* Difficult to find "collisions": two values with same hash function
		* Weak collision resistance: given y, hard to find x such that f(x) = y
		* Strong collision resistance: hard to find x and x' != x such that f(x) = f(x')
* Often, operate similar to encrytption algos
	* Produce fixed-length output rather than variable length output
	* Similar to XORing blocks of ciphertext together
* Common Algos include
	* MD5: 128 bit
	* SHA1: 160 bit
	* SHA-256: 256 bit

Digital signatures

* Digital sig computed by
	* Applying one-way hash to original doc
	* Encrypting result with senders private key
* Reciever can verify by
	* Applying one way has function to received doc
	* Decrypting sig using senders public key
	* Comparing the two results equality means doc unaltered

PGP

* Uses public key encryption
	* Facilitates key distribution
	* Alloww messages to be sent encrypted to a person (encrypt with public key)
	* Allows person to send message  that must have come from her (encrypt with person's private key)

* Problem: Public key encrypt is very slow
* Solution: Use public key encryption to exchange shared key
	* Shared key is relatively short (128 bits)
	* Message encrypted using symmetric key encryption
* PGP can also be used to authenticate sender
	* Use digital signature and send message as plaintext


Diffy Helman algorithm for Key Exchange

A^x mod p 
A^y mod p other way
A^x^y mod p = a^y^x mod p

p is large prime

Does  NOT authenticate identity

User authentication

* Problem: How does comp know who you are?
* Solution: Use authentication to identify
	* Something the user knows
	* Something the user has

* Using passwords
* Successful login lets user in

* Dealing with passwords
* Shouldbe memorable
	* Shouldn'tneed to write down
	* Users should be able to recall them easily
* Passwords shouldn't be stored in the clear
	* Password file is often readable by all system users!
	* Password must be checked against entry in this file
* Solution: use hashing to hide "real" password
	* ONe-way function converting password to meaninglessstring of digits (Unix passwrd hash, MD5, SHA-1)
	* Difficult to find another passwrod that hashes to the same random-looking string
	* Knowing the hasehd value and hash function givesno clue to the original password

Salting Passwords

* Passwords can be guessed
	* Before starting bild a table fo all dictionary words, names, etc
		* Table has each potential password in both plain and hashed
	* Hackers can get a copy of the password file
		* for each entry in password file, see if password in above table
		* If it is, you have a password: Works on more passwords than you'd think!
* Solution: Use "salt"
	* Random characters added to the password before hashing
	* Salt characers stored "in the clear"
	* INcrease the number of possible hash values for a given password
		* Actual password is "pass"
		*Salt = "aa"-> "passaa"
		Sal = "bb" -> "passbb"
	Result: cracker has to try many more combinations

One time passwords

* Often useful to have passwords that cannot be reused
	* User has list of passwords to use
	* Each password is invalid after being used once
* Often implemented using one way hash chain
	* Password n is calculated by doing f^n(s), where is is a secret and f is a one-way function
		* Hash s a total of n times for password n
	* Easy to calculate prev used passwordds
	* Difficult to caclc the next password in the list
* Server is initialized with the list of passwords (or just n)
* On each login, server passes n to the client, which hashes the password n times and returns the answer
	* Since n is decremented each time, attacker can't compute next password
	* Need to reinitialize after n password uses

Auth using physical object

* Magnetic card
	* Stores a password encoded in the magnetic strip
	* Allows for longer, harder to memorize passwords
* Smart card
	* Card has secret encoded on it, but not externally readable
	* Remote computer issues challenge to the smart card
	* Smart card computes the response and proves it knows the secret

Two factor auth

* Additional "password" using a hardware token
	* May also use a software program running ona smartphone
* Server and token share a (long) secret
	* Generated by server and readinto toekn
	* Generated by user and given to server
* Token computers a function of secret and current time
	* Display s the result - user enters it on web site after password verified

Authentication using biometrics

* Use basic body properties

CounterMessures

* Limiting times when someone can log in
* Automatic callback at number prespecified
	* Can be hard to use unless there's a modem involved
* Limited numberof login tries
	* Prevents attackers from trying lots of combinations quickly
* A database of all logins
* Simple login name/password as a trap
	* Security peronnel notified when attacker bites
	* Variation allow anyone to "login" but don't let intruders do antyhing usefule

Logic bomb

* Programmer writes complex program
	* Wants to ensure he's treated well
	* Embreds logic "flaws" that are triggered if certain thing saren't done
		* enters a password daily (weekly, whatever)
		* Ads a bit of code to fix things up
		* Provides a bit of code to fix things up
		* provides a certin set of inpu
		* programmers name appears on payroll, really

* Trap Door

* Login spoofing
	* no difference between real and phony login screen

* Buffer overflow

* String format attacks

* Generic security attacks
	* Request memory, disk space, tapes and just read
	* Try illigal sysstem calls
	* Start a login and hit DEL, RUBOUT, or BREAK
	* Try modifying complex os structures
	* Try to do spesified DO NOTs
	* Soecial engineering
		* Convince a system programmer to add a trap door
		* Beg admins secretary (or other people) to hep a poor user who forgot password
		* Pretend you're a tech support and ask random users for their help in debugging a problem



Security in a networked world

* External threat
	* Code transmitted to target machine
	* Code executed there, doing damage
* Goals of virus writer
	* Quickly spreading virus
	* Difficult to detect
	* Hard to get rid of
	* Optional: does something malicious
* Virus embeds itself into other legitimate code to reproduce and do its job
	* Attack its code to another program
	* Additionally, may do harm

Malware

*Program that attemps to cause damage
	* Goal : "infect" the target machine
* Types of damage
	* Denial of service
	* Permanent data damage
	* Espionage
	* Practical joke
	* Blackmail
* Terminology
	* backdoor: allows malware creator to control target machine
	* zomhbie: machine thats been taken over 
	* botnet: collection of zombies

Trojans

* Free program made available to unsuspecting user
	* Actually contains code to do harm
	* May do something useful as well
* Altered version of utility program on victim's computer
	* Trick users into running that program
* Example (getting superuser access on unix.ic?)
	* Place a file called ls in your home directory
		* File creates a shell in /tmp with priv of whoever ran it
		* File then actually runs the real ls
	* Complain to your sysadmin that you can't see any files in your directory
	* Sysadmin runs ls in your directory
	* HOpefully he runs your ls rather than the real one, dpends on his search path

How viruses work

* Virus lang
	* assmebly
	* Macro language: infects email and othe rdocs
		* Runs with email reader/browser programs open messages
		* Program "runs" virus (as attachment) automatically
	* Inserted into another program
		* Use tool called a dropper
		* May also infecgt system code (boo block, etc)
	* Virus dormant until program executed
		* Then infects other programs
		* Eventually executes "payload"

* Rootkits
* Set of code and files that work hard to hide its existence

Defenses

* Defend against attacks using "defense in depth"
	* Multiple layers of secuirrty
	* Breaking a single layer doesn't compromise the system
	* Layers ned to be diverse
* Many diff types of defense
	* Firewalls
	* Virus def
	* Code signing
	* Jails

Design principles

* PUblic, you aren't clever by hiding stuff
* Default to no access
* Check for current authority
* Give each process least priv possible
* Protection mech should be
	* Simple
	* Uniform
	* In lowest layer of system
* Scheme should be psychologically acceptable
* Biggest thing: keeep it simple

Hidning a virus

* Compress program to appropriate size
* 


## INput output

How fast is I/O hardware?

* Keyboard 10bytes/s
* Mouse 100 bytes/s
* 56k modem 7KB/sec
* Printer/scanner 1MB/sec
* USB 1.5/60/625 MB/sec
* Digital camcorder 4MB/sec
* Gigabit ethernet 125 MB/sec
* HDD 125MB/sec
* Flash drive 200MB/sec
* Displayport 81.Gbit/s per lane
*PCIE bus 985 MB/s

Device controllers

* I/O devices have components
	* Mechanical and electric
* Electric component controls device
	* may be able to handle multiple devices
	* May be more than one controller per mech component
* Controller tasks
	* Convert serial bit stream to block of bytes
	* Perform error correction as necessary
	* Make available to main memory

Memory mapped IO

* 3 ways
	* Separate IO and memory
	* Memory mapped IO
		* Dedicate parts of memory to IO
	* Hybrid

How is memory apped IO done?

* Single bus
	* All mem access go over a shared bus
	* IO and RAM accesses compete for bandwidth
* Dual bus
	* RAM access over high speed bus
	* Less competition for bus
	* More handware (more expensive)

* Direct memory access (DMA)
	* CPU Programs the dma controller
	* DMA controller requests transer to memory
	* Data is transferred from disk to mem (skips cpu)
	* ACK
	* Interrupt when done

* Hardware view of interrupt
	* Device finishes
	* Controller issues interrupt
	* CPU acks interrupt

* IO Software goals
	* Device independence
		* Programs can access any io device
		* NO need to specify device in advance
	* Uniform naming
		* Name of a file or device is a string or integer
		* Doesn't dpend on the machine (underlying hardware)
	* Error handling
		* Done as close to the hardware as possible
		* Isolate higher-level software
	* Snchronous vs asynchronous transfer
		* Blocked vs interrupt driven
	* Buffering
		* Data coming off a device cannot be stored in final destination 
	* Sharable vs dedicated devices

Programmed IO

IO Using dma

Lyaers of io

* User soft and lib
* Device ind os code
* Device drivers
* Interrupt handlers
* Hardware

Interrupt handlers

* Best hidden
	* Driver stars IO and blocks
	* Interrupt notifies completion
* Interrupt procedure does its task
	* Then ublocks driver that started it
	* Perform minimal actions at interrupt time
		* Some functionality can be done by driver aftet its ublocked
* Interrupt handler must
	* Save registers not already saved by innterrupt hardware
	* Set up ocntext for interrupt service procedure

What happens on an interrupt

* Set up stack for interrupt service procedure
* Ack interrupt controller, rennable interrupt
* Copy registers from where saved
*RUn service procdure
* Pick new process to run next (opt)

Device drivers

* Device drivers go between device conggtrollers and rest of os
	* Drivers standadize interface to widely varied device
* Device drivers communicate with controller over bus
	* Controlers communcate with device itself

Device independent IO software


* Common lib routines for io software
* Helps drivers maintain a standard appearance to os
* Uniifrm interface for many device drivers for
	* Buffering
	* Error reporting
	* Allocating and releasing dedicated devices
	* Suspending and resuming processes
* Commmon resource pool
	* Device-ind block size
	* Other device driver resources

Why standardize driver interface

* Non standard
	* Diff for each driver
	* HIgh os complex
	* Less code reuse

* Standard
	* Less os/driver interface code
	* Lower os ocmplex
	* Easy to add new drivers

* Buffering deviceinput
	* Unbuffered goes direct to user space
	* Buffering in user space
	* Buffer in kernel copy to user space (safe)
	* Double buffer in kernel

Bandwidth avg flow rate, Latency delay, Jitter variability ini rate

What happens where on an IO requet

* User proc: Make io call; format io; sppoling
* Device ind code: Nameing, protection, blocking/buffering/allocation
* Dev drivers: Manage device registers and status
* Interrupt handler: Signal device driver on comleted io
* Hardware: Actaully do IO in hardware

Disk Drive structure

* Data stored on surfaces
	* Up to two surfaces per platter
	* One or more platters per disk
* Data in concentric tracks
	* Tracks broken into sectors
		* 256-4kb per sector
	* Cylinder: corresponding tracks on all surfaces
* Data read and written by heads
	* Actuator moves heads
	* Heads move in unison

