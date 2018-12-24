#ifndef DATA_H
#define DATA_H

#include <ostream>
#include <string>

namespace atsp { namespace data {

// the basic all access types (read-write)
typedef uint *  row_t;
typedef row_t * matrix_t;

// locked read-only access type
typedef const matrix_t const_matrix_t;

// locked read-only globally visible access points

extern const const_matrix_t  &   data;
extern const uint &             size;
extern const std::string &      id;

// specialized classes to do the actual data loading
// derived classes have the intermidiate limited
// write access

class data_loader;

// dumps the currently loaded data to a stream

void dump(std::ostream & os);

// loads the data using a data loader

void load(const data_loader * loader);

// loads atsp data from a file
// this class manipulates the actual data that
// is kept read-only for its users

class data_loader
{
public:

    data_loader( const char * const &);
    virtual ~data_loader();

private:

    friend void load(const data_loader * loader);
    virtual void operator()() const = 0;

protected:

    const char * const &            m_fname;

    static matrix_t &               m_data;
    static const uint &             m_size; // read only. Set through set_size
    static std::string &            m_id;

    void set_size(uint sz) const;
};


}
}
#endif // DATA_H
