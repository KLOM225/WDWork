#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <algorithm>

// 创建类Configuration，通过它读取服务器程序的输入信息
// 读取配置文件的代码，从../SmartHomeMonitorServer/conf/server.conf
// 辅助函数：去除字符串前后空格


class Configuration {
public:
    // 删除拷贝构造函数和赋值运算符
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    // 获取单例实例 (支持首次调用指定配置文件路径)
    static Configuration& getInstance(const std::string& config_file_path = "conf/server.conf") {
        static Configuration instance(config_file_path);
        return instance;
    }

    

    // 获取配置参数
    std::string GetIP() const { return ip_; }
    uint16_t GetPort() const { return port_; }
    int GetThreadNum() const { return thread_num_; }
    int GetTaskNum() const { return task_num_; }
    std::string GetVideoPath() const { return video_path_; }
    std::string GetLogFile() const { return log_file_; }

private:
    explicit Configuration(const std::string& config_file_path = "conf/server.conf");
    
    std::string ip_;
    uint16_t port_ = 0;
    int thread_num_ = 0;
    int task_num_ = 0;
    std::string video_path_;
    std::string log_file_;

    void ParseLine(const std::string &line);
    void Validate() const;
    static void trim(std::string& s);
};


#endif // CONFIGURATION_HPP