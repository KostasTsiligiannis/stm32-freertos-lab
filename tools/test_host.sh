#!/usr/bin/env bash
set -euo pipefail

mkdir -p build/host-test

cppcheck --enable=warning,performance,portability --error-exitcode=1 \
  -Iapp app/led_controller.c tests/test_led_controller.c

gcc -Wall -Wextra -Werror \
  tests/test_led_controller.c app/led_controller.c third_party/Unity/src/unity.c \
  -Iapp -Ithird_party/Unity/src \
  -o build/host-test/run_tests

./build/host-test/run_tests
