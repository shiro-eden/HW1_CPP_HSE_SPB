#!/usr/bin/env bash

# технические моменты, на технологиях программирования обучат, либо посёрчите
set -e
cd "$(dirname "$0")"
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
g++ -std=c++17 -Wall -Wextra -Werror compare_numbers.cpp -o "$tmp/run"

# check первое_число второе_число ответ
check() {
    "$tmp/run" "$1" "$2" > "$tmp/actual"
    echo "$3" > "$tmp/expected"
    diff -u "$tmp/expected" "$tmp/actual"
}

# bad_args arg_1 ... arg_n, проверяет, код возврата - равен ли 1
bad_args() {
    code=0
    "$tmp/run" "$@" </dev/null >/dev/null || code=$?
    test "$code" = 1
}

check 12.05 12.5 less
check -3.14 -3.14 equal
check 100000000000000000001 100000000000000000000 greater
check 0 +0 equal
check +12 12 equal
check -12 -2 less
check 0 -0.1 greater
check 9 10 less
check 0.1 0.10001 less
check -2 -2.001 greater
check 2.001 2 greater
check -0.01 0 less
bad_args
bad_args 1
bad_args 1 2 3

echo OK
