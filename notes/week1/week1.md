# Week 1 (Jan 4 - 8)

## Monday

Door code is: *8896*

Notable software: VMware, VirtualBox, lldb, dtrace

See [git2.soe.ucsc.edu](https://git2.soe.ucsc.edu/)

## Wednesday

Get a feeling for estimating numbers. E.g. Time to perform disc operation, # of disc operations per second

### Operating System

* Provides useful abstractions
* Standardizes interface to use across different hardware
* Manages resources
	+ Each program gets time and space
* Conflicting goals
	+ Use hardware efficiently
	+ Max performance per user

### Hardware Generations

#### First gen

* One job at a time
	* Enter program (by rewiring)
	* Run it
	* Record result
* Problem: Wasted time
	* Idle during first and last step
	* Very expensive

#### Second gen - Batch System

* Batch system using cards and tape
* Input card -> input tape -> output tape -> printer
	* Allowed expensive machine to be used more efficiently
	* Inexpensive machines produced tapes and printed
* Later used discs

#### Third gen - Multiprogramming

* Multiple jobs in memory
	* Processor switched between them when slow IO was required
* Timesharing
	* Allowed multiple jobs to be active at once

## Friday

### Storage speeds

 Storage Type        Time 
-------------        ------ 
Register             .4 ns
On-chip cache        4 ns
Cache                10 ns
DRAM                 50 ns
Flash                100 micros
Disk                 5 ms
Tape                 50 s

### Disk Drive Structure

* Data stored on surfaces
	* Up to two surfaces per platter
	* One or more platters per disk
* Data in concentric tracks
	* Broken into sectors
		* 256B - 1KB
* Data read by heads moved by actuator

### Flash Memory

* Divided into Erase Blocks
	* Erased before written
	* Erase blocks 256KB - 1MB+
* Written in Pages
	* 64 - 256 pages per erase block
* Flash Translation Layer (FTL)
	* Manages device
	* Makes it look like Disk

### Memory

* Single base/Limit Pair: Set for each process
* Two base/limit registers: One for program, one for Data