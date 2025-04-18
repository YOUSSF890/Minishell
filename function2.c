#include "minishell.h"


int ft_handle11(char *input,int *i,t_handel *handel)
{
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
            return(0);
        }
    }
    return(1);
}

void ft_handle33(char *input,int *i,t_handel *handel)
{
    if (((input[*i] == '\"') || input[*i] == '\'') && input[*i])
    {
        handel->temp[(handel->t)++] = input[*i];
        (*i)++;
        if(input[*i]) //  echo "$HOME$"$"youssef"    input[*i] = '\0'  او هدي *i++ حيت هدي نزيد ب
        {
            handel->a = *i;
            if(input[handel->a] == '\"')
                handel->quote_count = 1;
            else if(input[handel->a] == '\'')
                handel->q = 1;
            else if(input[*i] != ' ' && input[*i])
            {
                handel->temp[(handel->t)++] = input[(*i)++];
                handel->quote_count = 1;
                handel->q = 1;
                handel->a = *i;
            }
        }
        else
        {
            handel->temp[(handel->t)++] = input[(*i)++];
        }
    }
}