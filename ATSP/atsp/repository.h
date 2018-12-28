#ifndef REPOSITORY_H
#define REPOSITORY_H

/*

base::fast_srand();
atsp::path p;
atsp::get_random(p, 10);
uint m = 7;
uint l = 2;
uint cnt = 0;
atsp::path::const_iterator beg;
atsp::path::const_iterator end;

for( atsp::path::const_iterator x = p.begin(); x!=p.end(); x++ )
{
   cout << *x << " ";
   if( cnt == m ) beg = x;
   if( cnt == m+l-1 ) end = x;
   cnt++;
}
cout << endl;
cout << *beg << " " << *end << "\n";

atsp::path q = {10,10,11,11};

p.insert_after( beg, q.begin(),q.end() );

for( atsp::path::const_iterator x = p.begin(); x!=p.end(); x++ )
{
   cout << *x << " ";
}
return 0;

    os << "\nFirst 10x10 elements\n\n";

    for(unsigned int i = 0; i < 10;++i)
    {
        for(unsigned int j = 0; j < 10;++j)
            os<< data[i][j] << " ";
        os << endl;
    }

    os << "\nLast 10x10 elements\n\n";

    for(unsigned long i = sz - 10; i < sz; ++i )
    {
        for(unsigned long j = sz - 10; j < sz; ++j )
            os << data[i][j] << " ";

        os << endl;
    }
uint atsp::get_length(const path & p, const data::data_t & tspdata)
{
    auto i = p.cbegin();
    auto j = ++p.cbegin();
    uint len = 0;

    const atsp::data::data_matrix_t & db = tspdata.data;

    while ( j != p.end()  )
    {
       len += db[*i][*j];
       i++;
       j++;
    }
    return len;
}

void atsp::get_random(path & p, const uint sz, base::rand_fcn_t rnd)
{
    p.clear();

    path::iterator * it = new path::iterator[sz];

    for(uint i = 0; i <sz; ++i)
    {
        p.insert_after(p.before_begin(),i);
        it[i] = p.begin();
    }
    //linear shuffle
    for(uint i = 0; i <sz; ++i)
    {
        uint a = static_cast<uint>(rnd()) % sz;
        uint b = static_cast<uint>(rnd()) % sz;

        uint tmp = *it[a];
        *it[a] = *it[b];
        *it[b] = tmp;
    }
    // closes the loop
    p.insert_after(it[0],*it[sz-1]);
    delete [] it;
}

void get_shortest(path &p, const uint mstart, const uint mlength, const data::data_t & db)
{
//    // sanity check
//    if ( (mstart + mlength) > db.size )
//        throw runtime_error("path::get_shortest: inconsistent mask data (size, length).");

//    // find the nodes at the mask endpoints  (begin, end)
//    uint ms             = get_value(mstart);
//    uint me             = get_value(mstart+mlength-1);
//    uint mask_cost      = get_length( get_subpath(p,mstart,mlength), db );
//    auto mask_begin_it  = get_iterator(p,mstart-1);
//    auto mask_end_it    = get_iterator(p,mstart + mlength);

//    path X(p.cbegin(),mask_begin_it);
//    X.insert_after(X.end(),mask_end_it,p.cend());

//    uint Xcost              = get_length(X,db);
//    vector<uint> cost_upto;

//    // pointers to list items
//    uint counter = 0;
//    for( const auto & n:X  )
//    {
//        if ( counter == 0)
//        {
//            cost_upto.push_back(0);
//        }
//        else
//        {
//            uint cost = db.data[counter-1][counter];
//            cost_upto.push_back( cost_upto.at(counter) + cost );
//        }
//        counter++;
//    }
//    // get the index of the best transformation
//    uint best_length = std::numeric_limits<uint>::max();
//    uint index = 0;

//    for(uint i = 0; i < counter; i++)
//    {
//        uint cost_link1 = db.data[i][ms];
//        uint cost_link2 = db.data[me][i+1];

//        uint cost_forward_on = Xcost - cost_upto.at(i);

//        uint length = cost_upto.at(i) + cost_link1 + mask_cost + cost_link2 + cost_forward_on;

//        if ( length < best_length )
//        {
//            best_length = length;
//            index = i;
//        }
//    }
//    // save the best (shortest) path
//    if ( best_length < get_length(p,db) )
//    {
//        path res(p.cbegin(),get_iterator(p,index));
//        res.insert_after(res.end(), mask_begin_it++,mask_end_it);
//        res.insert_after(res.end(), get_iterator(p,index+1),p.cend());

//        path & q = const_cast<path &>(p);
//        q.assign(res.begin(),res.end());
//    }
//    // returns

}


//path::path(const path &rhs)
//{
//   //*this=rhs;
//}

//const uint & path_::at(uint pos) const
//{
//    if (pos > m_sz )
//        throw std::runtime_error("path::at: invalid position.");
//    return m_path[pos];
//}

//path_ path_::subpath(const uint start, const uint size) const
//{
//    if (!size)
//        throw std::runtime_error("path::subpath: size must be greater than zero.");
//    if ( start + size - 1 > m_sz )
//        throw std::runtime_error("path::subpath: invalid start/length.");

//    path_ newp(size);

//    uint j = 0;

//    for(uint i = start; i < start + size; ++i)
//        newp.m_path[j++] = m_path[i];

//    return  newp;
//}

path_ &path_::operator =(const path_ & rhs)
{
    m_path.resize(rhs.m_path.size());
    m_path = rhs.m_path;

    m_length_set = false;
    m_length_upto_set = false;
    m_length_forward_on_set = false;
    return *this;
}
path_ &path_::operator +=(const path_ & rhs)
{
    m_path.insert(m_path.end(), rhs.m_path.begin(),rhs.m_path.end());
    m_length_set = false;
    m_length_upto_set = false;
    m_length_forward_on_set = false;
    return *this;
}

uint path::length_upto(const data::data_matrix_t & db, uint pos)
{
     if ( !m_length_upto_set )
     {
         if (m_length_upto) delete[] m_length_upto;
         m_length_upto = uintptr_t( new uint[m_sz]());

         for(uint i = 1; i < m_sz; i++)
             m_length_upto[i] = m_length_upto[i-1] + db[ m_path[i-1] ][ m_path[i] ];
         m_length_upto_set = true;
     }
     return m_length_upto[pos];
}
uint path::length_forward_on(const data::data_matrix_t & db, uint pos)
{
    if ( !m_length_forward_on_set )
    {
        if (m_length_fwd) delete []  m_length_fwd;
        m_length_fwd = uintptr_t( new uint[m_sz]());

        uint pathlen = length(db);

        for(uint i = 0; i < m_sz-1; i++)
            m_length_fwd[i] = pathlen - length_upto(db,i); // $OPTIMIZE

        m_length_forward_on_set = true;
    }
    return m_length_fwd[pos];
}


    // copies the original path up to the insertion point
    std::memcpy(new_pwm_ptr, pwm_ptr, ( pos + 1 )*sizeof(uint) );

    // copies the mask
    std::memcpy(new_pwm_ptr + pos + 1,
                path_ptr + msk_start,
                ( msk_size )*sizeof(uint) );

    // copies the rest of the path
    std::memcpy(new_pwm_ptr + pos + msk_size + 1,
                pwm_ptr + pos + 1,
                ( path_wm_sz - pos - 1 )*sizeof(uint) );

    delete [] m_path;
    m_path = new_pwm_ptr;
    m_length_set = false;


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

    atsp::data::load( new data::tsplib_reader(argv[1]) );

    atsp::data::dump( cout );
    atsp::Path p;

    //p.move(2,10,3);
    //p.move(12,4,2);
    //p.move(13,0,1);
    //p.move(0,14,2);

    uint runs    = static_cast<uint>(atoi( argv[2]) );
    uint iters   = static_cast<uint>(atoi( argv[3]) );
    uint msk_sz  = static_cast<uint>(atoi( argv[4]) );

    cout<<"\n\nATSP solution by random search\n";
    cout<<"\n\nData file: " << argv[1] << " (" << data::size << " nodes)\n";
    cout<< runs << " executions, " << iters << " iterations per run.\n";
    cout<<"Mask size: " << msk_sz << "\n\n";
    cout<< "|0      50|      100|\n" << flush;

    uint min = std::numeric_limits<uint>::max();
    atsp::Path best(p);

    //base::fast_srand();
    const uint msk_range = data::size - msk_sz;

    clock_t begin = clock();
    atsp::greedy_algorithm * greedy = new atsp::greedy_algorithm();
    greedy->_length = msk_sz;

    for(uint run = 0; run < runs; run++)
    {
        p.randomize();
        for(uint iter = 0; iter < iters; ++iter)
        {
            greedy->_pos = static_cast<uint>(base::fast_rand()) % msk_range;
            uint cmin = p.shorten( greedy );
            if ( cmin < min )
            {
                min = cmin;
                best = p;
            }
        }
        if ( run % (runs / 20) == 0) cout<<"|" << flush;
    }

    cout<<"|" << endl;
    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;
    cout<< "Final result: " << min << endl;
    //cout<< "Best path: " << best;
    delete greedy;
    return 0;

}





//namespace
//{

//// the actual data

//matrix_t    dataObj = nullptr;
//uint        sizeObj = 0;
//string      idObj;

//void release()
//{
//    for( uint i = 0; i < sizeObj; ++i )
//        delete[] dataObj[i];

//    delete[] dataObj;
//    dataObj = nullptr;
//}

//// The idea here is to have a global variable and
//// rely on its destructor to release any memory
//// alocated on dataObj.

//struct Releaser
//{
//   ~Releaser()
//   {
//      if (dataObj)
//      {
//          release();
//      }
//   }

//} releaser;

//}
//// the constant read-only references

//const const_matrix_t &  atsp::data::data    = dataObj;
//const uint &            atsp::data::size    = sizeObj;
//const string &          atsp::data::id      = idObj;

//// the data read-write access points, available only to loaders

//matrix_t &      data_loader::m_data   = dataObj;
//const uint &    data_loader::m_size   = sizeObj;
//string &        data_loader::m_id     = idObj;

//data_loader::data_loader(const char * const & fname): m_fname(fname){}
//data_loader::~data_loader(){}

//void data_loader::set_size(uint sz) const
//{
//    if (dataObj) release();

//    sizeObj = sz;

//    dataObj = matrix_t( new row_t[sizeObj] );

//    for( uint i = 0; i < sizeObj; ++i )
//        dataObj[i] = row_t( new uint[sizeObj]);

//    // m_data[0][0] = 100; // OK
//    // m_data[0] = nullptr; // compile error as expected
//}

//void atsp::data::dump(std::ostream & os)
//{
//    os << "--- atsp data dump ---\n";
//    os << "Problem name: " << id << endl;
//    os << "Dimension:    " << size << endl;
//    os << "Data (edge weights)\n\n";

//    for(unsigned int i = 0; i < size; ++i)
//    {
//        for(unsigned int j = 0; j < size;++j)
//            os<< dataObj[i][j] << "  ";
//        os << endl;
//    }
//    os<< "\n--- end of atsp data dump ---\n";
//}

//void atsp::data::load(const data_loader * loader)
//{
//    (*loader)();
//}


//    Path();
//    explicit Path(uint sz);
//    Path(const Path &);
//    Path(const Path &, uint pos, uint len); // cut construction
//    ~Path();

//    uint length() const;
//    uint length(uint start, uint length);
//    uint size() const;
//    void randomize();
//    void move(uint insertion, uint pos, uint length);
//    uint shorten(atsp::algorithm *);

//    static void setRandonFcn(base::rand_fcn_t);

//    Path & operator=(const Path &);
//    const uint & operator[](uint)const;

//private:

//    friend std::ostream & operator << (std::ostream &, const Path & p);

//    uint *  _path;

//    mutable bool    _length_set; // lazy evaluation
//    mutable uint    _length;

//    uint    _size; // size (#of vertices) on the path

//    static base::rand_fcn_t _rnd_fcn;

//    void set();

//#include "path.h"
//#include "data.h"
//#include "algorithm.h"

//using namespace atsp;

//#ifdef __DEBUG__
//#include <cassert>
//#include <iostream>
//#endif

//base::rand_fcn_t Path::_rnd_fcn = base::fast_rand;

//// size constructor: constructs a new path given a size
//// the path has initially the vertexes (cities) in order:
//// 1,2,3...,N

//Path::Path():_size(data::size)
//{
//    set();
//}
//Path::Path(uint sz):_size(sz)
//{
//    set();

//}

//// constructs a path from raw data: a pointer to a memory area
//// and a size. This is used to speed some things up.
//// Note to self: evaluate cons of changing to more robust c++

//Path::Path(const Path & rhs):_size(rhs._size)
//{
//    _path = new uint[_size];
//    for (uint i = 0; i <_size; ++i)
//        _path[i] = rhs._path[i];

//    _length_set = false;
//}

//Path::Path(const Path & p, uint pos, uint length):_size(p._size-length)
//{
//    _path = new uint[_size];

//    // copies the original path up to the mask start

//    std::memcpy(_path, p._path, (pos)*sizeof(uint) );

//    // copies the original path from after the mask end to the end

//    std::memcpy(_path + pos,
//                p._path + pos + length,
//                ( p._size - pos - length )*sizeof(uint) );

//    _length_set = false;
//}

//Path & Path::operator=(const Path & rhs)
//{
//    for (uint i = 0; i <_size; ++i)
//        _path[i] = rhs._path[i];
//    return *this;
//}

//const uint &Path::operator[](uint at) const
//{
//    return _path[at];
//}

//void Path::set()
//{
//    _path = new uint[_size];
//    for (uint i = 0; i <_size; ++i)
//        _path[i] = i;

//    _length_set = false;
//}

//Path::~Path()
//{
//    if (_path) delete[] _path;
//}

//void Path::randomize()
//{
//    // linear shuffle
//    for(uint i = 0; i < _size; ++i)
//    {
//        uint a = static_cast<uint>(_rnd_fcn()) % _size;
//        uint b = static_cast<uint>(_rnd_fcn()) % _size;

//        uint tmp = _path[a];
//        _path[a] = _path[b] ;
//        _path[b] = tmp;
//    }
//    _length_set = false;
//}

//void Path::move(uint ins, uint msk_init, uint msk_count)
//{
//    // attempt #1: no memory allocation. O( n * count )

//    if ( msk_init > ins )
//    {
//        for ( uint i = 0; i < msk_count; ++i)
//        {
//            uint temp = _path[ msk_init + i];
//            for ( uint j = 0; j < msk_init - ins - 1; ++j)
//                _path[ msk_init + i - j ] = _path[ msk_init + i - j -1 ];
//            _path[ ins + i + 1 ] = temp;
//        }
//    }
//    else
//    {
//          for ( uint i = 0; i < msk_count; ++i)
//          {
//              uint temp = _path[ msk_init + msk_count - i - 1];

//              for ( uint j = 0; j < ins - msk_init + 1; ++j)
//                  _path[ msk_init + msk_count - i + j  - 1 ] = _path[ msk_init + msk_count - i + j ];

//              _path[ ins + msk_count - i ] = temp;
//          }

//    }

//    _length_set = false;
//}

//void Path::setRandonFcn(base::rand_fcn_t fcn)
//{
//   _rnd_fcn = fcn;
//}

//std::ostream & atsp::operator <<(std::ostream & os, const Path & p)
//{
//    for (uint i = 0; i < p._size -1; i++)
//        os << p._path[i] << ", ";
//    os << p._path[p._size-1] << "\n";

//    return os;
//}

//uint Path::length() const
//{
//   const auto & db = atsp::data::data;

//   if ( !_length_set )
//   {
//       _length = 0;

//       for (uint i = 0; i < _size - 1; ++i)
//          _length += db[ _path[i] ][ _path[i+1] ];
//       // closes the loop
//       _length += db[_path[_size-1]][_path[0]];
//       _length_set = true;
//   }
//   return _length;
//}

//uint Path::length(uint start, uint size)
//{
//    const auto & db = atsp::data::data;

//    uint  _len = 0;

//    for (uint i = start; i < start+size-1; ++i)
//       _len += db[ _path[i] ][ _path[i+1] ];

//    return _len;
//}

//uint Path::size() const
//{
//    return _size;
//}

//uint Path::shorten(atsp::algorithm * shorten_algorithm)
//{
//    return (*shorten_algorithm)(*this);
//}

    atsp::Data data;
    data.load( atsp::TSPLibLoader(argv[1]) );

    base::fast_srand();

    clock_t begin = clock();

    const uint dataSize = data.getSize();
    auto dataPtr = data.getDataPtr();

    atsp::Path path(dataSize);
    uint q = 0;

    auto _path = path.getDataPtr();

    uint ** __data = new uint * [dataSize];
    for (uint i = 0; i < dataSize; ++i)
        __data[i] = new uint[dataSize];

    for (uint i = 0; i < dataSize; ++i)
        for (uint j = 0; j < dataSize; ++j)
            __data[i][j] = dataPtr[i][j];

    uint * __path = new uint[dataSize];
    for (uint i = 0; i < dataSize; ++i)
        __path[i] = _path[i];

    for (unsigned long long i = 0; i < 5000 * 2000; i++)
    {
        uint p = static_cast<uint>(base::fast_rand()) % dataSize;
        q = dataPtr[p][p];

        uint r = path.getLength(dataPtr);
        //uint r = path.getLength(data);
        //uint r = 0;

//        for (uint i = 0; i < dataSize - 1; ++i)
//          r += __data[ _path[i] ][ _path[i+1] ];

//        // closes the loop
//        r += __data[_path[dataSize-1]][_path[0]];


// slow
//        for (uint i = 0; i < dataSize - 1; ++i)
//          r += data[ _path[i] ][ _path[i+1] ];

//        // closes the loop
//        r += data[_path[dataSize-1]][_path[0]];

//    for (uint i = 0; i < dataSize - 1; ++i)
//        r += dataPtr[ __path[i] ][ __path[i+1] ];

//    // closes the loop
//    r += dataPtr[__path[dataSize-1]][__path[0]];

        q = f(r);
        q = f(q);
    }

    cout<< "Elapsed time: " << fixed << setprecision(2) <<
           (clock() - begin) / static_cast<double>(CLOCKS_PER_SEC) << endl;

    cout<< "Final result: "<< q << endl;
    return 0;




*/

/*
 This class is the interface for the concept
 of an algorithm to solve the atsp problem.

 Many different algorithms exist, each with its
 particularities, but all have something in common:
 they do manipulate a path in the process of
 finding the minimum Eulerian Cycle

 Also, any algorithm works through two steps:

 1 - setup: values must be passed to the algorithm
 to set it up prior to its execution.

 The problem is that each algorithm has its own parameters.

 There are dozens of ways of doing this setup:

 class constructor: each dfferent algorithm requires different set
 of parameters what makes the implementation of polymorphism
 impossible.

 setters and getters: they are a pain in the neck and also change
 on each concrete algorithm

 some virtual method implemented as a variadic function: this is ugly,
 unsafe and slow, since the variable parameters shall be properly
 retrieved on every execution of the method

 Builder pattern: note to self: return on this later

 Derivation: is the chosen method. Its expected to have
 a single instance of an algorithm per execution, so
 the derived class variables are static.

 Access restrictions (read-write) are implemented through
 references, because there is only one instance of a particular
 algorithim and because direct access through references
 may speed things up a bit compared to a accessor method

 2 - execution: this can be done in many ways:
 I chose to enforce it by amking it just a functor.
 One less method to name (execute(), load(), action(),
 run().....)

*/
/*
class Path;

class algorithm
{
public:
    typedef unsigned uint;
    virtual ~algorithm();
    virtual uint operator()(Path &) const = 0;
};

// greedy is used by many other algorithms

class greedy_algorithm : public algorithm
{

public:

    greedy_algorithm();

    virtual uint operator()(Path &) const;

    uint _pos;
    uint _length;

};
*/

//#include "path.h"
//#include "data.h"
//#include <cassert>

//using namespace atsp::data;

//atsp::algorithm::~algorithm(){}

////uint atsp::greedy_algorithm::_pos = 0;
////uint atsp::greedy_algorithm::length = 2;

//atsp::greedy_algorithm::greedy_algorithm():_pos(0),_length(0)
//{
//}

//uint atsp::greedy_algorithm::operator()(atsp::Path & p) const
//{
//   //  gets a path without the mask using a specialized constructor.
//    const Path pwm(p,_pos,_length);
//    const uint pwm_length = pwm.length();

////    // finds the length of path along the mask
//    uint msklen = p.length(_pos,_length);

////    // starts with the current length as the minimum
//    uint minlen = p.length();

////    // try # 1: single loop, no memory allocation
////    // mask's 1st and last node

//    const uint  m1st    = p[ _pos ];
//    const uint  mlast   = p[ _pos + _length -1 ];
//    const uint  pwm_sz  = pwm.size();
//    uint        insert  = 0;

//    const auto & db = atsp::data::data;

//    for (uint i = 0; i < pwm_sz - 1; ++i )
//    {
//        // if (i == _pos) continue;
//        const uint len =
//                pwm_length - // sub path original length
//                db[ pwm[i] ][ pwm[i+1] ] + // minus the way being disconnected
//                db[ pwm[i] ][ m1st ] + // plus going into the mask
//                msklen + // plus going through the mask
//                db[ mlast ][ pwm[i+1] ]; // plus going from the mask back to the path

//        if (len < minlen)
//        {
//            insert = i;
//            minlen = len;
//        }
//    }

////    // try the last _postion

////    const uint len =
////            pwm_length - // sub path original length
////            db[ pwm[ pwm_sz - 1 ] ][ pwm[ 0 ] ] + // minus the way being disconnected
////            db[ pwm[ pwm_sz - 1 ] ][ m1st ] + // plus going into the mask
////            msklen + // plus going through the mask
////            db[ mlast ][ pwm[ 0 ] ]; // plus going from the mask back to the path

////    if (len < minlen)
////    {
////        insert = pwm_sz - 1;
////        minlen = len;
////    }

////    if ( minlen < p.length() )
////    {
////      p.move(insert,_pos,_length);

////#ifdef __DEBUG__
////       assert( p.length() == minlen );
////#endif
////    }

// //   return minlen;
//}

/*
 *
 * auto _path = Algorithm::getPathPtr(path);
    auto sz = path.getSize();

    for (uint i = 0; i < 5; i++)
    {
        uint a = static_cast<uint>(rand()) % sz;
        uint b = static_cast<uint>(rand()) % sz;

        uint tmp = _path[a];
        _path[a] = _path[b];
        _path[b] = tmp;
    }

    return atsp::getLength(data, path) + _msksz + _mask;
    */


/*
 *
 * //    auto pathPtr = Algorithm::getPathPtr(path);
//    auto size = path.getSize();

//    uint msklen = 0;

//    auto db = data.getDataPtr();

//    for (uint i = _mask; i < _mask + _msksz - 1; ++i)
//       msklen += db[ pathPtr[i] ][ pathPtr[i+1] ];

//    uint * pwm = new uint[ size - _msksz ];

//    // copies the original path up to the mask start

//    std::memcpy(pwm, pathPtr, (_mask)*sizeof(uint) );

//    // copies the original path from after the mask end to the end

//    std::memcpy(pwm + _mask,
//                pathPtr + _mask + _msksz,
//                ( size - _mask - _msksz )*sizeof(uint) );

//    const uint pwmLength =  getLength(data,pwm,size-_msksz);
//    delete[] pwm;

*/
#endif // REPOSITORY_H
