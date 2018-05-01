To run the program:
    I have included a makefile in this folder. Simply type the command make to compile and 
    to run the code type the command ./blockchain
    
Intro to blockchain and other preliminaries:
        Blockchains are secure chains of nodes that that are hashed using a cryptographic
    hashing algorithm. In the financial market, they are typically used as a public ledger 
    to keep track of transactions between various individuals in a variety of currencies 
    (Peters, Panayi, & Chapelle, 2015, p. 5). The most famous of such currencies being Bitcoin. 
    One of the unique benefits of using blockchain technology is that once entered, information
    cannot be removed or destroyed. In the application of Bitcoin, this property allows for a 
    verifiable record of each transaction that is made (Crosby, Nachiappan, Pattanayak, & 
    Kalyanaraman, 2016, p. 9).
        A huge part of creating a cryptocurrency such as Bitcoin is the process of mining a 
    block. The creation of blocks allows for the verification of transactions as they occur. 
    Each in the case of Bitcoin, each block will contain the transaction information for the 
    transactions that occurred over 10-minute intervals (Peters, Panayi, & Chapelle, 2015,
    p. 16). With this in mind, there is a set difficulty level that prevents just anyone from
    being able to mine a block. Being able to mine a block “requires specialized equipment, as 
    well as substantial electricity costs” (Peters, Panayi,& Chapelle, 2015, p. 16). Higher 
    difficulties will make it more challenging and time consuming to mine a block.
        In this project, we aim to implement a basic blockchain. We will use this simple 
    blockchain to demonstrate how higher-level difficulties of mining will affect the runtime 
    of creating a new block. We will also try and demonstrate why block chains are so secure 
    and why they are a good fit for cryptocurrency. 

    
What to expect:
    When you run the program, depending on the set difficulty level, it may take some 
    time to run. We recommend initially running the program on a difficulty level between
    3 and 6. Once the program completes its run, it will print out each block and its 
    contents. We have set the main function to only generate 3 blocks, but you can change 
    this as you please. Note that the time it takes to mine each block will vary and mostly 
    depends on the preset difficulty level.
  
  
Design choice:
    In most blockchain blockchain programs, programmers typically choose to hash to hexidecimal;
    however, in our program, we chose to hash to base 10. Furthermore, when we hash each block, we
    call the built in hash function in C++. Additionally, when we set the difficulty, it 
    corresponds to the number of 1's we'd like to see in the first few digits of the hash value. 
    This varies from many tutorials, where programmers may choose to count the number of 0's instead.
    
    
Overall structure:
    The majority of this program is based on the Block and BlockChain classes:
    
        To keep track of the attributes of each block, we created a Block class. This class will 
    store the public variables that each block’s hash depends on: timestamp, data, and the 
    previous hash, and a nonce variable. The timestamp will hold the current time to ensure the
    uniqueness of a hash. The data will be a string that is designated in the main program. The 
    previous hash is obtained at the instantiation of a new block. Finally, the nonce variable 
    is used in the process of mining.
    
        The BlockChain class is mainly comprised of a vector of Blocks from the Block class. It 
    also contains functions to add new blocks as well as receive information on the previous 
    block. Most importantly, it holds the current difficulty level that we desire for the mining
    process. When theBlockChain class is initially called, it creates a new block with previous 
    hash value of 0. This block is then mined and pushed onto the vector.
        After the first block has been added to the chain, the addBlock function will be called
    to create and add each subsequent block to the chain. This addBlock function takes in the 
    data to be mined. Given this information, the function will call the constructor of the Block 
    class with this data and the previous block’s hash to get a new block. This block will then 
    be mined and finally pushed onto the vector of blocks.
    
        As previously mentioned, the most important/influential attribute of the BlockChain class 
    is the value of the difficulty. This value is important in the process of mining a new Block
    as it determines the sort of specificity we are looking for in our hash. In our 
    implementation, the difficulty corresponds to the number of 1’s we desire to obtain in the 
    first few digits of our hash. In order to make sure we are receiving a hash value that obeys 
    the difficulty level, we have created a mineBlock function. This function primarily consists 
    of a do while loop which will run as long as the current hash does not meet the requirements 
    specified by the difficulty. The idea is that the higher the difficulty, the more time will 
    be spent in the mineBlock function, and therefore the longer it will take to mine a block.
    
    
Future Goals:
    Below is a list of future goals or ideas we would explore in the future:
        1. As previously mentioned, this is a simplified implementation of a BlockChain. Perhaps 
           in the future, we would want to make this into a database. Then, we could see how 
           different computers mine blocks, and how the blockchain would handle multiple users.
        2. We could consider implementing mining rewards. Currently, those that mine blocks for 
           applications such as Bitcoin recieve some sort of incentive/reward. It would be 
           interesting to add this as a feature in our code.
        3. We could work on applying this to financial transactions. As previously mentioned, 
           many cryptocurrencies use blockchains to keep track of transaction records. This is 
           something that we could consider using our program to complete. For example, a user 
           could input information on what they want to buy and how much it costs, then the 
           process of mining a block would begin.
    
Bibliography:

Crosby, M., Nachiappan, Pattanayak, P., & Kalyanaraman, V. (2016). BlockChain Technology: 
        Beyond Bitcoin. Applied Innovation Review,(2), 6-19. Retrieved from 
        http://scet.berkeley.edu/wp-content/uploads/AIR-2016-Blockchain.pdf

Peters, G. W., Panayi, E., & Chapelle, A. (2015). Trends in Crypto-Currencies and Blockchain 
        Technologies: A Monetary Theory and Regulation Perspective. SSRN Electronic Journal,
        3(3), 1-43. doi: 10.2139/ssrn.2646618

        