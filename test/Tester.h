/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 12:41:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/07/18 14:59:20 by lde-la-h      ########   odam.nl         */
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

static int32_t _fds[2];			// stderr pipe
static int32_t _expected;		// Expected test result
static int32_t _result = -1;	// The test result, -1 is not set.
static const char* _name;		// Test name

void handle(void)
{
	// If we reached this, it means we exited normally
	if (_result < 0)
		_result = (_expected == PASS ? EXIT_SUCCESS : EXIT_FAILURE);

	static char buff[256] = {0};
	ssize_t bread = read(_fds[READ], buff, sizeof(buff));
	printf("%s\n", _result == 0 ? "PASS" : "FAIL");
	printf("%s", buff);
}

#define TEST_EXPECT(expect)		\
	{ _expected = expect; }		\

#define TEST_EXIT(code)	\
	{ _result = code; exit(code); }		\

void sighandle(int32_t sig) 
{
	_result = (_expected == PASS ? EXIT_FAILURE : EXIT_SUCCESS);
	exit(_result); 
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
