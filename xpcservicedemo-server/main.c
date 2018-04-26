#include <xpc/xpc.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
    xpc_connection_t listener =
    xpc_connection_create_mach_service("com.marmolak.xpcservicedemo-server", NULL, XPC_CONNECTION_MACH_SERVICE_LISTENER);
    
    xpc_connection_set_event_handler(listener, ^(xpc_object_t peer)
    {
        xpc_connection_set_event_handler(peer, ^(xpc_object_t event)
        {
            xpc_type_t type = xpc_get_type(event);
            assert(type == XPC_TYPE_DICTIONARY);
            const char *s = xpc_dictionary_get_string(event, "s");
            FILE *fd = fopen("/tmp/lala", "w");
            fwrite(s, strlen(s), 1, fd);
            fclose(fd);
        });
        xpc_connection_resume(peer);
    });
    
    xpc_connection_resume(listener);
    
    dispatch_main(); // never returns
    exit(EXIT_FAILURE);
}
