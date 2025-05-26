#include <mysql/mysql.h>
#include <string>
#include <vector>

class MySQLClient {

public:

   MySQLClient(){
        _conn = nullptr;
        _res = nullptr;
        init();
    
    }

   ~MySQLClient(){
        if (_res) {
            mysql_free_result(_res);
        }
        if (_conn) {
            mysql_close(_conn);
        }
   }

   void init(){
        mysql_library_init(0, nullptr, nullptr);
        _conn = mysql_init(nullptr);
        if (_conn == nullptr) {
            throw std::runtime_error("mysql_init failed");
        }


   }

   void connect(const string & host,

                      const string & user,

                      const string & passwd,

                      const string & db,

                      unsigned short port)
                      {
        if (mysql_real_connect(_conn, host.c_str(), user.c_str(), passwd.c_str(),
                               db.c_str(), port, nullptr, 0) == nullptr) {
                throw std::runtime_error("mysql_real_connect failed: " + string(mysql_error(_conn)));
                               
        }


                      }

   //写操作封装(INSERT/UPDATE/DELETE)

   bool writeOperationQuery(const string & sql){
        if (mysql_query(_conn, sql.c_str())) {
            throw std::runtime_error("mysql_query failed: " + string(mysql_error(_conn)));
        }
        return mysql_affected_rows(_conn) > 0;
   }

   //读操作封装(SELECT)

   vector<vector<string>> readOperationQuery(const string &sql){
        if (mysql_query(_conn, sql.c_str())) {
            throw std::runtime_error("mysql_query failed: " + string(mysql_error(_conn)));
        }

        _res = mysql_store_result(_conn);
        if (_res == nullptr) {
            throw std::runtime_error("mysql_store_result failed: " + string(mysql_error(_conn)));
        }

        vector<vector<string>> result;
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(_res)) != nullptr) {
            vector<string> rowData;
            for (unsigned int i = 0; i < mysql_num_fields(_res); ++i) {
                rowData.push_back(row[i] ? row[i] : "NULL");
            }
            result.push_back(rowData);
        }
        return result;
   }

private:

   MYSQL * _conn;

   MYSQL_RES * _res;

};