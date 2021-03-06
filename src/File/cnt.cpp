// Headers
#include "File.hpp"


void File::cnt(Sti_t &i)
{
    const Sti_t
        ptr = getNumber(Symbol::ptr),
        mrk = getNumber(Symbol::mrk);

    String_t &tosrch(getString(m_instructions[++i]));
    Sti_t occurrence = 0, last = ptr - (ptr > 0 ? 1 : 0);

    if (ptr == mrk) // Unrestricted area (from pointer to file end)
    {
        if
        (
            (last = getString(Symbol::cntnt).find(tosrch, (ptr > 0 ? ++last : last))) != getString(Symbol::cntnt).npos
        )
        {
            ++occurrence;
            while ((last = getString(Symbol::cntnt).find(tosrch, (++last))) != getString(Symbol::cntnt).npos)
            {
                ++occurrence;
            }
        }
    }
    else // Restricted area (from pointer till marker)
    {
        if
        (
            ((last = getString(Symbol::cntnt).find(tosrch, (ptr > 0 ? ++last : last))) != getString(Symbol::cntnt).npos)
            && ((last + tosrch.size() - 1) < mrk)
        )
        {
            ++occurrence;
            while
            (
                ((last = getString(Symbol::cntnt).find(tosrch, (++last))) != getString(Symbol::cntnt).npos)
                && ((last + tosrch.size() - 1) < mrk)
            )
            {
                ++occurrence;
            }
        }
    }
    getRegister(Symbol::cnt) = occurrence;
}
