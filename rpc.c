//sudo apt-get install rpcbind 
//rpcinfo                                                         
//add.x 
/*combine the arguments to be passed to the server side in a structure*/
struct numbers{
int a;
int b;
};
program ADD_PROG{
version ADD_VERS{
int add(numbers)=1;
}=1;
}=0x4562877;
//rpcgen -a -C add.x  
//Edit add_server.c
#include "add.h"
int *add_1_svc(numbers *argp, struct svc_req *rqstp) {
static int result;
printf("add(%d, %d) is called\n", argp->a, argp->b);
result = argp->a + argp->b;
return &result;
}
//Edit add_client.c
#include "add.h"
void add_prog_1(char *host, int x, int y) {
CLIENT *clnt;
int *result_1;
numbers add_1_arg;
#ifndef DEBUG
clnt = clnt_create(host, ADD_PROG, ADD_VERS, "udp");
if (clnt == NULL) {
clnt_pcreateerror(host);
exit(1);	
}
#endif /* DEBUG */
add_1_arg.a = x;
add_1_arg.b = y;
result_1 = add_1(&add_1_arg, clnt);
if (result_1 == (int *)NULL) {
clnt_perror(clnt, "call failed");
} else {
printf("Result: %d\n", *result_1);
}
#ifndef DEBUG
clnt_destroy(clnt);
#endif /* DEBUG */
}
int main(int argc, char *argv[]) {
char *host;
if (argc < 4) {
printf("usage: %s server_host\n", argv[0]);
exit(1);
}
host = argv[1];
add_prog_1(host, atoi(argv[2]), atoi(argv[3]));
exit(0);
}
//make -f Makefile.add
//Server
//Sudo ./add_server
//Client
//Sudo ./add_client localhost 3 2
                   


