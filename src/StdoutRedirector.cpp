#include "StdoutRedirector.h"
#include "unistd.h"
#include <cstdio>
#include <fcntl.h>
#include <stdexcept>

bool StdoutRedirector::isRedirecting = false;
int StdoutRedirector::oldStdout = 0;

void StdoutRedirector::redirectStdout(bool redirect)
{
    // Turn on redirecting stdout
    if (redirect) {
        if (isRedirecting) {
            throw std::runtime_error("Already redirecting. Don't call it twice.");
        }
        fflush(stdout);
        oldStdout = dup(1);
        int newTarget = open("/dev/null", O_WRONLY);
        dup2(newTarget, 1);
        close(newTarget);
        isRedirecting = true;
    }
    // Turn off redirecting stdout
    else {
        if (!isRedirecting) {
            throw std::runtime_error("Don't turn off redirecting twice.");
        }
        fflush(stdout);
        dup2(oldStdout, 1);
        close(oldStdout);
        isRedirecting = false;
    }
}
