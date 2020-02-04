/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pganglof <pganglof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:35:27 by mcraipea          #+#    #+#             */
/*   Updated: 2020/02/04 13:17:36 by pganglof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**add_env(int *i, char **env, char *value, t_data *data)
{
	int			j;
	char		**new;

	if (!(new = ft_calloc(*i + 2, sizeof(char*))))
		exit_failure("malloc", data);
	j = 0;
	while (env[j])
	{
		if (!(new[j] = ft_strdup(env[j])))
			exit_failure("ft_strdup", data);
		j++;
	}
	if (!(new[j] = ft_strdup(value)))
		exit_failure("ft_strdup", data);
	j++;
	new[j] = NULL;
	j = 0;
	while (j < *i)
		free(env[j++]);
	return (new);
}

static char			**del_env(int *i, char **env, char *value, t_data *data)
{
	int			j;
	int			k;
	int			l;
	char		**new;

	j = 0;
	while (env[j])
	{
		if (ft_strcmp(env[j], value) == 0)
		{
			if (!(new = ft_calloc(*i, sizeof(char*))))
				exit_failure("malloc", data);
			l = 0;
			k = 0;
			while (env[l])
			{
				if (ft_strcmp(env[l], value) != 0)
				{
					if (!(new[k] = ft_strdup(env[l])))
						exit_failure("ft_strdup", data);
					l++;
					k++;
					new[k] = NULL;
				}
				else
					l++;
			}
			j = 0;
			while (j < *i)
				free(env[j++]);
			return (new);
		}
		j++;
	}
	return (env);
}

void			ft_export(t_parsing *tmp, t_data *data)
{
	int			i;
	char		buffer[128];

	i = 0;
	while (tmp->arg[1][i] != '=')
	{
		buffer[i] = tmp->arg[1][i];
		i++;
	}
	buffer[i] = tmp->arg[1][i];
	buffer[i] = '\0';
	i = 0;
	while (data->env[i])
		i++;
	data->env = del_env(&i, data->env, buffer, data);
	i = 0;
	while (data->env[i])
		i++;
	data->env = add_env(&i, data->env, tmp->arg[1], data);
}
