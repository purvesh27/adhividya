#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstdio>
#include <string>
using namespace std;
// function to append zeros to a string
string append_zeros(string s, int n){
	string temp;
	for(int i = 0; i < n; i++){
		temp += "0";
	}
	s = temp + s;
	return s;
}
	
// function to remove extra zeros from the string
string remove_zeros(string s){
	int count = 0, i;	
	for(i = 0; i < s.length(); i++){
		if(s[i] == '0'){
			count++;
		}
		else{
			break;
		}
	}
	return s.substr(i);
}

int main()
{
	string input_string1, input_string2, operation;
	string result, bigger, smaller;
	bool which_operation = true;
	int bigger_length, smaller_length;
	bool isNegetive = false;

	// taking input from the user 
	cout << "Enter 1st number\n";
	cin >> input_string1;
	cout << "Enter 2nd number\n";
	cin >> input_string2;
	cout << "Enter 'add' for addition and 'sub' for substraction\n";
	cin >> operation;

	// checking which operation to perform addition or substraction
	if(operation == "add"){
		which_operation = true;
	}
	else if(operation == "sub"){
		which_operation = false;
	}
	
	// compairing the length of the two input string 
	// and assigning bigger and smaller strings
	int length_1 = input_string1.length();
	int length_2 = input_string2.length();
	if(length_1 < length_2){
		bigger = input_string2;
		smaller = input_string1;
		isNegetive = true;
	}
	else if(length_1 > length_2){
		bigger = input_string1;
		smaller = input_string2;
	}
	else if(length_1 == length_2){
		for(int i = 0; i < length_1; i++){
			if(input_string1[i] == input_string2[i]){
				continue;
			}
			else if(input_string1[i] < input_string2[i]){
				bigger = input_string2;
				smaller = input_string1;
				isNegetive = true;
				break;
			}
			else if(input_string1[i] > input_string2[i]){
				bigger = input_string1;
				smaller = input_string2;
				break;
			}
		}
	}
	else{
		bigger = input_string1;
		smaller = input_string2;
	}

	bigger_length = bigger.length();
	smaller_length = smaller.length();


	// appending zeros to bigger and smaller strings
	bigger = append_zeros(bigger, 15 - bigger_length%15);
	smaller = append_zeros(smaller, bigger.length() - smaller.length());
	
	//cout << bigger << "\n";
	//cout << smaller << "\n";


	// if the operation to perform is additions
	if(which_operation){
		// reverse the bigger and smaller string
		reverse(bigger.begin(), bigger.end());
		reverse(smaller.begin(), smaller.end());

		bool isCarry = false;

		for(int i = 0; i < bigger_length; i += 15){
			// making substring from the main string part1 and part2
			string part1 = bigger.substr(i, 15);
			string part2 = smaller.substr(i, 15);

			reverse(part1.begin(), part1.end());
			reverse(part2.begin(), part2.end());

			// converting part1 and part2 to long long int
			long long int part1_int = stoll(part1, nullptr, 10);
			long long int part2_int = stoll(part2, nullptr, 10);
			long long int temp_result;

			// check if carry

			if(isCarry){
				// if carry add the parts including the carry
				temp_result = part1_int + part2_int + 1;
			}
			else{
				// as the carry is not present add the parts without carry
				temp_result = part1_int + part2_int;
			}

			// temporary string to hold the result of operation carried out by a part
			string temp_str = to_string(temp_result);
			// append zeros to the part if it is less than the parts length
			temp_str = append_zeros(temp_str, 15 - temp_str.length());
			//cout << "temp_str = " << temp_str << "\n";


			// if temporary string length exceeds the groups length then carry is present
			// else just carry out the addition of the result
			if(temp_str.length() > 15){
				isCarry = true;
				result = temp_str.substr(1, 15) + result;
			}
			else{
				result = temp_str + result;
				isCarry = false;
			}
			//cout << "result = " << result << "\n";

		}
		// removing excessive zeros from the result
		result = remove_zeros(result);
		cout << "result = " << result << "\n";

	}
	else{
		// reverse bigger and smaller strings
		reverse(bigger.begin(), bigger.end());
		reverse(smaller.begin(), smaller.end());
		bool isBorrow = false;

	for(int i = 0; i < bigger_length; i += 15){
		// make substring from the bigger and smaller strings
		string part1 = bigger.substr(i, 15);
		string part2 = smaller.substr(i, 15);
		//cout << "part1_str " << part1 << "\n";
		//cout << "part2_str " << part2 << "\n";

		// reverse the parts created from main strings
		reverse(part1.begin(), part1.end());
		reverse(part2.begin(), part2.end());

		// converting the parts to long long int
		long long int part1_int = stoll(part1, nullptr, 10);
		long long int part2_int = stoll(part2, nullptr, 10);
		//cout << "part1_int " << part1_int << "\n";
		//cout << "part2_int " << part2_int << "\n";
		long long int temp_result;

		// check if borrow
		if(isBorrow){
			temp_result = part1_int - part2_int - 1;
		}
		else{
			temp_result = part1_int - part2_int;
			//cout << "temp_result " << temp_result << "\n";
		}
		string temp_str;

		if(temp_result < 0){
			isBorrow = true;
			temp_str = to_string(1000000000000000 + temp_result);
		}
		else{
			isBorrow = false;
			temp_str = to_string(temp_result);
			
		}

		temp_str = append_zeros(temp_str, 15 - temp_str.length());
		result = temp_str + result;
		//cout << "temp_str = " << temp_str << "\n";

		//cout << "result = " << result << "\n";

	}

	// removing excessive zeros from the result
	result = remove_zeros(result);

	// if the first number is smaller than the second number then add negative sign 
	if(isNegetive){
		cout << "result = " << "-" + result << "\n";
	}
	else{
		cout << "result = " << result << "\n";
	}
	//cout << "result = " << result << "\n";

	}
	return 0;
}