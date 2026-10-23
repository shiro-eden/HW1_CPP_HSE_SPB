#!/usr/bin/env bash

# технические моменты, на технологиях программирования обучат, либо посёрчите
set -e
cd "$(dirname "$0")"
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
g++ -std=c++17 -Wall -Wextra -Werror dot_product.cpp -o "$tmp/run"

# check n ввод ответ; \n означает перевод строки.
check() {
    printf '%b' "$2" > "$tmp/input"
    "$tmp/run" "$1" < "$tmp/input" > "$tmp/actual"
    LC_ALL=C awk -v expected="$3" '
        { for (i = 1; i <= NF; i++) { n++; x = $i } }
        END {
            if (n != 1 || x !~ /^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?$/) exit 1
            d = x - expected; if (d < 0) d = -d
            s = expected; if (s < 0) s = -s
            exit !(d <= 1e-5 * (s > 1 ? s : 1))
        }
    ' "$tmp/actual"
}

# bad_args arg_1 ... arg_n, проверяет, код возврата - равен ли 1
bad_args() {
    code=0
    "$tmp/run" "$@" </dev/null >/dev/null || code=$?
    test "$code" = 1
}

check 3 '1.5 -2 0.25\n2 3 -4\n' -4.0
check 3 '1 2 3\n4 5 6\n' 32.0
check 1 '0\n10\n' 0.0
check 1 '-10\n10\n' -100.0
check 1 '-1.25\n-2.345678\n' 2.9320975
check 1 '0.000001\n-0.000001\n' -0.000000000001
check 2 '10 -10\n10 10\n' 0.0
bad_args
bad_args 1 2
bad_args 1 2 3

echo OK
