/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:49:37 by dantremb          #+#    #+#             */
/*   Updated: 2023/02/13 16:44:51 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void    perr(char *str){
    while (*str)
        write(2, str++, 1);
}

void cd(char **argv)
{
    if (argv[1] == NULL)
        return (perr("error: cd: bad arguments\n"), 1);
    else if (chdir(argv[1]) == -1)
    {
        perr("error: cd: cannot change directory to ")
        perr(argv[1])
        perr("\n")
    }
}

void exec(char **argv, char **envp, int i)
{
    int fd[2];
    int pip;

    if (argv[i] && !strcmp(argv[i], "|"))
        pip = 1;
    else
        pip = 0;
    if (pipe(fd) == -1)
        return (perr("error: fatal\n"), 1);
    int pid = fork();
    if (!pid)
    {
        argv[i] = 0;
        close(fd[0]);
        if (pip)
            dup2(fd[1], 1);
        else
            close(fd[1]);
        execve(*argv, argv, envp);
        return (perr("error: cannot execute "), perr(*argv), perr("\n"), 1);
    }
    close(fd[1]);
    if (pip)
        dup2(fd[0], 0);
    else
        close(fd[0]);
    waitpid(pid, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    int i = 0;
  
    while (*argv && *(argv + 1))
    {
        ++argv;
        i = 0;
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (!strcmp(*argv, "cd"))
            cd(argv);
        else if (i)
            exec(argv, envp, i);
        argv += i;
    }
    return(0);
}