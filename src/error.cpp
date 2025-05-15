#include "error.hh"

ParseError::ParseError(std::string message) :
    m_errorMsg(message)
{
}

const char* ParseError::what() const noexcept {
    return m_errorMsg.c_str();
}
