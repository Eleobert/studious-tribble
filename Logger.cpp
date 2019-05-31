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

#include "Logger.h"
#include <cassert>
#include <ctime>
#include <iostream>
#include <sstream>



Log::Log(const std::string& filename): filterLevel(Log::Level::verbose)
{
    file.exceptions(std::ofstream::failbit);
    this->open(filename);
#ifdef _WIN32
	console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &csbInfo);
    oldColorAttrs = csbInfo.wAttributes;
#endif
}

Log::Log(Log&& log) noexcept
{
    *this = std::move(log);
}

Log& Log::operator=(Log&& log) noexcept
{
    file = std::move(log.file);
    buffer = std::move(log.buffer);
    name = std::move(log.name);
#ifdef _WIN32
    console = log.console;
    oldColorAttrs = log.console;
    csbInfo = log.csbInfo;
#endif
    filterLevel = log.filterLevel;
    consoleOutput = log.consoleOutput;
    return *this;
}

Log::Log(): filterLevel(Log::Level::verbose)
{
    file.exceptions(std::ofstream::failbit);

}

Log::~Log()
{
    this->close();
}

void Log::updateTimeBuffer()
{
    std::time(&rawTime);
    timeinfo = localtime(&rawTime);
    std::strftime(timeBuffer, sizeof(timeBuffer), "%d-%m-%Y %I:%M:%S", timeinfo);
}


void Log::open(const std::string& filename)
{
    assert(isOpen() == false);
    file.open(filename);
    this->name = filename;
}

void Log::close()
{
    if(!file.is_open())
    {
        return;
    }
    std::lock_guard<std::mutex> guard(m);
    updateTimeBuffer();

    file << '[' << timeBuffer << ']' << " Log finished";
    if(consoleOutput)
    {
        std::cout << '[' << timeBuffer << ']' << " Log finished\n";
    }

    file.close();
}
