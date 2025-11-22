#include <unistd.h>
#include <stdio.h>
#include <libft.h>



typedef enum {
    PIPE, // "|"
    REDIR_IN, // "<""
    REDIR_OUT, // ">"
    HEREDOC, // "<<"
    APPEND, // ">>"
    WORD, // "str"
    END, 
    ERROR,
} token_type;

typedef enum {
    UNQUOTED,
    SINGLE_QUOTED,
    DOUBLE_QUOTED,
} token_origin;

typedef struct {
    token_type type;
    char* text;
    token_origin origin;
    int idx; // token idx
    t_token *next;
} t_token;

t_token *tokenize(char *line);
int emptyline(const char *line);