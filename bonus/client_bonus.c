/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soer-ret <soer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:19:34 by soer-ret          #+#    #+#             */
/*   Updated: 2025/03/23 21:33:33 by soer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_putstr(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	exit(1);
}

int static	ft_space(char c)
{
	return (
		c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	ft_atoi(const char *str)
{
	int				i;
	int				final_value;
	long long int	nbr;

	nbr = 0;
	i = 0;
	final_value = 1;
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			final_value = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i++] - '0';
		if (nbr < (-2147483648) && final_value == -1)
			return (0);
		if (nbr > 2147483647 && final_value == 1)
			return (-1);
	}
	if (str[i])
		return (0);
	return (nbr * final_value);
}

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_putstr("Error: Failed to send signal\n", 2);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_putstr("Error: Failed to send signal\n", 2);
		}
		usleep(500);
	}
}

int	main(int argc, char *argv[])
{
	int			server_pid;
	const char	*message;
	int			i;

	if (argc != 3)
		ft_putstr("Usage: ./client <pid> <message>\n", 2);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		exit(1);
	message = argv[2];
	i = 0;
	while (message[i])
		send_signal(server_pid, message[i++]);
	send_signal(server_pid, '\n');
	ft_putstr("message is sent\n", 1);
	return (0);
}
