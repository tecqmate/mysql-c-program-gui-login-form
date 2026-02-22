#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "config.h"

int auth_login(const char *username, const char *password) {

    DBConfig config;

    if (!load_config(&config)) {
        printf("Config load failed\n");
        return 0;
    }

    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn,
                            config.host,
                            config.user,
                            config.password,
                            config.database,
                            config.port,
                            NULL,
                            0)) {
        printf("DB Connection Failed\n");
        mysql_close(conn);
        return 0;
    }

    const char *query =
        "SELECT id FROM users WHERE username=? AND password=?";

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, query, strlen(query));

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)password;
    bind[1].buffer_length = strlen(password);

    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    mysql_stmt_store_result(stmt);

    int rows = mysql_stmt_num_rows(stmt);

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return rows > 0;
}
