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

# run_local:
# 	./local utils.csv

run_server:
	./server 12354

run_client:
	./client 12354

# debug_local:
# 	gutils --args ./local utils.csv

debug_server:
	gutils --args ./server 12345

debug_client:
	gutils --args ./client 12345