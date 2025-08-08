/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:50:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/08 14:06:15 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../include/bonus.h"

static void	print_res_msg(const char *fncName, int ret);
static int	test_ft_atoi_base(void);

int main(void)
{
	int	results[1] = {0};
	char	*fncNames[1] = {"ft_atoi_base"};

	printf("---- LIBASM BONUS TESTER ----\n\n");

	results[0] = test_ft_atoi_base();

	printf("\t---- SUMMARY ----\n\n");

	for (unsigned long i = 0; i < sizeof(results) / sizeof(int); i++)
		print_res_msg(fncNames[i], results[i]);

	return 0;
}

static int test_ft_atoi_base(void)
{
	struct test_case {
		const char *str;
		const char *base;
		int expected;
	};

	int ret = 0;
	struct test_case tests[] = {
		// Basic decimal
		{"123", "0123456789", 123},
		{"-123", "0123456789", -123},
		{"+123", "0123456789", 123},

		// Hexadecimal uppercase
		{"1A", "0123456789ABCDEF", 26},
		{"-1A", "0123456789ABCDEF", -26},
		{"FF", "0123456789ABCDEF", 255},

		// Hexadecimal lowercase base
		{"1a", "0123456789abcdef", 26},
		{"ff", "0123456789abcdef", 255},

		// Binary base
		{"1010", "01", 10},
		{"-1010", "01", -10},

		// Octal base
		{"777", "01234567", 511},

		// Base with weird chars
		{"xyz", "xyz", 5}, // x=0, y=1, z=2; xyz = 0*3^2 + 1*3^1 + 2*3^0 = 0+3+2=5

		// Leading spaces and tabs
		{"   \t 42", "0123456789", 42},

		// Signs with spaces after sign
		{"-   42", "0123456789", 0}, // invalid, sign must be immediately before digits

		// Empty string
		{"", "0123456789", 0},

		// Zero
		{"0", "0123456789", 0},

		// Only sign
		{"+", "0123456789", 0},

		// Base too short (should fail)
		{"123", "0", 0},

		// Base with duplicates (should fail)
		{"123", "01223345", 0},

		// Base containing unauthorized chars (space, +, -)
		{"123", "01234567+", 0},

		// String with invalid characters for base
		{"123Z", "0123456789", 123}, // stop parsing at 'Z'

		// String with no valid digits at all
		{"ZZZ", "0123456789ABCDEF", 0},

		// Multiple signs
		{"--+--123", "0123456789", 123},
		{" +--+-+42", "0123456789", -42},

		// NULL strings (should safely return 0)
		{NULL, "0123456789", 0},
		{"123", NULL, 0},
		{NULL, NULL, 0},

		{NULL, NULL, 0} // terminator
	};

	printf("\t---- TEST FT_ATOI_BASE ----\n\n");
	for (int i = 0; tests[i].base != NULL || tests[i].str != NULL; i++)
	{
		int result = ft_atoi_base(tests[i].str, tests[i].base);
		int ok = (result == tests[i].expected);
		printf("Test %d: str=\"%s\", base=\"%s\" | %s\n",
			i,
			tests[i].str ? tests[i].str : "(null)",
			tests[i].base ? tests[i].base : "(null)",
			ok ? "✅ OK" : "❌ KO");
		printf("\tExpected: %d\n\tGot     : %d\n\n", tests[i].expected, result);
		if (!ok)
			ret++;
	}
	if (ret)
		printf("❌ %d/%d tests failed\n\n", ret, (int)(sizeof(tests)/sizeof(tests[0]) - 1));
	else
		printf("✅ All tests passed!\n\n");

	return ret;
}

static void	print_res_msg(const char *fncName, int ret)
{
	printf("%s : %s\n", fncName, ret ? "❌ KO" : "✅ OK");
}
