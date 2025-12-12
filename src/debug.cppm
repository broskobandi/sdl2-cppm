module;

export module sdl2:debug;
import std;

#ifndef NDEBUG
constexpr bool g_debug {true};
#else
constexpr bool g_debug {false};
#endif

using std::runtime_error;
using std::string;

namespace sdl2 {

void dbg(const string& msg);
runtime_error err(const string& msg);
string get_error();

}
