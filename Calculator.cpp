#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>  
#include "ArgumentManager.h"
using namespace std;

template <class T>
struct node{
	T Operator;
	node<T>* next;
};

template <class T>
class Equation{
	node<T>* top;
	public:
	Equation(){top = NULL;}
	void remuveSpace(string&);
	bool Operator(char);
	bool NoError(string);
	bool garbage(char);
	bool balanced(string);
	bool isEmpty();
	bool is_digits(string);
	T Top();
	void push(T);
	void pop(T&);
	int priority(T);
	void convert(string, string&);
	void evaluate(string, T&); 
	void calculate(char,T,T,T&);
	~Equation();
};

template <class T>
void Equation<T>::remuveSpace(string& I){
	string i = "";
	char c;
	int index = 0;
	while(index != I.length()) {
		c = I[index];
		if(c != ' ' && c != '\r')
			i += c;	
		index++;	
	}
	I = i;
}

template <class T>
bool Equation<T>::Operator(char c){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

template <class T>
bool Equation<T>::garbage(char c){
	return !Operator(c) && !isdigit(c) && c != '(' && c != ')';
}

template <class T>
bool Equation<T>::balanced(string i){
	char t;
	for(char c: i){ 
		if(c == ')'){
			if(isEmpty()){
				push(c);
				break;
			} else{
				pop(t);
			}
		} else if(c == '(') {
			push(c);
		}
	}
	
	if(!isEmpty())
		return false;
	return true;	
}

template <class T>
bool Equation<T>::NoError(string I){
	bool correct = true;
	remuveSpace(I);
	int index = 0;
	if(I[index] == '*' || I[index] == '/' || Operator(I.back()) || garbage(I.back()) || !balanced(I)){
		correct = false;	
	}
	while(correct && index != I.length()-1){
		if(isdigit(I[index])){
			if(I[index+1] == '(')
				correct = false;
		} else if( I[index] == '('){
			if(I[index+1] == '/' || I[index+1] == '*'|| I[index+1] == ')')
				correct = false;
		} else if(I[index] == ')'){
			if(I[index+1] == '(' || isdigit(I[index+1]))
				correct = false;
		} else if(Operator(I[index])){ 
			if(Operator(I[index+1]) || I[index+1] == ')')
				correct = false;
		} else if(garbage(I[index])){
				correct = false;
		}
		index++;
	}
	return correct;
}

template <class T>
bool Equation<T>::isEmpty(){
	if(top == NULL)
		return true;
	return false;	
}

template <class T>
T Equation<T>::Top(){
	return top->Operator;
}

template <class T>
void Equation<T>::push(T o){
	node<T>* temp = new node<T>;
	temp->Operator = o;
	temp->next = top;
	top = temp;
} 

template <class T>
void Equation<T>::pop(T &c) {
	node<T>* temp = top;
	c = temp->Operator;
	top = temp->next;
	delete temp;
}

template <class T>
int Equation<T>::priority(T o){
	if(o == '*' || o == '/')
		return 2;
	else if(o =='+' || o == '-')
		return 1;
	else
		return -1;		
}

template <class T>
bool Equation<T>::is_digits(string e){
	int index = 0;
	while(index != e.length()-1){
		if(!isdigit(e[index]))
			return false;
		index++;	
	}		
	return true;
}

template <class T>
void Equation<T>::convert(string in, string& post){
	T t,c;
	int index = 0;
	bool cont = true;
	remuveSpace(in);
	while(index != in.length()){ 
		c = in[index];
		cont = true;
		if(isdigit(c)){ 
				post += c;
		} else if((c == '+' && index == 0) || (in[index-1] == '(' && c == '+')){
				post += "P"; //indicates it is a 1
				post += " ";
				push('*');		
		} else if((c == '-' && index == 0) || (in[index-1] == '(' && c == '-')){
				post += "N"; //indicates it is a -1
				post += " ";
				push('*');
		}else if(isEmpty() && Operator(c)){ 
			post += " ";
			push(c);
		} else if(c == '('){	
			push(c);
		}else{
			while(cont != false){
				pop(t);  
			 	if(priority(c) > priority(t)){ 
			 		cont = false;
			 		post += " ";
			 		push(t);
					push(c);
			 	} else { 
			 		if(priority(c) == -1){
						if(priority(t) != -1){
							post += " ";
							post += t; 
						} else {
							cont = false;
						}
					}	else { 
						post += " ";
						if(top != NULL){
							post += t;
						}else{
							push(c);
							post += t;
							cont = false;
						}
						post += " ";
					}
				}
			}
		}
		index++;
	}
	while(top != NULL){
		pop(t);
		post += " ";
		post += t;
	}
	post += " ";
}

template <class T>
void Equation<T>::evaluate(string p, T &total){
	int index = 0;
	string line = "";
	long long int d1, d2;
	if(is_digits(p) == true){
		d1 = stoll(p);
		push(d1);
		index = p.length()-1;
	}
	while(index != p.length()-1){
		if(p[index] == 'N'){
			push(-1);
		} else if (p[index] == 'P'){
			push(1);	
		}	else if (isdigit(p[index])){
			line += p[index];
		} else if(p[index] == ' ' && line != ""){
			d1 = stoll(line);
			line = "";
			push(d1);		
		} else if(Operator(p[index])){
			pop(d2);
			pop(d1);
			calculate(p[index],d1,d2,total);
			push(total);
		}
		index++;
	}
	pop(total);
}

template <class T>
void Equation<T>::calculate(char o, T t1, T t2,T& total){
		switch (o){
		case '+':
			total = t1+t2;
			break;
		case '-':
			total = t1-t2;
			break;
		case '*':
			total = t1*t2;
			break;
		case '/':
			total = t1/t2;		
		default:
			return;
	}	
}

template <class T>
Equation<T>::~Equation(){
	T temp;
	while(!isEmpty()){
		pop(temp);
	}
}

int main(int argc, char* argv[]){
	
	if(argc < 3) {
		// Tell the user how to run the program
        cerr << "Input and output files not specified." << endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
	}


	string i = argv[1];
	string o = argv[2];

	ifstream in("input/" + i);
	ofstream out("output/" + o);
	string inFix;
	Equation<char> P;
	Equation<long long int> E;
	long long int total = 0;
	string postFix;
	bool fileEmpty = true;
	
			while(!in.eof()){
				getline(in,inFix);
				
				if(inFix != ""){
					fileEmpty = false;
					if(!P.NoError(inFix)){
						out << "error" << endl;
						P.~Equation();
					} else {
						P.convert(inFix, postFix);
						E.evaluate(postFix, total);
						out << inFix << "=" << total << endl;
						P.~Equation();
						E.~Equation();
						postFix = "";
					}
				}
				if (in.eof() && inFix == "" && fileEmpty == true)
					out << "error" << endl;
			}
	
	return 0;
}
