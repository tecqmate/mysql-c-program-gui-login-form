#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char host[100];
    char user[100];
    char password[100];
    char database[100];
    int port;
} DBConfig;

int load_config(DBConfig *config);

#endif
