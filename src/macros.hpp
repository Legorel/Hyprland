#pragma once

#include "helpers/MiscFunctions.hpp"
#include "debug/Log.hpp"
#include <cmath>
#include <csignal>
#include <utility>

#ifndef NDEBUG
#ifdef HYPRLAND_DEBUG
#define ISDEBUG true
#else
#define ISDEBUG false
#endif
#else
#define ISDEBUG false
#endif

// git stuff
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "?"
#endif
#ifndef GIT_BRANCH
#define GIT_BRANCH "?"
#endif
#ifndef GIT_COMMIT_MESSAGE
#define GIT_COMMIT_MESSAGE "?"
#endif
#ifndef GIT_DIRTY
#define GIT_DIRTY "?"
#endif
#ifndef GIT_TAG
#define GIT_TAG "?"
#endif

#define SPECIAL_WORKSPACE_START (-99)

#define PI 3.14159265358979

#define STRVAL_EMPTY "[[EMPTY]]"

#define LISTENER(name)                                                                                                                                                             \
    void               listener_##name(wl_listener*, void*);                                                                                                                       \
    inline wl_listener listen_##name = {.notify = listener_##name}
#define DYNLISTENFUNC(name)    void listener_##name(void*, void*)
#define DYNLISTENER(name)      CHyprWLListener hyprListener_##name
#define DYNMULTILISTENER(name) wl_listener listen_##name

#define VECINRECT(vec, x1, y1, x2, y2) ((vec).x >= (x1) && (vec).x <= (x2) && (vec).y >= (y1) && (vec).y <= (y2))

#define DELTALESSTHAN(a, b, delta) (abs((a) - (b)) < (delta))

#define STICKS(a, b) abs((a) - (b)) < 2

#define HYPRATOM(name)                                                                                                                                                             \
    { name, 0 }

#define RASSERT(expr, reason, ...)                                                                                                                                                 \
    if (!(expr)) {                                                                                                                                                                 \
        Debug::log(CRIT, "\n==========================================================================================\nASSERTION FAILED! \n\n{}\n\nat: line {} in {}",            \
                   getFormat(reason, ##__VA_ARGS__), __LINE__,                                                                                                                     \
                   ([]() constexpr->std::string { return std::string(__FILE__).substr(std::string(__FILE__).find_last_of('/') + 1); })());                                         \
        printf("Assertion failed! See the log in /tmp/hypr/hyprland.log for more info.");                                                                                          \
        raise(SIGABRT);                                                                                                                                                            \
    }

#define ASSERT(expr) RASSERT(expr, "?")

#if ISDEBUG
#define UNREACHABLE()                                                                                                                                                              \
    {                                                                                                                                                                              \
        Debug::log(CRIT, "\n\nMEMORY CORRUPTED: Unreachable failed! (Reached an unreachable position, memory corruption!!!)");                                                     \
        raise(SIGABRT);                                                                                                                                                            \
    }
#else
#define UNREACHABLE() std::unreachable();
#endif