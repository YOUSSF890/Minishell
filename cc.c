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
        printf("++++\n");
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
}char *ft_strlen_key(int *i,char *str)
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
        printf("++++\n");
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




void ft_exp2(t_node *lst, t_env *my_env,char *dap,int *i, int *a)
{
    int j;
    int b;
    char src[100];

    j = 0;
    (*i)++;
    while((lst->data[*i] >= 97 && lst->data[*i] <= 122) 
        || (lst->data[*i] >= 65 && lst->data[*i] <= 90) || (lst->data[*i] == 95))
    {
        printf("\n----------00%p\n",i);
        src[j++] = lst->data[(*i)++];
        printf("\n---------------%p\n",i);
    }
    src[j] = '\0';
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

\\\\\\\\\\\\\\\\\

void ft_handle_double_single(char *input, int *i, t_list **lst)
{
    int a;
    int t = 0;
    int quote_count = 1;
    int q = 1;
    char temp[100];
    a = *i;
    while (input[*i])
    {
        if (input[a] == '\"' && input[*i] == '\"')
            quote_count++;
        if (input[a] == '\'' && input[*i] == '\'')
            q++;
        while((quote_count % 2 == 0 && input[a] == '\"') || (q % 2 == 0 && input[a] == '\''))
        {
            if(*i != a && ((input[*i] == '\"' && input[a] == '\"') || (input[*i] == '\'' && input[a] == '\'')))
                break ;
            temp[t++] = input[*i];
            (*i)++;
            if(input[*i] == '\0') // break; دشي علاش مع توصل \0 دير  "ls d""skfjfe حيت هدي تبقى تقرى لا م نهاية فية حالة كان
            {
                printf("eroor\n");
                break;
            }
        }
        if (((input[a] == '\"') || input[a] == '\'') && input[*i])
        {
            temp[t++] = input[*i];
            (*i)++;
            if(input[*i])
            {
                a = *i;
                if(input[a] == '\"')
                    quote_count++;
                else if(input[a] == '\'')
                    q++;
                else
                {
                    temp[t++] = input[(*i)++];
                    quote_count = 1;
                    a = *i;
                }
            }
        }
        if ((input[*i] == ' ' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
        {
            if(input[*i] == '\0') // باش متبداش تقرة لية من مور '\0'
                ;
            else
                (*i)++;
            break;
        }
    }
    temp[t] = '\0';
    ft_lstadd_back(lst, ft_lstnew(temp));
}


////
if (((input[a] == '\"') || input[a] == '\'') && input[*i])
        {
            if(input[a] == '\"')
            {
                temp[t++] = input[(*i)++];
                quote_count++;
            }
            else if(input[a] == '\'')
            {
                temp[t++] = input[(*i)++];
                q++;
            }
            else
            {
                temp[t++] = input[(*i)++];
            }
            a = *i;
        }


/////////////////////////////////////

// void ft_handle_double_single(char *input, int *i, t_list **lst)
// {
//     int a;
//     int t = 0;
//     int quote_count = 1;
//     int q = 1;
//     char temp[100];
//     a = *i;
//     while (input[*i])
//     {
//         if (input[a] == '\"' && input[*i] == '\"')
//             quote_count++;
//         if (input[a] == '\'' && input[*i] == '\'')
//             q++;
//         while((quote_count % 2 == 0 && input[a] == '\"') || (q % 2 == 0 && input[a] == '\''))
//         {
//             if(*i != a && ((input[*i] == '\"' && input[a] == '\"') || (input[*i] == '\'' && input[a] == '\'')))
//                 break ;
//             temp[t++] = input[*i];
//             (*i)++;
//             if(input[*i] == '\0') // break; دشي علاش مع توصل \0 دير  "ls d""skfjfe حيت هدي تبقى تقرى لا م نهاية فية حالة كان
//             {
//                 printf("eroor\n");
//                 break;
//             }
//         }
//         if (((input[a] == '\"') || input[a] == '\'') && input[*i])
//         {
//             temp[t++] = input[*i];
//             (*i)++;
//             if(input[*i])//  echo "$HOME$"$"youssef"    input[*i] = '\0'  او هدي *i++ حيت هدي نزيد ب
//             {
//                 a = *i;
//                 if(input[a] == '\"')
//                     quote_count++;
//                 else if(input[a] == '\'')
//                     q++;
//                 else
//                 {
//                     temp[t++] = input[(*i)++];
//                     quote_count = 1;
//                     q = 1;
//                     a = *i;
//                 }
//             }
//         }
//         if ((input[*i] == ' ' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<' || input[*i] == '\0'))
//         {
//             if(input[*i] == '\0') // باش متبداش تقرة لية من مور '\0'
//                 ;
//             else
//                 (*i)++;
//             break;
//         }
//     }
//     temp[t] = '\0';
//     ft_lstadd_back(lst, ft_lstnew(temp));
// }