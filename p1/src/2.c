#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
int main(){

    struct rlimit limit;
    getrlimit(RLIMIT_NPROC,&limit);
    __uid_t uid = getuid();
    printf("el limite de procesos activos del usuario %s (uid : %u) es: %u \n\n",getpwuid(uid)->pw_name, uid ,(unsigned int)  limit.rlim_max );
    return 0;
}
     