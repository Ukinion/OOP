#pragma once

#include "tuple_printer.h"

class FileError : public std::exception
{
 public:
  const char* what() const noexcept override;
};

const char* FileError::what() const noexcept
{
  return "\nWARNING! Detected non-recoverable error. Process terminated.\n";
}

class UnsupportedDataFormat : public std::exception
{
 public:
    UnsupportedDataFormat(int col, int row, std::string type)
    {
        msg_ = "\nFile has wrong format!\n";
        msg_ += "Detected unknown type instead of " + type;
        msg_ += "\nError in\n";
        msg_ += "column " + std::to_string(col);
        msg_ += "\nrow " + std::to_string(row) + "\n";
    }
  const char* what() const noexcept override;
private:
  std::string msg_;
};

const char* UnsupportedDataFormat::what() const noexcept { return msg_.c_str(); }

class InvalidCountOfArgs : public std::exception
{
 public:
  InvalidCountOfArgs(int row, int valid_count, int invalid_count)
  {
    msg = "\n\tFile must have ";
    msg += std::to_string(valid_count);
    msg += " columns per row, but have ";
    msg += std::to_string(invalid_count);
    msg += ".";
    msg += '\n';
    msg += '\t';
    msg += "row: ";
    msg += std::to_string(row);
  }
  const char* what() const noexcept override;

  private:
  std::string msg;
};

const char* InvalidCountOfArgs::what() const noexcept { return msg.c_str(); }

class ValidStringFormat : std::exception {};

class UnknownDataType : public std::exception {
 public:
  const char* what() const noexcept override;
};

const char* UnknownDataType::what() const noexcept {
  return "\n\tUnsupported type!\n\tTry: int, long long, double, char, std::string.\n";
}
