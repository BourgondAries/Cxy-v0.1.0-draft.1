#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

// Headers
#include <TTL/TTL.hpp>
#include "Register.hpp"
#include <iosfwd>
#include <boost/filesystem.hpp>


class File
{
public:

    File(const std::string &file);
    ~File() = default;


    void process();     // Performs: read, include, parse, and interpret in that order.

    // Preparation stages:
    void read();        // Reads the entire file's contents into the buffer.
    void include();     // includes all #cxy <file> files.
    void parse();       // parse all #cxy statements.

    // Execution stages:
    void compile();     // Transform the statements into bytecode.
    void execute();     // Execute all bytecode, faster than interpreting mnemonics.

    void setShow(bool state); // Sets whether the show command executes or not.

    friend std::ostream &operator<<(std::ostream &os, const File &file);

private:

    // Type definitions - allows an easy change of types.
    typedef boost::filesystem::directory_iterator              bfdirit;             // Directory iterator
    typedef char                                               Symbol_enum_t;       // Which type the enum class uses internally.
    typedef std::size_t                                        Sti_t;               // Requirements: Largest possible index on the architecture of an array. Unsigned integer.
    typedef std::string                                        String_t;            // Which ordering type we use, most likely a string (from mnemonics), class must have < comparison.
    typedef ::Register                                         Register_t;          // Requirements: Convertible/Assignable to/from both String_t and Sti_t.

    typedef std::map<String_t, std::vector<Register_t>>        Data_t;              // Requirements: A switch from one String_t to a stack of Register_t.
    typedef std::vector<String_t>                              Instructions_t;      // Requirements: A random access iteratable collection of String_t.

    static_assert(std::numeric_limits<String_t::value_type>::digits >= std::numeric_limits<Symbol_enum_t>::digits, "A character must be able to hold any single instruction symbol.");

    enum class Symbol : Symbol_enum_t;

    // Useful shortening functions.
    Sti_t getNumber(const String_t &);                      // Returns a number from a register
    Sti_t getNumber(const String_t &) const;                // Returns a number from a register
    Sti_t getNumber(const Symbol);                      // Returns a number from a register
    Sti_t getNumber(const Symbol) const;                // Returns a number from a register

    String_t &getString(const Symbol);                  // Returns a string reference contained in a register
    const String_t &getString(const Symbol) const;      // Returns a const string reference contained in a register
    String_t &getString(const String_t &);                  // Returns a string reference contained in a register
    const String_t &getString(const String_t &) const;      // Returns a const string reference contained in a register

    Register_t &getRegister(const Symbol);              // Returns a reference to a register
    const Register_t &getRegister(const Symbol) const;  // Returns a const reference to a register
    Register_t &getRegister(const String_t &);              // Returns a reference to a register
    const Register_t &getRegister(const String_t &) const;  // Returns a const reference to a register

    const String_t &reg2str(const Symbol) const;

    // Parsing functions.
    String_t tokenize(const String_t &str, Sti_t &position); // Parses out a single statement
    void reinstruct(const std::string &instructions);

    // Statements: All statements behave like text editor statements.

    // "RISC" String_t operations (these are complete.)
    void ins(Sti_t &i); // Replace pointer-marker part with register content  (1) -> void
    void del(Sti_t &i); // Delete button behaviour                            (0) -> void
    void bck(Sti_t &i); // backspace behaviour                                (0) -> void
    void cnt(Sti_t &i); // count occurrence of String_t                       (1) -> cnt
    void find(Sti_t &i); // Finds a String_t and marks it completely          (1) -> ptr, mrk
    void rfind(Sti_t &i); // Reverse-Finds a String_t and marks it completely (1) -> ptr, mrk
    void size(Sti_t &i); // Store the size of a String_t                      (1) -> size
    void capt(Sti_t &i); // Capture the marked substr into a register.        (0) -> capt
    void trim(Sti_t &i); // Remove non characters from the sides.             (1) -> [1]
    void cnc(Sti_t &i); // Concatenate 2 registers                            (2) -> [1]
    void drf(Sti_t &i); // Dereferencing operator                             (1) -> drf
    void rdf(Sti_t &i); // Reads an entire file into a register               (2) -> [1]
    void swap(Sti_t &i); // Very fast Register swap                           (2) -> [1]
    void repl(Sti_t &i); // Replace using a regexp                            (2) -> [1]
    void match(Sti_t &i); // Matches cntnt using a regexp                     (1) -> [1]
    void srch(Sti_t &i); // Matches cntnt using a regexp                     (1) -> [1]

    // Directory iteration
    void dir(Sti_t &i); // Open a directory.
    void odir(Sti_t &i); // Read the full path + filename
    void isdr(Sti_t &i); // Queries whether the pointed-to item is a dir.
    void extp(Sti_t &i); // Extracts the path (without the file).
    void updr(Sti_t &i); // Traverses up a directory tree, stops at root.
    void fln(Sti_t &i); // Extracts the current file name from the path.
    void adir(Sti_t &i); // Advance the directory iterator

    // CISC
    void show(Sti_t &i); // Print a String_t to stdout                        (1) -> void
    void reset(Sti_t &i); // Reset all states                                 (0) -> void
//    void halt(Sti_t &i); //

    // RISC, operations are considered complete and fully functional
    void if_statement(Sti_t &i); // Check whether to execute or not           (1) -> void
    void goto_statement(Sti_t &i); // Jump inside the code
    void eq(Sti_t &i); // Check whether two registers are equal               (2) -> eq
    void neq(Sti_t &i); // Opposite of eq                                     (2) -> neq
    void lt(Sti_t &i); // Check register1 > register2, store in "lt"          (2) -> lt
    void st(Sti_t &i); // Check register1 < register2, store in "st"          (2) -> st
    void inc(Sti_t &i); // increase a register by 1                           (1) -> [1]
    void dec(Sti_t &i); // Decrease a register by 1                           (1) -> [1]
    void add(Sti_t &i); // Increment a register by another                    (2) -> [1]
    void sub(Sti_t &i); // Decrement a register by another                    (2) -> [1]
    void push(Sti_t &i); // Push a register                                   (1) -> [1]
    void pop(Sti_t &i); // Pop a register                                     (1) -> [1]
    void mov(Sti_t &i); // mov between registers                              (2) -> [1]
    void cpy(Sti_t &i); // copy the next statement into a register            (1*) -> [1]
    void next(Sti_t &i); // Move the marker +1                                (0) -> mrk
    void prev(Sti_t &i); // Move the cursor -1                                (0) -> ptr
    void and_statement(Sti_t &i);
    void or_statement(Sti_t &i);
    void xor_statement(Sti_t &i);
    void not_statement(Sti_t &i);
    void get(Sti_t &i);
    void set(Sti_t &i);
    void hght(Sti_t &i);

    // Compiled:
    void goto_statement_c(Sti_t &i);
    void if_statement_c(Sti_t &i);

    // Member data
    std::string                 m_file;
    Instructions_t              m_instructions;
    Data_t                      m_data;
    const char                  m_parser_sign = '#';
    bfdirit                     m_directory_iterator;
    bool                        m_exec_show = true;

    enum class Runstate
    {Interpret, Execute}        m_runstate = Runstate::Execute;
    std::string                 m_id[2][25]
    {
        {
            "cnt",
            "eq",
            "neq",
            "lt",
            "st",
            "ptr",
            "mrk",
            "size",
            "next",
            "prev",
            "and",
            "or",
            "xor",
            "not",
            "capt",
            "drf",
            "cntnt",
            "odir",
            "isdr",
            "extp",
            "fln",
            "match",
            "get",
            "set",
            "hght"
        },
        {}
    };

    enum class Symbol : Symbol_enum_t
    {
        cnt,
        eq,
        neq,
        lt,
        st,
        ptr,
        mrk,
        size,
        next,
        prev,
        and_statement,
        or_statement,
        xor_statement,
        not_statement,
        capt,
        drf,
        cntnt,
        odir,
        isdr,
        extp,
        fln,
        match,
        get,
        set,
        hght,

        END_REGISTER_SYMBOLS,

        add,
        adir,
        bck,
        cnc,
        cpy,
        dec,
        del,
        dir,
        find,
        rfind,
        goto_statement,
        if_statement,
        inc,
        ins,
        mov,
        pop,
        push,
        rdf,
        reset,
        repl,
        show,
        srch,
        stop,
        sub,
        swap,
        trim,
        updr,

        END_ALL // Allows us to fetch the size of the enum class

    };

public:

    auto getInstructions() const -> const Instructions_t &;

};


#endif // FILE_HPP_INCLUDED
