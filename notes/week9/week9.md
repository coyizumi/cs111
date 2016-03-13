# Week 9

* Structure of disk sector
	* Preamble contains info about the sector
		* Sectornum and location inf
	* Data is usually 512 or 1024 bytes
	* ECC (Error cocrrection code) used to detect and correct minor errors in the data

* Sector layout on disk
* Sectors numbered sequentially on each track
* Numbering starts in idfferent poaolce on each trakc
	* Allows tiem for switching head from track to track
	* Done to minimize delay in seq transfers
* Zoning
	* Diff zones have diff number of sectors per track
	* OUter zones ahve higher transfer rate
	* Typically 8-30 zones
	* Zones set at manufacture time

* Disk addresssing
	* Millions of sectors on the disk must be labeled
	* Two poss
		* Cylinder/track/sector
		* Sequentail numbering
	* Modern drives use seq numberrs
		* Disks map sequential numbers into specific location
		* Mapping may be modified by the disk
			* Remap bad sectors
			* OPtimize perfomrance
		* Hide the exact geometry, making life simpler for the OS

When good disks go bad
	
* Disks have defects
	* With billions of sectors, not surprising
* Ecc helsp but sometimes isn't enough
* Disks keep spare sectors normally unused and remap bad sectors into these spares
	* If theres' time, the whoel track couldbe reordered
* All is transparent to user (and typicaly OS)

Building a better "disk"

* Problem: CPU performance has been increasing exponentially, but disk perf hasn't
	* LImited by mechanics
* Prob: Disks aren't all that reliabel
* Solution: Dist data across disks, and use some of the space to improve reliability
	* Data transferred in paralel
	* Data stored across drives (striping)
* Problem: more disks means lesss reiliablity
	* Gen and store info to allow data from a failed disk to be recovered

D0 XOR D1 XOR D2 = P

D2 dies

X0 XOR D1 XOR P = D2

* Calculating parity
* Goal: Keep extra info to reover from device failure
* Use the extra info to rebuild the data on the missing device
	* There are formulas to recover from more than one faiilure with additional "parity" drives

* Raid 0 just stripe
* Raid 1 mirrored copies
* Raidi 4 striped with parity
* Raid 5 parity rotates through disks

* CD/DVD-ROM recording
* DVD has data in a sprial
	* Hard drives have concentric circles of data
* ONe continuous track: just like vinyl records!
	* Starts from center
* PIts and lands "simulated" with heat-sensitive material on DVD-Rs and -RWs

What's in a disk requrest?

* TIme required to read or wtire dtermined by 3 factors
	* Seektime
		* Typically 2-8ms, depending on dist
		* Longer seeks take longer, but not linear with dist
	* Rotational delay
		* Avg delay = 1/2 rotation time
		* Ex: rotate in 10 ms, avg rotation delay = 5ms
	* Actual transfer time
		* Transfer time= time to rotate over sector
		* Ex: Rotate in 10 ms, 1000 sectors/track -> 10/1000ms = 0.01ms (10 microseconds) transfer time per sector
* Seek time and rotation time comparable
* Eror checking done by ondisk controller

Disk request scheduling

* Goal: Use disk hardware efifcinetly
	* Highest bandwidth
	* Disk ransferring as often as possible (not seeking)
* We want to
	* Minimize seek time (moving track to track)
	* Minimize rotational latency (waiting for disk to rotate the desired sector under the read/write head)
* Calculate disk bandwidth by
	* Total bytes transferred/time to service request
	* Seek time and rotational latency are overhead(no data is transferred) and reduce disk bandwidth
* Minimize seek time and rotational latency by
	* Using algorithms to find a good sequence for servicing requests
	* Placing blocks of a given file "near" each other

Disk scheduling algorithms

* Schedule disk requests to minimize disk seektime
	* Seek tie increases as distance increases though not linearly
	* Mnimize seek dist -> minimize seek time
* Disk seek algorithm examples assume a request queueu and blah

First come first served

* Serviced in order they arrive
	* Easy but may have unnecessary distance

* Shortest seek time first
	* Service with shortest seek time from current position
		* Form of SJF sched
		* May starve some requests
		* OPtimal but may starve

* SCAN elevator
	* Disk arm starts at one end of the disk and moves toward the other end, servicing request as it goes
		* Reveres direction when it gets to end of disk
		* Also known as elevator algorithm

* C-SCAN
	* Identical to SCA, except head reutnrs to cylinder 0 when it reaches end of the disk
		* Treats clinder list as a circular list that wraps around the disk
		* Waiting time is more uniform for cylidnerings near edge of the disk
	* Reduces the variance

* C-LOOK
	* CSCAN, excecpt only travels as far as last request in each direction
		* Saves seek time from last sector to end of disk

* Picking a disk scheduling algorithm
	* SSTF is easy to impl and works OK if not toomany requests (optimal) Not fair
	* SCAN works better under heavy loads
		* More fair
		* Use look rather than scan to save time
	* Long seeks aren't too expensive so choose C-LOOk over LOOk to make response time more even
	* Disk request scheduling interacts with algorithms for allocating blocks tofiles
		* Make scheduling algorithm modular: allow it to be changed without chaning the file system
	* Use SSTF or FCFS for lightly loaded systems
	* Use C-LOOk for heavily loaded systems

* Flash mem and ssds
* Compared to disk
	* Faster
	* Expensive
	* MOre reliable devices
	* Less reliable sectors
* COmpared ot DRAM
	* Cheaper
	* Non-volatile
	* Slower
* Use flash as a lvel between disk and mem?
* Issues can't overwite sectors "in place"
* Flash wears out; can only write 3000-100000 times per memory cell

Writing to flash

* Can't overwirte pages in place
	* Needto write toclean region
	* Unit of erase is erase block
* One sol: Copy entire erase block to new location
	* MOdify the page being written
* This isn't efficient!
	* Flash vendors spend a lot of time on flash translation layers
	* FTLs map logical page numbers to physical pages
	* Also manage wear leveling: distribute erases among blocks

Better way to manage?

* Log structured
	* Append updates to log
* Periodically "clean" structures
	* Reqrite live data to a new log segment
	* Obsolete data ins't rewritten

* Handling in OS
	* Treat it like disk?
		* Flash is written in blocks likedisk
			* Blocks have to be erased first, somewhat slow
		* Random access like disk
		* Often used!
	* Need to be careful about wearing out
		* Most flash devices do "wear leveljing" : remap internally when they're erased
		* File systems for flahs hsould take wear into account
			* Many don't, including vfat

Clock Hardware

* Crystal oscillator with fixed freq (only when comp on)
	* Typically used to time short intervals (~1 sec)
	* May be used to correct time of day clock
* Time of day clock runs when system is off
	* Keeps minutes hours days
	* May not be too accurate
	* Used to load sysstem clock as startup
* Time kep in seconds and ticks
	* Number of seconds since particular time
		* Jan 1 1970
	* Number of ticks this second
	* Advance ticks once per clock interrupt
	* Advance seconds when ticks overflow

* Check time via the web
	* ntp
* What happens when system clock is slow
	* Advance clock to the correct time
	* May be done all at once or over a minute or two
* What happens when system clock is fas?
	* can't have time run backwards!
	* Instead advance time more slowly than normal until the clock is correct
* Track clock drift, do periodic update to keep clock accurate

* Using timers in software
	* No probs if inter freq low
	* May have multiple timers using a single clock chip
* Short interval clock for timer interrupts
	* Specified by aps
* Use soft timers to avoid interrupts
	* Kernel chekc for soft timer expiration ebfore it exits to user mode
	* Less accurate than usinga hardware timer
	* How well this works depends on rate of kernel entries

Time of day clock in CPU

Register, put number in it. Hardware, subtracts 1 from that number  at certain freq. When reg reaches 0 an interrupt happens.

Suppose 10kz reg decrements, 16 bit, 65535. Put 10,000 in register. Every second get an interrupt. Bam, time of day clock.

Where does power go?

* How much power does each part of a laptop computer use?
	* Dispaly biggeetst
	* Chipset inc memory is next
* Save power by
	* Reduce bright
	* Slow CPU
	* Using less of CPU
	* Using an alt GPU
	* Powering down hddd
	* Using flash based drive

* Reduce CPU power
* Turn down voltage/freq
* Run at full clock
	* Finish quicly
	* High energy cons
	* 50-75 watts!
* Cutting volt by two
	* Cut clock speed by two: procs take longer
	* Cuts power by four
	* Cuts energy consumption in half

* How can we reduce power usage?
* Tell progs to use less energy
	* May mean poorer user exp
	* akes batts last longer
* Examples
	* Dim
	* Switch to lower power proc modes
	* Fewer image updates per second (one reason why kindle so power efficient)
	* Use application specific chips (Apple M7/8 for motion cap)

## FileSystems

Nullfs, use sed to replace all variables to cryptofs

Make program asking for passphrase, sha1 it, take middle 128 of those, there's key.

Run program to set key ^

* Files
* Directories and naming
* File system  imp
* Example file systems

* Why important?

* Long term storage
	* Must store large amounts of data
	* Stored nifo must surveive the termination of the proc using it
		* LIfetime seconds -> years
		* Must have soee way of finding it
	* Muliple proces must be able to access info concurrenctly

* Naming
	* Important to find files
	* Every file at least one name
	* Can be
		* Human-accesilbe "foo.c" "my_photo"
		* Mahcine usable: 1138, 812381
	* Case may or may not matter
		* Depends on fs
	* Name may include info about the file's contents
		* Certainly does for the user (name should make it easy to figure out what's in it)
		* May use parts to determine file type

* Typical file extensions
	* .txt, .c, .jpg, etc...

* File structures
	* Sequence of bytes
		* Used by unix
	* Seq of records
	* Tree

INternal file strucutre

Executatble

* Header
	* Magic number
		* #!
	* Text size
	* Data size
	* BSS size
	* Symbol table size
	* Entry point
	* Flags
* Text
* Data
* Relocation bits
* Symbol table

Archive file

* Header
	* Module name
	* Dtae
	* Owner
	* Protection
	* Size
* Object module
* Header
* OBject module
* etc

Accessing files

* Seq
	* Read all bytes from beginning
	* cannot jump
		* May rewind
	* Convenient when tape or disk
	* Useful when whole file is needed
* Random access
	* Bytes or records read in any order
	* Essential for database systems
	* Read can be
		* MOve file marker (seek) then read
		* Read then move file marker

File attributes

* Some files have protection, password, etc

* File ops
	* Read create write open close write appepdn seek get attr set attr rename add name

* Memory mapped files
* Seqmented process before mampping files into its address space
* Process after mapping
	* Existing file abc into one segment
	* Creating new segment for xyz
* Conventient abstraction
	* Example, string search can be done with just mem
	* Let os do the buffering (r&w) in virtual mem system
* Some issues
	* HOw long is the file
	* easy if read only
	* Difficult if writes allowe what if write past

Directories

* Naming is nice but limited
* Group for conven
* File system allow this to be done with dir
* Grouping makes it easier
	* Find files in the first place: remember the enclosing directories for the file
	* Locate related files (Or determine which are related)

Single level dir systems

* One dir in the file system
* Ex directories
	* Contains 4 files 
	* Owned by 3 people
* Prob what if b wants to create file with same name as A'sfile

Two level dir
	
* Solves naming prob: eash user has own dir
* Mult users cna use the same file name
* By defautl users acces files in their own dir
* Ext: Allow suers to acces filesin others dirs

* Hierarchical dir system

* Unix dir tree

* OPs on directories
	* Create delete open close readdir rename link unlink



## File system implementation issues

* How are disks divivded up into file systems?
* How does the file system allocate blocks to files
* How does the file sysstem manage free space
* How are directories handled?
* How can the file system improve
	* Perf
	* Reliability

* Carving up the disk
	* Disks have partitions, partition table, masterboot record
* Partition
	* Boot block
	* Super block
	* Free space managemen
	* INdex nodes
	* Files and directories

* Contiguoous allocation for file blocks
* COnfious allocation requires all blocks of a file to be consecutive on disk
* Prob: deleting files leaves holes
	* Similar tomemory allocation sisues
	* compacting disk can be very slow procedure
* CDs and DVDs use contiguous allocation
* Data in each file is sstored in consecutive blocks on disk
* Simple and efficient indexing
	* Strating location (block #) on disk
	* Length of file in blocks
* Random access well-supported
* Difficult to grow files
	* Must pre-allocate all neded space
	* Wasteful of storage if file isnt' using all of thespace
* Logical to physical mapping is easy
	* `blocknum= (pos / 1024) + start;`
	* `offset_in_block = pos % 1024`

* LInked allocation
* File is a linekd list of disk blocks
	* BLocks may be scattered around the disk drive
	* Block contains both pointer to next block and data
	* Files may be as long as needed
* New blocks are allocated as needed
	* Linked into list of the blocks in file
	* Removedfrom list (bitmap) of free blocks

* finding blocks with linked allocation
* Directory strucutre is simple
	* Starting address jlooedk up from directory
	* Dreictory only keeps track of first block
* No wasted space - all blocks can be used
* Random access is difficult; must alwasy starte at first block
* Logical to physical mapping is done by
	
	block = start;
	offset_in_block = pos %1020;
	for (j = 0; j < pos / 1020; j++) {
		block = block->next;
	}

* Assumes that next pointer is stored at end of block
* May require a long time for seek to random location in file

* Linked allocation using a table in RAM
* LInks on disk are slow
* Keep linkedlist in memory
* Advantages
	* Faster
	* Disk blocks aren't an odd size
* Disadvantages
	* Have to read it from disk at some point (startup?)
	* Have to keep in-memory and on-disk copy consistent

* Using a block index for allocation
* Store file block addresses in an array
	* Array itself is stored ona disk block
	* DIrectory has a pointer to this disk block
	* Non-existne blocks indicated by -1
* random access easy
* LImit on file size?
* Array for each file

* Finding blocks with index allocation
* Need location of index table: look up in directory
* Random and seq access both easy: look up block num in index table
* Space utilization is good
	* No wasted disk blocks (allocate individ)
	* files can grow and shrink easy
	* Overhead of single disk block per file
* Logical to phys mapping is easy
* Limited file size: 256 pointers per index block, 1kb per file block -> 256KB per file limit


*Two level indexed allocation
* Allow larger files by creating an index of index blocks
	* File size stilil limited, ut much larger
	* Limit for 1kb blocks = 1KB * 256 * 256 = 2^26 bytes = 64MB

* Can be extended to more than 2 levels if larger files are needed
* Variation used in linux/freebsd

* BLock allocation with extents
* Reduce space consumed by index pointers
	* Often consecutive blocks in file are sequential on disk
	* Store <block,count> instead of just block in index
	* At each level, keep total count for the index for efficiency
* Lookup procedure is:
	* Find correct index block by checking the starting file ofset for each index block
	* Find correct (bloc,count) entry by running through index bloc, keeping tack of how far into file the entry is
	* Find correct block in <bloc,count) pair
* More efficient if file blocks tend to be consecutive on disk
	* Allocating blocks likethis allows faster reads and writes
	* Lookup is somewhatmore complex

* Managing free space: bit vector
* Keep a bit vector, with one tentyr per file block
	* Number bits from 0 through n-1, there n is the number of blocks available for files on the disk
	* if bit[j] == 0, block j is free
	* if bit[j] == 1, block j is in use by a file (for data or index)
* Search for free blocks by looking for words with bits unset
* Easy to find consecutive blocks for a single file
* Bit map must be stored on disk and consumes space
	* Assume 4kb, 256gb disk -> 64M blocks
	* 64M bits = 2^26= 2^23 bytes = 8MB overhead

* Managing free space linked list
* LIst of free blocks
	* Simlar to for file alloc
	* NO wasted space for bitmap
	* NO need for random access unless we want to find consec blocks for a single file
* Difficult to know how many blocks are free unless it's tracked elsewhere in system
* Difficult to group nearby blocks together if they're freed at different times
	* Less efficent allocation of blocks to files
	* Files read and written more because consecutive blocks not nearby


* Issues with free space management
* OS must protcet data structures used for free space management
* OS keep in-mem and in-disk consistent
	* Updaate free list when block is removed; change a pionter in the prev block in the free list
	* Update bit map when block is allocated
		* Caution: on=disk map must never indicate that a block is free hwen it's part of a file
		* Solution: set bit[j] in free map to 1 on disk before using block[j] in a file and setting bit[j] to 1 in memory
		* New prob: OS crash may leave bit[j] == 1 when block ins't actually used in a file
		* New sol: OS checks file system when it boots up
	* Manging free space is a big source of slowdown in file systems

Big or small file blocks??

* Larger blocks are
	* Faster: More data per seek
	* Less efficeint: waste space

* What's in a directory
* Two tpes of info
	* File names
	* File metadata
* Basic choices for dir info
	* Store all info in dir
		* FIxed size entries
		* Disk addresses anttributes in dir entry
	* Store names and pointers to index nodes (inodes)
	* Inodes detach cahnges to attributes from changes to directory system


* Directory strucutre
* Structure
	* LInear list of files (often itself stored in a file)
		* Simpleto program
		* Slow to run
		* Increase in speed by keeping it sorted (insertions are slower!)
	* Hash table: name hashed and looked up in file
		* Decrease search time
		* May be difficult to expand
		* Can reulst in collisions (two files hash to same location
	* Tree
		* Fast for searching
		* Easy to expand
		* Difficult to do in on-disk dir
* Name length
	* Fixed: easy to prog
	* Variable: more flxible, better for users








