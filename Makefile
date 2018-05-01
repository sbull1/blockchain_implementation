all: blockchain

blockchain: blockchain.o 
	g++ blockchain.o -std=c++11 -o blockchain

blockchain.o: blockchain.cpp 
	g++ -c blockchain.cpp -std=c++11

clean:
	rm -rf *.o blockchain
