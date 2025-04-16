#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

const char fst[] = R"(
&&&&&&&&&&&&&&&&Xxx&&&&&$XXXxXxxxxxxxxxxxxxxxxxxxX&&$$X&&;;+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&x$$XXxxxXxxxxxxxxxxxxxxxxxxxxxxxx$&x;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&$xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&x&&&&&$&&&xxx+++++++++++xxxxxxxxxxxxxxxxxxxxxxxx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&xx&&&&$$&xx+++++++++++++++++++xxxxxxxxxxxxxxxxxxx&&&&$$$X$&&&X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&XXXX$$xxxx++++++++++++;+;+;++++++xxxxxxx+++x+xxxx$&$$$XXX$&xX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&$XX$$xx+x++++++++++;+;+;+;+;;;;+++++++xxx++++++x++x$$$XxxXXX$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&$$Xxxxxx+++++++;++;++++;+;+++;;;;;;;++++++++++++++xxXXxXxxX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&$xx+xxxx+++++++;;+xx+++++;+;++;;;;++;;;+++++++++;;;;;Xxx$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&xxxxxxxx++++++++;x+;;;;+;+;+;+;+;;+;+;;;;;;+++++;;;;;X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&x&$xxxxx+++++++;x+;;;;;+++++;;+;;+;;;;x;;;;;;+++;;;;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&$$&&&&&&&&xxxxxx+++++++xx;;;;;;;++;+;;;;xx$$XXXXx;;;;;;+;;;;;&&&&&&&&&&&$&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&XX$$$&&xxxxxxxx++++xx$&$$$$&&X;+;+;;;xx:X$X$X$;+;x;;;;;;;;;&&&$&&$&$XX&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&$$$$$&$xxxxxxx++XxxxX;;$$$$$$;;;;;+++$$X$$$$$:+;;+;;+;;;;;&&&X&XXXX$&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&X$$$$$$&&xxxxxxxx;xX$$$$$$$;;;++++;;X$$$$X:;;;;x;++;;;;;&XxXXXX$&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&$$$$$$X+xx$Xx++;;+$$$$$$$;;;;;;;;;;;Xx;:;;+;;;;;;;;;;;;;;;+$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&xxxXxxxx++;;;;xxx;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;&&&$&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&Xxxxxxxxxx+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;&$$&$&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&xxxxXxxXXxx+x+++;;;;;;;;;;;;;++$x;;;;;;;;;;;;;;;;;;;;;;$$&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&xxxxxX$$&&&Xx+$&&Xxx++++xx++xx$X&X;;;;;;;;;;;;;;;;;;+;;;$$$&&&&&&&&&&&&&&&&$$$$$$&&&&
&&&&&&&&&&&&&&xxxX$$&&&&&&&&$x+$$$X+$$$;+xxxxxXxx;;;;;;;;;;;;;;;;;;;;;+$&&&&&&&&&&&&&&&&&&&$$$$$$&&&
&&&&&&&&&&&&&xxX$$&&&&&&&&&&&&+x+xx+++;+x;x+Xxx+$;;;;;;;;;;;;;;;;;;;;+&&&&&&&&&&&&&&&&&&&&&&&&$$$&&&
&&&&&&&&&&&&&$xXX$&&&&&&&&&&&&;xxxx+Xx+xx;xx;x+;&x;;;;;;;;;;;;;;;;;;&&&&$$$&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&$+x$&&&&&&&&&&&&xxXxXx+Xxxxxxx++x;&&&;;;;;;;;;;;;;;;$&&&$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&
&&$&&&&&&&&&&&$Xx$&$&&&&&&&&&&&xXxxxXxxx;xxx+;++&&&;;;;;;;;;;;;;;;$$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&
$$$$$$&&&&&&XXXX$$&&&&&&&&&&&&&&&&&&$$XXXX$&&&&&&&&$+;;;;;;;;;+;;x$&$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&
$$$$$$&&&&XxXX$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&XXxxXXX$$&&&&&&&&&&&&&&&&&&&&&&&&&&&
&$$$$$&&$XXX$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&XXXxxXxxx&&&&&&&&&&&&&&&&&&&&&&&&$&&
&&&&&&&xxX$$&&&&&&&&&&&&&&&&&&;$$$$$$$$$$$$x+XXx&&&&&&&&&&&&&&&&XXXXXxXxxx$&&&&&&&&&&&&&&&&&&&&&&$$$
&&&&&XxxX$&&&&&&&&&&&&&&&&&&&&+xXxx;;x;;;;;;XXxx&&&&&&&&&&&&&&&&XXXxXxxxXxx$&&&&&&&&&&&&&&&&&&&&$$$$
)";

const char snd[] = R"(
&&&&&&&&&&&&&&&&Xxx&&&&&$XXXxXxxxxxxxxxxxxxxxxxxxX&&$$X&&;;+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&x$$XXxxxXxxxxxxxxxxxxxxxxxxxxxxxx$&x;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&xx&&&&&&&$XXXXxxxxxxxxxxxxx$&&X$XX&&;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&XxX&XXXxxxxxxxxxxxxxxxxxxxxx$&&x;x&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&xxxxxxxxxxxxxxxxxxxxxxxxxxxx$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&x&&&&$&&xx+x++++++++xxxxxxxxxxxxxxxxxxxx&&&&&&$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&Xx&&$$$xx+++++++++++;+++++xxxxxxxxxx+xxxx&&$$$x$$&$X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&XXX$$xxx+++++++++;+++;+;+;+++xxxx+x+++xxxX$$$XXxXx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&X$x+xxx++++++;++;+;;+;+;+;;;+;+++++++++++X&XxXxXx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&xxxxxx++++++;;+x++++;++;+;;;x;;;++++++++;;;xXxX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&xxxxxx++++++++x;;;+++;+;+;;;;;+;;;;;+++;;;;xX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&$$&&&&&&&&&&&&X&$xxxxx++++++x;;;;;++++;;;;+;;;;+;;;;+x+;;;x&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&X$&&&&&$$&$&&$xxxxx+++++xx;;;++x;+;+;;;&xX$$Xx;+;;;;;;;;x&&&&&&&&X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&$&&&&&&$$$X&xxxxxxx++xxx+;$$$$$x+;;;++$xX$$$x;+;+;+;;;;x&&&&XXXX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$$$$$$&xxxxxXx;X$$$$$$$;;+++;;X$$$X::+;x;x+;;;x&xxXXX$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&$X$$$+xxXX+x;;x$$X$X;;;;;;;;;;x::;;;+;;;;;;;;;;;+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&+xxxxxx+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;&&$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&xxxxxxxx++;;;;;;;;;;;;;;;;+;;;;;;;;;;;;;;;;;+$$&$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&xxxxxX$$$x+$$xx+++;;++x+x$$&;;;;;;;;;;;;;;;;;;;&$&&&&&&&&&&&&&&$$$&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&xxX$$$&&&&&$x+$$$XX$x+xx+xXxX;;;;;;;;;;;;;;;;;;$$&&&&&&&&&&&&&&&$$$$$&&&&$$$&&&&
&&&&&&&&&&&&&&&&&&&xXX$$&&&&&&&&&$x+x++xx;xx+XX+&;;;;;;;;;;;;;;;;;$&&&&&&&&&&&&&&&&&&&&$$&&&&$$$$&&&
&&&&&&&&&&&&&&&&&&&&xxX&&&&&&&&&&Xxxx;xx;xxx+;x+&&;;;;;;;;;;;;;;x&&$$$$&&&&&&&&&&&&&&&&&&&&&&&$$$&&&
&&&&&&&&&&&&&&&&&&&&&xx&&&&&&&&&&&x$XxXxxxx;;;;;&&&;;;;;;;;;;;;x$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&$$$$&&&&&&XXX$&&&&&&&&&&&&&$$xxxxx+xxx$&&&;;;;;;;;;;;;$$$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&$&&&&&$$$$$$&&&XXX$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$XxxXX$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
$$$$$$&&&&$$$&&XxX$$&&&&&&&&&&&&&&$&&&&&&&&&&&&$&&&&$&&&&&&&&$XXxXxxx$&&&&&&&&&&&&&&&&&&&$&&&&&&&&&&
$$$$$$&&&&&&&$xx$$&&&&&&&&&&&&&&&x$$XxXXXxxx;xX;&&&&&&&&&&&&&$XXXXxXxxX&&&&&&&&&&&&&&&&&&$$$&&&&&&&&
&$$$$$&&&&&&XxX$$&&X&&&&&&&&&&&&&;+$+xxxxX;;;;X;&&&&&&&&&&&&&&XXXxXxXxx$$&&&&&&&&&&&&&&&&$$$&&&&&$&&
&&&&&&&xxX$$&&&&&&&&&&&&&&&&&&;$$$$$$$$$$$$x+XXx&&&&&&&&&&&&&&&&XXXxXxXxxx$&&&&&&&&&&&&&&&&&&&&&&$$$
&&&&&XxxX$&&&&&&&&&&&&&&&&&&&&+xXxx;;x;;;;;;XXxx&&&&&&&&&&&&&&&&XXXXXxxxXxx$&&&&&&&&&&&&&&&&&&&&$$$$
)";

const char trd[] = R"(
&&&&&&&&&&&&&&&&Xxx&&&&&$XXXxXxxxxxxxxxxxxxxxxxxxX&&$$X&&;;+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&x$$XXxxxXxxxxxxxxxxxxxxxxxxxxxxxx$&x;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&xx&&&&&&&$XXXXxxxxxxxxxxxxx$&&X$XX&&;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&XxX&XXXxxxxxxxxxxxxxxxxxxxxx$&&x;x&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&xxxxxxxxxxxxxxxxxxxxxxxxxxxx$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$&&&&&&&&&&&&xx&$XXxxXxxxxxxxxxxxxxX&&&;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$&&&&&&&&&&&&&$xxxxxxxxxxxxxxxxxxxxxxx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&$$&&&$&xx+++++++++xxxxxxxxxxxxxxx&&&&&X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&XX$$$xx++++++++++;+++++xxxxx+xxxx$&$$X$&X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&X$x+xx++++++++;++;+;+++++++++++++x$XxXxX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&xxxxx++++;;;x+++;++;;;;+;;++++++;;;Xxx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&$$&&&&&&&&&&&&&&&&&&&xxxxx++++++x;;;;+;+;+;;;;;;;;+++;;;x&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&X$&&&&&$$&$&&$&&&&&&xxxxx++++x;;;;;++;+;xxX$$$;;;;+;;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&$&&&&&&$$$&&&&$$$&xxxxxx++x$x$$$$&+;;;+$;X$X+;;+;;;;;$&&&$$XX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$&&&&&X$$$$&$xxXxx;X$$$$X;+++;+$$$X:;;x;x;;;$&xXXX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&$$$x+XXxx;;$$$$x;;;;;;;;:;;;;;;;;;;;;;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&xxxxxx+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;&$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&xxxxX$x+Xx++;;;;;;;+x$;;;;;;;;;;;;;;;x$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&xx$$&&&&&x+$$$+XxxxxxX&+;;;;;;;;;;;;;;&$&&&&&&&&&&&$$$$$&&&$$&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&xX$$&&&&&&&&xxx+xX++xxxx;;;;;;;;;;;;;;&&&&&&&&&&&&&&&&&$$&&&$$$$&&&&$$$&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&xx&&&&&&&&&xxxx;++xx;xx&;;;;;;;;;;;$&&$$$&&&&&&&&&&&&&&&&&&&&$$&&&&$$$$&&&
&&&&&&&&&&&&&&&&&$$&&&&&&&Xx&&&&&&&&&xxxxxx+xx;;$&&;;;;;;;;;;$$$$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&$$$&&&
&&&&&&&&&&&&&&&&$$$$$&&$XX$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&XXXX$$$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&$$$$&&&&&$$&&xX$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$XxxXxx&&&&&&&&&&&&&&&&$&&&&&&&&&&&&&&&&&
&&$&&&&&$$$$$$&&&&&&xXX$&&&&&&&&&&&&x$x;xx+x;;XX$&&&&&&&&&&$XXXxXxx&&&&&&&&&&&&&&&$$&&&&&&&&&&&&&&&&
$$$$$$&&&&$$$&&XxX$$&&&&&&&&&&&&&&$&&&&&&&&&&&&$&&&&$&&&&&&&&$XXxXxxx$&&&&&&&&&&&&&&&&&&&$&&&&&&&&&&
$$$$$$&&&&&&&$xx$$&&&&&&&&&&&&&&&x$$XxXXXxxx;xX;&&&&&&&&&&&&&$XXXXxXxxX&&&&&&&&&&&&&&&&&&$$$&&&&&&&&
&$$$$$&&&&&&XxX$$&&X&&&&&&&&&&&&&;+$+xxxxX;;;;X;&&&&&&&&&&&&&&XXXxXxXxx$$&&&&&&&&&&&&&&&&$$$&&&&&$&&
&&&&&&&xxX$$&&&&&&&&&&&&&&&&&&;$$$$$$$$$$$$x+XXx&&&&&&&&&&&&&&&&XXXxXxXxxx$&&&&&&&&&&&&&&&&&&&&&&$$$
&&&&&XxxX$&&&&&&&&&&&&&&&&&&&&+xXxx;;x;;;;;;XXxx&&&&&&&&&&&&&&&&XXXXXxxxXxx$&&&&&&&&&&&&&&&&&&&&$$$$
)";

const char frt[] = R"(
&&&&&&&&&&&&&&&&Xxx&&&&&$XXXxXxxxxxxxxxxxxxxxxxxxX&&$$X&&;;+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&x$$XXxxxXxxxxxxxxxxxxxxxxxxxxxxxx$&x;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&xx&&&&&&&$XXXXxxxxxxxxxxxxx$&&X$XX&&;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&XxX&XXXxxxxxxxxxxxxxxxxxxxxx$&&x;x&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&xxxxxxxxxxxxxxxxxxxxxxxxxxxx$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$&&&&&&&&&&&&xx&$XXxxXxxxxxxxxxxxxxX&&&;;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$&&&&&&&&&&&&&$xxxxxxxxxxxxxxxxxxxxxxx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&$&&&&&&&&&&&x$XxXxxxxxxxxxxxxx&&;&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$&&xx+x+xxxxxxxxxxxxxxx&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&x&&$Xx++++++++;++xxxxxxxxxx&$$X$&X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&X$xx+++++++;+;;;;+;++++++++$$XxXX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&$$&&&&&&&&&&&&&&&&&&&&&&&&xxxx+++;;++;+++;;;++;;++++;;+x&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&X$&&&&&$$&$&&$&&&&&&&&&$&xxx++++x;;;+;+;+;;;+;;;++;;+&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&$&&&&&&$$$&&&&X$&&&$$$&xxxx+++xxX$x;+;;;xX$X:x;;;;;+&&&$&X&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&$&&&&&$&&&&$$$&&&xxxx+$$$$X;;+;$$$$:+;;x;;+&xXX$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$X+xx+;;$$$;;;;;;;;;;;;;;;;;;;$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$xxxxx+;;;;;;;;;;;;;;;;;;;;;;+$&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&xxX$&&x+&$xxxx;xX&;;;;;;;;;;;;;$&&&&&&&&&$$$&&&&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&xX$&&&&&&xxxx;xxx++;;;;;;;;;;;;&&&&&&&&&&&&&$$&&$$$$&&&$$&&&&&&&&&&&&&
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&Xx&&&&&&&;xxxx+xxx;&+;;;;;;;;&&$$$&&&&&&&&&&&&&&&&$$&&&$$$$&&&&$$$&&&&
&&&&&&&&&&&&&&&&&&&&&&&$$&&&&&XX&&&&&&&&&Xxxxx+;x&$;;;;;;;;$$$$$&&&&&&&&&&&&&&&&&&&&&&&$$&&&&$$$$&&&
&&&&&&&&&&&&&&&&&$$&&&$$$$&&XX$&&&&&&&&&&&&&&&&&&&&&&&&&&$XxxX&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&$$$&&&
&&&&&&&&&&&&&&&&$$$$$&&&&&xX$&&&&&&&&&&x$$XXXx;$+&&&&&&&&&XXXxxX&&&&&&&&&&&&$$&&&&&&&&&&&&&&&&&&&&&&
&&&&&&&&&$$$$&&&&&$$&&xX$$&&&&&&&&&&&&&&&&&&&&&&$&&&&&&&&&&$XxXXxx&&&&&&&&&&&&&&&&$&&&&&&&&&&&&&&&&&
&&$&&&&&$$$$$$&&&&&&xXX$&&&&&&&&&&&&x$x+xx+x;;XX$&&&&&&&&&&$XXXxXxx&&&&&&&&&&&&&&&$$&&&&&&&&&&&&&&&&
$$$$$$&&&&$$$&&XxX$$&&&&&&&&&&&&&&$&&&&&&&&&&&&$&&&&$&&&&&&&&$XXxXxxx$&&&&&&&&&&&&&&&&&&&$&&&&&&&&&&
$$$$$$&&&&&&&$xx$$&&&&&&&&&&&&&&&x$$XxXXXxxx;xX;&&&&&&&&&&&&&$XXXXxXxxX&&&&&&&&&&&&&&&&&&$$$&&&&&&&&
&$$$$$&&&&&&XxX$$&&X&&&&&&&&&&&&&;+$+xxxxX;;;;X;&&&&&&&&&&&&&&XXXxXxXxx$$&&&&&&&&&&&&&&&&$$$&&&&&$&&
&&&&&&&xxX$$&&&&&&&&&&&&&&&&&&;$$$$$$$$$$$$x+XXx&&&&&&&&&&&&&&&&XXXxXxXxxx$&&&&&&&&&&&&&&&&&&&&&&$$$
&&&&&XxxX$&&&&&&&&&&&&&&&&&&&&+xXxx;;x;;;;;;XXxx&&&&&&&&&&&&&&&&XXXXXxxxXxx$&&&&&&&&&&&&&&&&&&&&$$$$
)";

static char* cmd;
static char* term;
static const char* secret = " 0xbadcoffee";

char* get_term(char* ptr, uint32_t stop) {
    size_t sz = strlen(ptr);
    char* idx = ptr + sz;
    uint32_t i = 0;
    while (i != stop) {
        if (*idx == '-') {
            idx -= 3;
            ++i;
        } else {
            idx -= 1;
        }
    }
    idx += 4;
    ptr = idx;
    while (*idx != '-') {
        ++idx;
    }
    *idx = 0;
    return ptr;
}

void no_u(int signo) {
    if (!fork()) {
        execlp(term, "-e", "/bin/bash", "-c", cmd, NULL);
        // system("foot -e /bin/bash -c /home/archie/Desktop/junko_mw/a.out");
    }
    sleep(1);
    exit(0);
}

int main(int argc, char** argv) {
    uint32_t stop = 4;
    printf("%i\n", argc);
    printf("%s\n", argv[0]);
    if (argc == 2 && !strcmp("0xbadcoffee", argv[1])) {
        stop = 3;
    }
    size_t sz = strlen(*argv);
    size_t sz2 = strlen(getenv("PWD"));

    pid_t pid = getpid();
    char cmd_ps[21 + 13];
    strcpy(cmd_ps, "pstree -sA ");
    sprintf(cmd_ps + strlen(cmd_ps), "%ld", pid);

    FILE* fd = NULL;
    fd = popen(cmd_ps, "r");
    size_t termsz;
    term = NULL;
    getline(&term, &termsz, fd);
    term = get_term(term, stop);

    if (*argv[0] != '/') {
        cmd = malloc(sz + sz2 );
        memcpy(cmd, getenv("PWD"), sz2);
        memcpy(cmd + sz2, *argv + 1, sz - 1);
    }
    else {
        cmd = *argv;
    }
    char* tmp = cmd;
    cmd = malloc(strlen(tmp) + strlen(secret));
    cmd[0] = 0;
    strcat(cmd, tmp);
    strcat(cmd, secret);

    signal(SIGINT, no_u);
    signal(SIGSTOP, no_u);
    signal(20, no_u);
    signal(SIGTERM, no_u);
    signal(SIGABRT, no_u);

    while (4) {
        printf("%s", fst + 1);
        usleep(1000000 >> 1);
        printf("\e[1;1H\e[2J"); // xdd
        printf("%s", snd + 1);
        usleep(1000000 >> 1);
        printf("\e[1;1H\e[2J"); // xdd
        printf("%s", trd + 1);
        usleep(1000000 >> 1);
        printf("\e[1;1H\e[2J"); // xdd
        printf("%s", frt + 1);
        usleep(1000000 >> 1);
        printf("\e[1;1H\e[2J"); // xdd
        printf("%s", trd + 1);
        usleep(1000000 >> 1);
        printf("\e[1;1H\e[2J"); // xdd
        printf("%s", snd + 1);
        usleep(1000000 >> 1);
        printf("\e[1;1H\e[2J"); // xdd
    }
}
