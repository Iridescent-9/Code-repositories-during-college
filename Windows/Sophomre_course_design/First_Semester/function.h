#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <fstream>
#include "graph.h"
#include "lgraph.h"
int choice ( int n )
{
    switch ( n )
    {
        case 1:
            {
                int node_num , edge , weight;
                string n1 , n2 , act;
                ifstream fin ( "D:/MyCode/VisualStudio/VSC/VS-Code/Windows/Sophomre_course_design/First_Semester/graph.txt" );
                if ( !fin )
                {
                    cout << "文件打开失败" << endl;
                    ofstream fout ( "graph.txt" );
                    fout.close ( );
                    return 0;
                }
                fin >> node_num;
                lgraph g ( node_num );
                fin >> edge;
                for ( int i = 0; i < edge; i++ )
                {
                    fin >> n1;
                    fin >> n2;
                    fin >> act;
                    fin >> weight;
                    g.insertE ( n1 , n2 , act , weight );
                }
                g.print ( );
                g.CriticalPath ( );
            }
            break;

        case 2:
            {
                int node_num , edge , weight;
                string n1 , n2 , act;
                cout << "请输入节点数:";
                cin >> node_num;
                lgraph g ( node_num );
                cout << "请输入边数:";
                cin >> edge;
                cout << endl;
                cout << "请输入边两端节点名称及权值" << endl;
                for ( int i = 0; i < edge; i++ )
                {
                    cin >> n1;
                    cin >> n2;
                    cin >> act;
                    cin >> weight;
                    g.insertE ( n1 , n2 , act , weight );
                }
                g.print ( );
                g.CriticalPath ( );
            }
            break;
    }
    return 0;
}
int menu ( )
{
    int n = 0;
    cout.fill ( '-' );
    cout.width ( 50 );
    cout << "-" << endl;
    cout.fill ( ' ' );
    cout.width ( 10 );
    cout << " ";
    cout << "1.从文件直接读取" << endl;
    cout.fill ( ' ' );
    cout.width ( 10 );
    cout << " ";
    cout << "2.手动输入" << endl;
    cout.fill ( '-' );
    cout.width ( 50 );
    cout << "-" << endl;
    cout << "输入功能序号" << endl;
    cin >> n;
    choice ( n );
    return 0;
}
#endif