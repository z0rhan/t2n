#ifndef ERROR_HH
#define ERROR_HH

#include <exception>
#include <string>

class ParseError : public std::exception {
public:
    explicit ParseError(std::string message);
    ~ParseError() = default;
    const char* what() const noexcept override;
private:
    std::string m_errorMsg;
};

#endif // ERROR_HH
