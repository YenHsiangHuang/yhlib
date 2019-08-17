#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ArgStrings = std::vector<std::string>;

class ArgumentMarshaler {
   public:
    virtual void set(const ArgStrings& args, unsigned int curr_arg_idx) = 0;
};

class BoolArgumentMarshaler : public ArgumentMarshaler {
   public:
    void set(const ArgStrings& args, unsigned int curr_arg_idx) override;
    static bool get_value(ArgumentMarshaler* am);

   private:
    bool value = false;
};

class StringArgumentMarshaler : public ArgumentMarshaler {
   public:
    void set(const ArgStrings& args, unsigned int curr_arg_idx) override;
    static std::string get_value(ArgumentMarshaler* am);

   private:
    std::string value;
};
class IntArgumentMarshaler : public ArgumentMarshaler {
   public:
    void set(const ArgStrings& args, unsigned int curr_arg_idx) override;
    static int get_value(ArgumentMarshaler* am);

   private:
    int value = 0;
};

class DoubleArgumentMarshaler : public ArgumentMarshaler {
   public:
    void set(const ArgStrings& args, unsigned int curr_arg_idx) override;
    static double get_value(ArgumentMarshaler* am);

   private:
    double value = 0.0;
};

// class StringVectorArgumentMarshaler : public ArgumentMarshaler {
//    public:
//     void set(const ArgStrings& args, unsigned int curr_arg_idx) override;
//     static std::vector<std::string> get_value(ArgumentMarshaler* am);

//    private:
//     std::vector<std::string> value;
// };

class Args {
   public:
    Args(std::string schema, ArgStrings args);
    ~Args();

    void parse_schema(std::string schema);
    void parse_schema_element(std::string element);
    void validate_schema_element_id(char elem_id);
    void parse_argument_strings();
    void parse_argument_chars(std::string arg_chars);
    void parse_argument_char(char arg_char);

    // bool has(char arg);
    // int next_arg();
    bool get_bool(char arg);
    std::string get_string(char arg);
    int get_int(char arg);
    double get_double(char arg);
    // std::vector<std::string> get_string_vector(char arg);

   private:
    std::unordered_map<char, ArgumentMarshaler*> marshalers;
    std::unordered_set<char> args_found;

    const ArgStrings args;
    unsigned int curr_arg_idx;
};

enum ArgsErrorCode {
    OK,
    INVALID_ARGUMENT_NAME,
    INVALID_ARGUMENT_FORMAT,
    UNEXPECTED_ARGUMENT,
    MISSING_STRING,
    MISSING_INTEGER,
    INVALID_INTEGER,
    MISSING_DOUBLE,
    INVALID_DOUBLE,
};

// class ArgsException : public std::exception {
class ArgsException {
   public:
    using ErrorCode = int;

   public:
    ArgsException();
    ArgsException(ErrorCode ec) : error_code(ec) {}
    ArgsException(ErrorCode ec, char eai) : error_code(ec), error_argument_id(eai) {}
    ArgsException(ErrorCode ec, char eai, std::string ep) : error_code(ec), error_argument_id(eai), error_param(ep) {}

    void set_error_argument_id(char eai) { this->error_argument_id = eai; }

   private:
    char error_argument_id = '\0';
    std::string error_param;
    ErrorCode error_code = OK;
};
// #endif