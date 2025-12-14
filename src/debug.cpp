/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** @file debug.cpp
 * @brief Module implementation for the debug module partition. */

module;

#include <SDL2/SDL_error.h>

module sdl2;
import :debug;

using std::println;
using std::string;
using std::runtime_error;

namespace sdl2 {

/** Prints a debug message unless the library was compiled with NDEBUG
 * @param msg The debug message to be prented. */
void dbg(const string& msg) {
	if (g_debug) println("{}", msg);
}

/** Returns a retuntime_error that contains the provided error message 
 * and SDL error information if available.
 * @param msg The error message to be printed. */
runtime_error err(const string& msg) {
	return runtime_error(msg + get_error());
}

/** Returns a string that contains the return value of SDL_GetError() */
string get_error() {
	return string(SDL_GetError());
}

}
