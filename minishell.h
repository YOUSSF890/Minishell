#ifndef MINSHELL_H
# define MINSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_list
{
    char            *content;
    int             type;
    // int             eroor;
    struct s_list   *next;
}                   t_list;

typedef struct t_node
{
    char            *data;
    int             type;
    struct t_node   *next;
}                   t_node;

typedef struct t_env
{
	char *key;
	char *value;
	struct t_env *next;
}				t_env;

typedef struct t_handel
{
	char temp[100];
    int t;
    int q;
    int quote_count;
    int a;
	struct t_handel *next;
}				t_handel;



int ft_fun(char *input,t_list **lst);
t_node *ft_type_comente_in_out_put(t_list *lst);

void ft_lstadd_back1(t_node **lst, t_node *new_node);
t_node *ft_lstnew1(char *content, int type);

void ft_lstadd_back(t_list **lst, t_list *new_node);
t_list *ft_lstnew(char *content);
void ft_pips(char *input, int *i, t_list **lst);
int ft_handle_double_single(char *input, int *i, t_list **lst);
int ft_handle_string(char *input, int *i, t_list **lst);

t_env	*ft_lstnewt(char *env_key, char *env_value);
void	claiming_env(char **env_p, t_env *my_env);
void	ft_lstadd_back12(t_env **lst, t_env *new);


int ft_handle11(char *input,int *i,t_handel *handel);
void ft_handle33(char *input,int *i,t_handel *handel);


#endif
