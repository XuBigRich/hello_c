#include "format.h"
#include <mysql.h>
#include <stdio.h>

int mysql_quey() {
  char *host = "127.0.0.1";
  char *user = "root";
  char *password = "rr998xhz1997";
  char *database = "user";
  MYSQL *conn;
  // 初始化mysql链接
  conn = mysql_init(NULL);
  // 建立mysql链接
  if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
    printf("Error connecting to database: %s\n", mysql_error(conn));
    return 1;
  }
  // 执行sql语句
  char *query = "select id,nick_name,username from user;";
  if (mysql_query(conn, query)) {
    printf("Error making query: %s\n", mysql_error(conn));
    return 1;
  }
  // 获取查询结果
  MYSQL_RES *result = mysql_store_result(conn);
  if (result == NULL) {
    printf("Error storing result: %s\n", mysql_error(conn));
    return 1;
  }
  //打印输出结果
  printf("查询结果:\n");
  printf("id\tnick_name\tusername\n");
  MYSQL_ROW row;
  while ( (row = mysql_fetch_row(result))!=NULL) {
    printf("%s\t%s\t%s\n",row[0],row[1],row[2]);
  }
  mysql_free_result(result);
  mysql_close(conn);
  return 0;
}
int main() {
  printf("Hello, World!\n");
  //使用自定义函数
  char a = result1();
  printf("%c", a);
  //使用第三方库执行mysql查询
  // mysql_quey();
  return 0;
}
