#ifndef SRC_ERROR_H
#define SRC_ERROR_H
#include <exception>
#include <string>
using std::string;
class error : public std::exception {
private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};
#endif

