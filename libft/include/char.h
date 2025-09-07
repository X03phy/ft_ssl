/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:07:01 by ebonutto          #+#    #+#             */
/*   Updated: 2025/03/28 16:13:51 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_H
# define CHAR_H

# include <stdbool.h>

bool	ft_char_charset(int c, char *charset);
int		ft_char_occurence(char *str, char c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_issign(int c);
int		ft_isspace(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
