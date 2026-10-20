# Run with cmake -P on every build. Rewrites OUTPUT only when its content changes,
# so the dependents are rebuilt only when the commit or the minute changes.

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
string(TIMESTAMP BUILD_DATETIME "%Y-%m-%d %H:%M")

set(CONTENT "#define SLIC3R_GIT_COMMIT \"${GIT_COMMIT}\"\n#define SLIC3R_BUILD_DATETIME \"${BUILD_DATETIME}\"\n")

set(OLD_CONTENT "")
if (EXISTS ${OUTPUT})
    file(READ ${OUTPUT} OLD_CONTENT)
endif ()
if (NOT CONTENT STREQUAL OLD_CONTENT)
    file(WRITE ${OUTPUT} "${CONTENT}")
endif ()
