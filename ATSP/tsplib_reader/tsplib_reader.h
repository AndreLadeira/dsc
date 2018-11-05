#ifndef TSPLIB_READER_H
#define TSPLIB_READER_H

#include <string>

class tsplib_reader
{
public:
    explicit tsplib_reader(const char * fname);
    ~tsplib_reader();

    unsigned int            size() const;
    const unsigned int *    operator[](const unsigned int index) const;
    void                    print(void) const;

    unsigned int min() const;
    unsigned int max() const;

private:

    std::string     m_name;
    unsigned int    m_sz;
    unsigned int ** m_data;
    unsigned int    m_max;
    unsigned int    m_min;
};

#endif // TSPLIB_READER_H
