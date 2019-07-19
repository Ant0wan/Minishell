/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:59:39 by abarthel          #+#    #+#             */
/*   Updated: 2019/07/16 18:46:00 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**lexer(char *input)
{
	char **tokens;
	char **retsplit;

	retsplit = ft_strsplit(input, ' ');
	tokens = ft_tabcpy(retsplit);
	ft_tabdel(&retsplit);
	return (tokens);
}
