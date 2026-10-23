#!/usr/bin/env bash

# технические моменты, на технологиях программирования обучат, либо посёрчите
set -e
cd "$(dirname "$0")"
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
g++ -std=c++17 -Wall -Wextra -Werror cyclic_shift.cpp -o "$tmp/run"

# check n ввод ответ; \n означает перевод строки.
check() {
    printf '%b' "$2" > "$tmp/input"
    "$tmp/run" "$1" < "$tmp/input" > "$tmp/actual"
    printf '%b' "$3" > "$tmp/expected"
    diff -u "$tmp/expected" "$tmp/actual"
}

# bad_args arg_1 ... arg_n, проверяет, код возврата - равен ли 1
bad_args() {
    code=0
    "$tmp/run" "$@" </dev/null >/dev/null || code=$?
    test "$code" = 1
}

check 5 '1 2 3 4 5\n2\n' '4\n5\n1\n2\n3\n4 5 1 2 3\n'
check 1 '-10\n0\n' '-10\n-10\n'
check 1 '-10\n1\n' '-10\n-10\n'
check 1 '-10\n-1\n' '-10\n-10\n'
check 1 '-10\n1000000000\n' '-10\n-10\n'
check 1 '-10\n-1000000000\n' '-10\n-10\n'
check 2 '1 2\n0\n' '1\n2\n1 2\n'
check 2 '1 2\n1\n' '2\n1\n2 1\n'
check 2 '1 2\n-1\n' '2\n1\n2 1\n'
check 2 '1 2\n2\n' '1\n2\n1 2\n'
check 2 '1 2\n-2\n' '1\n2\n1 2\n'
check 2 '1 2\n3\n' '2\n1\n2 1\n'
check 2 '1 2\n-3\n' '2\n1\n2 1\n'
check 5 '-1 0 1 2 3\n-2\n' '1\n2\n3\n-1\n0\n1 2 3 -1 0\n'
check 3 '1 2 3\n-1000000000\n' '2\n3\n1\n2 3 1\n'
check 2 '-1000000000 1000000000\n1\n' '1000000000\n-1000000000\n1000000000 -1000000000\n'
bad_args
bad_args 1 2
bad_args 1 2 3

echo OK
