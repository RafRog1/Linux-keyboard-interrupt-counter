# Linux Keyboard Interrupt Counter
**Kernel module (key_interrupt_counter)** - Counts keyboard interrupts. Additionally, it stores the time from the interrupts are counted.
**User space aplication (userApp)** - It is for communication with the kernel module. It can: 
 1. display number of interrupts,  
 2. display date from when interrupts are counted, 
 3. reset the interrupt counter.

### Usage
If you don't have Development Environment, install with command:
***apt-get install build-essential linux-headers-$(uname -r)***

In files location:

1. Compile module using ***make*** command
2. Compile userspace app writing ***gcc -o userApp userApp.c***
3. Init kernel module ***insmod key_interrupt_counter.ko***
4. Use app:
	***./userApp -gc*** - to get the counter value,
	***./userApp -gt*** - to get time when counter was reset,
	***./userApp -rc*** - to reset conuter

*Administrator privilages may be required to execute some commands.*
Write ***rmmod key_interrupt_counter*** to disable module.
