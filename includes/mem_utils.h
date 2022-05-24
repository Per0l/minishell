/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol-h <aperol-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:13:57 by aperol-h          #+#    #+#             */
/*   Updated: 2022/05/24 16:51:56 by aperol-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_UTILS_H
# define MEM_UTILS_H

void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t ori_size, size_t size);
#endif