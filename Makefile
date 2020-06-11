#usage:
#make  #compile all the binary 
#make clean #clean all the trash 

CC = clang
CFLAG = -g -Wall



client: client.cpp
	${CC} -o user ${CFLAG} client.cpp

server: server.cpp
	${CC} -o lamb ${CFLAG} server.cpp

clean:
	@echo "Clean all the garbarge"
	rm -rf user lamb
	rm -rf *.dSYM

