/*
        XO game by Hassan El-shazly
        updated with levels 
*/
#include <iostream>
#include <vector>
#include <limits>
#include <string>
using namespace std;

const int minLevel = 3 ;
const int maxLevel = 16 ;

class Game 
{
    int level ;
    char game[maxLevel][maxLevel];
    vector<int> moves ;
    public:
    Game();
    void setGame(int z , char value);
    void setLevel(int x);
    void printGame();
    void printGameStart();
    int isPlayed(float a);
    char viewWinner();
};
Game::Game()
{
    // initialize level with 4 
    level = 4 ; 
    // initialize the board with '-'
    for(int i = 0 ; i < maxLevel ; i++)
    {
        for (int j = 0 ; j < maxLevel ; j++)
        {
            game[i][j] = '-' ;
        }
    }
}
void Game::setGame(int z , char value )
{
    // add the place to the taken places
    moves.push_back(z) ;
    // set the game
    z = z - 1 ;
    int y = z % level ;
    int x = (z - y) / level ;
    game[x][y] = value ;
}
void Game::setLevel(int x)
{
    level = x ;
}
void Game::printGame()
{
    // print the board with player moves
    for(int i = 0 ; i < level ; i++ )
    {
        for (int j = 0 ; j < level ; j++ )
        {
            cout << "  " << game[i][j] << "  " ;

        }
        cout << endl ; 
    }   
}
void Game::printGameStart()
{
    // print the board filled with numbers
    int count = 1 ;
    for(int i = 0 ; i < level ; i++ )
    {
        for (int j = 0 ; j < level ; j++ )
        {
            cout << count << "\t" ;
            count ++ ;

        }
        cout << endl ; 
    }   
}
int Game::isPlayed(float a )
{
    // check if the move was alread played 
    int possibleMoves = level * level ;
    int myints[possibleMoves] ;
    for (int i = 0 ; i < possibleMoves ; i++)
    {
        myints[i] = i + 1 ;
    }
    bool flag = true ;
    for (int i = 0 ;  i < possibleMoves ; i++)
    {
        if ( a == myints[i] )
            flag = false ;
    }
    if ( flag )
        return -1 ;  

    for(int i = 0 ; i < moves.size() ; i++)
    {
        if ( a == moves[i] )
        {
            return 1 ;
        }
    }
    return 0 ;
}
char Game::viewWinner()
{
    for (int i = 0 ; i < level ; i++)
    {
        // check in row
        int countx = 0 , county = 0 ;
        for (int j = 0 ; j < level ; j++)
        {
            if ( game[i][j] == 'x')
                countx++ ;
            else if ( game[i][j] == 'o')
                county++ ;
        }
        if (countx == level)
            return 'X' ;
        else if (county == level)
            return 'O' ;
        // check 4 in column
        countx = 0 ; county = 0 ;
        for (int j = 0 ; j < level ; j++)
        {
            if ( game[j][i] == 'x')
                countx++ ;
            else if ( game[j][i] == 'o')
                county++ ;
        }
        if (countx == level)
            return 'X' ;
        else if (county == level)
            return 'O' ;    
    }
    // check digonal from left to right
    int countxd = 0 , countyd = 0;
    for (int i = 0 ; i < level ; i++)
    {
        if ( game[i][i] == 'x')
            countxd++ ;
        else if ( game[i][i] == 'o')
            countyd++ ;
    }
    if (countxd == level)
        return 'X' ;
    else if (countyd == level )
        return 'O' ;
    // check digonal from right to left
    countxd = 0 ; countyd = 0;
    for (int i = 0 ; i < level ; i++)
    {
        if ( game[i][level-1-i] == 'x')
            countxd++ ;
        else if ( game[i][level-1-i] == 'o')
            countyd++ ;
    }
    if (countxd == level)
        return 'X' ;
    else if (countyd == level )
        return 'O' ;
    // there is no winner 
    return 'T' ;
}

int main ()
{
    /* starting the game by promt users for Thier names */
    string userX = "", userO = ""; 
    Game game ;
    int level ;
    do
    {
        cout << "Enter level (" << minLevel << " to " << maxLevel << ") : "  ;
        cin >> level ;
        if (!(cin))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input\n";
        } 
    } while ( level < minLevel or level > maxLevel) ;
    game.setLevel(level) ;
    cout << "Enter player name to be x : "  ;
    cin >> userX ;
    cout << "Enter player name to be o : "  ;
    cin >> userO;
    game.printGameStart();
    for (int i = 0 ; i < level * level / 2 ; i++ )
    {
        // (float) to return invalid if the user entered a float number
        float x = 0 ;
        cout << "Enter number from 1 to " << level * level << "\n" ;
        // confrim that the place is available
        do
        {
            cout << userX << " turn to play : " ;
            cin >> x ;
            if(game.isPlayed(x) == 1)
                cout << "This place is already taken\n" ;
            // if the input was string or float
            if (!(cin) or game.isPlayed(x) == -1)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invalid input\n";
            } 
        } while(game.isPlayed(x)) ;
        // print the bord with the new place
        game.setGame(x,'x');
        game.printGame();
        // check if there is a winner  
        if (game.viewWinner() == 'X')
        {
            cout << userX << " is the winner\n";
            break;
        }
        else if ( game.viewWinner() == 'O')
        {
            cout << userO << " is the winner\n";
            break;
        }

        // repeat the process again with the secend player
        cout << "Enter number from 1 to " << level * level << "\n" ;
        do
        {
            cout << userO << " turn to play : " ;
            cin >> x ;
            if(game.isPlayed(x) == 1)
                cout << "This place is already taken\n" ;
            if (!(cin) or game.isPlayed(x) == -1)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invalid input\n";
            } 
        } while(game.isPlayed(x)) ;
        game.setGame(x,'o');
        game.printGame();

        if (game.viewWinner() == 'X')
        {
            cout << userX << " is the winner\n";
            break;
        }
        else if ( game.viewWinner() == 'O')
        {
            cout << userO << " is the winner\n";
            break;
        }
    }
    // if the available places were out with no winner then the game is tied
    if (game.viewWinner() == 'T')
        {
            cout <<"the game is tied\n" ;
        }  
    cout << " press Enter to exit " ;
    cin.get();
    cin.get();
    return 0 ;
}