# Week 10

* Use links

* Keep reference count to files
	* When reach 0, file disappears

* Sym links are just strings pointing to stuff

* Log-structured filesystems
* Trends in disk and memory
	* Faster CPUs
	* Larger memeories
* Result
	* More mem-> disk caches can also be larger
	* INcreasing number of read requests can come from cache
	* Thus, most disk accesses willbe writes
* LFS strcutres entiredisk as a log
	* All writes initially buffered in memory
	* Periodically write these to end of the disk log
	* whwn the file opened, locate i-node, thenfind blocks
* Issue: what happpens when blocks are deleted?

* Log structured file system
* Divide into segments
	* Write data sequenttially to segment
	* Read data from wherever it's stored
* Periodically "clean" segments
	* Go through a segment and copy live data to a new locatoin
	* MArkt he segment as free

* Disk quotas
* Quaotas limit users' allocation
	* Space might be rented
	* Protect the system from rogue programs allocating space
* Hard limits may not be exceeded
* Soft limits generate warnings
	* Number of warnings may be lmited
	* Generate too many warnings -> treat as hard limit

* Backing up a file system
* Goa; Create an etra copy of each file in the file system
	* Protect against disk failure
	* Protect against human error
	* Allow the system to track changes over time
* Two basic types of abckups
	* Full backup: make a copy of every file in the system
	* INcremental backup: only make a copy of files that have changed since the last backup
		* Faster
		* Smaller
* Incremental backups typically reuiqre a full backup as a "base"

*Backup mechanics
* Actually copy blocks from one system to another
* Snapshot
	* New data doesn't overwrite olddata
	* Easy to recover deleted files
	* Fast
	* Not as helpful for failed devices or corrupted fs
	* Snapshots can be done with hard links

*Finding files to back up
* walk the file system tree
	* Slow
	* Works on any fs
* Scan the list of inodes looking for modified files
	* Faster (seq access)
	* FS-specific code (may require raw disk access)
* Keep a log of changes the fs make
	* Can be very fast
	* Requires help from the fs

* Checking a file system for ocnsitency
	* Build "in use" map by traversing all file inodes
		* Add 1 to blockentry if mentioned in block list
	* Free map built from free list (or just use free block bitmap if it exists)

* Fixing inconsistencies
	* IF a file system check reveals inconsistentis
* BLock marked netiehr freenor in use: mark free
	* NO file using, so free
* BLock marked both free and in use: mark in use
	* Best give it tot the file that's using it
* BLock marked free more than once: Mark free
	* Ensure only in free list once
* BLock in use in two files: ask user?
	* Difficult to decide what to do in this case
	* Consistency checking is designed to avoid having this happen: other cases are easy to ahdnle
* This is reasoning behind ordered updates of data and metadata

File system cache

* Many files are used repeatedly
	* OPtion read each time frmo disk
	* Better: keep a copy in mem
* File sysem cache
	* Set of recently used file blocks
	* Keep blocks just referenced
	* Throw out old, unused blocks
		* Same kindsof algorithms as for virtual mem
		* MOre effort per ref is OK: File refs are a lot less freq than mem ref
* Goal: Eliminate as many disk accesses as possible
	* Repeated reads and writes
	* Files deleted before they're ever written to disk

Managing the file ache: reads

* Update block lists on every read and write
	* Affordable: update is fast even compared to read of cached data
	* Evict blocks from cache using LUR, LFU, aging or other VM-like algorithms
* Readahead: fetch blocks that might be needed soon
	* Example: read block n+1 after reading block n of a file
	* May be very inedpesnvei: disk controller has the block in its own cache
	* Particularly helpful if file is accessed sequentially: keep track of sequantialitiy to decide whther to read ahead
	* Not very detrimental if the os guesses wrong; only waste a bit of disk bandiwdth and often no seek

* Managing file cache: writes
* Buffer writes in cache
* Periodifically write dirty blocks
	* 30 secondsor so
* Benefits
	* Multiple writes to a single file block are calesced
	* File that are created and deleted quickly are never written to disk!
* Cache can be flushed manually if needed
* Issue: should disk blocks be allocated on write to cache or on write to disk

Inodes near start of disk (old)

Disk divided into cylinder groups each with own inodes

Defraggmenting disks

* Files on disk are stored where there's space
* Ona ful disk files can be fragmented: stored non-contiguoisly
	* Older disks can have lots of fragmented files
* Solution: defragment the disk
	* Collect blocks of each file together and store them contiguously
	* Some files systems do this automatically

* Ext2 and Ext3: th elinux filesystem
* Ext2/3 were the standard linux file system
	* Similar to bsds fast file system ffs
* Ext3 has journaling
* Ext2/3 designed to be
	* Flexible across range of workloads
	* Realatively simple toimplement
	* Relieable
	* USable across a wide range of file system sizes from hundreds of megabytes to terabytes
* Basic design hasn't changed much in 20 years!
	* Ext4 now in use


large scale structure in ext3

* Disk broken into x block groups
* Each block group is a mostly self contained unit
	* Files can span block groupos, but doesn'thappen often
	* most info is local to the block group
* Bitmaps must fit into a single file system block limiting the number of data blocks
* Copies of the superblock and group descirptors are stored in every block group for reliability

* Superbock
* Info about fs as a whole
	* File block size and num blocks
	* Frag size and num frags
	* Num m blocks/frags/inodes / group
* Updated when the fs is modified
	* Free blokc and free inode counters
	* Time of lasat mount and write
* Superblock cached in mem, updated on disk freq
* DSuperblock copy kepti n each block group
	* Guards against loss of the superblock to disk corrutipn
	* Makes it more conventient to write out a copy in the nearest locatoin

* Group descriptor
* ONe for each group
* Block numbers for
	* BLockbitmap
	*inode bitmap
	* First inode table block
* Counts 9limited to 16 bit ints
	* Free blocks in the group
	* Free inodes in group
	* Directories

* More on block groups
* LImited to maximum of block_zise * 8 blocks
	* Max size (8kb blocks) is 512 meg

Know linux inode

* Inode contents
* Inode contains files metadata
	* Ownership and permissions
	* Time stamps
	* BLock pointers
* INodesstored in the inode region in the block group
	* Inode number maps a particular gropu/offset for theinode
* Soft link stored in inode if possible (using block pointers0)
* File "hole" missing blocks in the middle of a large file

More on unix ffs and linux ext3

* First few block pointers kept in inode
	* Small files have no oeverhead for index blocks
	* Reading and writing small files very fast
* Indirect sstructures only allocated if needed
* For 4KB blocks max files sizes are:
	* 48KB in dir (usually 12 dir blocks)
	* 1024* 4k = 4M of additional file data for single ind
	* 1024 * 1024 * 4 = 4G double
	* 1024 * 1024 * 1024 * 4 4TB for triple
* Max of 5 acces for any file block on disk
	* 1 accessto read inode and 1 to read file block
	* Maximum 3 accesstoindex blocks
	* USually much fewer 1-2 because inode in mem

* LInux dirs
* Linux supports
	* Plailn text dirs
	* Hashed dirs
	* Plain text morecommon,but slower
* Dirs just like reg files
* Name length limited to 255 bytes
* Hashed dirs
	* USe extendible hasing to make lookup faster
	* May be "sparse"

* * * Polyphase merge sort

* Major isue: consistency
* Creating a file can require 5 disk writes
	* a crash in the middle can leave the file system in an inconsistent state
	* Example: inode allocate, but not inserted into directory
* This is unacceptable!
* Solution : use journaling, as provided in ext3
* Problem what do you journal
	* Metadata and data?
	* Metadata only?
		* This introduces an orderin gcontraint
		* Dta must be written before metadata is written

Journaling in ext3
* Uses a journal to record ops before they are written to disk
* Three journaling mode
	* Journal record everythingn to journal
		* Slowest
		* Records data and metadata as soon as they're written
	* Ordered: record only metadata but order data and metadata writes so there's no inconsist
		* Faster less safe: Metadata updates not ocmmit immediately
		* Defaultmode for ext3
	* Metadata only 
		*Not as safe as other two
		* Fastest of 3

* Ext3 journal details
* Log records: Basic entry in journal
	* One per disk req
	* Span of bytes, or entire block
* Atomic operation handle: used to group log records toegehr
	* Typically one handle corresponds toa single system call
	* Ensures that high level operatin either completes r never happens
* Transaction: consists of multiple atomic ops
	* Done for efficiency reasons
	* Entire transaction written at once
	* Only one transaction "open"  at any time

Freebsd vs ext3

* CD-ROm
* Fiel catalog in first few blocks of disk
	* List all files on the CD
	* HIerachical structure can be built by trating files as directories
* Files all allocated contiguiously
	* No need to handle overwrites
* Current standard (UDF) is a superset of this

* MS-DOS file system
* Originally designed for floppy disks
* Originally designed for small hard drives
* Commmonly used for thumb drives and sd cards

* Single list of blocks in used
	* Fixed overhead per block
	* easy to find all blocks in a file
* Root directory file starts in block 0
	* Other files have first block number in directory entry

* FAT does not have inodes

Zetttabyte file system (ZFS)

* Designed to handle very large disk partitions
* Extensive error checking and recovery
	* Checksumson individual blocks
	* RAID at the file level (RADIZ)

* Never overwrites data in place; no chance of inconsistency
	* Write new blocks to disk in previously free blocks
	* Writea new uberblock to ref the new file system state
		* Transistion from one consistent state to another is done with a single block write
* Some properities similar to log strcture fs
	* No overwriting in place
	* Needs clearning
	* But can write anywhere ondisk, no need for segments
* COmpleicated

Virtual file system switch

* How can os handle multiple file systems
* Much code is common between them
* Solution virtual file system vfs switch
	* Abstracts out common functionality

Laying file systems

* Often useful to layer one file system on top of another one
