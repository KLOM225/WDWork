#include "Bluet_to_wifi.h"

/**
 * @brief 转换WiFi配置字符串为AT指令格式
 * @param input  输入字符串（格式：!ssid=password!）
 * @param output 输出缓冲区（需保证足够大）
 * @param out_len 输出缓冲区长度
 * @return 转换结果：
 *         - 0: 成功
 *         - -1: 输入格式错误
 *         - -2: 输出缓冲区不足
 */
int convert_wifi_config(const char* input, char* output, size_t out_len) {
    // 参数有效性检查
    if (!input || !output || out_len < 32) {
        return -2;
    }

    // 验证输入格式：至少包含两个!和一个=
    size_t len = strlen(input);
    if (len < 5 || input[0] != '!' || input[len-1] != '!') {
        return -1;
    }

    // 提取中间部分（去掉首尾的!）
    const char* middle = input + 1;
    size_t middle_len = len - 2;

    // 查找等号位置
    const char* eq_pos = memchr(middle, '=', middle_len);
    if (!eq_pos || eq_pos == middle || eq_pos == (input + len - 2)) {
        return -1; // 无效的等号位置
    }

    // 分割SSID和密码
    size_t ssid_len = eq_pos - middle;
    size_t pass_len = (input + len - 2) - eq_pos - 1;

    // 构造AT指令（带缓冲区溢出保护）
    int ret = snprintf(output, out_len, 
                      "AT+CWJAP_DEF=\"%.*s\",\"%.*s\"",
                      (int)ssid_len, middle,
                      (int)pass_len, eq_pos + 1);

    // 检查输出是否被截断
    if (ret < 0 || (size_t)ret >= out_len) {
        output[0] = '\0';
        return -2;
    }

    return 0;
}
