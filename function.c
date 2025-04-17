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
void ft_lstadd_back1(t_node **lst, t_node *new_node)
{
    if (!*lst)
    {
        *lst = new_node;
        return;
    }
    t_node *temp = *lst;
    while (temp->next)
        temp = temp->next;

    temp->next = new_node;
}

t_node *ft_lstnew1(char *content, int type)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->data = strdup(content);
    new_node->type = type;
    new_node->next = NULL;
    return new_node;
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

void ft_handle1(char *input,int *i,t_handel *handel)
{
    // handel->a = *i;
    if (input[handel->a] == '\"' && input[*i] == '\"')
        (handel->quote_count)++;
    if (input[handel->a] == '\'' && input[*i] == '\'')
        (handel->q)++;
    while((handel->quote_count % 2 == 0 && input[handel->a] == '\"') || (handel->q % 2 == 0 && input[handel->a] == '\''))
    {
        if(*i != handel->a && ((input[*i] == '\"' && input[handel->a] == '\"') || (input[*i] == '\'' && input[handel->a] == '\'')))
            break ;
        handel->temp[(handel->t)++] = input[*i];
        (*i)++;
        if (!input[*i]) // break; دشي علاش مع توصل \0 دير  "ls d""skfjfe حيت هدي تبقى تقرى لا م نهاية فية حالة كان
        {
            printf("eroor\n");
            break;
        }
    }
}

void ft_handle3(char *input,int *i,t_handel *handel)
{
    if (((input[*i] == '\"') || input[*i] == '\'') && input[*i])
    {
        handel->a = *i;
        handel->temp[(handel->t)++] = input[*i];
        (*i)++;
        if(input[*i]) //  echo "$HOME$"$"youssef"    input[*i] = '\0'  او هدي *i++ حيت هدي نزيد ب
        {
            if(input[handel->a] == '\"')
                (handel->quote_count)++;
            else if(input[handel->a] == '\'')
                (handel->q)++;
            else
            {
                handel->temp[(handel->t)++] = input[(*i)++];
                handel->quote_count = 1;
                handel->q = 1;
                handel->a = *i;
            }
        }
    }
}

int ft_handle2(char *input,int i,t_handel *handel)
{
    int n = 0;
    int q = 1;
    int quote_count = 1;
    while(input[i])
    {
        if (input[handel->a] == '\"' && input[i] == '\"')
            (quote_count)++;
        if (input[handel->a] == '\'' && input[i] == '\'')
            (q)++;
        if((quote_count % 2 == 1 && input[handel->a] == '\"' && (input[i + 1] == ' ' || input[i + 1] == '\0'))
            || (q % 2 == 1 && input[handel->a] == '\'' && (input[i + 1] == ' ' || input[i + 1] == '\0'))) // 
            break ;
        i++;
        n++;
    }
    return(n);
}


t_handel *ft_lstnew_handl(int i)
{
    t_handel *new_node = malloc(sizeof(t_handel));
    if (!new_node)
        return NULL;
    // new_node->a = i;
    new_node->t = 0;
    new_node->q = 1;
    new_node->quote_count = 1;
    new_node->next = NULL;
    return new_node;
}
void ft_handle_double_single(char *input, int *i, t_list **lst)
{
    t_handel *handel;
    handel = ft_lstnew_handl(*i);
    handel->temp = malloc(sizeof(char) * (ft_handle2(input, *i, handel) + 1));
    while(input[*i])
    {
        ft_handle1(input,i,handel);
        ft_handle3(input,i,handel);
        if ((input[*i] == ' ' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
        {
            if(input[*i] == '\0') // باش متبداش تقرة لية من مور '\0'
                ;
            else
                (*i)++;
            break;
        }
    }
    handel->temp[handel->t] = '\0';
    ft_lstadd_back(lst, ft_lstnew(handel->temp));
}


// void ft_handle_string(char *input, int *i, t_list **lst)
// {
//     // char *temp;
//     t_handel *handel;
//     handel = ft_lstnew_handl(*i);
//     handel->temp = malloc(sizeof(char) * (100 + 1));

//     while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
//     {
//         if(input[*i] == '\"' || input[*i] == '\'')
//         {
//             handel->a = *i;
//             while(input[*i])
//             {
//                 ft_handle1(input,i,handel);
//                 ft_handle3(input,i,handel);
//                 if ((input[*i] == ' ' || input[*i] == '|' || input[*i] == '>'
//                     || input[*i] == '<' || input[*i] == '\0'))
//                 {
//                     if(input[*i] == '\0') // باش متبداش تقرة لية من مور '\0'
//                         ;
//                     else
//                         (*i)++;
//                     break ;
//                 }
//             }
//         }
//         else
//         {
//             handel->temp[(handel->t)++] = input[*i];
//             (*i)++;
//         }
//         if(input[*i - 1] == '\0' || input[*i - 1] == ' ')
//             break ;
//     }
//     handel->temp[handel->t] = '\0';
//     ft_lstadd_back(lst, ft_lstnew(handel->temp));
// }

void ft_handle_string(char *input, int *i, t_list **lst)
{
    int a = 0;
    int quote_count = 0;
    char temp[100];

    while (input[*i] && input[*i] != ' ' && input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
    {
        if(input[*i] == '\"' || input[*i] == '\'')
        {
            while(input[*i])
            {
                if(input[*i] == '\"')
                    quote_count++;
                if(quote_count % 2 == 0 && (input[*i+1] == '|' || input[*i+1] == '>' || input[*i+1] == '<' || input[*i+1] == ' '))
                {
                    temp[a] = input[*i];
                    a++;
                    (*i)++;
                    break;
                }
                temp[a] = input[*i];
                a++;
                (*i)++;
            }
        }
        else
        {
            temp[a++] = input[*i];
            (*i)++;
        }
    }
    temp[a] = '\0';
    ft_lstadd_back(lst, ft_lstnew(temp));
}
