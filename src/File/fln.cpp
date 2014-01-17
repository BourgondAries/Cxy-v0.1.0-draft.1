// Headers
#include "File.hpp"


void File::fln(Sti_t &i)
{
    if (m_directory_iterator != boost::filesystem::directory_iterator())
    {
        getRegister("fln") = m_directory_iterator->path().filename().generic_string();
    }
    else
    {
        getRegister("fln") = "";
    }
}
