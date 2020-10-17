#pragma once

/* Some extra C++ "features" */

namespace _cxxutil {
    class StaticRunner {
    public:
        template <typename T>
        inline StaticRunner& operator+(T t) {
            t();
            return *this;
        }
    };

    template <typename T>
    class DeferredRunner {
    public:
        DeferredRunner(T func)
            : func(func) {}
        ~DeferredRunner() {
            func();
        }
    private:
        T func;
    };

    class DeferredRunnerHelper {
    public:
        template <typename T>
        inline DeferredRunner<T> operator+(T t) {
            return DeferredRunner<T>(t);
        }

    };
}

#define _CXXUTIL_CONCAT_INTERNAL(x, y)   x ## y
#define _CXXUTIL_CONCAT(x, y)            _CXXUTIL_CONCAT_INTERNAL(x, y)
#define _CXXUTIL_UNIQUE_NAME(name)       _CXXUTIL_CONCAT(name, __LINE__)

/* Run some code once, then never again */
#define run_static  static auto _CXXUTIL_UNIQUE_NAME(_runner) = _cxxutil::StaticRunner() + [=]()

/* Run code on scope end */
#define defer       auto _CXXUTIL_UNIQUE_NAME(_deferred_runner) = _cxxutil::DeferredRunnerHelper() + [=]()