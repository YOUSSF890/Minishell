// #include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_list
{
    char *content;
    struct s_list *next;
}                  t_list;

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *tmp;

    if (*lst == NULL) {
        *lst = new;
    } else {
        tmp = *lst;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
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

void ft_fun(char *input)
{
    int i = 0;
    int j = 0;
    int a = 0;
    int y = 0;

    t_list *lst = NULL;
    char temp[100];
    while(input[i])
    {
        while (input[i] && input[i] != ' ')
        {
            a = 0;
            if(input[i] == '|' || input[i] == '>' || input[i] == '<')
            {
                // ft_pips(input,&i lst);
                temp[a] = input[i];
                if((input[i] == '>' && input[i+1] == '>') || (input[i] == '<' && input[i+1] == '<'))
                {
                    a++;
                    i++;
                    temp[a] = input[i];
                }
                temp[a+1] = '\0';
                t_list *new_node = ft_lstnew(temp);
                ft_lstadd_back(&lst, new_node);
                i++;
            }
            else if(input[i] == '\"' || input[i] == '\'')
            {
                // ft_handle_double_single(input, &i, lst);
                if (input[i] != ' ' && input[i])
                {
                    
                    while(input[i])
                    {
                        if(input[i] == '\"')
                            y++;
                        if(y % 2 == 0 && (input[i+1] == '|' || input[i+1] == '>' || input[i+1] == '<' || input[i+1] == ' '))
                        {
                            temp[a] = input[i];
                            a++;
                            i++;
                            break;
                        }
                        temp[a] = input[i];
                        a++;
                        i++;
                    }
                    temp[a] = '\0';
                    t_list *new_node = ft_lstnew(temp);
                    ft_lstadd_back(&lst, new_node);
                }
            }
            else
            {
                // void ft_handle_string(input,i,lst);
                while(input[i] && input[i] != ' ' && input[i] != '|'
                    && input[i] != '>' && input[i] != '<')
                {
                    if(input[i] == '\"' || input[i] == '\'')
                    {
                        while(input[i])
                        {
                            if(input[i] == '\"')
                                y++;
                            if(y % 2 == 0 && (input[i+1] == '|' || input[i+1] == '>' || input[i+1] == '<' || input[i+1] == ' '))
                            {
                                temp[a] = input[i];
                                a++;
                                i++;
                                break;
                            }
                            temp[a] = input[i];
                            a++;
                            i++;
                        }
                    }
                    else
                    {
                        temp[a++] = input[i];
                        i++;
                    }
                }
                temp[a] = '\0';
                t_list *new_node = ft_lstnew(temp);
                ft_lstadd_back(&lst, new_node);
            }
        }
        if(input[i] == ' ')
            i++;
    }
    t_list *tmp = lst;
    while (tmp) {
        printf("Command: [%s]\n", tmp->content);
        tmp = tmp->next;
    }
}

int main()
{

    while (1)
    {
        char *input = readline("Enter your command: ");
        if (!input)
            return (0);
        add_history(input);
        ft_fun(input);
    }
    
    return (0);
}