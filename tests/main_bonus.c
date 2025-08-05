/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:50:21 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/05 15:18:10 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../include/bonus.h"

static void	print_res_msg(const char *fncName, int ret);

int main(void)
{
	int	results[0] = {0};
	char	*fncNames[0] = {"ft_strlen"};

	printf("---- LIBASM BONUS TESTER ----\n\n");

	return 0;
}

static void	print_res_msg(const char *fncName, int ret)
{
	printf("%s : %s\n", fncName, ret ? "❌ KO" : "✅ OK");
}
