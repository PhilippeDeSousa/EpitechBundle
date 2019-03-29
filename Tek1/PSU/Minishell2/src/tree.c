#include "minishell.h"

static const char *OPERATORS[] = {
    "|",
    "<",
    "<<",
    ">",
    ">>",
    "&&"
};

void create_left(char **tab, t_tree *bin)
{
    t_tree *new = malloc(sizeof(t_tree));

    new->command = tab[0];
    new->left = NULL;
    new->right = NULL;
    create_tree(tab, new);
    bin->left = new;
}

void create_right(char **tab, t_tree *bin)
{
    t_tree *new = malloc(sizeof(t_tree));

    new->command = tab[0];
    new->left = NULL;
    new->right = NULL;
    create_tree(tab, new);
    bin->right = new;
}

void separate_lines(int i, char **tab, t_tree *bin)
{
    char **tmp1;
    char **tmp2;
    int size1;
    int size2;
    int j;

    bin->command = tab[i];
    for (size1 = 0; size1 < i; size1++);
    for (size2 = i + 1; tab[size2]; size2++);
    tmp1 = malloc(sizeof(char *) * (size1 + 1));
    for (j = 0; j < size1; j++)
        tmp1[j] = tab[j];
    tmp1[j] = NULL;
    tmp2 = malloc(sizeof(char *) * (size2 + 1));
    for (j = i + 1; tab[j]; j++)
        tmp2[j - (i + 1)] = tab[j];
    tmp2[j - (i + 1)] = NULL;
    create_left(tmp1, bin);
    create_right(tmp2, bin);
    free(tmp1);
    free(tmp2);
}

void create_tree(char **tab, t_tree *tree) {
    for (int i = 1; tab[i]; i++) {
        for (size_t j = 0; j < sizeof(OPERATORS) / sizeof(*OPERATORS); j++)
            if (my_strcmp(OPERATORS[j], tab[i]) == 0) {
                separate_lines(i, tab, tree);
                break;
            }
    }
}

void print_tree(t_tree *bin)
{
    if (bin->left) {
        printf("Je vais à gauche: \n");
        print_tree(bin->left);
    }
    printf("%s\n", bin->command);
    if (bin->right) {
        printf("Je vais à droite: \n");
        print_tree(bin->right);
    }
}
