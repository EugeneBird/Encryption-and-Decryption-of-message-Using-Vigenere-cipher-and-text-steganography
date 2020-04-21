#include<bits/stdc++.h>
#include<fstream>
using namespace std;
char bit_to_char(int arr_bit[]){                                      //Binary to char
	int ascii_char=(arr_bit[7]*1)+(arr_bit[6]*2)+(arr_bit[5]*4)+(arr_bit[4]*8)+(arr_bit[3]*16)+(arr_bit[2]*32)+(arr_bit[1]*64)+(arr_bit[0]*128);
	if(ascii_char==0){
		return '\0';
	}
	return (char)ascii_char;
}
string decryption(string encrypted,string key){                       //Decryption of vingenere cipher
	string decrypted="";
	for(int i=0;i<encrypted.length();i++){
		if(encrypted[i]=='\0'){
			return decrypted;
		}
		int k=(int)encrypted[i]-((int)key[i%key.length()]-96);
		if(k<97){
			k=k+26;
		}
		decrypted=decrypted+(char)k;
	}
	return decrypted;
}
int main(){
	string key;
	cout<<"Enter Key :-  ";
	cin>>key;
	string encrypted="";
	ofstream fout;                                        //Creating file output object
	ifstream fin;                                         //creating file input object
	
	fin.open("cyber_test_output_final.txt");             //Opening file "cyber_test_output.txt" has STEGO text
	fout.open("cyber_test_decrypted_final.txt");
	
	string line;                                          //String which will contain the STEGO text line by line
	int bit_line=0;                                       //line of which bits are beign extracted
	
	int enc_char_to_bit=0;                                 //Tells the char to be converted to binary for stegnography
	int arr_bit[8]={0};                                    //Contains a particular char in binary
	
	while(fin){                                            //Reading the file and extracting bits
		getline(fin,line);
		int position;
		int flag=0;
		if(bit_line<8){
			if(line[0]>=97 && line[0]<=122){
				arr_bit[bit_line]=0;
			}
			else if(line[0]>=65 && line[0]<=90){
				arr_bit[bit_line]=1;
			}
			bit_line++;
			position=fin.tellg();
		}
		else if(bit_line>=8){
			int flag=0;
			for(int i=0;i<8;i++){
				if(arr_bit[i]==1){
					flag=1;
				}
			}
			char c='\0';
			if(flag==1){
				c = bit_to_char(arr_bit);
			}
			for(int i=0;i<8;i++){
				arr_bit[i]=0;
			}
			bit_line=0;
			encrypted=encrypted+c;
			fin.seekg(position,ios::beg);
		}
	}
	string decrypted="";
	decrypted=decryption(encrypted,key);                                  //Decrypting the message found in STEGO text
	fout<<decrypted<<endl;                                                //Storing decrypted msg in "cyber_test_decrypted_final.txt" file
	fin.close();	
}
