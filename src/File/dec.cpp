// Headers
#include  "File.hpp"


void File::dec(Sti_t &i)
{
    Sti_t num = getNumber(m_statements[++i]);
    getData(m_statements[i]) = std::to_string(num - 1);
}
