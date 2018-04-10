# O5

## Build
run **./build.sh**

## Run
run **./run.sh**

## Add File to File System
in filesystem folder, create the files you want to add to the file system(up to 10 files) the run the flowing command:
 **./fsg.exe [file to add] [name on file system]...**
 then run **./build.sh**
 

## Create Executable
create an assembly file and compile using:
**nasm -f bin filename.asm -o e.filename**
the binary file name must start with "e." to indicate it's an executable. 
the assembly must be compiled to 32 bit binary so you need to add "**bits 32**" at the head of the assembly file.

## Print
to print you must use "**int 31**".
**example:**

    bits 32
    start:
	    move eax, [esp+4] ; the argument passed to the program is the address of the program
	    add eax, string-start ; get strings relative offset and using that and the program address, get the absolute offset
	    mov ebx, eax
	    int 31 
	    ret
	string db "hello world", 0
    



 
