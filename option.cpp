#include "option.h"

Option::Option(const std::string& name, bool mandatory) : m_name(name), m_mandatory(mandatory)
{

}

bool Option::mandatory() const
{
    return m_mandatory;
}
const std::string& Option::name() const
{
    return m_name;
}

void Option::operator<<(const std::string& str)
{
    setValue(str);
}

template <>
void OptionImpl<std::string>::setValue(const std::string& str)
{
    m_value = str;
}
