#!/bin/bash

gcc -Wall -Wextra -Werror -I../includes parsing.c get_next_line.c
./a.out sample.cub
