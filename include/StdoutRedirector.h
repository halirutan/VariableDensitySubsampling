#pragma once
#include <cstdio>

/**
 * Provides a way to temporarily redirect stdout into the nirvana to silence printf messages in the library code.
 * Note that this (probably) only silences printf calls and not C++ output with cout.
 */
class StdoutRedirector
{
public:
    /**
     * Turn on/off redirection of stdout. This function call should always come on pairs
     * where you must not forget to turn redirection off after your done.
     *
     * @param redirect Turn on (true) or off (false)
     *
     * @note
     */
    static void redirectStdout(bool redirect);

    StdoutRedirector(const StdoutRedirector &) = delete;
    StdoutRedirector &operator=(const StdoutRedirector &) = delete;
    StdoutRedirector(StdoutRedirector &&) = delete;
    StdoutRedirector &operator=(StdoutRedirector &&) = delete;

private:
    StdoutRedirector() = default;
    static bool isRedirecting;
    static int oldStdout;
};