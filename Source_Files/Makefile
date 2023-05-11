server: server.o files.o users.o utils.o
	gcc -pthread -g server.o files.o users.o utils.o -o server

client: client.o files.o users.o utils.o
	gcc -g client.o files.o users.o utils.o -o client

# local: local.o files.o users.o utils.o
# 	gcc -g local.o files.o users.o utils.o -o local

client.o: client.c
	gcc -Wall -g -c client.c

server.o: server.c
	gcc -Wall -g -c server.c

# local.o: local.c
# 	gcc -Wall -g -c local.c

files.o: files.c
	gcc -Wall -g -c files.c

users.o: users.c
	gcc -Wall -g -c users.c

utils.o: utils.c
	gcc -Wall -g -c utils.c

clean:
	rm -f *.o local server client

run_server:
	./server 12345

run_client:
	./client 12345

debug_server:
	gdb --args ./server 12345

debug_client:
	gdb --args ./client 12345