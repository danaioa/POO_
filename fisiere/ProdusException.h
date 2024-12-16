#ifndef PRODUS_EXCEPTION_H
#define PRODUS_EXCEPTION_H

#include <exception>
#include <string>

class ProdusException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit ProdusException(std::string msg) : mesaj(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class FisierException : public ProdusException {
public:
    explicit FisierException(const std::string& msg) : ProdusException(msg) {}
};

class ProdusInvalidException : public ProdusException {
public:
    explicit ProdusInvalidException(const std::string& msg) : ProdusException(msg) {}
};

#endif
