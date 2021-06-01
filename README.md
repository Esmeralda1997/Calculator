# Calculator
Using a single stack we convert from infix to postfix. We first check for any arithmetic errors that might cause problems later in the calculation. Then we check for negatives, operators, and digits to form an ordered postfix. Then we use the same stack and we start to evaluate the postfix. The remaining integer in the stack is the answer.

How to use:
First, navigate to the folder in which the program is in. In the IDE of your liking open up the terminal window. 

Type into the terminal window:
g++ -std=c++11 Calculator.cpp -o Calculator

This will create an executable file called Calculator which you can run from the terminal. 

Then type the below command into the terminal:
./Calculator input3-.txt output3-.txt

*Replace the input3-.txt and output3-.txt with the correct files in the directory. If you want to create new input files just add them to the input folder. 

This program checks if the paranthesis in an expression are balanced and if they are it calculates the output of the expression.
