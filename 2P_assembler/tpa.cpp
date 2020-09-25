#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first

using namespace std;

/*
    42 = reg reg imm. addr.
    41 = reg reg reg
    32 = reg imm. addr.
    31 = reg reg
    
    11   = addess
    10   = zero
    00 = inst requires jumping to a label
*/
//Unchecked Error: if format is right, invalid regcode
/*
EXPECTED INPUT ASSEMBLY CODE:
label1: opcode operand
opcode operand
label2: opcode operand
HLT

cannot be:
label1:
opcode operand

*/

struct mot_s{
    string name;
    string bincode;
    int format;
};

vector<mot_s> mot;

vector<pair<string, int>> SYMBOL_TABLE;

struct Symbol{
    string inst;
    int addr;
    int format;
};

void init()
{
	//Initializing Machine Opcode Table
    mot.clear();
    mot.resize(13);
	mot[0] = {"ADD","00000001",31};
	mot[1] = {"ADDI","00000010",42};
	mot[2] = {"CMP","00000011",31};
	mot[3] = {"INC","00000100",11};
	mot[4] = {"JEQ","00000101",00};
	mot[5] = {"JMP","00000110",00};
	mot[6] = {"LOAD","00000111",31};
	mot[7] = {"LOADI","00001000",32};
	mot[8] = {"MOVI","00001001",32};
	mot[9] = {"MOV","00001010",31};
	mot[10] = {"HLT","00001011",10};
	mot[11] = {"STORE","00001100",31};
	mot[12] = {"STORI","00001101",32};
}

vector<string> split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();
 
    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;
 
        pos = txt.find( ch, initialPos );
    }
 
    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );
    vector<string> ans=strs;
    return ans;
}

string getRegCode(string r){
    if(r=="R0")
        return "00000";
    if(r=="R1")
        return "00001";
    if(r=="R2")
        return "00010";
    if(r=="R3")
        return "00011";
    if(r=="R4")
        return "00100";
    if(r=="R5")
        return "00101";
    if(r=="R6")
        return "00110";
    if(r=="R7")
        return "00111";
    else
        return "11111"; //CODE FOR INVALID REGISTER
    
}

//CHECK IF CONVERSION IS RIGHT
string decToBinary(int n) 
{ 
    // counter for binary array 
    int i = 0; 
    string num;
    char c;
    while (n > 0) { 
  
        // storing remainder in binary array 
        int t=n%2;
        c=t+'0';
        //cout<<"here: "<<c;
        num.pb(c);
        n = n / 2; 
    } 
    
    reverse(num.begin(), num.end());
    return num;
} 

int main(){

    init(); //Initialize the machine code before beginning

    int ilc=0;  //instrn location counter
    int base=0;
    //Read the input file
    ifstream file;
    file.open ("input.txt");
    if (!file.is_open()){
        cout<<"ERROR!: could not open file"<<endl;
        return 0;
    }

    //PASS1
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        vector<string> v;
        v.clear();
        vector<string> words=split(line, v, ' ');
        for(auto &word: words){
            if(word[word.size()-1]==':'){    //LABEL FOUND
                cout<<"Label Found"<<endl;
                Symbol* symbol=new Symbol();
                word.pop_back();
                SYMBOL_TABLE.pb(mp(word, ilc+1+base));
                cout<<"wrote in "<<word<<endl;
            }
        
        }
        ilc++;
    }
    file.close();

    //PASS 2
    ifstream infile;
    infile.open ("input.txt");
    ofstream outfile;
    outfile.open("otput.txt", ios::out | ios::trunc);

    if (!infile.is_open()){
        cout<<"ERROR! couldnt open input.txt";
        return 0;
    }
    if(!outfile.is_open()){
        cout<<"ERROR! couldnt open output.txt";
        return 0;
    }
    string word;
    while (infile >> word)
    {
        bool found=false;
        string r1,r2,r3;
        int imm_num;
        if(word[word.size()-1]==':'){
            outfile<<endl;
            continue;
        }
        cout<<word<<endl;
        //find the inst in mot
        for(auto &e: mot){
            if(e.name==word){
                found=true;
                outfile<<e.bincode<<" ";
                if(e.format==32){
                    infile>>word;
                    r1=word;
                    outfile<<getRegCode(r1)<<" ";
                    infile>>word;
                    imm_num=stoi(word);
                    outfile<<decToBinary(imm_num)<<endl;
                }
                else if(e.format==31){
                    infile>>word;
                    r1=word;
                    outfile<<getRegCode(r1)<<" ";
                    infile>>word;
                    r2=word;
                    outfile<<getRegCode(r2)<<endl;
                }
                else if(e.format==42){
                    infile>>word;
                    r1=word;
                    infile>>word;
                    r2=word;
                    infile>>word;
                    imm_num=stoi(word);
                    outfile<<getRegCode(r1)<<" "<<getRegCode(r2)<<" "<<decToBinary(imm_num)<<endl;
                }
                else if(e.format==41){
                    infile>>word;
                    r1=word;
                    infile>>word;
                    r2=word;
                    infile>>word;
                    r3=word;
                    outfile<<getRegCode(r1)<<" "<<getRegCode(r2)<<" "<<getRegCode(r3)<<endl;
                }
                else if(e.format==11){
                    infile>>word;
                    r1=word;
                    outfile<<getRegCode(r1)<<endl;
                }
                else if(e.format==10){
                    continue;
                } 
                else if(e.format==00){
                    infile>>word;
                    cout<<"looking for label "<<word<<endl;
                    bool found_sym=false;
                    //search for the word in symbol table
                    for(auto &sym:SYMBOL_TABLE){
                        if(sym.fi==word){
                            found_sym=true;
                            outfile<<decToBinary(sym.se);
                            break;
                        }
                    }
                    if(found_sym==false){
                        cout<<"ERROR!!NO SUCH LABEL FOUND! EXITING...";
                        return 0;
                    }
                } 
            }
            

        }
        if(!found){
            cout<<word<<" ";
            cout<<"INVALID INSTRUCTION!!! EXITING..."<<endl;
            return 0;
        }
    }
    infile.close();
    outfile.close();

    return 0;
}