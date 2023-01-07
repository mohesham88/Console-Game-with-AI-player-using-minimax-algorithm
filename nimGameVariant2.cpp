#include <iostream>

#define NO_GOOD_MOVE  0
#define MAX_MOVE 3
#define N_COINS 23
#define HUMAN 1
#define COMPUTER 0
int computer_pile_choice;
using namespace std;


int pile_num;




int calc_sum(int pile[3]){
	int sum = 0;


    for(int i = 0 ; i <= 2;i++){
		sum += pile[i]; 
	}

	return sum;
}

bool game_over(int piles[3]){
	if(calc_sum(piles) == 1)
		return true;


	return false;
}


int minimax(int piles[3],bool is_max){


	if(game_over(piles)){

		if(is_max){
			return -1;
		}
		else{
			return +1;
		}

	}
	

    if(is_max){

        int best = -1000;
		for(int i = 0; i <= 2;i++){ 
			for(int j = 1; j <= MAX_MOVE;j++){

				if( piles[i] - j >= 0){
					// DO
					piles[i] -= j;
					best = max(best,minimax(piles,!is_max));				
					// UNDO
					piles[i] += j;
				}
			}
    	}

		if(best == -1000)
			best = -1;

        return best;
    
    }

    else{


        int best = 1000;
		for(int i = 0; i <= 2;i++){ 
			for(int j = 1; j <= MAX_MOVE;j++){
				if( piles[i] - j >= 0){

					piles[i] -= j;
					best = min(best,minimax(piles,!is_max));									
					piles[i] += j;
				}
			}
    	}
		if(best == 1000)
			best = -1;
        return best;
    }



}

int find_best_move(int piles[3]){

    int best_move = -1;
	int play = 1;
	
    for(int i = 0; i <= 2;i++){ 

		for(int j = 1; j <= MAX_MOVE;j++){
		
			if( piles[i] - j >= 0){

				piles[i] -= j;
				//int move = minimax(coins ,true);
				int move = minimax(piles,false);
				
				// cout << minimax(coins - i,true) << '\n';
				piles[i] += j;

				if(move > best_move){
					best_move = move;
					play = j;
					pile_num = i + 1;
				}


			}
		}

    }
	
    return play;
 
}














int main() {
    int nCoins = N_COINS, n;
    int piles[3] = {3,4,5};
    int whoseTurn = HUMAN;
    cout << "Welcome to Nim. We start with " << nCoins << endl;
    cout << "Each one picks 1 to " << MAX_MOVE << " coins.\n";

    while (calc_sum(piles) != 0) {
		cout << "\nWe have " << '{' << piles[0] << "," << piles[1] <<  "," << piles[2]  << "}.\n";
		cout << (whoseTurn ? "Human" : "Computer") << " plays: ";
		int pile_number = 4;
		switch (whoseTurn) {
			case HUMAN:
				n = nCoins + 10;
				
				while(pile_number  < 1 || pile_number  > 3){
					cout << "Pls pick the pile you want to take from (from 1 to 3): ";
					cin >> pile_number;
					if(piles[pile_number - 1] == 0){
						cout << "\nthe pile you chosed is empty";
						// to loop again
						pile_number = 4;
					}	
				}
				
				while (n < 1 || n > 3 || n > nCoins) {	
					cout << "Pls pick 1 to 3 coins and <= remaining coins: ";
					cin >> n;


					// loop again
					if(piles[pile_number - 1] - n < 0){
						cout << "";
						n = nCoins + 10;
					}

					else{
						piles[pile_number - 1] -= n;
					}
				}
				pile_number = 4;
				break;


			case COMPUTER:
				n = find_best_move(piles);

				cout << "Computer takes " << n << " coins."  << "from pile number " << pile_num << '\n';
				piles[pile_num - 1] -= n;
		}
		whoseTurn = (whoseTurn + 1) % 2;
    }
    cout << "\n\nWinner is : " << (whoseTurn ? "Human \n" : "Computer \n");
}
