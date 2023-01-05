#ifndef ERROR
#define ERROR
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

