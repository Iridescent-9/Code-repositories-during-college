#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <string>
#include <vector>
#include <map>
using namespace std;
class graph
{
protected:
    int nv;
    vector<string> vectors;
    map<string , int> iov;

public:
    graph ( int );
    virtual bool insertV ( string );
    virtual bool insertE ( string , string , string , int );
    virtual bool insertE ( int , int , string , int ) = 0;
};

graph::graph ( int n = 0 )
{
    nv = n;
}

bool graph::insertV ( string v )
{
    if ( iov.find ( v ) != iov.end ( ) )
    {
        return false;
    }
    vectors.push_back ( v );
    iov [ v ] = nv;
    nv++;
    return true;
}

bool graph::insertE ( string first , string secend , string act , int weight )
{
    return insertE ( iov [ first ] , iov [ secend ] , act , weight );
}
#endif