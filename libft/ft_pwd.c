/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouturi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:20:53 by acouturi          #+#    #+#             */
/*   Updated: 2017/11/16 15:34:11 by acouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_pwd(int i, unsigned int n)
{
	return (n == 0 ? 1 : i * ft_pwd(i, n - 1));
}
