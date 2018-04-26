//
//  main.c
//  xpcservicedemo
//
//  Created by Robin Hack on 26/04/2018.
//  Copyright © 2018 Robin Hack. All rights reserved.
//

#include <xpc/xpc.h>

int main(int argc, const char * argv[])
{
    xpc_connection_t conn = xpc_connection_create_mach_service("com.marmolak.xpcservicedemo-server", NULL, 0);
    xpc_object_t message = xpc_dictionary_create(NULL, NULL, 0);
    xpc_connection_set_event_handler(conn, ^(xpc_object_t object) {});
    xpc_connection_resume(conn);
    
    xpc_dictionary_set_string(message, "s", "!!!!!!\n\n");
    xpc_connection_send_message_with_reply(conn, message, dispatch_get_main_queue(),
                                           ^(xpc_object_t object) {});
    
    return (EXIT_SUCCESS);
}
