// Headers
#include "File.hpp"
#include <boost/tokenizer.hpp>
#include "read_var.hpp"
#include <TTL/TTL.hpp>

#define sout(X) (std::cout << X << "\n");
extern std::string get_first_most_nested_cxy_data(const std::string &content);
extern std::string get_second_most_nested_data(const std::string &content);
extern std::string erase_all_cxy_statements(const std::string &content);
extern void erase_first_most_nested_cxy_data(std::string &content);
extern void replace_second_most_nested_scope(std::string &content, std::string &with);


/*
    Parse all the #cxy statements from the file.
    Binary nestings must run before the previous nest.
*/
void File::parse()
{
    std::string content = getString(m_id[Sti_t(Runstate::Execute)][Sti_t(Symbol::cntnt)]);
    content.push_back('\n');
    try
    {
        while (content.find("#cxy star") != std::string::npos)
        {

            sout("==================================================\n");
            sout("GENCONTENT:\n")
            sout(content)
            sout("==================================================\n");

            std::string instructions = get_first_most_nested_cxy_data(content);
            sout("==================================================\n");
            sout("Instructions queried:")
            sout(instructions)
            sout("==================================================\n");
            std::string operating_data;
            try
            {
                 operating_data = erase_all_cxy_statements(get_second_most_nested_data(content));
            }
            catch (std::exception &e)
            {
                std::cout << "Error during erasion stage: " << e.what() << std::endl;
            }

            reinstruct(instructions);
            m_data[m_id[Sti_t(Runstate::Execute)][Sti_t(Symbol::cntnt)]].push_back(operating_data); // Turn "cntnt" into the name... goto sleep

            compile();
            execute();

            std::string generated_content = m_data[m_id[Sti_t(Runstate::Execute)][Sti_t(Symbol::cntnt)]].back();

           // Remove the trailing � or \n

            try
            {
                if (generated_content.size())
                generated_content.pop_back();
            }
            catch (std::out_of_range &exc_obj)
            {
                std::cout << "Out of range: " << exc_obj.what() << "\n";
                throw;
            }
                generated_content.push_back('\n');



                replace_second_most_nested_scope(content, generated_content);
                erase_first_most_nested_cxy_data(content);

        }

        m_data[m_id[Sti_t(Runstate::Execute)][Sti_t(Symbol::cntnt)]].back() = content;


    }
    catch (std::exception &e)
    {
        std::cout << "Error occurred during parsing: " << e.what() << std::endl;
        throw;
    }
}

