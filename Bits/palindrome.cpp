#include<iostream>
#include<string>
using namespace std;

/*There are in total 3 cases that we need to handle
*	Case 1 - The input is all nines eg. 999. Output should be 1001
*	
*	Case 2 - The input is not a palindrome
*
*	Case 3 - Input is a palindrome.
*
*	In Cases 2 and 3 we have to handle two subcases where the number of digits are odd
*	or even. The logic is that the middle number is incremented by 1 and the carry is 
*	propogated on the left hand side and simultaneously the left hand side is copied to the right hand side.
*
*/
bool is_all_nines(string a){
	int l = a.length(), i = 0;
	while(i < l){
		if(a[i] != '9')
			return false;
		i++;
	} 
	return true;
}
int main(){
	int l; string number;
	cin>>number;
	if(is_all_nines(number)){
		l = number.length();
		int i = 1;
		cout<<1;
		while(i<l){
			cout<<0;
			i++;
		}
		cout<<1<<endl;
	}
	else{
		int l = number.length();
		int mid = l/2;
		int i = mid - 1;
		int j = (l%2)? mid+1 : mid;
		bool case2 = false;
		while( i >= 0 and number[i] == number[j]){
			i--, j++;
		}
		if( i < 0 or number[i] < number[j])
			case2 = true;
			
		while (i >= 0){
			number[j] = number[i];
			j++;
			i--;
		}
		if(case2){
			i = mid - 1;
			int carry = 1, total;
			
			if(l%2==1)
			{
				total = (number[mid] - 48) + carry;
				carry = total / 10;
				number[mid] = (char)((total % 10) + 48);
				j = mid + 1;
			}				
			else
				j = mid;

			while(i >= 0){
				total = (number[i] - 48) + carry;
				carry = total / 10;
				number[i] = (char)((total) % 10 + 48);
				number[j++] = number[i--];
				}
		}
		else{
			while(i >= 0){
				number[j++] = number[i--];
			}
			
		}
		cout<<number<<endl;
		
	}
	return 0;
}
