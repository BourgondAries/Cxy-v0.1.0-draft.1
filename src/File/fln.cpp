// Headers
#include "File.hpp"


void File::fln(Sti_t &i)
{
    if (m_directory_iterator != boost::filesystem::directory_iterator())
    {
        getRegister(reg2str(Symbol::fln)) = m_directory_iterator->path().filename().generic_string();
    }
    else
    {
        getRegister(reg2str(Symbol::fln)) = "";
    }
}
