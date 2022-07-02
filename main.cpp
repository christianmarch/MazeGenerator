#include "grid.cpp"
#include <stdio.h>
#include <ctime>
#include <unordered_map>
#include <map>
using namespace std;

#define WIDTH 20
#define HEIGHT 20
#define CELL_SIZE 30

void binary_tree(grid &test)
{
    int rando;
    vector<cell*> n;
    for(int i=1;i<=test.rows;i++)
    {
        for(int j=1; j<=test.columns; j++)
        {
            n.clear();
            if(test.verify_bound2(i-1, j))  //north
            {
                n.push_back(&((test.g)[i-1][j]));
            }
            if(test.verify_bound2(i, j+1))  //east
            {
                n.push_back(&((test.g)[i][j+1]));
            }
            if(n.size() == 0)
            {
                continue;
            }

            rando = rand()%(n.size());
            ((test.g)[i][j]).link(n[rando]);
        }
    }
    /*for(int i=1;i<=test.rows;i++)
    {
        for(int j=1; j<=test.columns; j++)
        {
            ((test.g)[i][j]).links();
            cout << endl;
        }
    }*/
}

void aldous_broder(grid &test)
{
    int rando;
    vector<cell*> n;
    cell *here = test.random_cell();
    cell *neighbor;
    int unvisited = test.size()-1;
    while(unvisited>0)
    {
        n.clear();
        n = (*here).neighbors();
        rando = rand()%(n.size());
        neighbor = n[rando];
        if(((*neighbor).link_vec).empty())
        {
            (*here).link(neighbor);
            unvisited -= 1;
        }
        here = neighbor;
    }
}

bool find(unordered_map<int, cell*> &unvisited, cell* c)
{
    unordered_map<int, cell*>:: iterator itr;
    for(itr = unvisited.begin(); itr != unvisited.end(); ++itr)
    {
        if((*(itr->second)).isEqual(c))
        {
            return true;
        }
    }
    return false;
}

int contains(vector<cell*> path, cell *c)
{
    for(int i=0; i<path.size(); i++)
    {
        if((*(path[i])).isEqual(c))
        {
            return i;
        }
    }
    return -1;
}

int find_index(unordered_map<int, cell*> &unvisited, cell* c)
{
    unordered_map<int, cell*>:: iterator itr;
    for(itr = unvisited.begin(); itr != unvisited.end(); ++itr)
    {
        if((*(itr->second)).isEqual(c))
        {
            return itr->first;
        }
    }
}

void stamp(vector<cell*> &path)
{
    for(int i=0; i < path.size();i++)
    {
        cout << (*path[i]).row << (*path[i]).column << "|";
    }
    cout << endl;
}

void wilsons(grid &test)
{
    int rando;
    unordered_map<int, cell*> unvisited;
    vector<cell*> path;
    int a = 1;
    for(int i=1;i<=test.rows;i++)
    {
        for(int j=1; j<=test.columns; j++)
        {
            unvisited.insert({a, &((test.g)[i][j])});
            a++;
        }
    }
    rando = (rand()%(unvisited.size()))+1;
    cell *here = unvisited[rando];
    unvisited.erase(rando);
    int n;
    while(!unvisited.empty())
    {
        //scelgo una cella casuale dalle unvisited
        unordered_map<int, cell*>::iterator it_rand = unvisited.begin();
        advance(it_rand, rand()%unvisited.size());
        here = it_rand -> second;
        /*rando = (rand()%(unvisited.size()))+1;
        cell *here = unvisited[rando];*/
        
        path.clear();
        path.push_back(here);
        //int key = ((((*here).row)-1)*test.columns) + ((*here).column);
        while(find(unvisited, here))
        {
            here = (*here).rand_neighbor();
            if((n = contains(path, here))>=0)
            {
                path.resize(n+1);
                path.shrink_to_fit();
                //cout << "RESET PATH con " << (*here).row<< " "<< (*here).column << endl;
            }
            else
            {
                path.push_back(here);
                //stamp(path);
            }
        }
        //cout << "CREAZIONE LINKS" << endl;
        for(int i=0; i < path.size()-1; i++)
        {
            (*path[i]).link(path[i+1]);
            unvisited.erase(find_index(unvisited, path[i]));
        }
    }  
}

void recursive_backtraker(grid &test)
{
    vector<cell*> stack;
    vector<cell*> neighbors;
    vector<cell*> unvisited_neighbors;
    cell *here = test.random_cell();
    cell *neighbor;
    int initial_size;
    stack.push_back(here);
    while(!stack.empty())
    {
        neighbors.clear();
        unvisited_neighbors.clear();
        here = stack.back();
        neighbors = here->neighbors();
        initial_size = neighbors.size();
        for(int i=0; i<initial_size; i++)
        {
            if((neighbors[i]->link_vec).empty())
            {
                unvisited_neighbors.push_back(neighbors[i]);
            }
        }
        if(unvisited_neighbors.empty())
        {
            stack.pop_back();
        }
        else
        {
            neighbor = unvisited_neighbors[rand()%unvisited_neighbors.size()];
            here->link(neighbor);
            stack.push_back(neighbor);
        }
    }
}

void kruscal(grid &test)
{
    vector<vector<cell*>> couples;
    vector<cell*> tmp;
    //pair<cell*, cell*> tmp;
    unordered_map<cell*, int> set_for_cell;
    multimap<int, cell*> cells_in_set;
    vector<cell*> losers;
    //INIZIALIZZAZIONE GRID
    int a = 1;
    for(int i=1;i<=test.rows;i++)
    {
        for(int j=1; j<=test.columns; j++)
        {
            set_for_cell.insert({&((test.g)[i][j]), a});
            cells_in_set.insert({a, &((test.g)[i][j])});
            a++;
        }
    }
    //RIEMPIMENTO COUPLES
    for(int i=1;i<=test.rows;i++)
    {
        for(int j=1; j<=test.columns; j++)
        {
            //tmp.clear();
            if(test.g[i][j].south->row > 0 && test.g[i][j].south->column > 0)
            {
                
                //tmp = make_pair(&(test.g[i][j]), test.g[i][j].south);
                tmp.push_back(&(test.g[i][j]));
                tmp.push_back((test.g[i][j]).south);
                couples.push_back(tmp);
            }
            //tmp.clear();
            if(test.g[i][j].east->row > 0 && test.g[i][j].east->column > 0)
            {
                //tmp = make_pair(&(test.g[i][j]), test.g[i][j].east);
                tmp.push_back(&(test.g[i][j]));
                tmp.push_back((test.g[i][j]).east);
                couples.push_back(tmp);
            }
        }
    }
    //INIZIO ALGORITMO
    //tmp.clear();    //ora viene utilizzato per estrarre le coppie
    int winner;
    int loser;
    while(!couples.empty())
    {
        vector<vector<cell*>>::iterator it_rand = couples.begin();
        advance(it_rand, rand()%couples.size());
        tmp = *it_rand;
        couples.erase(it_rand);
        if(set_for_cell[tmp[0]] != set_for_cell[tmp[1]])
        {
            tmp[0]->link(tmp[1]);
            winner = set_for_cell[tmp[0]];
            loser = set_for_cell[tmp[1]];
            
            //RIEMPIO LOSERS
            losers.clear();
            multimap<int,cell*>::iterator itr;
            pair<multimap<int, cell*>::iterator, multimap<int, cell*>::iterator> ret;
            ret = cells_in_set.equal_range(loser);
            for (itr=ret.first; itr!=ret.second; ++itr)
            {
                losers.push_back(itr->second);
            }

            //AGGIORNO LE DUE MAPPE
            for(int i=0; i<losers.size(); i++)
            {
                //esempio se winner=1 e loser=2 e losers=a,b,c
                cells_in_set.insert({winner, losers[i]});       //inserisco a,b,c in cells_in_set con chiave 1
                set_for_cell.erase(losers[i]);                  //elimino a,b,c da set_for_cell
                set_for_cell.insert({losers[i], winner});       //reinserisco a,b,c in set_for_cell con valore 1 al posto di 2
            }
            cells_in_set.erase(loser);                          //elimino gli elementi con chiave 2 da cells_in_set
        }
    }
}

int main()
{
    srand(time(NULL));
    grid test(HEIGHT, WIDTH);
    //binary_tree(test);
    //aldous_broder(test);
    //wilsons(test);
    //recursive_backtraker(test);
    kruscal(test);
    //test.display_grid();
    test.display_grid_sfml(WIDTH, HEIGHT, CELL_SIZE);
    return 0;
}