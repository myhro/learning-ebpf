#!/usr/bin/python3

import sys


def int_to_bytes(n):
    n = '{0:032b}'.format(n)
    binary = [n[i:i+8] for i in range(0, 32, 8)]
    binary.reverse()  # Little Endian -> Big Endian
    decimal = [int(b, 2) for b in binary]
    return ' '.join([str(d) for d in decimal])


def str_to_bytes(s):
    max_len = 12
    s = s[:max_len-1]  # Truncate leaving at least one byte for '\0' at the end
    s = [str(b) for b in s.encode('utf-8')]
    for i in range(max_len - len(s)):
        s.append('0')
    return ' '.join(s)


def main():
    if len(sys.argv) != 4:
        print('Usage: {} <id> <key> <value>'.format(sys.argv[0]))
        sys.exit(1)

    map_id = sys.argv[1]
    map_key = sys.argv[2]
    map_value = sys.argv[3]

    map_key = int_to_bytes(int(map_key))
    map_value = str_to_bytes(map_value)

    print('bpftool map update id {id} key {key} value {value}'.format(id=map_id, key=map_key, value=map_value))


if __name__ == '__main__':
    main()
