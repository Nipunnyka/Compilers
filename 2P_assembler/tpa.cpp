#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first


using namespace std;

/*
    32 = reg reg imm. addr.
    31 = reg reg reg
    22 = reg imm.
    21  = reg reg
    11   = add
    10   = zero
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
	mot[1] = {"ADDI","00000010",32};
	mot[2] = {"CMP","00000011",22};
	mot[3] = {"INC","00000100",11};
	mot[4] = {"JEQ","00000101",11};
	mot[5] = {"JMP","00000110",11};
	mot[6] = {"LOAD","00000111",21};
	mot[7] = {"LOADI","00001000",32};
	mot[8] = {"MVI","00001001",32};
	mot[9] = {"MOV","00001010",21};
	mot[10] = {"HLT","00001011",10};
	mot[11] = {"STORE","00001100",21};
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
            }
        
        }
        ilc++;
    }
    file.close();

    for(auto&e: SYMBOL_TABLE){
        cout<<e.fi<<": "<<e.se<<endl;
    }
    
    return 0;
}