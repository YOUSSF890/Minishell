#include "minishell.h"

t_list *ft_fun(char *input)
{
    int i;
    t_list *lst;

    i = 0;
    lst = NULL;
    while (input[i])
    {
        while (input[i] && input[i] != ' ')
        {
            if (input[i] == '|' || input[i] == '<' || input[i] == '>')
                ft_pips(input, &i, &lst);
            else if (input[i] == '\"' || input[i] == '\'')
                ft_handle_double_single(input, &i, &lst);
            else
                ft_handle_string(input, &i, &lst);
        }
        if (input[i] == ' ')
            i++;
    }
    // t_list *tmp = lst;
    // while (tmp)
    // {
    //     printf("Token: [%s]\n", tmp->content);
    //     tmp = tmp->next;
    // }
    return(lst);
}

void ft_syntax_erorr(t_list *lst)
{
    if(lst->content[0] == '|' || (((lst->content[0] == '<' || lst->content[0] == '>') && (lst->next == NULL)))
        || ((lst->content[0] == '<' || lst->content[0] == '>') && (lst->next->content[0] == '|' || lst->next->content[0] == '<' || lst->next->content[0] == '>')))
    {
        printf("bash: syntax error near unexpected token `%c'\n",lst->content[0]);
    }
    else
    {
        while(lst->next)
        {
            if((lst->content[0] == '<' || lst->content[0] == '>')
                && (lst->next->content[0] == '|' || lst->next->content[0] == '<' || lst->next->content[0] == '>'))
            {
                printf("bash: syntax error near unexpected token `%s'\n", lst->next->content);
            }
            else if((lst->content[0] == '|') && (lst->next->content[0] == '|'))
            {
                printf("bash: syntax error near unexpected token `|'\n");
            }
            lst = lst->next;
            if (lst->next == NULL && (lst->content[0] == '|' || lst->content[0] == '<' || lst->content[0] == '>'))
            {
                printf("bash: syntax error near unexpected token `newline'\n");
            }
        }
    }
}


t_node *ft_type_comente_in_out_put(t_list *lst) 
{
    t_node  *arg;
    arg = NULL;
    while(lst)
    {
        if(lst->content[0] == '<' || lst->content[0] == '>')
        {
            if(lst->content[0] == '<' && lst->content[1] == '\0')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,1));
            else if(lst->content[0] == '>' && lst->content[1] == '\0')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,2));
            else if(lst->content[0] == '<' && lst->content[1] == '<')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,3));
            else if(lst->content[0] == '>' && lst->content[1] == '>')
                ft_lstadd_back1(&arg, ft_lstnew1(lst->next->content,4));
            lst = lst->next;
        }
        else if(lst->content[0] == '|')
            ft_lstadd_back1(&arg, ft_lstnew1(lst->content,5));
        else
            ft_lstadd_back1(&arg, ft_lstnew1(lst->content,0));
        lst = lst->next;
    }
    t_node *tmp = arg;
    while (tmp)
    {
        printf("Token: [%s]---->{%d}\n", tmp->data,tmp->type);
        tmp = tmp->next;
    }
    return(arg);
}
void ft_copy(char *dap, char *str, int *a)
{
    int i;

    i = 0;
    while(str[i])
    {
        dap[*a] = str[i];
        i++;
        (*a)++;
    }
}

char *ft_strlen_key(int *i,char *str)
{
    int a;
    int j;
    int len_key;
    char *src;
    a = *i;
    j = 0;
    while((str[a] >= 97 && str[a] <= 122) 
        || (str[a] >= 65 && str[a] <= 90) || (str[a] == 95))
    {
        len_key++;
        a++;
    }
    src = malloc(sizeof(char) * len_key + 1);
    while(((str[*i] >= 97 && str[*i] <= 122) 
        || (str[*i] >= 65 && str[*i] <= 90) || (str[*i] == 95)))
    {
        src[j++] = str[(*i)++];
    }
    src[j] = '\0';
    return (src);
}

void ft_exp2(t_node *lst, t_env *my_env,char *dap,int *i, int *a)
{
    int b;
    char *src;

    (*i)++;
    if((lst->data[*i] >= 97 && lst->data[*i] <= 122) 
        || (lst->data[*i] >= 65 && lst->data[*i] <= 90) || (lst->data[*i] == 95))
    {
        src = ft_strlen_key(i,lst->data);
    }
    while(my_env)
    {
        b = 0;
        while(my_env->key[b])
        {
            if(my_env->key[b] != src[b])
                break;
            b++;
        }
        if(my_env->key[b] || src[b])
            my_env = my_env->next;
        else
        {
            ft_copy(dap, my_env->value, a);
            break ;
        }
    }
}

void ft_strlen_$(int *i,char *lst)
{
    int t;
    t = 0;
    while(lst[*i] == '$')
    {
        (*i)++;
        t++;
    }
    if(t % 2 == 1)
    {
        (*i)--;
    }
}

void ft_exp(t_node *lst, t_env *my_env, int t)
{
    int a;
    int i;
    int y;
    char *dap;

    dap = malloc(sizeof(char) * (t + 1));
    a = 0;
    i = 0;
    y = 0;
    while(lst->data[i])
    {
        if(lst->data[i] == '$' && ((lst->data[i + 1] >= 97 && lst->data[i+1] <= 122)
            || (lst->data[i + 1] >= 65 && lst->data[i+1] <= 90) || (lst->data[i+1] == 95)))
                ft_exp2(lst, my_env,dap, &i, &a);
        else
        {
            if(lst->data[i] == '$' && lst->data[i+1] == '$')
                ft_strlen_$(&i,lst->data);
            else if(lst->data[i] == '$' && lst->data[i+1] == '\"')
            {
                y++;
                if(y % 2 == 0)
                    dap[a++] = lst->data[i];
                i++;
            }
            else
                dap[a++] = lst->data[i++];
        }
    }
    dap[a] = '\0';
    lst->data = dap;
}
void ft_expand_variables(t_node *lst, t_env *my_env)
{
    int i;
    int a;

    i = 0;
    a = 0;
    t_node *tmp = lst;
    while(lst)
    {
        i = 0;
        if(lst->data[0] != '\'')
        {
            a = 0;
            while(lst->data[i])
            {
                if(lst->data[i] == '$')
                    a++;
                i++;
            }
            if(a > 0)
            {
                ft_exp(lst, my_env, i);
            }
        }
        lst = lst->next;
    }
    while (tmp)
    {
        printf("Token: [%s]\n", tmp->data);
        tmp = tmp->next;
    }
}

int main(int argc, char **argv, char **envp)
{
    t_list *lst;
    t_node *arg;
    t_env *my_envp;

    lst = NULL;
    arg = NULL;
    while (1)
    {
        char *input = readline("minishell> ");
        if (!input)
            break ;
        add_history(input);
        lst = ft_fun(input);
        ft_syntax_erorr(lst);
        arg = ft_type_comente_in_out_put(lst);
        // claiming_env(envp, my_envp);
        my_envp->key = "HOME";
        my_envp->value = "YOUST";
        my_envp->next = NULL;
        ft_expand_variables(arg, my_envp);
    }
    return 0;
}
