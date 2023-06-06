# File Transfer Protocol (FTP) Server
This project is a simple FTP server implemented in C using TCP socket programming. The server allows clients to connect and transfer files to and from the server.

## Getting Started
To start the server, run the command `make server`. 
To run the server, use the command `make run_server`. 

To start the client, run the command `make client`. 
To run the client, use the command `make run_client`. 

The server accepts requests from clients and also reads commands from the server's STDIN. It will continue running until it receives the "exit" command from the STDIN.

The client can send unlimited requests to the server, as long as the "exit" command is not entered. Before accessing the server, clients are required to authenticate by providing a username and password. Once authenticated, clients can send and receive files to and from the server.

## User Manual
- `get files list`: Retrieves a list of all available files in the "server_public_files" directory.
- `upload file`: Uploads a file from the client to the server's public folder.
- `download file`: Downloads a file from the server's "server_public_files" directory to the client, saving it in the "client_public_files" directory.
- `exit`: Exits and ends the socket connection.

Both the client and the server use the same flexible functions to handle file transfers. The server logs all connections, login attempts, and file transfers.

To clean all object files, use the command `make clean`.