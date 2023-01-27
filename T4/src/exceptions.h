#pragma once

#include "tuple_printer.h"

class FileError : public std::exception {
 public:
  const char* what() const noexcept override;
};

const char* FileError::what() const noexcept {
  return "\nWARNING! Detected non-recoverable error. Process terminated.\n";
}

class InvalidDataFormat : public std::exception {
 public:
  InvalidDataFormat(const char* type) {
      msg_ = "Incorrect format for: ";
      msg_ += type;
  }
  const char* what() const noexcept override;

private:
  std::string msg_;
};

const char* InvalidDataFormat::what() const noexcept { return msg_.c_str(); }

class UnsupportedDataFormat : public std::exception {
 public:
  const char* what() const noexcept override;
};

const char* UnsupportedDataFormat::what() const noexcept {
  return "\n\tUnsupported type!\n\tTry: int, string.\n";
}
