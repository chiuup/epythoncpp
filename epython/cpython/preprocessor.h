#pragma once
#define STRINGIZE(a) #a
#define CAT(a,b) a ## b

#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
#define SELECT_EVAL(NAME, NUM) SELECT(NAME, NUM)

#define EXPAND(X) X    // for MSVC10 compatibility

// compute number of (variadic) macro arguments
// from http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5?pli=1
#define PP_NARG(...) EXPAND( PP_NARG_(__VA_ARGS__, PP_RSEQ_N()) )
#define PP_NARG_(...) EXPAND( PP_ARG_N(__VA_ARGS__) )
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, N, ...) N
#define PP_RSEQ_N() 6, 5, 4, 3, 2, 1, 0

#define VA_SELECT(NAME, ...) EXPAND(SELECT_EVAL(NAME, EXPAND(PP_NARG(__VA_ARGS__)))(__VA_ARGS__))