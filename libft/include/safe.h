/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:27:44 by ebonutto          #+#    #+#             */
/*   Updated: 2025/04/01 15:27:14 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_H
# define SAFE_H

# include <stdlib.h>
# include <unistd.h>
# include "fd.h"
# include <stdio.h>

void	ft_close(int *fd);
void	ft_dfree(char ***split);
void	ft_error(char *str, int exit_status);
void	ft_perror(char *str, int exit_status);
void	ft_sfree(void **ptr);

#endif
