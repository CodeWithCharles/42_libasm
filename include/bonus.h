/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:48:59 by cpoulain          #+#    #+#             */
/*   Updated: 2025/08/11 15:40:36 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mandatory.h"

/* ------------------------------- Structures ------------------------------- */

typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

/* --------------------------------- Helpers -------------------------------- */

char	*ft_strchr(const char *s, int c);
t_list	*ft_list_new(void *data);

/* ---------------------------------- Bonus --------------------------------- */

int		ft_atoi_base(const char *input, const char *base);
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list);
void 	ft_list_sort(t_list **begin_list, int (*cmp)());
void	ft_list_remove_if(t_list **begin_list,
			void *data_ref,
			int (*cmp)(),
			void (*free_fct)(void *));
void	ft_list_remove(t_list *lst, void (*del)(void *));
