/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:50:14 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/07 21:12:57 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Структура для аргументов, чтобы не релоцировать память
typedef struct s_arguments
{
	char *argument;
	struct s_arguments *next;
	struct s_arguments *head;
} t_arguments;

// Общая структура для выполнения команд оболочкой
typedef struct s_execute
{
	char	*command;
	char	*option;
	t_arguments *argument;
	char	*stdIn;
	char	*stdIn2;
	char	*stdOut;
	char	*stdOut2;
	struct s_execute *next;
	struct s_execute *head;
} t_execute;

// Инициализия структур и их очистка
t_execute *first_execute(void);
t_execute	*new_execute(t_execute *info);
void first_argument(t_execute *info);
void	new_argument(t_execute *info);
void	free_arguments(t_arguments *arguments);
void	free_execute(t_execute *info);
void free_all(t_execute *info);

// Функции парсера и лексера
int	ft_strlen(char *str);
int size_line(char *line);
int	final_size_env(char	*line);
int	final_size_dquotes(char	*line);

// Парсинг > и >>
char *parse_double_output(t_execute *info, char *line);
char	*parse_output(t_execute *info, char *line);

// Парсинг < и <<
char *ft_strjoin(char *first, char *second);
int	string_compare(char *str1, char *str2);
char	*parse_double_input2(char *docstr);
char *parse_double_input(t_execute *info, char *line);
char	*parse_input(t_execute *info, char *line);

// Парсинг ""
int size_line_env(char *line);
char	*get_env(char	*str);
int	size_line_dquotes(char *str);
char	*parse_double_quotes2(t_execute	*info, char	*line, int size);
char	*parse_double_quotes(t_execute *info, char *line);

// Парсинг ''
int	size_line_quotes(char *str);
char	*parse_quotes(t_execute *info, char *line);

// Парсинг |
char	*next_command(t_execute *info, char *line);
char	*parse_pipe(t_execute *info, char	*line);


// Парсинг переменных окружения и аргументов
char	*parse_arguments(t_execute *info, char *line);
int	single_dollar(t_execute *info, char *line, int i);
char *parse_env(t_execute *info, char *line);
int	parse_env2(t_execute *info, char *line, int i);

// Парсинг команды и флагов
char *parse_options(t_execute *info, char *line);
char *parse_command(t_execute *info, char *line);

// Начало парсинга
char	*isHandle(t_execute *info, char *line);
void	start_parse(t_execute *info, char *line);

// Мемная функция
void printDir();

#endif