/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 12:41:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/07/20 10:05:28 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
#define TESTER_H
# include <stdio.h>
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

int32_t resolveExitCode(void)
{
	return (_result == _expected ? EXIT_SUCCESS : EXIT_FAILURE);
}

void handle(void)
{
	static char buff[256] = {0};

	// Something went wrong
	if (_result != _expected)
	{
		// Signal
		if (!_normalExit)
		{
			ssize_t bread;
			if ((bread = read(_fds[READ], buff, sizeof(buff))) < 0)
			{
				perror("read");
				return;
			}
		}
		else // Exit code did not match
			_result = FAIL;
	}
	else
		_result = PASS;
	
	// Print result
	printf("%s\n", _result == PASS ? "[OK]" : "[FAIL]");
	printf("%s", buff);
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
#define TEST_DECLARE(Name)				\
	_name = Name;						\
	printf("Testing: %s -> ", _name);	\
	if (pipe(_fds) < 0) { 				\
		perror("pipe");					\
		exit(EXIT_FAILURE);				\
	}									\
	dup2(_fds[WRITE], STDERR_FILENO);	\
	/* Now redirect the signals!	*/	\
	atexit(handle);						\
	signal(SIGABRT, sighandle);			\
	signal(SIGSEGV, sighandle);			\
	signal(SIGILL,	sighandle);			\
	signal(SIGTERM, sighandle);			\
	signal(SIGKILL, sighandle);			\
	signal(SIGBUS,	sighandle);			\

#endif

//////////////////////////////////////////////////////////////////////////////////
