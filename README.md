﻿# Cxy #

Official Cxy interpreter and compiler.

Version numbering not applied.

## About ##

Cxy is an interpreted; as well as compiled, imperative-declarative, non-functional procedural recursive programming language.  
The language is a translator of a piece of text. This text could also be itself. Thereby, Cxy can define a higher level of itself. Cxy can also define a new language by translating small units of change in another language into that language.  

Not implemented:
What if we wanted to have a folder with tonnes of small statements. Instead of having to manually add each statement to a switch and .hpp file, we could put all these little files into a single folder which is read by cxy. For each file, cxy can copy the necessary information into header files and makefiles.
The best example of this is the compiler/interpreter itself. There are quite a few small assembly-like mnemonic statements all in the src/File folder. 

Implemented:
An example of changing some language-related parameters:

	std::function<void(std::shared_ptr<Base>)> func([](std::shared_ptr<Base> x){/*statements*/});
	add_object(std::make_shared<Derived>()); // uses func on each object

In some cases, it may be hard or impossible to make the compiler deduce how to case the Derived class into the Base class.  
One could therefore let add_object be a template function. By reading what type we put in, we can add the string "\<Derived\>" 
right after the "add_object" string. Thus, we have solved a problem. 




# Quick Overview #

## Language ##

### Hello World ###

Tier 0 Cxy is an assembly-like language.
Data in Tier 0 is put into a tree of stacks.
Data can be accessed by simply using the stack's name in an operation.
Here's Hello World:

	#cxy start

	push ax
	cpy ax "Hello World"
	show ax
	pop ax

	#cxy stop

push ax: creates a new element on the "ax" stack.  
cpy ax "Hello World": copies the string after ax into the ax register.  
show ax: prints the contents of ax to stdout.  
pop ax: removes the top of the stack of ax.  

### Reference ###

In this reference, I will briefly discuss the language syntax, then explain what a register is, as well as the standard registers. After that, instructions will be explained.  

#### Language Syntax ####

The syntax of cxy is defined by space-separated tokens. A single token can contain spaces if it is enclosed by quotation marks "".  

#### Registers ####

A register is simply a stack with a name. We always work on the top of the register.
We can put numeric or string data in a register. A register is operated upon by instructions.

The standard registers:
"register_name" : <explanation>

"cnt" : Integer register containing the result of the cnt instruction.  
"eq" : Boolean register containing the result of the eq instruction.  
"neq" : Boolean register containing the result of the neq instruction.  
"lt" : Boolean register containing the result of the lt instruction.  
"st" : Boolean register containing the result of the st instruction.  


"ptr" : Integer register containing the position of the text pointer.  
"mrk" : Integer register containing the position of the text marker.

"size" : Integer register containing the size returned by the size instruction.  
"next" : Character returned by the "next" instruction.  
"prev" : Character returned by the "prev" instruction.

"and" : Boolean result of the AND operator instruction.  
"or" : Boolean result of the OR operator instruction.  
"xor" : Boolean result of the XOR operator instruction.  
"not" : Boolean result of the NOT operator instruction.  

"capt" : String of the captured data between ptr and mrk.  
"drf" : Character of a dereferenced integer.  

"cntnt" : The content that is being operated upon.  


#### Instructions ####

 - note: delta means change.  
 - Examples will contain frames of each instruction.  
 - "||" denotes ptr and mrk position respectively. (mrk > ptr).  
 - ">" denotes a sequence of statements, 1 or more.  
 - "register : "x"" denotes the contents of a register.  

##### ins #####

Argument: 1 register.  
Output: delta in "cntnt".  
Uses: ptr, mrk.  

Description:
Inserts text at the position of ptr-mrk. Behaviour is easier to explain by an example, so here is one:  
	
We see that ptr and mrk = 0.  

	cntnt: "||this is data"
	> push x
	> cpy x "Hello"
	> ins x
	cntnt: "Hello||this is data"
	> cpy x 5
	> add mrk x
	cntnt: "Hello|this |is data"
	> ins ptr
	cntnt: "Hello5||is data"

We observe that it works exactly like a standard text editor. If you press a character when we have nothing selected, it is inserted. If we have selected text, that text is deleted, and your new character inserted.  

##### del #####

Argument: void.  
Output: void.  
Uses: ptr, mrk.  

Description:
Implements the "delete" button behaviour.  

	cntnt: "||this is data"
	> cpy x 5
	> add mrk x
	cntnt: "|this |is data"
	> del
	cntnt: "||is data"
	> del
	cntnt: "||s data"


##### bck #####

Argument: void.  
Output: void.  
Uses: ptr, mrk.  

Description:
Implements the "backspace" button behaviour.  

	cntnt: "||this is data"
	> push x
	> cpy x 5
	> add mrk x
	> cpy x 3
	> add ptr x
	cntnt: "thi|s |is data"
	> bck
	cntnt: "thi||is data"
	> bck
	cntnt: "th||is data"


##### cnt #####

Argument: 1 register.  
Output: cnt register.  
Uses: ptr, mrk, cntnt.  

Description:  
Counts the elements matching the argument within ptr and mrk. If ptr = mrk, then the text is scouted from ptr until the end.  

	cntnt: "||this is data"
	> push x
	> cpy x i
	> cnt i
	cnt: 2


##### find #####

Argument: 1 register.  
Output: ptr, mrk.  
Uses: ptr, mrk, cntnt.  

Description:  
Finds the nearest instance of the string that matches the register. Searches between ptr and mrk. If ptr = mrk, then it searches from ptr to the end of cntnt.  

	cntnt: "||this is data"
	> push x
	> cpy x "s is"
	> find x
	cntnt: "thi|s is| data"


##### size #####

Argument: 1 register.  
Output: size.  
Uses: void.  

Description:  
Stores the size of the argument register in the size register. 

	cntnt: "||this is data"
	> size cntnt
	size: 13

There are 12 characters in this string, but one has to consider the terminating character as well.  


##### capt #####

Argument: void.  
Output: capt.  
Uses: ptr, mrk, cntnt.  

Description:  
Captures the marked piece on cntnt into the capt register.  

	cntnt: "||this is data"
	> push x
	> cpy x 3
	> add mrk x
	cntnt: "|thi|s is data"
	> capt
	capt: "thi"


##### trim #####

Argument: 1 register.  
Output: 1 register.  
Uses: void.  

Description:  
Trim all whitespace from the edges of a register. Stores the result in the same register.  

	cntnt: "||this is data"
	> push x
	> cpy x 5
	> add mrk x
	cntnt: "|this |is data"
	> capt
	capt: "this "
	> trim capt
	capt: "this"


##### cnc #####

Argument: 2 registers.  
Output: 1 register.  
Uses: void.  

Description:  
Concatenates 2 strings into the first string given as an argument. 

	>push x
	>push y

	>cpy x "beta"
	>cpy y "alfa"

	>cnc x y
	>show x

x now contains "betaalfa".  


##### drf #####

Argument: 1 register.  
Output: drf register.  
Uses: void.  

Description:  
Puts the current character _at_ the number given as a register into the drf register.  

	cntnt: "t|his |is data"
	> drf ptr
	drf: "h"
	> drf mrk
	drf: "i"

##### rdf #####

Argument: 2 registers.  
Output: 1 register.  
Uses: void.  

Description:  
Reads the content of a file into the first register given as argument. If the register wants to write to itself using:  

	cntnt: "||this is data"
	> push x
	> cpy x file.txt
	> rdf x x
	x: "contents of file.txt"

then x will simply be overwritten by the contents of the file that x held before the instruction.  


##### swap #####

Argument: 2 registers.  
Output: 2 registers.  
Uses: void.  

Description:  
Swaps the content of 2 registers.  

	x: "cat"
	y: "pony"
	> swap x y
	x: "pony"
	y: "cat"

then x will simply be overwritten by the contents of the file that x held before the instruction.  


##### dir #####

Argument: 1 registers.  
Output: dir register.  
Uses: void.  

Description:  
Starts a directory iteration at the given path.  

	x: "C:\"
	> dir x
	> odir
	odir: "C:\BOOT"

dir opens a path to be read from. See odir.  


##### odir #####

Argument: void.  
Output: 1 register.  
Uses: dir's state.  

Description:  
Reads the next item in the directory.  

	x: "C:\"
	> dir x
	> odir
	odir: "C:\BOOT"
	> odir
	odir: "C:\Documents and Settings"
	> odir
	odir: "C:\eula.txt"

The odir instruction can both point to a file or a subdirectory.  
And easy method of opening a subdirectory is:  

	x: "C:\"
	> dir x
	> odir
	> dir odir
	> odir


##### show #####

Argument: 1 register.  
Output: void.  
Uses: void.  

Description:  
Prints the contents of a register to stdout.  

	cntnt: "||this is data"
	> push x
	> cpy x "content has nothing to say!"
	> show x
	
outputs: "content has nothing to say!", without the quotation marks.  


##### reset #####

Argument: void.  
Output: all registers except cntnt.  
Uses: void.  

Description:  
Resets all register states to the initial state.  

	cntnt: "||this is data"
	> inc mrk
	cntnt: "|t|his is data"
	> reset
	cntnt: "||this is data"


##### if #####

Argument: 1 register.  
Output: instruction execution pointer (EIP) (Not accessible to the user).  
Uses: instruction store (Not accessible to the user).  

Description:  
Checks if the register holds a 0 or 1. If it holds a 1, the code within the if-stop pair will be executed. If it holds a 0, EIP will be put on the stop statement and continue execution from there.  

	> push x
	> push y
	> cpy x 0
	> cpy y 0
	> eq x y
	> if eq
	> show x
	> stop

This script will output 0, because x is equal to y, and the if runs.  


##### goto #####

Argument: 1 label.  
Output: EIP (Not accessible to the user).  
Uses: instruction store (Not accessible to the user).  

Description:  
Jumps to a given point in the instructions stored and continues execution from there.  

	> :label
	> goto label

This code loops infinitely.  


##### eq #####

Argument: 2 registers.  
Output: eq register.  
Uses: void.  

Description:  
Compares the content of 2 registers and stores a boolean true or false in the eq register denoting the result of the is-equal comparison.  

	cntnt: "||this is data"
	> push x
	> cpy x t
	> drf mrk
	> eq x drf
	eq: 1


##### neq #####

Argument: 2 registers.  
Output: neq register.  
Uses: void.  

Description:  
Compares the content of 2 registers and stores a boolean true or false in the neq register denoting the result of the not-equal comparison.  

	cntnt: "||this is data"
	> push x
	> cpy x t
	> drf mrk
	> neq x drf
	neq: 0


##### lt #####

Argument: 2 registers.  
Output: lt register.  
Uses: void.  

Description:  
Compares the content of 2 registers and stores a boolean true or false in the lt register denoting the result of the larger-than comparison.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 2
	> cpy y 19
	> lt x y
	lt: 0


##### st #####

Argument: 2 registers.  
Output: st register.  
Uses: void.  

Description:  
Compares the content of 2 registers and stores a boolean true or false in the st register denoting the result of the smaller-than comparison.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 2
	> cpy y 19
	> st x y
	st: 1


##### inc #####

Argument: 1 register.  
Output: 1 register.  
Uses: void.  

Description:  
Increments the value a register holds by 1. If the register held a string, that string will be converted to 0, and then incremented by 1.  

	cntnt: "||this is data"
	> inc mrk
	mrk: 1


##### dec #####

Argument: 1 register.  
Output: 1 register.  
Uses: void.  

Description:  
Decrements the value a register holds by 1. If the register held a string, that string will be converted to 0, and then decremented by 1. Because the numbers are unsigned, that register will hold the maximum number a register can hold.  

	cntnt: "||this is data"
	> push x
	> cpy x 200
	> dec x
	x: 199


##### add #####

Argument: 2 registers.  
Output: 1 register.  
Uses: void.  

Description:  
Add the second register to the first register.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 20
	> cpy y 42
	> add x y
	x: 62
	y: 42


##### sub #####

Argument: 2 registers.  
Output: 1 register.  
Uses: void.  

Description:  
Subtract the second register from the first register.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 20
	> cpy y 42
	> sub y x
	x: 20
	y: 22


##### push #####

Argument: 1 instruction.  
Output: void.  
Uses: void.  

Description:  
Pushes a new element on the stack with the name encoded in the proceeding instruction.  

	> push "a name"
	> cpy "a name" "a string into this location"


##### pop #####

Argument: 1 instruction.  
Output: void.  
Uses: void.  

Description:  
Pops the top element from the stack with the name of the instruction argument.  

	> push x
	> cpy x 100
	x: 100
	> push x
	> cpy x 20
	x: 20
	> pop x
	x: 100
	> pop x
	x: undefined (error)


##### mov #####

Argument: 2 registers.  
Output: 1 register.  
Uses: void.  

Description:  
Copies the data from one register to another. Intel syntax is used here. That means that the first register named is the destination, and the second the source.  

	ptr: 19
	mrk: 230
	> mov ptr mrk
	ptr: 230
	mrk: 230


##### cpy #####

Argument: 1 register, 1 instruction.  
Output: 1 register.  
Uses: void.  

Description:  
Copies the following string on the instruction line to the register.  

	> push x
	x: "" (empty)
	> cpy x "This is an instruction on the instruction line, copied into x"
	x: "This is an instruction on the instruction line, copied into x"


##### next #####

Argument: void.  
Output: mrk register, next register.  
Uses: mrk.  

Description:  
Increments mrk and stores a dereferenced character into the next register.  

	cntnt: "||this is data"
	> next
	cntnt: "|t|his is data"
	> next
	cntnt: "|th|is is data"


##### prev #####

Argument: void.  
Output: ptr register, prev register.  
Uses: ptr.  

Description:  
Decrements ptr and stores a dereferenced character into the prev register.  

	cntnt: "this is d||ata"
	> prev
	cntnt: "this is |d|ata"
	> prev
	cntnt: "this is| d|ata"


##### and #####

Argument: 2 registers.  
Output: and register.  
Uses: void.  

Description:  
Compares 2 registers using the AND logic gate.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 1
	> cpy y 1
	> and x y
	and: 1


##### or #####

Argument: 2 registers.  
Output: or register.  
Uses: void.  

Description:  
Compares 2 registers using the OR logic gate.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 1
	> cpy y 0
	> or x y
	or: 1


##### xor #####

Argument: 2 registers.  
Output: xor register.  
Uses: void.  

Description:  
Compares 2 registers using the XOR logic gate.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 1
	> cpy y 1
	> xor x y
	xor: 0


##### not #####

Argument: 1 register.  
Output: not register.  
Uses: void.  

Description:  
Inverses the boolean contained in the register and stores it in not.  

	cntnt: "||this is data"
	> push x
	> push y
	> cpy x 1
	> cpy y 1
	> xor x y
	> not xor
	xor: 0
	not: 1


## TODO ##

~~ Implement recursivity ~~  
Escape sequences  
UTF8 support  

Tier 1 functionality:  
Functions  
if  
while  
operators  
do-while  
scope  

Tier 2 functionality:
structs  
classes  
lambdas  