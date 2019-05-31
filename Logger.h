/*
 * Copyright (c) 2019 Eleobert Espírito Santo eleobert@hotmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>


class Log
{
public:
    enum class Level
    {
        verbose,
        debug,
        info,
        warning,
        error
    };

private:
    std::ofstream file;
    std::stringstream buffer;
    std::string name;
    std::mutex m;

#ifdef _WIN32
    HANDLE console;
    WORD oldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
#endif

    Level filterLevel;
    bool consoleOutput = false;

    time_t rawTime;
    struct tm* timeinfo;
    char timeBuffer[25];

    void updateTimeBuffer();

    template<typename ...Args>
    void fillBuffer   (const Args& ...args);


public:
    Log();
    explicit Log(const std::string& filename);
    Log(Log &&log) noexcept;
    Log(const Log&) = delete;

    ~Log();

    Log& operator=(const Log&) = delete;
    Log& operator=(Log&& log) noexcept;

    std::string filename() { return name; }
    bool isOpen() noexcept { return file.is_open(); }

    void printstd(bool b) noexcept{consoleOutput = b;};
    void filter(Level level) noexcept { this->filterLevel = level; }

    void open(const std::string& filename);
    void close();

    template<typename... Args>
    void verbose(const Args&... args);  //normal
    template<typename... Args>
    void info(const Args&... args);     //green
    template<typename... Args>
    void debug(const Args&... args);    // blue
    template<typename... Args>
    void warning(const Args&... args);  //yellow
    template<typename... Args>
    void error(const Args&... args);    //red
};


template<typename... Args>
void Log::verbose(const Args&... args)
{
    if(filterLevel > Level::error)
    {
        return;
    }
    std::lock_guard<std::mutex> guard(m);

    updateTimeBuffer(); 
    file << '[' << timeBuffer << "] [verbose] ";
    fillBuffer(args...);
    file << buffer.str() << '\n';
    if(consoleOutput)
    {
        std::cout << '[' << timeBuffer << "] [verbose] " << buffer.str() << '\n';
    }
    buffer.str(std::string());
}


template<typename... Args>
void Log::info(const Args&... args)
{
    if(filterLevel > Level::error)
    {
        return;
    }
    std::lock_guard<std::mutex> guard(m);

    updateTimeBuffer(); 
    file << '[' << timeBuffer << "] [info   ] ";
    fillBuffer(args...);
    file << buffer.str() << '\n';
    if(consoleOutput)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(console, 10);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\x1B[33m";
#endif
        std::cout << '[' << timeBuffer << "] [info   ] " << buffer.str() << '\n';
#ifdef _WIN32
        SetConsoleTextAttribute ( console, oldColorAttrs);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\033[0m";
#endif
    }
    buffer.str(std::string());
}


template<typename... Args>
void Log::debug(const Args&... args)
{
#ifndef NDEBUG
    if(filterLevel > Level::error)
    {
        return;
    }
    std::lock_guard<std::mutex> guard(m);

    updateTimeBuffer(); 
    file << '[' << timeBuffer << "] [debug  ] ";
    fillBuffer(args...);
    file << buffer.str() << std::endl;
    if(consoleOutput)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(console, 9);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\x1B[34m";
#endif
        std::cout << '[' << timeBuffer << "] [debug  ] " << buffer.str() << std::endl;
#ifdef _WIN32
        SetConsoleTextAttribute ( console, oldColorAttrs);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\033[0m";
#endif
    }
    buffer.str(std::string());
#endif //NDEBUG
}


template<typename... Args>
void Log::warning(const Args&... args)
{
    if(filterLevel > Level::error)
    {
        return;
    }
    std::lock_guard<std::mutex> guard(m);

    updateTimeBuffer(); 
    file << '[' << timeBuffer << "] [warning] ";
    fillBuffer(args...);
    file << buffer.str() << '\n';
    if(consoleOutput)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(console, 14);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\x1B[93m";
#endif
        std::cout << '[' << timeBuffer << "] [warning] " << buffer.str() << '\n';
#ifdef _WIN32
        SetConsoleTextAttribute ( console, oldColorAttrs);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\033[0m";
#endif
    }
    buffer.str(std::string());
}


template<typename... Args>
void Log::error(const Args&... args)
{
    std::lock_guard<std::mutex> guard(m);

    updateTimeBuffer(); 
    file << '[' << timeBuffer << "] " << "[error  ] ";
    fillBuffer(args...);
    file << buffer.str() << std::endl;
    if(consoleOutput)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(console, 4);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\x1B[31m";
#endif
        std::cout << '[' << timeBuffer << "] [error  ] " << buffer.str() << std::endl;
#ifdef _WIN32
        SetConsoleTextAttribute ( console, oldColorAttrs);
#elif defined(__unix__) || defined(__APPLE__)
        std::cout << "\033[0m";
#endif
    }
    buffer.str(std::string());
}



template<typename ...Args>
void Log::fillBuffer(const Args& ...args) {
    (void)std::initializer_list<int>{(buffer << args, 0)...};
}
