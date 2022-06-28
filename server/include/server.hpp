#ifndef __SERVER_HPP__
    #define __SERVER_HPP__

// Create Server
int start_server(void);

// Connect server and client together
int connect_server(int socket_server);

// Loop talking to client (if connection keep alive)
void relation_client(int socket_client);
// Read message from client
void read_message(int socket_client);
// Send Response to request
void send_message(int socket_client);

#endif
