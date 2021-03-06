// Headers
#include "File.hpp"


void File::find(Sti_t &i)
{
    Sti_t
        ptr = getNumber(Symbol::ptr),
        mrk = getNumber(Symbol::mrk);



    String_t &tosrch(getString(m_instructions[++i]));
//    std::cout << "trying to find'" << tosrch << "'\n";
//    std::cout << "ptr's val:" << ptr << std::endl;
//    std::cout << "mrk's val:" << mrk << std::endl;

    Sti_t occurrence = 0, last = ptr - (ptr > 0 ? 1 : 0);

    if (ptr == mrk) // Unrestricted area (from pointer to file end)
    {
//        std::cout << "read content: " << getString(Symbol::cntnt) << "\n";
//        std::cout << "to search: " << tosrch << "\n";
        if ((last = getString(Symbol::cntnt).find(tosrch, (ptr > 0 ? ++last : last))) != getString(Symbol::cntnt).npos)
        {
//            std::cout << "Logic error?\n";
            ptr = last;
            getRegister(Symbol::mrk) = last + tosrch.size()/* - (ptr > 0 ? 0 : 1)*/;
            getRegister(Symbol::ptr) = ptr;
        }
    }
    else // Restricted area (from pointer till marker)
    {
        if ((last = getString(Symbol::cntnt).find(tosrch, (ptr > 0 ? ++last : last))) != getString(Symbol::cntnt).npos)
        {
            if (last + tosrch.size() < mrk)
            {
                ptr = last;
                getRegister(Symbol::mrk) = last + tosrch.size();
                getRegister(Symbol::ptr) = ptr;
            }
        }
    }
}
