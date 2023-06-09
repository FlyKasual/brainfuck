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
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, char** argv) {
    FILE* fp = NULL;
    printf("brainfuck  Copyright (C) 2023  Johannes Nielsen\n"
           "This program comes with ABSOLUTELY NO WARRANTY.\n"
           "This is free software, and you are welcome to redistribute it"
           "under certain conditions.\n\n");
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            perror("Unable to open file");
            exit(EXIT_FAILURE);
        }

        parse(&fp);
    }

    fclose(fp);
    fp = NULL;
    return EXIT_SUCCESS;
}
