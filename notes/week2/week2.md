# Week 2 (Jan 11 - 15)

## Process

* Process - Program in execution
	* Has address space the program can use
	* Has State (registers, including program counter and stack pointer)
* OS tracks processes in process table
* Processes can create other processes
	* Process tree tracks these relationships

*Process = Address Space + Thread of Control*

## Inside a UNIX Process

* Three Segments:
	* Text: contains the program code
	* Data: contains the program data
		* static variables
		* malloc, new
	* stack:
		* Automatic variables
		* Procedure call info
* Address space Growth
	* Text: No growth
	* Data and Stack grow towards each other

## Deadlocks are caused by Circular dependencies

## Interprocess Commmunication

* Processes work to exchange info with eachother
* Many ways
	* Network
	* Pipes

## System Calls

* OS runs in priveledged (supervisor) mode
	* User Processes do not
* Programs want OS to perform service
	* Access a file
	* Create process
* Accomplished with System Calls

## How System Calls Work

* User program enters priveledged mode through well defined entrypoint
* Program passes relevant info into OS
* OS performs service
	* Able to do so
	* Service is permitted for user process

* Example system calls
	* fork
	* waitpid
	* execvp

## Operating System Types

* Monolithic
	* All just a program
		* Any piece has access to other pieces
	* Sometimes Modular
		* Extra pieces dynamically added
		* Extra pieces part of whole
* Layered
	* CPU Supports layers of priveledge
		* Intel supports 4
		* User at outermost layer
	* Use priveledge layers to enforce separation and provide security
		* Outer layers can only move inward at certain gates
	* Not widely used, but a good idea
* Micro-Kernels
	* Bare minimum in kernel
	* Everything else in User-space
	* Inefficient

## Scheduling

* How are processes scheduled?
	* When they enter system
		* Batch Systems
			*Two types
				* New job runs scheduler
				* Scheduling done when job voluntarily gives up time
	* Fixed interval scheduling
		* Necessary for interactive systems

* Goals of Scheduling
	* Fairness: Fair chance at CPU
	* Enforcement: Ensure policy is carried out
	* Balance: Keep all parts of system busy
	* Batch
		* Throughput
		* Turnaround time
		* CPU utilization
	* Interactive
		* Response time
		* Proportionality: meet user expectations
	* Real time
		* meet deadlines
		* predictability 
	