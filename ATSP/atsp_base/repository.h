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
 */
#endif // REPOSITORY_H
