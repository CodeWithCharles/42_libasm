/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:50:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/06 09:42:01 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "../include/mandatory.h"

static void	print_res_msg(const char *fncName, int ret);
static int test_ft_strlen(void);
static int test_ft_strcpy(void);
static int test_ft_strcmp(void);
static int test_ft_write(void);

int main(void)
{
	int	results[4] = {0};
	char	*fncNames[4] = {"ft_strlen", "ft_strcpy", "ft_strcmp", "ft_write"};

	printf("---- LIBASM TESTER ----\n\n");

	results[0] = test_ft_strlen();
	results[1] = test_ft_strcpy();
	results[2] = test_ft_strcmp();
	results[3] = test_ft_write();

	printf("\t---- SUMMARY ----\n\n");

	for (unsigned long i = 0; i < sizeof(results) / sizeof(int); i++)
		print_res_msg(fncNames[i], results[i]);
}

static int test_ft_strlen(void)
{
	int	ret = 0;
	int	i;

	const char *tests[] = {
		"",
		"a",
		"hello",
		"42",
		"this is a longer string with spaces",
		"string with\0null",
		NULL};

	printf("\t---- TEST FT_STRLEN ----\n\n");

	for (i = 0; tests[i] != NULL; i++)
	{
		size_t expected = strlen(tests[i]);
		size_t result = ft_strlen(tests[i]);
		printf("Test %d: \"%s\" | %s\n", i, tests[i], expected != result ? "❌ KO" : "✅ OK");
		printf("\tExpected: %zu\n\tGot: %zu \n\n", expected, result);
		if (expected != result)
			ret++;
	}
	if (ret)
		printf("❌ %d/%d test failed\n\n", ret, i);
	else
		printf("✅ All tests passed!\n\n");
	return ret;
}

static int test_ft_strcpy(void)
{
	int		ret = 0;
	int		i;
	char	dest[100];
	char	expected[100];

	const char *tests[] = {
		"",
		"hello",
		"world",
		"1234567890",
		"string with spaces",
		"special chars: !@#$%^&*()",
		"a\0hidden",
		NULL
	};

	printf("\t---- TEST FT_STRCPY ----\n\n");

	for (i = 0; tests[i] != NULL; i++)
	{
		strcpy(expected, tests[i]);
		ft_strcpy(dest, tests[i]);
		printf("Test %d: \"%s\" | %s\n", i, tests[i], strcmp(dest, expected) != 0 ? "❌ KO" : "✅ OK");
		printf("\tExpected: \"%s\"\n\tGot: \"%s\"\n\n",
			expected, dest);
		if (strcmp(dest, expected) != 0)
			ret++;
	}

	if (ret)
		printf("❌ %d/%d test failed\n\n", ret, i);
	else
		printf("✅ All tests passed!\n\n");

	return ret;
}

static int test_ft_strcmp(void)
{
	int	ret = 0;
	int	i;

	const char *tests[][2] = {
		{"", ""},
		{"a", "a"},
		{"abc", "abc"},
		{"abc", "abd"},
		{"abd", "abc"},
		{"", "a"},
		{"a", ""},
		{"abc", "abcde"},
		{"abcde", "abc"},
		{"same prefix", "same prefix but longer"},
		{"shorter", "short"},
		{"same\0hidden", "same"},
		{"diff\0hidden", "diff"},
		{NULL, NULL}
	};

	printf("\t---- TEST FT_STRCMP ----\n\n");

	for (i = 0; tests[i][0] != NULL; i++)
	{
		int expected = strcmp(tests[i][0], tests[i][1]);
		int result = ft_strcmp(tests[i][0], tests[i][1]);
		int same_sign = (expected == 0 && result == 0)
			|| (expected < 0 && result < 0)
			|| (expected > 0 && result > 0);

		printf("Test %d: \"%s\" vs \"%s\" | %s\n",
			i, tests[i][0], tests[i][1],
			same_sign ? "✅ OK" : "❌ KO");

		printf("\tExpected: %d\n\tGot: %d\n\n", expected, result);

		if (!same_sign)
			ret++;
	}

	if (ret)
		printf("❌ %d/%d test failed\n\n", ret, i);
	else
		printf("✅ All tests passed!\n\n");

	return ret;
}


static int test_ft_write(void)
{
	int ret = 0;
	ssize_t res, exp;
	int fd;

	printf("\t---- TEST FT_WRITE ----\n\n");

	// --- 1. Write to STDOUT ---
	printf("Test 0: Writing to STDOUT (\"Hello World\\n\")\n");
	exp = write(STDOUT_FILENO, "Hello World\n", 12);
	res = ft_write(STDOUT_FILENO, "Hello World\n", 12);
	printf("Expected: %zd, Got: %zd | %s\n\n", exp, res,
		(exp == res ? "✅ OK" : "❌ KO"));
	if (exp != res) ret++;

	// --- 2. Write empty string ---
	printf("Test 1: Writing empty string to STDOUT\n");
	exp = write(STDOUT_FILENO, "", 0);
	res = ft_write(STDOUT_FILENO, "", 0);
	printf("Expected: %zd, Got: %zd | %s\n\n", exp, res,
		(exp == res ? "✅ OK" : "❌ KO"));
	if (exp != res) ret++;

	// --- 3. Write to valid file ---
	printf("Test 2: Writing to a file\n");
	fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		ret++;
	}
	else
	{
		exp = write(fd, "File test\n", 10);
		res = ft_write(fd, "File test\n", 10);
		printf("Expected: %zd, Got: %zd | %s\n\n", exp, res,
			(exp == res ? "✅ OK" : "❌ KO"));
		if (exp != res) ret++;
		close(fd);
		unlink("test_output.txt");
	}

	// --- 4. Invalid fd ---
	printf("Test 3: Writing to invalid fd\n");
	errno = 0;
	exp = write(-1, "fail", 4);
	int exp_errno = errno;
	errno = 0;
	res = ft_write(-1, "fail", 4);
	int res_errno = errno;
	int ok = (exp == -1 && res == -1 && exp_errno == res_errno);
	printf("Expected: %zd (errno=%d), Got: %zd (errno=%d) | %s\n\n",
		exp, exp_errno, res, res_errno, ok ? "✅ OK" : "❌ KO");
	if (!ok) ret++;

	if (ret)
		printf("❌ %d/%d test failed\n\n", ret, 4);
	else
		printf("✅ All tests passed!\n\n");

	return ret;
}

static void	print_res_msg(const char *fncName, int ret)
{
	if (ret)
		printf("%s : ❌ KO | %d tests failed\n", fncName, ret);
	else
		printf("%s : ✅ OK\n", fncName);
}
