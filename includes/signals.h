/*
** EPITECH PROJECT, 2018
** siganl
** File description:
** minishell
*/

#ifndef SIGNAL_H
#define SIGNAL_H

int error_pid(int pid);

struct s_error {
	int error;
	char *message;
};

struct s_error err[] = {
	{1, "Hangup"},
	{2, "blank"},
	{3, "Quit"},
	{4, "Illegal instruction"},
	{5, "Trace/BPT trap"},
	{6, "Abort"},
	{7, "Bus error"},
	{8, "Floating exception"},
	{9, "Killed"},
	{10, "User signal 1"},
	{11, "Segmentation fault"},
	{12, "User signal 2"},
	{13, "Broken pipe"},
	{14, "Alarm clock"},
	{15, "Terminated"},
	{16, "Stack limit exceeded"},
	{17, "Child exited"},
	{18, "Continued"},
	{19, "Suspend (signal)"},
	{20, "Suspended"},
	{21, "Suspended (tty input)"},
	{21, "Suspended (tty input)"},
	{23, "Urgent I/O condition"},
	{24, "Cputime limit exceeded"},
	{25, "Filesize limit exceeded"},
	{26, "Virtual time alarm"},
	{27, "Profiling time Alarm"},
	{28, "Window changed"},
	{29, "Pollable event occured"},
	{30, "Power failure"},
	{31, "Bad system call"},
};

#endif
