all: Client.c Server.c
	make servidor
	make cliente
	make clear

servidor: Client.c
	gcc Client.c -o Client

cliente: Server.c
	gcc Server.c -o Server


remove:
	rm -f Server
	rm -f Client
