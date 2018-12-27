#ifndef DATA_H
#define DATA_H

#include <ostream>
#include <string>

namespace atsp {

class DataLoader;

class Data
{
public:
    Data();
    ~Data();

    // read only access points (slow)
    //uint const * operator[](uint i) const;

    uint getSize() const;

    // in most compilers this results in the fastest access
    uint const * const * getDataPtr() const
    {
        return _data;
    }

    // uses a polimorfic DataLoader to load data into it
    void load(const DataLoader & loader);

private:

    // alows data access to DataLoaders
    friend class DataLoader;

    // outputs content to a stream
    friend std::ostream & operator <<(std::ostream &, const Data &);

    // allocs necessary memory
    void malloc(uint size);

    // releases alocated memory
    void release();

    uint **      _data;
    uint         _size;
    std::string  _id;

};

class DataLoader
{
public:

    virtual ~DataLoader();
    virtual void load(Data &) const = 0;

protected:

    void set(Data & d, std::string id,  uint sz) const;

    uint ** getDataPtr(Data & d) const;
};

std::ostream & operator <<(std::ostream &, const Data &);

}// ns atsp
#endif // DATA_H
