/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inchar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:53:21 by lucocozz          #+#    #+#             */
/*   Updated: 2021/08/02 15:04:49 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Self explanatory. */
t_inchar	*create_inchar(int value)
{
	t_inchar	*inchar;

	inchar = gc_malloc(sizeof(t_inchar) * 1);
	inchar->value = value;
	inchar->next = NULL;
	inchar->prev = NULL;
	return (inchar);
}

/* Self explanatory. */
void	free_inchars(t_inchar *inchars)
{
	t_inchar	*prev;

	while (inchars)
	{
		prev = inchars;
		inchars = inchars->next;
		gc_free((void **)&prev);
	}
}

/* Insert char in input line. */
void	insert_inchar(t_cursor *cursor, int value)
{
	char			*goto_cap;
	t_inchar		*new;
	t_history_data	*history;

	history = get_history();
	new = create_inchar(value);
	new->prev = cursor->on_inchar->prev;
	if (cursor->on_inchar->prev != NULL)
		cursor->on_inchar->prev->next = new;
	new->next = cursor->on_inchar;
	cursor->on_inchar->prev = new;
	print_inchars(cursor->on_inchar->prev);
	cursor_move_right(cursor);
	goto_cap = tgoto(tgetstr("cm", NULL), cursor->pos.y, cursor->pos.x);
	tputs(goto_cap, 1, ft_putchar_err);
	gc_free((void **)&history->input);
	history->input = inchars_to_line(inchars_head(cursor));
}

/* Convert string to inchar list. */
char	*inchars_to_line(t_inchar *inchars)
{
	int			i;
	int			size;
	char		*line;
	t_inchar	*tmp;

	i = 0;
	tmp = inchars;
	if (tmp->value == EOL)
		return (ft_strdup(""));
	size = inchars_len(tmp);
	line = gc_malloc(sizeof(char) * (size + 1));
	while (tmp->next != NULL)
	{
		line[i++] = tmp->value;
		tmp = tmp->next;
	}
	line[i] = '\0';
	return (line);
}

/* Convert inchar list to string. */
t_inchar	*line_to_inchars(char *line)
{
	int			i;
	t_inchar	*inchars;

	i = 0;
	inchars = NULL;
	if (line[0] == '\0')
		return (create_inchar(EOL));
	push_back_inchars(&inchars, line[i++]);
	while (line[i])
		push_back_inchars(&inchars, line[i++]);
	push_back_inchars(&inchars, EOL);
	return (inchars);
}
