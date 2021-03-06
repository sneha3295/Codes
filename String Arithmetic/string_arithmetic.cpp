/*
*	Date 30th August 2014	
*	@author Aditya Paliwal
*	Some arithmetic operations for very large numbers.
*	These functions are useful when a number is stored as a string
*	and cannot be stored as any of the default data types due to memory restrictions.
*/
#include<iostream>
#include<string>
#include<cmath>
using namespace std;

string add(string a, string b);
string sub(string a, string b);
string multiply(string a, string b);
string naive_multiply(string &a, string &b);

/*
*  A few helper functions
*/


/*This appends m 0s to the end of the string to act as a multiplication by 10^m*/
string shift_left(string &a, int m){
	while(m--){
		a = a + (char)(48);
	}
	return a;
}

/*This function removes all valueless 0s from the starting of the string*/
void unpad_zeroes(string &a){
	int i = 0;
	int l = a.length();
	string zero("0");
	while(a[i] == '0'){
		i++;
	}
	a = a.substr(i);
	if(a.length() == 0){
		a = zero;
	}
}

/*This appends 'l' of zeroes to the beggining of the string*/
void pad(string &a, int l){
	while(l--){
		a = '0' + a;
	}
	
	//return a;
}



/*This function adds the two numbers a and b using grade school addition method*/
string add(string a, string b){	
	/* 	
	*	If a is negative, the result is (b-a)
	*	If b is negative, the result is (a-b)
	*	If a and b are both negative the result is -(b+a)
	*/
	if(a[0] == '-' and b[0] == '-')
		return '-' + add(a.substr(1), b.substr(1));
	else if(a[0] == '-')
		return sub(b, a.substr(1));
	else if(b[0] == '-')
		return sub(a, b.substr(1));
	
	unpad_zeroes(a);
	unpad_zeroes(b);
	
	int a_length = a.length(), b_length = b.length();
	if(a == "0")	
		return b;
	else if(b == "0")
		return a;

	string c = "";		//This is the new string where the result will be stored
	
	int digit1, digit2, total = 0, carry = 0, j = b_length -1, i = a_length -1;		//digit1 and digit2 are the digits of a and b respectively
	
	for(; j >= 0 && i >= 0; j--){	//The loop runs till either of the numbers a or b run out of digits to compute upon
	
		//The character is converted from its ASCII value to an integer value, computed upon and then converted back to ASCII
		digit1 = a[i] - 48;		
		digit2 = b[j] - 48;
		
		total = digit1 + digit2 + carry;
		carry = total / 10;
		
		if(carry != 0) total -= 10;	
		//The total should always be a single digit, so if a carry is present, it means that the number is greater than 10
		
		c = char(total + 48) + c;
		
		i--;
	}
	if(i >= 0){				//This handles the case where a has more digits than b
		while(i >= 0){
		
			digit1 = a[i] - 48;
			
			total = digit1 + carry;
			carry = total/10;
			
			if(carry!=0) total -= 10;
			
			
			c = (char)(total + 48) + c;
			
			i--;
		}
	}
	if(j >= 0){							//This handles the case where b has more digits than a
		while(j>=0){
			digit2 = b[j] - 48;	
			total = digit2 + carry;
			carry = total/10;	
			if(carry!=0) total -= 10;		
			c = (char)(total + 48) + c;
			
			j--;
		}
	}
	
	if (carry != 0) c = char(carry + 48) + c;		//This takes care of the final carry over if any
	
	unpad_zeroes(c);
	return c;
}





/*Ths function subtracts two given strings of numbers*/
string sub(string a, string b){
	/* 	
	*	If a is negative, the result is -(b+a)
	*	If b is negative, the result is (a+b)
	*	If a and b are both negative the result is 	(b-a)
	*/
	if(a[0] == '-' and b[0] == '-')
		return sub(b.substr(1), a.substr(1));
	else if(a[0] == '-')
		return '-' + add(a.substr(1), b);
	else if(b[0] == '-')
		return add(a, b.substr(1));
	
	/*We pad the two numbers and check which one is bigger so that we can assert wether the result is negative or not*/
	int a_length = a.length(), b_length = b.length(), borrow_from, i, j;
	
	bool is_negative = false;		// Is the result of the subtraction negative? It is false by default

	string c = "", temp ="";		//The temp string has been made to accomodate string swaps
	
	if(a_length > b_length){
		pad(b, a_length - b_length);
		j = b_length - 1;
		i = a_length - 1;
	}		
	else if(a_length < b_length){
		pad(a , b_length - a_length);
		j = a_length - 1;
		i = b_length - 1;
	}
	else{
		j = a_length - 1;
		i = j;
	}
	
	/*
		This method to compare strings works accurately only if they are of equal length.
	    Hence we are padding them with zeroes if they are of unequal length
	 */
	if(b>a){
		is_negative = true;		//This means the result will be negative
		temp = a;
		a = b;
		b = temp;
	}
	
	unpad_zeroes(a);
	unpad_zeroes(b);
	
	if(b == "0"){
		return a;
	}

	for(j; j >= 0; j--){
		if(b[j] <= a[i]){	
			 //This is the case where we dont have to borrow from the next digits
			 c = (char) (a[i] - b[j] + 48) + c;	
		}
		else{	
			//In this case we have to borrow
			borrow_from = i - 1;	
			
			while(a[borrow_from] == '0'){	
				//This loop gives us the first index from where we can borrow a digit
				 borrow_from--;
			}
			a[borrow_from++]--;
			while(borrow_from < i) a[borrow_from++] = 57;
			
			c = char(a[i] - b[j] + 58) + c; // After succesfully borrowing, we can now subtract the numbers
		}
		i--;
	}
	if(i >= 0){			
		//In case the string a has more digits than b, then the remaining digits are appended in this loop
		while(i>=0){
			c = a[i] + c;
			i--;
		}
	}
	unpad_zeroes(c);
	if(is_negative)
		return '-' + c;
	
	return c;
}





/*This function divides a string number by 2. Works only for positive numbers and returns the answer rounded down to nearest integer*/
string div_by_two(string a){
	int a_length = a.length();
	int i = 0, digit = 0, carry = 0;
	string c = "";		//The result is stored in this new string c
	for(i = 0; i < a_length; i++){
	
		digit = a[i] - 48;
		
		c = c + (char) ((( digit + carry )/2) + 48); //Each digit is divided by 2
		
		if ( digit%2 == 1) // If the digit was odd it will have a carry over to the next digit
			carry = 10;
		else
			carry = 0;
	}
	
	unpad_zeroes(c);
	
	return c;
}


/*
*****Be warned! Dont use this for very large numbers as it will take significantly longer computational time.This function only works for non negative integers. It will give incorrect results for negative or non integral numbers*****
The grade school multiplication algorithm for 2 numbers. This is of order n*m and is just a helper function
for the Karatsuba algorithm.
*/
string naive_multiply(string &a, string &b){
	string c = "0", temp = "", zeroes = "";	// each time a single digit from 'a' is multiplied to b, it is stored in temp
	// 'c' is the final string that is returned
	int a_length = a.length(), b_length = b.length(), i = a_length - 1, j, digit1, digit2, total, carry = 0;
	while(i >= 0){
		carry = 0;
		j =  b_length - 1;
		digit1 = a[i] - 48;
		temp = "";
		while( j >= 0){
			digit2 = b[j] - 48;
			total = digit1 * digit2 + carry;
			carry = total/10;
			total = total % 10;
			temp = (char) (total + 48) + temp;
			j--;
		}
		if(carry != 0)
			temp = (char)(carry + 48) + temp;	//Adding the overflowed carry if any
		
		temp = temp + zeroes;//Padding the extra zeroes in the end corresponding to the stage of the multiplication
		
		zeroes = zeroes + (char)(48); //For the next stage one more zero will be required
		
		c = add(c, temp);	//Adding the new result to the total result
		
		i--;
	}
	
	unpad_zeroes(c);
	return c;
}


/*
*****Be warned!This function only works for non negative integers. It will give incorrect results for negative or non integral numbers*****
This functions multiplies two numbers that are stored as strings using the
Karatsuba fast multiplication algorithm.Since these functions are to be used for
extremely large numbers, Karatsuba algorithm should provide significantly faster
computations than the generic grade-school algorithm which involves n*m single digit 
mulitplications. The complexity is n^{\log_23}
 */
string multiply(string a, string b){
	unpad_zeroes(a);
	unpad_zeroes(b);
	if ( a == "0" or b == "0" or a == "" or b == "")
		return "0";
	float a_length = a.length(), b_length = b.length();
	
	/*If the either of the two strings represents a single digit number, then we apply the grade school algorithm.
	  This is the terminating case for recursion*/
	if(a_length < 2 or b_length < 2)
		return naive_multiply(a, b);
		
	string c("");
	int m = ceil(max(a_length, b_length) / 2);
	int p1 = a_length - m;
	int p2 = b_length - m;

	if(p1 < 0) p1 = 0;
	if(p2 < 0) p2 = 0;
	
	//The numbers are split into their upper and lower halves
	string low1 = a.substr(p1), low2 = b.substr(p2) , high1 = a.substr(0, p1), high2 = b.substr(0, p2);
	
	string z0 = multiply(low1, low2);
	string z2 = multiply(high1, high2);
	string z1 = sub( sub( multiply( add(low1, high1), add(low2,high2) ), z2), z0);
	
	c = add( add( shift_left(z2, 2*m), shift_left(z1, m) ), z0);
	return c;
}

int main(){
	string a,b;
	cin>>a>>b;
	//cout<<add(a,b)<<endl;
	//cout<<sub(a,b)<<endl;
	//cout<<multiply(a, b)<<endl;
	//cout<<naive_multiply(a,b)<<endl;
	//cout<<div_by_two(a)<<endl;
	return 0;
}
