#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

int load_config(DBConfig *config) {

    FILE *file = fopen(".env", "r");
    if (!file) return 0;

    char line[256];

    while (fgets(line, sizeof(line), file)) {

        char key[100], value[100];

        if (sscanf(line, "%[^=]=%s", key, value) == 2) {

            if (strcmp(key, "DB_HOST") == 0)
                strcpy(config->host, value);

            else if (strcmp(key, "DB_USER") == 0)
                strcpy(config->user, value);

            else if (strcmp(key, "DB_PASS") == 0)
                strcpy(config->password, value);

            else if (strcmp(key, "DB_NAME") == 0)
                strcpy(config->database, value);

            else if (strcmp(key, "DB_PORT") == 0)
                config->port = atoi(value);
        }
    }

    fclose(file);
    return 1;
}
