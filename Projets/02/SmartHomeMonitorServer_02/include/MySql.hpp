#ifndef MYSQL_HPP
#define MYSQL_HPP

#include "Mylogger.hpp"
#include <string>
#include <vector>
#include <map>
#include <mysql/mysql.h>

// 数据库连接配置
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "wd1th"
#define DB_PORT 3306

class MySql {
public:
    // 用户数据结构
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
        disconnect(); // 确保关闭现有连接
        
        _conn = mysql_init(nullptr);
        if (!_conn) {
            LogError("MySQL initialization failed");
            return false;
        }
        
        return connect();
    }

    // 连接数据库
    bool connect() {
        if (!mysql_real_connect(_conn, DB_HOST, DB_USER, DB_PASS,
                                DB_NAME, DB_PORT, nullptr, CLIENT_MULTI_STATEMENTS)) 
        {
            LogError("Connection error: %s", mysql_error(_conn));
            return false;
        }
        
        // 设置字符集为UTF8
        if (mysql_set_character_set(_conn, "utf8")) {
            LogWarn("Failed to set character set: %s", mysql_error(_conn));
        }
        
        LogInfo("Connected to MySQL database");
        return true;
    }

    // 断开数据库连接
    void disconnect() {
        if (_conn) {
            mysql_close(_conn);
            _conn = nullptr;
        }
    }

    // 检查连接状态
    bool is_connected() const {
        return _conn && mysql_ping(_conn) == 0;
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
                 const std::string& encrypt) 
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

    // 获取加密密文
    std::string get_encrypt(const std::string& username) {
        std::string query = "SELECT encrypt FROM users WHERE name = '" + 
                            escape_string(username) + "'";
        
        MYSQL_RES* result = execute_query(query);
        if (!result) return "";
        
        std::string encrypt;
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0]) {
            encrypt = row[0];
        }
        
        mysql_free_result(result);
        return encrypt;
    }

    // 更新用户盐值和加密密文
    bool update_user_credentials(const std::string& username,
                                const std::string& new_setting,
                                const std::string& new_encrypt) 
    {
        std::string query = "UPDATE users SET setting = '" + 
                            escape_string(new_setting) + 
                            "', encrypt = '" + 
                            escape_string(new_encrypt) + 
                            "' WHERE name = '" + 
                            escape_string(username) + "'";
        
        return execute_update(query);
    }

    // 获取用户完整信息
    User get_user(const std::string& username) {
        std::string query = "SELECT id, name, setting, encrypt FROM users WHERE name = '" + 
                            escape_string(username) + "'";
        
        MYSQL_RES* result = execute_query(query);
        if (!result) return User{};
        
        User user;
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row) {
            user.id = row[0] ? atoi(row[0]) : 0;
            user.name = row[1] ? row[1] : "";
            user.setting = row[2] ? row[2] : "";
            user.encrypt = row[3] ? row[3] : "";
        }
        
        mysql_free_result(result);
        return user;
    }

    // 获取所有用户
    std::vector<User> get_all_users() {
        std::string query = "SELECT id, name, setting, encrypt FROM users";
        MYSQL_RES* result = execute_query(query);
        if (!result) return {};
        
        std::vector<User> users;
        MYSQL_ROW row;
        
        while ((row = mysql_fetch_row(result))) {
            User user;
            user.id = row[0] ? atoi(row[0]) : 0;
            user.name = row[1] ? row[1] : "";
            user.setting = row[2] ? row[2] : "";
            user.encrypt = row[3] ? row[3] : "";
            users.push_back(user);
        }
        
        mysql_free_result(result);
        return users;
    }

    // 删除用户
    bool delete_user(const std::string& username) {
        std::string query = "DELETE FROM users WHERE name = '" + 
                            escape_string(username) + "'";
        return execute_update(query);
    }

    // 执行事务
    bool execute_transaction(const std::vector<std::string>& queries) {
        if (!is_connected()) return false;
        
        // 开始事务
        if (mysql_query(_conn, "START TRANSACTION")) {
            LogError("Start transaction failed: %s", mysql_error(_conn));
            return false;
        }
        
        bool success = true;
        for (const auto& query : queries) {
            if (mysql_query(_conn, query.c_str())) {
                LogError("Query failed: %s\nError: %s", query.c_str(), mysql_error(_conn));
                success = false;
                break;
            }
        }
        
        if (success) {
            if (mysql_query(_conn, "COMMIT")) {
                LogError("Commit failed: %s", mysql_error(_conn));
                success = false;
            }
        } else {
            mysql_query(_conn, "ROLLBACK");
        }
        
        return success;
    }

private:
    // SQL注入防护：转义特殊字符
    std::string escape_string(const std::string& input) {
        if (!_conn) return input;
        
        char* escaped = new char[input.length() * 2 + 1];
        mysql_real_escape_string(_conn, escaped, input.c_str(), input.length());
        std::string result(escaped);
        delete[] escaped;
        return result;
    }

    // 执行查询语句
    MYSQL_RES* execute_query(const std::string& query) {
        if (!is_connected() && !connect()) {
            LogError("Database not connected");
            return nullptr;
        }
        
        if (mysql_query(_conn, query.c_str())) {
            LogError("Query failed: %s\nError: %s", query.c_str(), mysql_error(_conn));
            return nullptr;
        }
        
        return mysql_store_result(_conn);
    }

    // 执行更新语句
    bool execute_update(const std::string& query) {
        if (!is_connected() && !connect()) {
            LogError("Database not connected");
            return false;
        }
        
        if (mysql_query(_conn, query.c_str())) {
            LogError("Update failed: %s\nError: %s", query.c_str(), mysql_error(_conn));
            return false;
        }
        
        return mysql_affected_rows(_conn) > 0;
    }

private:
    MYSQL* _conn;
};

#endif // MYSQL_HPP