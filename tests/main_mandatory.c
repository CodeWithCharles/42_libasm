/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:50:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/05 15:55:03 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../include/mandatory.h"

static void	print_res_msg(const char *fncName, int ret);
static int test_ft_strlen(void);
static int test_ft_strcpy(void);

int main(void)
{
	int	results[2] = {0};
	char	*fncNames[2] = {"ft_strlen", "ft_strcpy"};

	printf("---- LIBASM TESTER ----\n\n");

	results[0] = test_ft_strlen();
	results[1] = test_ft_strcpy();

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


static void	print_res_msg(const char *fncName, int ret)
{
	if (ret)
		printf("%s : ❌ KO | %d tests failed\n", fncName, ret);
	else
		printf("%s : ✅ OK\n", fncName);
}
