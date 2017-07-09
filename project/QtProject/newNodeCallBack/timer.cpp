#include <stdlib.h>
#include <sys/time.h>
void timer(void)
{
    struct itimerval val;
    val.it_value.tv_sec = 1;
    val.it_value.tv_usec = 0;
    val.it_interval = val.it_value;
    setitimer(ITIMER_REAL, &val, NULL);
}
