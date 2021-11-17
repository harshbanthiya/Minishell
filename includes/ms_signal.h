/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/16 14:50:57 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H
# include "minishell.h"

# define SIG_AMNT 31

typedef struct sigaction	t_sigact;

/* Signals */
void	set_signal(void (*act)(int), int code);
void	init_signals(void);
void	sig_set_all_default();
void	sigintr_handler(int sig_num);
void	sigquit_handler(int sig_num);
/* End signal */

#endif