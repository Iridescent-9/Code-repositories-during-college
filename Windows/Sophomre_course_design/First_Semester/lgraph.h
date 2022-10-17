#ifndef _LGRAPH_H_
#define _LGRAPH_H_
#include <iostream>
#include <algorithm>
#include <queue>
#include "graph.h"
using namespace std;
class lgraph : public graph
{
protected:
    bool topsort ( );
    void setadjL ( );
    vector<int> topo;
    vector<map<int , map<string , int> > > adjL;
    vector<int> size;

public:
    void print ( );
    bool CriticalPath ( );
    bool insertV ( string );
    bool insertE ( int , int , string , int );
    bool insertE ( string , string , string , int );
    lgraph ( int n = 0 ) :graph::graph ( n )
    {
        setadjL ( );
    };
};

bool lgraph::topsort ( )
{
    vector<int> inDegree ( nv , 0 );
    for ( auto vl : adjL )
    {
        for ( auto w : vl )
        {
            inDegree [ w.first ]++;
        }
    }
    queue<int> q;
    for ( int i = 0; i < nv; i++ )
    {
        if ( inDegree [ i ] == 0 )
        {
            q.push ( i );
        }
    }
    int count = 0 , v;
    while ( !q.empty ( ) )
    {
        v = q.front ( );
        topo.push_back ( v );
        q.pop ( );
        count++;
        for ( auto x : adjL [ v ] )
        {
            inDegree [ x.first ]--;
            if ( inDegree [ x.first ] == 0 )
            {
                q.push ( x.first );
            }
        }
    }
    if ( count != nv )
    {
        return false;
    }
    return true;
}

void lgraph::setadjL ( )
{
    adjL.resize ( nv );
    for ( auto x : adjL )
    {
        x.clear ( );
    }
    graph::nv = 0;
}

void lgraph::print ( )
{
    cout << "图的邻接表:" << endl;
    for ( int i = 0; i < nv; i++ )
    {
        int count = 0;
        cout << vectors [ i ] << "-->";
        for ( auto x : adjL [ i ] )
        {
            map<string , int>::iterator it = x.second.begin ( );
            cout << "  ";
            cout << vectors [ x.first ] << "[" << it->first << "=" << it->second << "]";
            cout << "  ";
        }
        cout << endl;
    }
}

bool lgraph::CriticalPath ( )
{
    if ( !topsort ( ) )
    {
        cout << "错误，图中有环" << endl;
        return false;
    }
    int aet , alt;
    vector<int> ve ( nv , INT_MIN ); //事件最早发生时间
    vector<int> anode;           //关键路径前一节点
    vector<int> bnode;           //关键路径后一节点
    ve [ 0 ] = 0;
    for ( int i = 0; i < nv; i++ ) //事件最早发生时间
    {
        for ( auto x : adjL [ topo [ i ] ] )
        {
            map<string , int>::iterator it = x.second.begin ( );
            if ( ve [ x.first ] < it->second + ve [ topo [ i ] ] )
            {
                ve [ x.first ] = it->second + ve [ topo [ i ] ];
            }
        }
    }
    vector<int> vl ( nv , ve [ static_cast< unsigned __int64 >( nv ) - 1 ] ); //事件最晚发生时间
    for ( int i = nv - 1; i >= 0; i-- )
    {
        for ( auto x : adjL [ topo [ i ] ] )
        {
            map<string , int>::iterator it = x.second.begin ( );
            if ( vl [ topo [ i ] ] > vl [ x.first ] - it->second )
            {
                vl [ topo [ i ] ] = vl [ x.first ] - it->second;
            }
        }
    }
    cout << "关键活动为:";
    for ( int i = 0; i < nv; i++ )
    {
        for ( auto x : adjL [ i ] )
        {
            map<string , int>::iterator it = x.second.begin ( );
            aet = ve [ i ];
            alt = vl [ x.first ] - it->second;
            if ( aet == alt )
            {
                cout << it->first << " ";
                anode.push_back ( i );
                bnode.push_back ( x.first );
            }
        }
    }
    cout << endl;
    cout << "关键路径为:" << endl;
    for ( int i = 0; i < anode.size ( ); i++ )
    {
        cout << vectors [ anode [ i ] ] << "-->" << vectors [ bnode [ i ] ] << endl;
    }
    auto max_time = max_element ( vl.begin ( ) , vl.end ( ) );
    cout << "花费的时间至少为:" << *max_time << endl;
    return true;
}

bool lgraph::insertV ( string v )
{
    if ( !graph::insertV ( v ) )
    {
        return false;
    }
    adjL.push_back ( map<int , map<string , int> > ( ) );
    return true;
}

bool lgraph::insertE ( int first , int secend , string act , int weight )
{
    if ( first < 0 || secend < 0 || first >= nv || secend >= nv )
    {
        return false;
    }
    if ( adjL [ first ].find ( secend ) != adjL [ first ].end ( ) )
    {
        return false;
    }
    map<string , int> a;
    a.insert ( make_pair ( act , weight ) );
    adjL [ first ].insert ( make_pair ( secend , a ) );
    return true;
}

bool lgraph::insertE ( string first , string secend , string act , int weight )
{
    graph::insertV ( first );
    graph::insertV ( secend );
    return graph::insertE ( first , secend , act , weight );
}

#endif