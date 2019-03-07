
#ifdef WIN32

#include <windows.h>
double getTime()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
}

void limparTela()
{
    system("cls");
}

#else

#include <sys/time.h>
#include <sys/resource.h>
double getTime()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

void limparTela()
{
    system("clear");
}

#endif
