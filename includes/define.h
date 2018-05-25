/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** DEFINE.H
*/

#ifndef DEFINE_H
#define DEFINE_H

#define ERROR_CD "%s: Not a directory.\n"
#define WRONG_ARCHITECTURE "%s: Exec format error. Wrong Architecture.\n"
#define PERM_DENIED "%s: Permission denied.\n"
#define AMBIGUOUS "Ambiguous output redirect.\n"
#define NULL_COMMAND "Invalid null command.\n"

enum STATUS {
	EXIT_FAIL = 84,
	EXIT_NORMAL = 0,
	NUMBER
};

#endif
