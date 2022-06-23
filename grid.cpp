#include <vector>
#include <stdio.h>
#include "cell.cpp"
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

class grid
{
public:
    int rows;
    int columns;
    vector<vector<cell>> g;
    cell *out_bound;        //cella non valida

    grid(int r, int c)
    {
        rows = r;
        columns = c;
        cell invalid(0,0);
        out_bound = &invalid;
        
        //riempimento iniziale griglia
        vector<cell> empty_vec;
        g.push_back(empty_vec);         //aggiungo riga iniziale non valida
        vector<cell> horizontal;
        for(int i=1;i<=rows;i++)
        {
            horizontal.clear();
            horizontal.push_back(*out_bound);   //aggiungo colonna iniziale non valida
            for(int j=1; j<=columns; j++)
            {
                cell ce(i, j);
                horizontal.push_back(ce);
            }
            g.push_back(horizontal);
        }
        
        //assegnazione vicini
        for(int i=1;i<=rows;i++)
        {
            for(int j=1; j<=columns; j++)
            {
                g[i][j].north = verify_bound(i-1, j);
                g[i][j].east = verify_bound(i, j+1);
                g[i][j].south = verify_bound(i+1, j);
                g[i][j].west = verify_bound(i, j-1);
            }
        }
    }

    cell* verify_bound(int i, int j)
    {
        if(i<1 || i>rows || j<1 || j>columns)
        {
            return out_bound;
        }
        else
        {
            return &g[i][j];
        }
    }
    
    bool verify_bound2(int i, int j)
    {
        return !(i<1 || i>rows || j<1 || j>columns);
    }

    cell* random_cell()
    {
        int row = (rand()%rows)+1;
        int column = (rand()%columns)+1;
        return &g[row][column];
    }

    int size()
    {
        return rows*columns;
    }

    vector<cell> get_column(int column)
    {
        vector<cell> column_vec;
        for(int i=1;i<=rows;i++)
        {
            column_vec.push_back(g[i][column]);
        }
        return column_vec;
    }

    vector<cell> get_row(int row)
    {
        return g[row];
    }
    
    vector<vector<cell>> get_grid()
    {
        return g;
    }

    void display_grid()
    {
        cout << "+";
        for(int j=1; j<=columns; j++)
        {
            cout << "---+";
        }
        cout << "\n";

        for(int i=1; i<=rows; i++)
        {
            string top = "|";
            string bottom = "+";
            for(int j=1; j<=columns; j++)
            {
                top = top + "   ";
                if(g[i][j].linked(g[i][j].east))
                {
                    top = top + " ";
                }
                else
                {
                    top = top + "|";
                }

                if(g[i][j].linked(g[i][j].south))
                {
                    bottom = bottom + "   ";
                }
                else
                {
                    bottom = bottom + "---";
                }
                bottom = bottom + "+";
            }
            cout << top << endl;
            cout << bottom << endl;
        }
    }

    void display_grid_sfml(int width, int height, int cell_size)
    {
        sf::RenderWindow window(sf::VideoMode(width*cell_size, height*cell_size), "Maze Generator");
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            grid_creation(window, cell_size);
            digging(window, cell_size);
            window.display();
        }
    }
    void grid_creation(sf::RenderWindow &window, int cell_size)
    {
        for(int i=1;i<=rows;i++)
        {
            for(int j=1; j<=columns; j++)
            {
                int gx = (j * cell_size)-cell_size;
                int gy = (i * cell_size)-cell_size;
                
                sf::RectangleShape rectangle_north;
                rectangle_north.setFillColor(sf::Color::White);
                rectangle_north.setSize(sf::Vector2f(cell_size, 2));
                rectangle_north.setPosition(gx, gy);
                window.draw(rectangle_north);
                
                sf::RectangleShape rectangle_south;
                rectangle_south.setFillColor(sf::Color::White);
                rectangle_south.setSize(sf::Vector2f(cell_size, 2));
                rectangle_south.setPosition(gx, gy+(cell_size-2));
                window.draw(rectangle_south);
                
                sf::RectangleShape rectangle_west;
                rectangle_west.setFillColor(sf::Color::White);
                rectangle_west.setSize(sf::Vector2f(2, cell_size));
                rectangle_west.setPosition(gx, gy);
                window.draw(rectangle_west);
                
                sf::RectangleShape rectangle_east;
                rectangle_east.setFillColor(sf::Color::White);
                rectangle_east.setSize(sf::Vector2f(2, cell_size));
                rectangle_east.setPosition(gx+(cell_size-2), gy);
                window.draw(rectangle_east);
            }    
        }
    }

    void digging(sf::RenderWindow &window, int cell_size)
    {
        for(int i=1;i<=rows;i++)
        {
            for(int j=1; j<=columns; j++)
            {
                int gx = (j * cell_size)-cell_size;
                int gy = (i * cell_size)-cell_size;
                vector<cell*> link_v = (g[i][j]).link_vec;
                vector<cell*>:: iterator itr;
                for(itr = link_v.begin(); itr != link_v.end(); ++itr)
                {
                    if((*(*itr)).isEqual((g[i][j]).south))
                    {
                        sf::RectangleShape passage;
                        passage.setFillColor(sf::Color::Black);
                        passage.setSize(sf::Vector2f(cell_size-4, 4));
                        passage.setPosition(gx+2, gy+(cell_size-2));
                        window.draw(passage);
                    }
                    if((*(*itr)).isEqual((g[i][j]).east))
                    {
                        sf::RectangleShape passage2;
                        passage2.setFillColor(sf::Color::Black);
                        passage2.setSize(sf::Vector2f(4, cell_size-4));
                        passage2.setPosition(gx+(cell_size-2), gy+2);
                        window.draw(passage2);
                    }
                }
            }
        }
    }
};