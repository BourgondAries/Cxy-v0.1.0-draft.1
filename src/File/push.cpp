// Headers
#include  "File.hpp"


void File::push(Sti_t &i)
{
    if (m_data[m_instructions[i + 1]].size() > 0)
        m_data[m_instructions[i + 1]].emplace_back(m_data[m_instructions[i + 1]].back());
    else
        m_data[m_instructions[i + 1]].emplace_back("");
    ++i;
}
