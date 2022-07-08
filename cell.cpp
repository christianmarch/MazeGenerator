#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <list>
#include <ctime>
using namespace std;

class cell
{
    public:
    int row;
    int column;
    cell *north;
    cell *east;
    cell *south;
    cell *west;
    vector<cell*> link_vec;

    cell(int r, int c)
    {
        row = r;
        column = c;
    }

    void link(cell *c, bool bidi=true)
    {
        link_vec.push_back(c);
        if(bidi)
        {
            (*c).link(this, false);
        }
    }

    void unlink(cell *c, bool bidi=true)
    {
        vector<cell*>:: iterator itr;
        for(itr = link_vec.begin(); itr != link_vec.end(); ++itr)
        {
            if((*(*itr)).isEqual(c))
            {
                link_vec.erase(itr);
            }
        }
        if(bidi)
        {
            (*c).unlink(this, false);
        }
    }

    void links()
    {
        vector<cell*>:: iterator itr;
        for (itr = link_vec.begin(); itr != link_vec.end(); ++itr)
        {
            cout << (*(*itr)).row << " " << (*(*itr)).column<< endl;
        }
    }

    bool linked(cell *c)
    {
        vector<cell*>:: iterator itr;
        for (itr = link_vec.begin(); itr != link_vec.end(); ++itr)
        {
            if((*(*itr)).isEqual(c))
            {
                return true;
            }
        }
        return false;
    }
    
    vector<cell*> neighbors()
    {
        vector<cell*> n;
        if((*north).row > 0 && (*north).column > 0)
        {
            n.push_back(north);
        }
        if((*east).row > 0 && (*east).column > 0)
        {
            n.push_back(east);
        }
        if((*south).row > 0 && (*south).column > 0)
        {
            n.push_back(south);
        }
        if((*west).row > 0 && (*west).column > 0)
        {
            n.push_back(west);
        }
        return n;
    }

    cell* rand_neighbor()
    {
        vector<cell*> n = neighbors();
        return n[rand()%n.size()];
    }

    bool isEqual(cell *c)
    {
        return (row == (*c).row && column == (*c).column);
        /*{
            return true;
        }
        else
        {
            return false;
        }*/
    }
};