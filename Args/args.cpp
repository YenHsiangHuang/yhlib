#include "args.hpp"
#include "stringutil.hpp"

Args::Args(std::string schema, ArgStrings args) : args(std::move(args)) {
    parse_schema(schema);
    parse_argument_strings();
}

Args::~Args() {}

void Args::parse_schema(std::string schema) {
    for (auto& element : StringUtil::split_string(schema, ','))
        if (element.length() > 0)
            parse_schema_element(StringUtil::trim(element));
}

void Args::parse_schema_element(std::string element) {
    char elem_id = element[0];
    std::string elem_tail = element.substr(1);
    validate_schema_element_id(elem_id);
    if (elem_tail.empty())
        marshalers.emplace(std::make_pair(elem_id, new BoolArgumentMarshaler()));
    else if (elem_tail == "*")
        marshalers.emplace(std::make_pair(elem_id, new StringArgumentMarshaler()));
    else if (elem_tail == "#")
        marshalers.emplace(std::make_pair(elem_id, new IntArgumentMarshaler()));
    else if (elem_tail == "##")
        marshalers.emplace(std::make_pair(elem_id, new DoubleArgumentMarshaler()));
    // else if (elem_tail == "[*]")
    //     marshalers.emplace(std::make_pair(elem_id, new StringVectorArgumentMarshaler()));
    else
        throw ArgsException(INVALID_ARGUMENT_FORMAT, elem_id);
}

void Args::validate_schema_element_id(char elem_id) {
    if (!std::isalpha(elem_id))
        throw ArgsException(INVALID_ARGUMENT_NAME, elem_id);
}

void Args::parse_argument_strings() {
    for (this->curr_arg_idx = 0; this->curr_arg_idx < this->args.size(); ++this->curr_arg_idx) {
        std::string curr_arg = this->args[this->curr_arg_idx];
        if (StringUtil::startswith(curr_arg, "-")) {
            parse_argument_chars(curr_arg.substr(1));
        } else {
            --this->curr_arg_idx;
            break;
        }
    }
}

void Args::parse_argument_chars(std::string arg_chars) {
    for (int i = 0; i < arg_chars.length(); ++i)
        parse_argument_char(arg_chars[i]);
}

void Args::parse_argument_char(char arg_char) {
    ArgumentMarshaler* m = marshalers[arg_char];
    if (m == nullptr) {
        throw ArgsException(UNEXPECTED_ARGUMENT, arg_char);
    } else {
        args_found.emplace(arg_char);
        try {
            m->set(this->args, this->curr_arg_idx);
        } catch (ArgsException& ae) {
            ae.set_error_argument_id(arg_char);
            throw ae;
        }
    }
}

bool Args::get_bool(char arg) {
    return BoolArgumentMarshaler::get_value(marshalers[arg]);
}

std::string Args::get_string(char arg) {
    return StringArgumentMarshaler::get_value(marshalers[arg]);
}

int Args::get_int(char arg) {
    return IntArgumentMarshaler::get_value(marshalers[arg]);
}

double Args::get_double(char arg) {
    return DoubleArgumentMarshaler::get_value(marshalers[arg]);
}

// ArgStrings Args::get_string_vector(char arg) {
//     return StringVectorArgumentMarshaler::get_value(marshalers[arg]);
// }

void BoolArgumentMarshaler::set(const ArgStrings& args, unsigned int curr_arg_idx) {
    value = true;
}

bool BoolArgumentMarshaler::get_value(ArgumentMarshaler* am) {
    if (am == nullptr) return false;
    BoolArgumentMarshaler* bam = dynamic_cast<BoolArgumentMarshaler*>(am);

    return bam == nullptr ? false : bam->value;
}

void StringArgumentMarshaler::set(const ArgStrings& args, unsigned int curr_arg_idx) {
    try {
        value = args.at(curr_arg_idx + 1);
    } catch (const std::out_of_range& e) {
        throw ArgsException(MISSING_STRING);
    }
}

std::string StringArgumentMarshaler::get_value(ArgumentMarshaler* am) {
    if (am == nullptr) return "";
    StringArgumentMarshaler* sam = dynamic_cast<StringArgumentMarshaler*>(am);

    return sam == nullptr ? "" : sam->value;
}

void IntArgumentMarshaler::set(const ArgStrings& args, unsigned int curr_arg_idx) {
    std::string int_string;
    try {
        int_string = args.at(curr_arg_idx + 1);
        value = std::stoi(int_string);
    } catch (const std::out_of_range& e) {  // std::vector::at
        throw ArgsException(MISSING_INTEGER);
    } catch (const std::invalid_argument& e) {  // std::stoi
        throw ArgsException(INVALID_INTEGER);
    }
}

int IntArgumentMarshaler::get_value(ArgumentMarshaler* am) {
    if (am == nullptr) return 0;
    IntArgumentMarshaler* iam = dynamic_cast<IntArgumentMarshaler*>(am);

    return iam == nullptr ? 0 : iam->value;
}

void DoubleArgumentMarshaler::set(const ArgStrings& args, unsigned int curr_arg_idx) {
    std::string double_string;
    try {
        double_string = args.at(curr_arg_idx + 1);
        value = std::stod(double_string);
    } catch (const std::out_of_range& e) {  // std::vector::at
        throw ArgsException(MISSING_DOUBLE);
    } catch (const std::invalid_argument& e) {  // std::stoi
        throw ArgsException(INVALID_DOUBLE);
    }
}

double DoubleArgumentMarshaler::get_value(ArgumentMarshaler* am) {
    if (am == nullptr) return 0;
    DoubleArgumentMarshaler* dam = dynamic_cast<DoubleArgumentMarshaler*>(am);

    return dam == nullptr ? 0 : dam->value;
}

// void StringVectorArgumentMarshaler::set(const ArgStrings& args, unsigned int curr_arg_idx) {
    
// }

// std::vector<std::string> StringVectorArgumentMarshaler::get_value(ArgumentMarshaler* am) {
// }