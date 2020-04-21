#include<bits/stdc++.h>
#include<fstream>
using namespace std;
string msg_without_spaces(string msg_initial){            //Removing spaces from msg
	string msg="";
	int j=0;
	for(int i=0;i<msg_initial.length();i++){
        if(msg_initial[i]!=' '){
            msg=msg+msg_initial[i];
            j=j+1;
        } 
    }
    return msg;
}
string encryption(string msg,string key){                  //Encrypting the msg using vigenere cipher
	string encrypted="";
	for(int i=0;i<msg.length();i++){
		int k=(int)msg[i]+((int)key[i%key.length()]-96);
		if(k>122){
			k=k-26;
		}
		encrypted=encrypted+(char)k;
	}
	return encrypted;
}
int* encrypted_to_bits(char c,int arr_bit[8]){            //Conver a char to binary
	int curr_msg=(int)c;
    int j=0;
    while(curr_msg>0) {
    	arr_bit[7-j] = curr_msg%2;
    	curr_msg = curr_msg/2;
    	j++;
	}
	return arr_bit;
}
int main(){
	string msg_initial; 
	cout<<"Enter Message :-  ";         
	getline(cin,msg_initial);                             //Taking intial msg as input
	
	string msg=msg_without_spaces(msg_initial);           //Msg without spaces
	
	string key;
	cout<<"Enter Key :-  ";    
	cin>>key;                                             //Taking key input
	
	string encrypted=encryption(msg,key);                 //encrypting the msg using vigenere cipher
	
	
	
	ofstream fout;                                        //Creating file output object
	ifstream fin;                                         //creating file input object
	
	fout.open("cyber_test_output_final.txt");             //Opening file "cyber_test_output.txt" has STEGO text
	fin.open("cyber_test_final.txt");                     //Opening file "cyber_test.txt" has COVER text
	
	string line;                                          //String which will contain the cover text line by line
	int bit_line=0;                                       //(Line in which stego is being performed) Mod 8
	
	int enc_char_to_bit=0;                                 //Tells the char to be converted to binary for stegnography
	int arr_bit[8]={0};                                    //Contains a particular char from encrypted in bits
	
	encrypted_to_bits(encrypted[enc_char_to_bit],arr_bit);
	
	while(fin){                                            //Applying text stego
		getline(fin,line);
		int position;
		int flag=0;
		if(enc_char_to_bit < encrypted.length()){
			if(bit_line<8){
				if(arr_bit[bit_line]==1){
					line[0]=line[0]-32;
				}
				else if(arr_bit[bit_line]==0){
					
				}
				bit_line=bit_line+1;
				position=fin.tellg();
			}
			else if(bit_line >= 8){
				enc_char_to_bit=enc_char_to_bit+1;
				encrypted_to_bits(encrypted[enc_char_to_bit],arr_bit);
				bit_line=0;
				fin.seekg(position,ios::beg);
				flag=1;
			}
		}
		else if(enc_char_to_bit >= encrypted.length()){
			for(int i=0;i<8;i++){
				arr_bit[i]=0;
			}
			flag=0;
		}
		if(flag==0){
			fout<<line<<endl;;	
		}
	}
	fin.close();	
}
