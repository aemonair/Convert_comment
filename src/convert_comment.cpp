#include "convert_comment.h"

char *judge(char *input_string, char *output_string);

void Event(char character);
void event_no_pro(char character);
void event_cl_pro(char character);
void event_cp_pro(char character);
void event_st_pro(char character);

typedef enum
{
    NO_COMMENT_STATE,
    CL_COMMENT_STATE,
    CP_COMMENT_STATE,
    STR_COMMENT_STATE,
    END_STAGE
}STATE_ENUM;

typedef struct state
{
    FILE        *input_file;
    FILE       *output_file;
    STATE_ENUM      ulstate;
}STATE_MACHINE;

STATE_MACHINE g_state;
STATE_ENUM    OLD_COMMENT_STATE;

int convert_comment(FILE *input_file,FILE *output_file)
{
    char ch ;
    if(input_file == NULL || output_file == NULL)
    {
        cout<<"Argument Error !"<<endl;
        return -1;
    }

    cout<<"convert_comment:"<<endl;

    g_state.input_file  =       input_file;
    g_state.output_file =      output_file;
    g_state.ulstate     = NO_COMMENT_STATE;
    
    while((ch = fgetc(g_state.input_file))!= EOF)
    {
        //cout<<"ch"<<ch<<endl;
        Event(ch);
    }
}

void Event(char character)
{
    //cout<<"character"<<character<<endl;
    switch (g_state.ulstate)
    {
    case NO_COMMENT_STATE:
        event_no_pro(character);
        break;
    case CL_COMMENT_STATE:
        event_cl_pro(character);
        break;
    case CP_COMMENT_STATE:
        event_cp_pro(character);
        break;
    case STR_COMMENT_STATE:
        event_st_pro(character);
        break;
    default:
        break;
    }
}
void event_no_pro(char character)
{
    //cout<<"Event_no_comment:"<<endl;
    char next_char;
    switch(character)
    { 
    case '/':
        //cout<<"nextchar:"<<next_char<<endl;
        next_char = fgetc(g_state.input_file);
        if(next_char == '/')
        {
            fputc(character, g_state.output_file);
            fputc('*', g_state.output_file);
            g_state.ulstate = CP_COMMENT_STATE;
        }
        else if(next_char == '*')
        {
            fputc(character, g_state.output_file);
            fputc('*', g_state.output_file);
            g_state.ulstate = CL_COMMENT_STATE;
        }
        break;
    case '"':
        fputc(character, g_state.output_file);
        g_state.ulstate   = STR_COMMENT_STATE;
        OLD_COMMENT_STATE = NO_COMMENT_STATE;
        break;
    default:
        //cout<<"char:"<<character<<endl;
        fputc(character, g_state.output_file);
        break;
    }

}
void event_cl_pro(char character)
{
    char next_char;
    switch(character)
    {
    case '*':
        next_char = fgetc(g_state.input_file);
        if(next_char == '/')
        {
            fputc(character, g_state.output_file);
            fputc('/', g_state.output_file);
            g_state.ulstate = NO_COMMENT_STATE;
        }
        else if(next_char == '*')
        {
            fputc(character, g_state.output_file);
            fputc(next_char, g_state.output_file);
        }
        else if(next_char == '\n')
        {
            fputc(character, g_state.output_file);
            fputc('/', g_state.output_file);
            fputc(next_char, g_state.output_file);
            g_state.ulstate = NO_COMMENT_STATE;
        }
        else
        {
            fputc(character, g_state.output_file);
            fputc(next_char, g_state.output_file);
        }
        break;
    case '/':
        next_char = fgetc(g_state.input_file);
        if(next_char == '/')
        {
            fputc(' ', g_state.output_file);
            fputc(' ', g_state.output_file);
        }
        else if(next_char == '\n')
        {
            fputc(character, g_state.output_file);
            fputc(next_char, g_state.output_file);
            g_state.ulstate = NO_COMMENT_STATE;
        }
        break;
    case '"':
        fputc(character, g_state.output_file);
        g_state.ulstate   = STR_COMMENT_STATE;
        OLD_COMMENT_STATE = CL_COMMENT_STATE;
        break;
    default:
        fputc(character, g_state.output_file);
        break;
    }
}
void event_cp_pro(char character)
{
    char next_char;
    switch(character)
    {
    case '/':
        next_char = fgetc(g_state.input_file);
        if(next_char == '/')
        {
            fputc(' ', g_state.output_file);
            fputc(' ', g_state.output_file);
        }
        else if(next_char == '*')
        {
            fputc(' ', g_state.output_file);
            fputc(' ', g_state.output_file);
        }
        else
        {
            fputc(next_char, g_state.output_file);
        }
        break;
    case '\n':
        fputc('*',g_state.output_file);
        fputc('/',g_state.output_file);
        fputc(character, g_state.output_file);
        g_state.ulstate = NO_COMMENT_STATE;
        break;
    case '*':
        next_char = fgetc(g_state.input_file);
        if(next_char == '/')
        {
            fputc(' ', g_state.output_file);
            fputc(' ', g_state.output_file);
        }
        break;
    case '"':
        fputc(character, g_state.output_file);
        g_state.ulstate   = STR_COMMENT_STATE;
        OLD_COMMENT_STATE = CP_COMMENT_STATE;
        break;
    default:
        fputc(character, g_state.output_file);
        break;
    }
}
void event_st_pro(char character)
{
    switch(character)
    {
    case '"':
        fputc(character, g_state.output_file);
        g_state.ulstate = OLD_COMMENT_STATE;
        break;
    case '*':
        fputc(character, g_state.output_file);
        fputc('\', g_state.output_file);
    default:
        fputc(character, g_state.output_file);
        break;
    }
}
