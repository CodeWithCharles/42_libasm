/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:50:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/05 14:07:35 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../include/mandatory.h"

static void	print_res_msg(const char *fncName, int ret);
static int test_ft_strlen(void);

int main(void)
{
	int	results[1] = {0};
	char	*fncNames[1] = {"ft_strlen"};

	printf("---- LIBASM TESTER ----\n\n");

	results[0] = test_ft_strlen();

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

	printf("---- TEST FT_STRLEN ----\n\n");

	for (i = 0; tests[i] != NULL; i++)
	{
		size_t expected = strlen(tests[i]);
		size_t result = ft_strlen(tests[i]);
		printf("Test %d: \"%s\"\n", i, tests[i]);
		printf("Expected: %zu, Got: %zu | %s\n\n", expected, result, expected != result ? "❌ KO" : "✅ OK");
		if (expected != result)
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
	printf("%s : %s\n", fncName, ret ? "❌ KO" : "✅ OK");
}
