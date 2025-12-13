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

/** @file timer.cppm 
 * @brief Module partition interface file for the timer module in the sdl2-cppm library.
 * @details This file contains the timer class. */
module;

export module sdl2:timer;
import std;

using std::shared_ptr;
using std::uint32_t;

namespace sdl2 {

export class Sdl;

/** This class is responsible for timing functionality.
 * It is constructed via Sdl::timer(). */
export class Timer {
	private:
		shared_ptr<const Sdl> sdl;
		friend class Sdl;

		/** Private constructor. Sdl::timer() calls this. */
		Timer(shared_ptr<const Sdl> sdl);
	public:

		/** Returns the number of milliseconds since the 
		 * initialization of the SDL session. */
		uint32_t ticks() const;
		~Timer();
};

}
