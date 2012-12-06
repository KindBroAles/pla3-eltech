#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
using namespace std;

int main (int argc, char *argv[]) {
	
    int length; //length of the input and output lines
    string str; //rewriting string 
    size_t var = 0; //ASCII code of key
    char *key = 0; // coding key
    string param;// reading parameter
    string alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789"; //introduction of the alphabet
    string newAlphabet; //introduction of the new alphabet
    int count = 0; // the variable stores number under which the coding key is entered
    int errorinf = 0; // the variable stores information on existence of errors
    int type = 0; // if type=0 then encode, if type=1 then decode
    
    // =================Reading and processing of parameters==================
    int i;
    for (int i = 1; i<argc; i++) {
        param.assign(argv[i]);
        if (param == "crypt") {errorinf++;count=1;}
        if ((((param == "-t") && (param.assign(argv[i+1]) == "decode"))) || (param == "--type=decode")) { type = 1; errorinf++; count=1;}
        if ((((param == "-t") && (param.assign(argv[i+1]) == "encode"))) || (param == "-type=encode") || (param == "--type=encode")) { type = 0; errorinf++; count=1;}
        if ((param == "-h") || (param == "--help")) { system ("Help.txt"); errorinf++;count=1;}
        if ((param == "-a") && (param == "--alphabet=") { alphabet.assign(argv[i+1]); errorinf++; i++;count=1; }
        var = (size_t)*argv[i];
        if ((var > 48) && ((var < 58))) { key = argv[i]; errorinf++; count = i; break;}
        if (errorinf == 0) {cout<<"Incorrect parameter1"; system ("Help.txt");exit(0);}
	} 
    	if (count == 0) {cout<<"Incorrect parameter2"; system ("Help.txt");exit(0);}
	//========================================================================
   
    // ===================Reading of names of input and output files==========
    const char *inputFile;
    const char *outputFile;
    if ((count+3) == argc) { inputFile = argv[count+1]; outputFile = argv[count+2]; } 
    if ((count+2) == argc) { inputFile = argv[count+1]; outputFile = argv[count+1]; }
    //========================================================================

	ifstream vhod;
	vhod.open(inputFile);
	if (!vhod.good()) { 
        printf("%s\n", "Input file not found!");
        return -1;
    };

    //=====================Get the length of lines============================
    	int lengthAlphabet=alphabet.length();
    	string intermediate;
        while (!vhod.eof()){
            vhod>>intermediate;
            str.append(intermediate);
            str.append(" ");
        };
		length=str.length();
		str=str.substr(0,length-1);
		length=str.length();
	//========================================================================	
	
	//=====================check on the type of operation=====================
	int casecode=0;
	if (type==0) casecode=1; 
	if (type==1) casecode=-1; 
	//========================================================================
	
	newAlphabet=alphabet;
	*key=atoi(key); // obtaining numerical value of a key of coding
	switch (casecode){
		case 1: for (int i=0;i<lengthAlphabet;i++){newAlphabet[i]=alphabet[(i+*key)%lengthAlphabet];} //perform encoding
		break;
		case -1: for (int i=0;i<lengthAlphabet;i++){newAlphabet[i]=alphabet[(i-*key+lengthAlphabet)%lengthAlphabet];} //perform decoding
		break;
	}
    
    // ============ recording obtained data ==================================
    int codeerror=0;	
	for (int i=0;i<length;i++){						
		for(int j=0;j<lengthAlphabet&&codeerror!=1;j++){
			if (str[i]==alphabet[j]){
				str[i]=newAlphabet[j];
				codeerror=1;
			}
		}
		codeerror=0;
	}
	ofstream vihod;
	vihod.open(outputFile);
	if (!vihod.good()) { 
        printf("%s\n", "Output file not found!");
        return -1;};
    vihod<<str;
    vihod.close();
    // =======================================================================
   	return 0;
}