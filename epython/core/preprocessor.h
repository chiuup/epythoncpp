#pragma once
#define CORE_STRINGIZE(a) #a
#define CORE_CAT(a,b) a ## b

#define CORE_SELECT( NAME, NUM ) CORE_CAT( NAME ## _, NUM )
#define CORE_SELECT_EVAL(NAME, NUM) CORE_SELECT(NAME, NUM)

#define CORE_EXPAND(X) X    // for MSVC10 compatibility

// compute number of (variadic) macro arguments
// from http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5?pli=1
#define CORE_PP_ARG_N(_1, _2, _3, _4, _5, _6, N, ...) N
#define CORE_PP_RSEQ_N() 6, 5, 4, 3, 2, 1, 0
#define CORE_PP_NARG_(...) CORE_EXPAND( CORE_PP_ARG_N(__VA_ARGS__) )
#define CORE_PP_NARG(...) CORE_EXPAND( CORE_PP_NARG_(__VA_ARGS__, CORE_PP_RSEQ_N()) )

#define CORE_VA_SELECT(NAME, ...) CORE_EXPAND(CORE_SELECT_EVAL(NAME, CORE_EXPAND(CORE_PP_NARG(__VA_ARGS__)))(__VA_ARGS__))