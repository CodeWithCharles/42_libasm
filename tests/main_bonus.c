/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:50:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/11 15:38:47 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../include/bonus.h"

static void print_res_msg(const char *fncName, int ret);
static int test_ft_atoi_base(void);
static int test_ft_list_new_and_push_front(void);
static int test_ft_list_size(void);
static int test_ft_list_sort(void);
static int test_ft_list_remove_if(void);
static int cmp_int(void *a, void *b);
static void del_noop(void *ptr);

int main(void)
{
	int results[5] = {0};
	char *fncNames[5] = {"ft_atoi_base", "ft_list_push_front", "ft_list_size", "ft_list_sort", "ft_list_remove_if"};

	printf("---- LIBASM BONUS TESTER ----\n\n");

	results[0] = test_ft_atoi_base();
	results[1] = test_ft_list_new_and_push_front();
	results[2] = test_ft_list_size();
	results[3] = test_ft_list_sort();
	results[4] = test_ft_list_remove_if();

	printf("\t---- SUMMARY ----\n\n");

	for (unsigned long i = 0; i < sizeof(results) / sizeof(int); i++)
		print_res_msg(fncNames[i], results[i]);

	return 0;
}

static int cmp_int(void *a, void *b)
{
	int c = *((int *)a);
	int d = *((int *)b);
	return c - d;
}

static void del_noop(void *ptr)
{
	(void)ptr;
	// do nothing
}

static int test_ft_list_remove_if(void)
{
	int ret = 0;
	printf("\t---- TEST FT_LIST_REMOVE_IF ----\n\n");

	// Create some test data
	int vals[] = {10, 20, 30, 40, 50};
	const int n = sizeof(vals) / sizeof(vals[0]);

	t_list *head = NULL;

	// Build list: 50 -> 40 -> 30 -> 20 -> 10
	for (int i = 0; i < n; i++)
		ft_list_push_front(&head, &vals[i]);

	// Remove value not in list: 99
	ft_list_remove_if(&head, &(int){99}, cmp_int, del_noop);
	// List should remain unchanged and size = 5
	int size = ft_list_size(head);
	if (size != 5)
	{
		printf("❌ Failed to skip removing non-existent element (size=%d)\n", size);
		ret++;
	}

	// Remove head (50)
	ft_list_remove_if(&head, &(int){50}, cmp_int, del_noop);
	size = ft_list_size(head);
	if (size != 4 || *((int *)head->data) != 40)
	{
		printf("❌ Failed to remove head (expected 40 at head)\n");
		ret++;
	}

	// Remove tail (10)
	ft_list_remove_if(&head, &(int){10}, cmp_int, del_noop);
	size = ft_list_size(head);
	if (size != 3)
	{
		printf("❌ Failed to remove tail (size=%d)\n", size);
		ret++;
	}

	// Remove middle element (30)
	ft_list_remove_if(&head, &(int){30}, cmp_int, del_noop);
	size = ft_list_size(head);
	if (size != 2)
	{
		printf("❌ Failed to remove middle element (size=%d)\n", size);
		ret++;
	}

	// Remove all remaining
	ft_list_remove_if(&head, &(int){20}, cmp_int, del_noop);
	ft_list_remove_if(&head, &(int){40}, cmp_int, del_noop);
	if (head != NULL)
	{
		printf("❌ Failed to remove all elements (head != NULL)\n");
		ret++;
	}

	if (ret == 0)
		printf("✅ ft_list_remove_if passed all tests!\n");
	else
		printf("❌ ft_list_remove_if failed %d test(s)\n", ret);

	printf("\n");
	return ret;
}

static int test_ft_list_sort(void)
{
	int ret = 0;

	printf("\t---- TEST FT_LIST_SORT ----\n\n");

	int vals[] = {10, 42, -1, 23, -16};
	const int num_vals = sizeof(vals) / sizeof(vals[0]);

	// Build unsorted list
	t_list *head = NULL;
	for (int i = 0; i < num_vals; i++)
		ft_list_push_front(&head, &vals[i]);

	printf("List before sorting:\n");
	t_list *tmp = head;
	while (tmp)
	{
		printf("  - %d\n", *((int *)tmp->data));
		tmp = tmp->next;
	}

	// Sort list
	ft_list_sort(&head, cmp_int);

	// Expected sorted values
	int expected[] = {-16, -1, 10, 23, 42};

	printf("\nList after sorting:\n");
	tmp = head;
	for (int i = 0; i < num_vals; i++)
	{
		if (!tmp)
		{
			printf("❌ List ended prematurely at index %d\n", i);
			ret++;
			break;
		}

		int actual = *((int *)tmp->data);
		printf("  - %d\n", actual);
		if (actual != expected[i])
		{
			printf("❌ Node %d mismatch: expected %d, got %d\n", i, expected[i], actual);
			ret++;
		}
		tmp = tmp->next;
	}
	if (tmp) // Too many nodes
	{
		printf("❌ List longer than expected\n");
		ret++;
	}

	if (ret == 0)
		printf("\n✅ ft_list_sort passed all tests!\n");
	else
		printf("\n❌ ft_list_sort failed %d test(s)\n", ret);

	printf("\n");
	return ret;
}

static int test_ft_list_size(void)
{
	int ret = 0;

	printf("\t---- TEST FT_LIST_SIZE ----\n\n");

	t_list *head = NULL;

	// Test 0: empty list
	int size = ft_list_size(head);
	if (size != 0)
	{
		printf("❌ Test 0: Expected 0, got %d\n\n", size);
		ret++;
	}
	else
	{
		printf("✅ Test 0: Empty list size = 0\n\n");
	}

	// Prepare some values
	char vals[] = {'A', 'B', 'C'};

	// Add 1 node
	ft_list_push_front(&head, &vals[0]); // List: A
	size = ft_list_size(head);
	if (size != 1)
	{
		printf("❌ Test 1: Expected 1, got %d\n", size);
		ret++;
	}
	else
	{
		printf("✅ Test 1: List size = 1\n");
	}

	// Add 2 more nodes
	ft_list_push_front(&head, &vals[1]); // List: B -> A
	ft_list_push_front(&head, &vals[2]); // List: C -> B -> A

	size = ft_list_size(head);
	if (size != 3)
	{
		printf("❌ Test 2: Expected 3, got %d\n", size);
		ret++;
	}
	else
	{
		printf("✅ Test 2: List size = 3\n");
	}

	printf("\n");
	return ret;
}

static int test_ft_list_new_and_push_front(void)
{
	int ret = 0;

	printf("\t---- TEST FT_LIST_NEW + FT_LIST_PUSH_FRONT ----\n\n");

	t_list *head = NULL;
	char *vals = "Coucou";

	// First test: create new node
	t_list *node = ft_list_new(&vals[0]);
	if (!node || node->data != &vals[0] || node->next != NULL)
	{
		printf("ft_list_new failed ❌\n\n");
		ret++;
	}
	else
	{
		printf("ft_list_new passed ✅\n\n");
	}

	// Push front several values
	ft_list_push_front(&head, &vals[0]); // 1
	ft_list_push_front(&head, &vals[1]); // 2 -> 1
	ft_list_push_front(&head, &vals[2]); // 3 -> 2 -> 1

	// Now check list order and content
	t_list *current = head;
	int i = 2;
	while (current)
	{
		if (current->data != &vals[i])
		{
			printf("❌ Node %d has wrong value. Expected %d, got %d\n",
				   2 - i, vals[i], *(int *)current->data);
			ret++;
		}
		else
		{
			printf("✅ Node %d is correct: %d\n", 2 - i, *(int *)current->data);
		}
		current = current->next;
		i--;
	}

	printf("\n");
	return ret;
}

static int test_ft_atoi_base(void)
{
	struct test_case
	{
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
		printf("❌ %d/%d tests failed\n\n", ret, (int)(sizeof(tests) / sizeof(tests[0]) - 1));
	else
		printf("✅ All tests passed!\n\n");

	return ret;
}

static void print_res_msg(const char *fncName, int ret)
{
	printf("%s : %s\n", fncName, ret ? "❌ KO" : "✅ OK");
}
