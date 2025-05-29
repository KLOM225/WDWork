#ifndef MYSQL_HPP
#define MYSQL_HPP

#include <stdio.h>       // 标准输入输出函数（如printf, fprintf）
#include <stdlib.h>      // 标准库函数（如EXIT_SUCCESS, EXIT_FAILURE, atoi）
#include <mysql/mysql.h> // MySQL C API头文件

// 数据库连接配置宏定义
#define DB_HOST "localhost" // MySQL服务器地址
#define DB_USER "root"      // 数据库用户名
#define DB_PASS "1234"      // 数据库密码
#define DB_NAME "wd1th"     // 数据库名称
#define DB_PORT 3306        // MySQL服务端口（默认3306）

class MySql
{
public:
    MySql()
    {
        conn = mysql_init(NULL);
        // 初始化MySQL连接
        if (!conn)
        {
            fprintf(stderr, "MySQL initialization failed\n");
        }
        connect();

    }

    ~MySql()
    {
        // 关闭MySQL连接
        if (conn)
        {
            mysql_close(conn);
        }
    }

    void connect()
    {
        // 建立实际数据库连接
        // 参数说明：连接对象, 主机名, 用户名, 密码, 数据库名, 端口, Unix套接字, 客户端标志
        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS,
                                DB_NAME, DB_PORT, NULL, 0))
        {
            // 连接失败处理
            fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
            mysql_close(conn); // 关闭连接对象
            return ;
        }
        return;
    }

    // 检查用户是否存在的函数
    int user_exists(const char *username)
    {
        char query[256]; // 存储SQL查询语句的缓冲区

       
        // 构造SQL查询语句：统计指定用户名的记录数量
        // 注意：实际应用中应使用预处理语句防止SQL注入
        snprintf(query, sizeof(query),
                 "SELECT COUNT(*) FROM users WHERE name = '%s'",
                 username);

        // 执行SQL查询
        if (mysql_query(conn, query))
        {
            // 查询失败时输出错误信息
            fprintf(stderr, "Query error: %s\n", mysql_error(conn));
            return -1; // 返回错误状态
        }

        // 获取查询结果集
        MYSQL_RES *result = mysql_store_result(conn);
        if (!result)
        {
            // 结果集获取失败
            fprintf(stderr, "Result error: %s\n", mysql_error(conn));
            return -1;
        }else{
               //row的值为一个大于0的值, 说明已经有数据了
        int row = mysql_num_rows(result);
        int col = mysql_num_fields(result);
        printf("result (%d row, %d col)\n\n", row, col);

        //打印字段名
        MYSQL_FIELD  *filed = NULL;
        while((filed = mysql_fetch_field(result)) != NULL) {
            printf("%s\t", filed->name);
        }
        printf("\n");
        
        //打印每一行数据
        MYSQL_ROW strRow;
        while((strRow = mysql_fetch_row(result))!= NULL)  {
            //strRow是一个字符串数组
            for(int i = 0; i < col; ++i) {
                printf("%s\t", strRow[i]);
            }
            printf("\n");
        }
        }

        // 从结果集中提取第一行数据
        MYSQL_ROW row = mysql_fetch_row(result);
        int count = 0; // 用户计数

        // 检查行数据是否有效
        if (row)
        {
            // 将字符串转换为整数（row[0]是COUNT(*)的值）
            count = atoi(row[0]);
        }
        // 如果row为NULL，count保持0（用户不存在）

        // 释放结果集占用的内存
        mysql_free_result(result);

        // 返回用户是否存在（count>0则存在）
        return count > 0;
    }

// 添加新用户到数据库
    bool add_user(const std::string& username, 
                 const std::string& setting, 
                 const std::string& encrypt) 
    {
        char query[256];
        // 使用预处理语句防止SQL注入
        snprintf(query, sizeof(query),
                "INSERT INTO users (name, setting, encrypt) "
                "VALUES ('%s', '%s', '%s')",
                escape_string(username).c_str(),
                escape_string(setting).c_str(),
                escape_string(encrypt).c_str());
        
        if (mysql_query(conn, query)) {
            LogError("INSERT error: %s", mysql_error(conn));
            return false;
        }
        return true;
    }
    
private:
    // SQL注入防护：转义特殊字符
    std::string escape_string(const std::string& input) {
        char* escaped = new char[input.length() * 2 + 1];
        mysql_real_escape_string(conn, escaped, input.c_str(), input.length());
        std::string result(escaped);
        delete[] escaped;
        return result;
    }
private:
    MYSQL *conn;
};

#endif // MYSQL_HPP