/* Programmers: Shannon B., Lucas M., Ben S.
 * Date:        May 1, 2018
 * File Name:   blockchain.cpp
 * Description: The following is an implementation of a blockchain. For further documentation,
 *              see the README.txt
 */


#include <iostream>
#include <time.h>
#include <string>
#include <math.h>
#include <vector>
#include <limits>
#include <chrono>


using namespace std;

//Block class will hold an individual block 
class Block{
public:
    //the following three attributes are used to hash
    //a block. As you will see in the getHash function, 
    //they will be converted to strings
    long timeStamp;    
    string data;
    int nonce;
    
    //the following two functions are used in the hashing!
    size_t hashDiv(size_t k, size_t m);
    size_t stringToInt(std::string s);


    size_t prevHash;
    size_t currHash;
    size_t getHash();
    Block(string dta, size_t pHash);
    void mineBlock(size_t difficulty);
    double timeMine;
};


class BlockChain{
public:
    BlockChain();
    void addBlock(string data);
    void printChain();
    bool isValid();

    //the following is the vector that will hold all of our blocks,
    //and essentially represent our BlockChain
    vector<Block> vect;  
    
    size_t difficulty;
    void changeData(int, string);
    
    Block getlastblock(){
     return vect.back();   
     };
    
};



//Block object Constructor
//Data in:     The string of data the user wants to enter as well as the previous Block's hash
//Data out:    None.
//Description: This constructor will go through the process of creating a new Block.
//             to do this, it will assign the data and previous hash, then call
//             the getHash function to determine the current hash.
Block :: Block(string dta, size_t pHash){

    data = dta;
    prevHash = pHash;
    nonce = 0;
    timeStamp = static_cast<long int>(time(0));
    currHash = getHash();
}

//getHash function
//Data in:     None.      
//Data out:    A size_t integer corresponding to a hash
//Description: Calculates hash and returns it 
size_t Block :: getHash(){

    // if nonce wrapped around and checked every negative number, update time stamp to avoid infinite loop
    if(nonce == -1){ 
       timeStamp = static_cast<long int>(time(0)); 
    }
    
    // creates a string of the data, time stamp, previous hash, and nonce
    string input = (data + to_string(timeStamp) + to_string(prevHash) + to_string(nonce)); 
    
    
    size_t numVal, numHash;

    
    hash<string> h; // C++ standard hash
    numHash = h(input); // hashes to integer
        
    return numHash;
}

//mineBlock function
//Data in:     The current difficulty level.      
//Data out:    None.
//Description: Mines a Block using a proof of work algorithm. Essentially, it will
//             continually hash the block's content until it has the appropriate amount
//             of 1's in the first digits. This required number is given by the difficulty.
void Block:: mineBlock(size_t diff)
{
    string goal= "";
    for(int i=0; i<diff; i++)
    {
        goal+="1";
    } // the number of 1s at beginning of hash for it to be valid
    
    
    auto start = std::chrono::system_clock::now();
    
    string stringhash;
    
    do // keep rehashing while incrementing nonce until desired number of ones is at beginning of hash
    {
        nonce++;
        currHash = getHash();
        stringhash = to_string(currHash);
        
    }
    while(stringhash.substr(0,diff)!=goal);
    //breaks up string to see if the correct number of 1 is at the begining of hash
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    
    timeMine = elapsed_seconds.count();
    
    
    std::cout << "Block has been mined \n";    
}



//Block Chain Constructor
BlockChain :: BlockChain()
{
    difficulty = 4;     //number of ones required at beggining of the hash of each block
     
    Block input("SORT THESE NUMBERS!",0);// create,mine,and place genesis block in block chain, always hard coded
    input.mineBlock(difficulty);
    vect.push_back(input);
}

//changeData function
//Data in:     The block number you want to change and the new string of data you would like
//             to place inside it.
//Data out:    None.
//Description: This function is used to tamper with the data.
void BlockChain :: changeData(int index, string newData )
{
    vect[index].data = newData;
    vect[index].mineBlock(difficulty);
}


//addBlock function
//Data in:     The string corresponding to the data to be entered into the new block      
//Data out:    None.
//Description: Adds a new block to the chain and then mines this block.
void BlockChain :: addBlock(string data) // Adds a new block to the chain
{
    
    Block input(data, getlastblock().currHash); //mines new block and puts it on the end of the block chain
    input.mineBlock(difficulty);
    vect.push_back(input);
}


//isValid function
//Data in:     None.     
//Data out:    True if the chain is valid, false otherwise.
//Description: Checks to see if block chain is valid by making sure the
//             currenthash of a previous block matches the prevHash value.
//             This is repeated for each block.
bool BlockChain::isValid(){ 
    int size = vect.size();
  
       for(int i = 1; i < size; i++){

        //If data has been tampered with, return false.
         if(vect[i].currHash!=vect[i].getHash()){
            return false;
         } 
         
         if(vect[i].prevHash!=vect[i-1].getHash()){
            return false;
         }
           
       }
       
       return true; // Return true if data has not been tampered with
    
}


//printChain function
//Data in:     None.     
//Data out:    None.
//Description: This function will print out the attributes of each block in the chain.
void BlockChain:: printChain(){
    int size = vect.size();
    
    std::cout << "\nThe Block Chain....\n\n";
    
    for(int i = 0; i < size; i++){
     std::cout<<"   Block " << i+1 << " {\n";
     std::cout<<"       Data         : " << vect[i].data << "\n";
     std::cout<<"       TimeStamp    : " << vect[i].timeStamp << "\n";
     std::cout<<"       Nonce        : " << vect[i].nonce<<"\n";
     std::cout<<"       Hash         : " << vect[i].currHash << "\n";
     std::cout<<"       Previous Hash: " << vect[i].prevHash<<"\n"; 
     std::cout<<"       Time to Mine : " <<vect[i].timeMine<<"\n";
     std::cout<<"   }\n\n";
    }
    
}



int main()
{

    BlockChain ourChain;
    
    
    
    ourChain.addBlock("Mining the second block");
    ourChain.addBlock("Mining the third block");
    ourChain.printChain();
    
    
    if(ourChain.isValid() == false){
        cout<< "Chain has been tampered with!\n";
    }else{
     cout<<"Chain is valid!\n";   
    }

    //to test what happens when data is corrupted, remove the following comment:
    /*
    ourChain.changeData(0,"Dont sort these numbers");
    
    
    if(ourChain.isValid() == false){
        cout<< "Chain has been tampered with!\n";
    } else{
     cout<<"Chain is valid!\n";   
    }
    
    
     
     ourChain.printChain(); 
     */
     
     // DISCUSS HOW HASH OF FIRST ONE DOES NOT MATCH UP WITH THE PREVIOUS HASH OF THE SECOND ONE, 
     //SO TAMPERER MUST RE MINE ALL BLOCKS PLUS THE NEW ONE BEFORE ONE PERSON MINES JUST THE NEW ONE
     
    
    return 0;
}
