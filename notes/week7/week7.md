# Week 7

## Cybersecurity

Moxie marlin spike

Security threats

* Goal: Data Confidentiality
	* Threat: Exposure of data
	* Solution: Cryptography
* Goal: Data integrity
	* Threat: Tampering with data
	* Solution: Crypto
* Goal: System availability
	* Threat: Denial of service

Authentication - Proving you are who you say you are

* Something you know, have, or are
	* Know a password, have a key, are a person witha  specific fingerprint

## Modern Crypto

* AES
* Attacking AES
	* Infinite fast compupter
	* How much energy take to break AES?
	* Landauer limit: MIn energy to create or destroy bit
		* E > kT * ln2
			* k= 1.38 * 10^-23
			* T = 293
	* 128 bit AES would require all the electric powerof the USA for more than a year
	* 192 bit AES would require 1000 times anual solar flux
	* 256 bit AES would require a billion supernovae

* Attacking RSA
	* If we began at beginning of universe using all computers in the world and the best algorithm
		* We still would not have done it

* How to atack modern crypto?
	* Drugs and wrench
	* You cheat
	* Get extra info to bypass mathematics


When you can't win by playing by  the rules, you change the rules

* Lie cheat
* Look for mistakes
* Bad assumptions
* Weak spots
	* Often the human at the computer

## Security Cont

* What kinds of intruders?
	* Casual prying by non-technical users
		* Curiosity
	* Snooping by insiders
		* Curiosity or money
	* Determined attempt to make more money
		* May not even be an insider
	* Determined attempt to make mischief
		* Money typically not goal
		* Inconvenience or to prove a point
	* Commercial or military espionage
		* This is a big businenss!

* Accidents cause problems too
	* Acts of god
	* Hardware/software errors

*Protection
	* Security is about mechanism
		* How to enforce policies
		* Plicies largely independentof mech
	* Protection about specifying policies
		* How to decide who can access what
	* Specifications must be
		* Correct, efficient, easy to use

*Protection domains
	* Three protection domains
		* Each lists objects with permitted ops
	* Domains can share objects and permissions
		* Objects can have different permissions in different domains
		* There need be no overlap between object permissions in different domains
	* How can this arrangement be specified more formally?

* Protection matrix
	* Each domain is a row in the matrix
	* Each object has a column in the matrix
	* Entry for <object, column> has the permissions
	* Who's allowed to modify protection matrix
		* What changes can theymake?
	* Specify permitted operationson domains iin the matrix
	* Doing this allows flexibility in specifying domain permissions

* represent protection matrix
	* Need to find efficient rep
	* Most entries empty
	* Compress by:
		* Associate permissions with each object: access control list
		* Permissions with each domain: 

* Access control list
	* Each object has list attached
	* List has
		* Username
		* Group
		* Other
	* Access rights
		* r/w/e/others?
	* No entry for domain_> no rights for that domain
	* Operating system checks permissions when access is needed

*Access control lists in rela life
	* Unix file system
		* User group others
		* Include read write execute
		* Users may be in more than one gropu
	* AAFS (unix.ic)
		* Access lists only apply to directories: files inherit rights from the directory they're in
		* Access list may have many entriess on it with possible rights:
			* read/write/lock for files
			*lookup/insert/delete for directories
			*administer: ability to add or remove permissions

*Capability
	* Each process has a capability list
	* List has one entry per object the process can access
		* OBject name
		* OBject permissions
	* Objects are listed are not accessable
	* How are these secured?
		* Kept in kernel
		* Cryptographically secured

* Crypto protected capability
	* Rights include generics (read wrteii exec) and
		* copy capability
		* copy object
		* remove capability
		* Destroy object
	* Server has a secret (Check) and uses it to verify capablities presented to itf
		* Alt: Use public key sig techniques

* Protecting access matrix: sum
	* OS must ensure matrix isn't modified or accessed in unauthorized way
	* Access control list
		* Reading or modifying ACL is a system call
		* OS makes sure desired op is allowed
	* Capability list
		* Can be handled the same way as ACLs: reading andmodificationdone by OS
		* Can be handed to prcs and verified cryptographicaly later
		* May be better for widely distributed systems where capabilities can't be centrally checked

* Bell-La Padula ultilevel security model
	* Processes objects have security level
	* Simple security property
		* Process at level k can only read objects level k or lower

*Biba integrity model
	* Guarantee data integrity
	* Simple intregrity principle
		* A proc can write only objects at its security level or lower
		* No way to plant fake info at a higher level
	* The integrity * property
		* A proc can only read objects at its sec level or higher
		* Prevet someone from getting info from above and planting it at hteir level
	* Biba is in direct conflict with bella padula

* Covert channels
	* Circumvent security mode by using more suble ways of passing info
	* Can't directly send data against system's wishes
	* Send data using "side effects"
		* Allocating resources
		* USing the CPU
		* Locking a file
		* Makeing small changes in legal data exchange
	* Very difficult ot plug leaks in covert channels

* Steganography
	* Hide data in other data
	*Hide shakespear plays in picture of zebras

* Cryptography
	* Goal: Keep info form those not supposed to see it
		* Scramble data
	* Use a well known algorithm to do the scrambling
		* Algorithm has two inputs: data and key
		* Key is known only to authorized users
		* Relying upon the secrecey of the algorithm is a very bad idea (see WW2 Enigma for an example)
	* Cracking codes is difficult, Sneakers and Swordfish (and other movies) notwithstanding
