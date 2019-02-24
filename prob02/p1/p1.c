#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PWD_LEN 50

int main()
{
    struct termios term, old_term;
    int i = 0;
    char pass[MAX_PWD_LEN + 1], ch, echo = '*';

    write(STDOUT_FILENO, "Pass: ", 6);
    tcgetattr(STDIN_FILENO, &old_term);
    term = old_term;
    term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
    while(i < MAX_PWD_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\n'){
        pass[i++] = ch;
        write(STDOUT_FILENO, &echo, 1);
    }
    pass[i] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    write(STDOUT_FILENO, "\n\nPassword: ", 12);
    write(STDOUT_FILENO, pass, strlen(pass));
    write(STDOUT_FILENO, "\n", 1);
    return 0;
}