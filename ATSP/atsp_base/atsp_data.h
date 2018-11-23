#ifndef ATSP_DATA_H
#define ATSP_DATA_H

#include <memory>
#include <istream>
#include <string>

namespace atsp
{
typedef unsigned int uint;
namespace data
{
typedef uint value_t;
typedef std::unique_ptr<value_t[]> row_t;
typedef std::unique_ptr<row_t[]> data_matrix_t;

struct data_t
{
    data_matrix_t data;
    uint size;
    std::string id;
};

void alloc(data_t &);
void dump(const data_t & db, std::ostream & os);

// loads atsp data from a file
// this class manipulates the actual data that
// is encapsulated inside the data proxy class

class data_loader
{
public:

    data_loader( const char * const &);
    virtual ~data_loader();

private:

    friend class data_proxy;
    virtual void operator()( data_t & ) const = 0;

protected:

    const char * const & m_fname;
};

// data_proxy encapsulates and restrict the
// access the the actual data
// The class has a sigle access point to it
// through instance() (its a simplified meyer's singleton)

// It provides read-only direct access throug data_ptr()
// and exposes an interface to load data, through a proper
// data_loader class. This is the only way to change the
// actual data.


class data_proxy
{
public:
    // access point to the class single instance
    static data_proxy & instance();

    // read only access point to the data
    static const data_t & data_ptr();

    // load or reload data using a data loader
    static void load( data_loader const * );

private:

    static data_t m_data;

private:

    data_proxy(){}
    ~data_proxy(){}
    data_proxy(const data_proxy &) = delete;
    data_proxy & operator=(const data_proxy &) = delete;
};

}
}
#endif // ATSP_DATA_H
