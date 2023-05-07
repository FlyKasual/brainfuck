/**
 * brainfuck – A brainfuck parser written in C
 * Copyright (C) 2023  Johannes Nielsen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include "parser.h"

int parse(FILE** fp) {
    FILE* const _restore = *fp;
    static int buffer[BF_BUFF_SIZE];
    static int ptr = 0;
    static int openingBrackets = 0;
    static int closingBrackets = 0;
    int ch = '\0';

    while((ch = fgetc(*fp)) != EOF) {
        switch (ch) {
            case '+':
                ++buffer[ptr];
                break;
            case '-':
                --buffer[ptr];
                break;
            case '<':
                --ptr;
                if (ptr < 0)
                    perror("Index is out of bounds");
                break;
            case '>':
                ++ptr;
                if (ptr > BF_BUFF_SIZE - 1)
                    perror("Index is out of bounds");
                break;
            case '.':
                fputc(buffer[ptr], stdout);
                break;
            case ',':
                buffer[ptr] = fgetc(stdin);
                break;
            case ']':
                if (buffer[ptr] == 0) {
                    ++closingBrackets;
                    // FIXME: This check should happen earlier
                    if (closingBrackets > openingBrackets)
                        perror("For loop was closed but never opened");
                    return buffer[ptr];
                }
                *fp = _restore;
                break;
            case '[':
                ++openingBrackets;
                parse(fp);
                break;
            default:
                break;
        }
    }
    if (closingBrackets != openingBrackets)
        perror("For loop was opened but never closed");
    return buffer[ptr];
}
