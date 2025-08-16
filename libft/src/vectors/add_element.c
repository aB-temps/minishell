/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enchevri <enchevri@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:21:28 by abetemps          #+#    #+#             */
/*   Updated: 2025/08/08 14:08:11 by enchevri         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

enum e_bool	add_element(t_vector *vec, void *element)
{
	if (!grow_vector(vec, 1))
		return (FALSE);
	ft_memcpy(vec->array + vec->occupied_bytes, element, vec->datatype_size);
	vec->occupied_bytes += vec->datatype_size;
	vec->nb_elements++;
	return (TRUE);
}
