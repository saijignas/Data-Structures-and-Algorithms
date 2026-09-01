// A minimal, self-contained test framework -- no external dependency,
// no build system beyond a single compiler invocation. In keeping with
// this repo's own point (data structures built from scratch, not
// wrappers around a library), the test runner is built from scratch too.
#pragma once

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace testfw {

struct TestCase {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(const std::string& name, std::function<void()> fn) {
        registry().push_back({name, fn});
    }
};

inline int& current_failures() {
    static int failures = 0;
    return failures;
}

inline int& current_checks() {
    static int checks = 0;
    return checks;
}

inline void report_check(bool passed, const std::string& expr, const char* file, int line) {
    current_checks()++;
    if (!passed) {
        current_failures()++;
        std::cerr << "  FAILED CHECK: " << expr << " (" << file << ":" << line << ")\n";
    }
}

inline int run_all() {
    int total_failed_tests = 0;
    for (const auto& t : registry()) {
        int before = current_failures();
        std::cout << "[ RUN  ] " << t.name << "\n";
        t.fn();
        if (current_failures() > before) {
            std::cout << "[ FAIL ] " << t.name << "\n";
            total_failed_tests++;
        } else {
            std::cout << "[  OK  ] " << t.name << "\n";
        }
    }
    std::cout << "\n"
              << (registry().size() - total_failed_tests) << "/" << registry().size()
              << " test cases passed (" << current_checks() << " checks total, "
              << current_failures() << " failed).\n";
    return total_failed_tests == 0 ? 0 : 1;
}

}  // namespace testfw

// Two-layer token-paste indirection: pasting ## suppresses macro expansion
// of its operands, so TESTFW_CONCAT_ must be called through TESTFW_CONCAT
// to let __LINE__ expand to a number *before* the paste happens.
#define TESTFW_CONCAT_(a, b) a##b
#define TESTFW_CONCAT(a, b) TESTFW_CONCAT_(a, b)

#define TEST_CASE(name)                                                                    \
    static void TESTFW_CONCAT(test_fn_, __LINE__)();                                       \
    static ::testfw::Registrar TESTFW_CONCAT(test_reg_, __LINE__)(name, TESTFW_CONCAT(test_fn_, __LINE__)); \
    static void TESTFW_CONCAT(test_fn_, __LINE__)()

#define CHECK(expr) ::testfw::report_check((expr), #expr, __FILE__, __LINE__)

#define TEST_MAIN()          \
    int main() {             \
        return ::testfw::run_all(); \
    }
