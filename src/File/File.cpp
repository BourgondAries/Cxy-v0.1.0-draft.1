#include  "File.hpp"
#include  <iostream>
#include  <stdexcept>


File::File(const std::string &file)
:
    m_file(file)
{
    m_data["cnt"].emplace_back("0");
    m_data["eq"].emplace_back("0");
    m_data["neq"].emplace_back("0");
    m_data["lt"].emplace_back("0");
    m_data["st"].emplace_back("0");
    m_data["ptr"].emplace_back("0");
    m_data["mrk"].emplace_back("0");
    m_data["size"].emplace_back("0");
    m_data["next"].emplace_back("");
    m_data["prev"].emplace_back("");
    m_data["and"].emplace_back("0");
    m_data["or"].emplace_back("0");
    m_data["xor"].emplace_back("0");
    m_data["not"].emplace_back("0");
    m_data["capt"].emplace_back("");
    m_data["drf"].emplace_back(" ");
    m_data["cntnt"].emplace_back("");
    m_data["odir"].emplace_back("");
    m_data["isdr"].emplace_back("0");
    m_data["extp"].emplace_back("");
    m_data["fln"].emplace_back("");
    m_data["match"].emplace_back("");
    m_data["get"].emplace_back("");
    m_data["set"].emplace_back("");
    m_data["hght"].emplace_back("0");

    // Prepare compile-register symbols.
    {
        String_t utmp(1, ' ');
        for (Sti_t i = 0; i < Sti_t(Symbol::END_REGISTER_SYMBOLS); ++i)
        {
            utmp[0] = static_cast<char>(static_cast<Symbol>(i));
            m_id[Sti_t(Runstate::Execute)][i] = utmp;
            m_data[m_id[Sti_t(Runstate::Execute)][i]] = m_data[m_id[Sti_t(Runstate::Interpret)][i]];
        }
    }
}
