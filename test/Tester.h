/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 12:41:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/07/21 10:41:26 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
#define TESTER_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <assert.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>

# define READ 0
# define WRITE 1

# define PASS 0
# define FAIL 1

//////////////////////////////////////////////////////////////////////////////////

// TODO: Clean this up ...

static int32_t _fds[2];
static int32_t _expected;
static int32_t _result = -1;
static bool _normalExit;
static const char* _name;

static void printError(void)
{
	printf("\r\033[35C\033[31;1m[ERROR] %s\033[0m\n", strerror(errno));
}

static int32_t resolveExitCode(void)
{
	return (_result == _expected ? EXIT_SUCCESS : EXIT_FAILURE);
}

void handle(void)
{
	static char buff[256] = {0};

	// Check result
	if (_result != _expected)
	{
		if (_normalExit)
			_result = FAIL;
	}
	else
		_result = PASS;
	
	// If we failed and exit was abnormal
	if (_result == FAIL && !_normalExit)
	{
		ssize_t bread;
		if ((bread = read(_fds[READ], buff, sizeof(buff))) < 0)
		{
			printError();
			return;
		}
	}

	// Print result
	printf("\r\033[35C%s\n", _result == PASS ? "\033[32;1m[OK]\033[0m" : "\033[31;1m[FAIL]\033[0m");
	printf("\033[31;1m%s\033[0m", buff);
}

#define TEST_EXPECT(expect)		\
	{ _expected = expect; }		\

#define TEST_EXIT(code)	\
	{ _result = code; _normalExit = true; exit(resolveExitCode()); }		\

void sighandle(int32_t sig) 
{
	(void)sig;

	_result = (_expected == PASS ? EXIT_FAILURE : EXIT_SUCCESS);
	_normalExit = false;
	exit(resolveExitCode()); 
}

// Initialize the function as a test.
#define TEST_DECLARE(Name)							\
	_name = Name;									\
	printf("Testing: %s", _name);	\
	if (pipe(_fds) < 0) { 							\
		printError();								\
		exit(EXIT_FAILURE);							\
	}												\
	dup2(_fds[WRITE], STDERR_FILENO);				\
	/* Now redirect the signals!	*/				\
	atexit(handle);									\
	signal(SIGABRT, sighandle);						\
	signal(SIGSEGV, sighandle);						\
	signal(SIGILL,	sighandle);						\
	signal(SIGTERM, sighandle);						\
	signal(SIGBUS,	sighandle);						\

#endif

//////////////////////////////////////////////////////////////////////////////////
