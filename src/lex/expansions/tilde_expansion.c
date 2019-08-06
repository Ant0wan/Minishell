/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/01 18:48:23 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error.h"

int	replace_tilde(char **str, char *start, char *env)
{
	char	*cpy;
	
	if (!env)
		return (e_success);
	if (!(cpy = ft_strjoin(env, start)))
		return (e_cannot_allocate_memory);
	ft_memdel((void**)str);
	*str = cpy;
	return (e_success);
}

int	ft_tilde_expansion(char **str)
{
	char	*env;
	int	ret;

	if (!(*str)[1] || (*str)[1] == '/')
	{
		env = ft_getenv("HOME");
		ret = replace_tilde(str, &(*str)[1], env);
		return (ret);
	}
	else if ((*str)[1] == '-' && ((*str)[2] == '/' || !(*str)[2]))
	{
		env = ft_getenv("OLDPWD");
		ret = replace_tilde(str, &(*str)[2], env);
		return (ret);
	}
	else if ((*str)[1] == '+' && ((*str)[2] == '/' || !(*str)[2]))
	{
		env = ft_getenv("PWD");
		ret = replace_tilde(str, &(*str)[2], env);
		return (ret);
	}
	return (e_success);
}