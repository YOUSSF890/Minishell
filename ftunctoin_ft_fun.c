#include "minishell.h"

void ft_lstadd_back(t_list **lst, t_list *new_node)
{
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    t_list *temp = *lst;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}


t_list *ft_lstnew(char *content)
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->content = strdup(content);
    new_node->next = NULL;
    return new_node;
}

void ft_pips(char *input, int *i, t_list **lst)
{
    char temp[100];
    int a = 0;
    temp[a++] = input[*i];

    if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<'))
    {
        (*i)++;
        temp[a++] = input[*i];
    }
    temp[a] = '\0';
    ft_lstadd_back(lst, ft_lstnew(temp));
    (*i)++;
}

int ft_handle_double_single(char *input, int *i, t_list **lst)
{
    t_handel *handel;
    handel = ft_lstnew_handl(*i);
    handel->temp = malloc(sizeof(char) * (ft_handle2(input, *i, handel) + 1));
    handel->a = *i;
    while(input[*i])
    {
        if(!ft_handle1(input,i,handel))
            return(0);
        ft_handle3(input,i,handel);
        if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
        {
            break;
        }
    }
    handel->temp[handel->t] = '\0';
    ft_lstadd_back(lst, ft_lstnew(handel->temp));
    return(1);
}
int ft_handle_string(char *input, int *i, t_list **lst)
{
    t_handel *handel;
    handel = ft_lstnew_handl(*i);
    handel->temp = malloc(sizeof(char) * (100 + 1));

    while (input[*i] && (input[*i] != ' ' || input[*i] == '\t') && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
    {
        if(input[*i] == '\"' || input[*i] == '\'')
        {
            handel->a = *i;
            while(input[*i])
            {
                if(!ft_handle1(input,i,handel))
                    return(0);
                ft_handle3(input,i,handel);
                if ((input[*i] == ' ' || input[*i] == '\t' || input[*i] == '|' || input[*i] == '>'
                    || input[*i] == '<' || input[*i] == '\0'))
                {
                    break ;
                }
            }
        }
        else
            handel->temp[(handel->t)++] = input[(*i)++];
        if(input[*i - 1] == '\0' || input[*i - 1] == ' ' || input[*i - 1] == '\t')
            break ;
    }
    handel->temp[handel->t] = '\0';
    ft_lstadd_back(lst, ft_lstnew(handel->temp));
    return(1);
}
