#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
int main(){

    struct rlimit limit;
    getrlimit(RLIMIT_NPROC,&limit);
    printf("the limit is : %u",(unsigned int)  limit.rlim_max );
    return 0;
}
     