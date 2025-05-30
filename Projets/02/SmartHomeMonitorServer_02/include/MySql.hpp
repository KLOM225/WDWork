#ifndef MYSQL_HPP
#define MYSQL_HPP

#include <string>
#include <vector>
#include <mysql/mysql.h>

class MySql {
public:
    struct User {
        int id;
        std::string name;
        std::string setting;
        std::string encrypt;
    };

    MySql() : _conn(nullptr) {
        init();
    }

    ~MySql() {
        disconnect();
    }

    // 初始化数据库连接
    bool init() {
        disconnect();
        
        _conn = mysql_init(nullptr);
        if (!_conn) return false;
        
        return connect();
    }

    // 连接数据库
    bool connect() {
        const char* host = "localhost";
        const char* user = "root";
        const char* pass = "1234";
        const char* db = "wd1th";
        unsigned int port = 3306;
        
        if (!mysql_real_connect(_conn, host, user, pass, db, port, nullptr, 0)) {
            return false;
        }
        
        mysql_set_character_set(_conn, "utf8mb4");
        return true;
    }

    // 断开数据库连接
    void disconnect() {
        if (_conn) {
            mysql_close(_conn);
            _conn = nullptr;
        }
    }

    // 检查用户是否存在
    bool user_exists(const std::string& username) {
        std::string query = "SELECT COUNT(*) FROM users WHERE name = '" + 
                            escape_string(username) + "'";
        
        MYSQL_RES* result = execute_query(query);
        if (!result) return false;
        
        bool exists = false;
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0]) {
            exists = (atoi(row[0]) > 0);
        }
        
        mysql_free_result(result);
        return exists;
    }

    // 添加用户
    bool add_user(const std::string& username, 
                 const std::string& setting, 
                 const std::string& encrypt = "") 
    {
        std::string query = "INSERT INTO users (name, setting, encrypt) VALUES ('" +
                            escape_string(username) + "', '" +
                            escape_string(setting) + "', '" +
                            escape_string(encrypt) + "')";
        
        return execute_update(query);
    }

    // 获取用户盐值
    std::string get_setting(const std::string& username) {
        std::string query = "SELECT setting FROM users WHERE name = '" + 
                            escape_string(username) + "'";
        
        MYSQL_RES* result = execute_query(query);
        if (!result) return "";
        
        std::string setting;
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0]) {
            setting = row[0];
        }
        
        mysql_free_result(result);
        return setting;
    }

    // 更新用户加密密文
    bool update_encrypt(const std::string& username, const std::string& encrypt) {
        std::string query = "UPDATE users SET encrypt = '" + 
                            escape_string(encrypt) + 
                            "' WHERE name = '" + 
                            escape_string(username) + "'";
        
        return execute_update(query);
    }

private:
    // SQL注入防护：转义特殊字符
    std::string escape_string(const std::string& input) {
        if (!_conn) return input;
        
        char* escaped = new char[input.length() * 2 + 1];
        unsigned long len = mysql_real_escape_string(_conn, escaped, input.c_str(), input.length());
        std::string result(escaped, len);
        delete[] escaped;
        return result;
    }

    // 执行查询语句
    MYSQL_RES* execute_query(const std::string& query) {
        if (!_conn && !init()) return nullptr;
        
        if (mysql_query(_conn, query.c_str())) {
            return nullptr;
        }
        
        return mysql_store_result(_conn);
    }

    // 执行更新语句
    bool execute_update(const std::string& query) {
        if (!_conn && !init()) return false;
        
        if (mysql_query(_conn, query.c_str())) {
            return false;
        }
        
        return mysql_affected_rows(_conn) > 0;
    }

private:
    MYSQL* _conn;
};

#endif // MYSQL_HPP