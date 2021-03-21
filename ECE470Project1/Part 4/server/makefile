all:server

server: smartHomeServer.cpp server_marshal.h tcp_server.h smartHomeServer.h datamodel.h
	g++-7 -g smartHomeServer.cpp -o server

clean:
	rm server
