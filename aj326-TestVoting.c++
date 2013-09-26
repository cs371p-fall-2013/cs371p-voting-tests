/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main

    % valgrind TestVoting > TestVoting.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "gtest/gtest.h"

#include "Voting.h"

// ----------
// TestVoting
// ----------

// ----------------
// voting_read_case
// ----------------

TEST(Voting, voting_read_case) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int i;
    const bool b = voting_read_case(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);}

TEST(Voting, voting_read_case_2) {
    std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nThom York\nFlea\nJoe Satch\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n2 3 1");
    int i;
    const bool b = voting_read_case(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    2);}
    
TEST(Voting, voting_read_case_3) {
    std::istringstream r("7\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nThom York\nFlea\nJoe Satch\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n2 3 1");
    int i;
    const bool b = voting_read_case(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    7);}
    
    
// --------------------
// voting_read_num_cand
// --------------------

TEST(Voting, voting_read_num_cand) {
    std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int i;
    const bool b = voting_read_num_cand(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    3);}
    
TEST(Voting, voting_read_num_cand_2) {
    std::istringstream r("5\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int i;
    const bool b = voting_read_num_cand(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    5);}
    
TEST(Voting, voting_read_num_cand_3) {
    std::istringstream r("1\nJohn Doe\n1\n1\n1\n1\n1");
    int i;
    const bool b = voting_read_num_cand(r, i);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(i ==    1);}
    
// ---------------------
// voting_read_cand_name
// ---------------------

TEST(Voting, voting_read_cand_name) {
    std::istringstream r("John Doe\nJane Smith\nSirhan Sirhan\n");
    int num_cand = 3;
    std::string expected_str[3] = {"John Doe", "Jane Smith", "Sirhan Sirhan"};
    struct cand c[20];
    const bool b = voting_read_cand_name(r, num_cand, c);
    ASSERT_TRUE(b == true);
    for(int i = 0; i < num_cand; i++){
        ASSERT_TRUE(c[i].name == expected_str[i]);
      
    }
    }
    
TEST(Voting, voting_read_cand_name_2) {
    std::istringstream r("John Doe\n");
    int num_cand = 1;
    std::string expected_str[1] = {"John Doe"};
    struct cand c[20];
    const bool b = voting_read_cand_name(r, num_cand, c);
    ASSERT_TRUE(b == true);
    for(int i = 0; i < num_cand; i++){
        ASSERT_TRUE(c[i].name == expected_str[i]);
      
    }
    }
  
TEST(Voting, voting_read_cand_name_3) {
    std::istringstream r("John Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\nJohn Doe\n");
    int num_cand = 20;
    std::string expected_str[20] = {"John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe", "John Doe"};
    struct cand c[20];
    const bool b = voting_read_cand_name(r, num_cand, c);
    ASSERT_TRUE(b == true);
    for(int i = 0; i < num_cand; i++){
        ASSERT_TRUE(c[i].name == expected_str[i]);
      
    }
    }
// -------------------
// voting_read_ballots
// -------------------

TEST(Voting, voting_read_ballots) {
    std::istringstream r("1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    int matrix[1000][20] = {{0}};
    int expected_matrix[5][3] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2}};
    int cand_num = 3;
    bool eof = false;
    int i = 0;
    bool b = voting_read_ballots(r, cand_num, matrix, i, eof);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(eof == true);
    for(int i = 0; i < 5; i++){
        for(int x = 0; x < cand_num; x++){
            ASSERT_TRUE(matrix[i][x] == expected_matrix[i][x]);
            }
        }
    }
    
TEST(Voting, voting_read_ballots_2) {
    std::istringstream r("1 2 3");
    int matrix[1000][20] = {{0}};
    int expected_matrix[1][3] = {{1, 2, 3}};
    int cand_num = 3;
    bool eof = false;
    int i = 0;
    bool b = voting_read_ballots(r, cand_num, matrix, i, eof);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(eof == true);
    for(int i = 0; i < 1; i++){
        for(int x = 0; x < cand_num; x++){
            ASSERT_TRUE(matrix[i][x] == expected_matrix[i][x]);
            }
        }
    }
    
TEST(Voting, voting_read_ballots_3) {
    std::istringstream r("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
    int matrix[1000][20] = {{0}};
    int expected_matrix[2][20] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}};
    int cand_num = 20;
    bool eof = false;
    int i = 0;
    bool b = voting_read_ballots(r, cand_num, matrix, i, eof);
    ASSERT_TRUE(b == true);
    ASSERT_TRUE(eof == true);
    for(int i = 0; i < 1; i++){
        for(int x = 0; x < cand_num; x++){
            ASSERT_TRUE(matrix[i][x] == expected_matrix[i][x]);
            }
        }
    }
    
// -------------
// assignBallots
// -------------

TEST(Voting, voting_assignBallots) {
    int matrix_eval[5][3] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++)
	for (int j = 0; j<3; j++)
	    matrix[i][j] = matrix_eval[i][j];
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    int expected_assignments[3] = {2, 2, 1};
    bool winnerFound = assignBallots(matrix, c, 5);
    ASSERT_TRUE(!winnerFound);
    for(int i = 0; i < 3; i++)
         ASSERT_TRUE(c[i].ballotsWon == expected_assignments[i]);
}

TEST(Voting, voting_assignBallots_2) {
    int matrix_eval[5][3] = {{3, 1, 2}, {2, 3, 1}, {2, 3, 1}, {1, 2, 3}, {1, 3, 2}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++)
	for (int j = 0; j<3; j++)
	    matrix[i][j] = matrix_eval[i][j];
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    int expected_assignments[3] = {2, 2, 1};
    bool winnerFound = assignBallots(matrix, c, 5);
    ASSERT_TRUE(!winnerFound);
    for(int i = 0; i < 3; i++)
         ASSERT_TRUE(c[i].ballotsWon == expected_assignments[i]);
}

TEST(Voting, voting_assignBallots_3) {
    int matrix_eval[5][4] = {{3, 1, 2, 4}, {2, 3, 1, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}, {1, 3, 2, 4}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++)
	for (int j = 0; j<4; j++)
	    matrix[i][j] = matrix_eval[i][j];
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    c[3].name = "Glenn Downing";
    c[3].eliminated = false;
    int expected_assignments[4] = {2, 2, 1, 0};
    bool winnerFound = assignBallots(matrix, c, 5);
    ASSERT_TRUE(!winnerFound);
    for(int i = 0; i < 4; i++)
         ASSERT_TRUE(c[i].ballotsWon == expected_assignments[i]);
}

// -----------
// areE
// -----------

TEST(Voting, voting_areE) {
    struct cand c[20];
    init(c);
    c[0].ballotsWon = 1; 
    c[0].eliminated = false;
    c[1].ballotsWon = 1;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    c[3].ballotsWon = 1;
    c[3].eliminated = false;
    ASSERT_TRUE(areE(c,4));
    for(int i = 0; i< 4; i++){
	ASSERT_TRUE(c[i].isWinner);
	}
}

TEST(Voting, voting_areE_2) {
    struct cand c[20];
    init(c);
    c[0].ballotsWon = 2; 
    c[0].eliminated = false;
    c[1].ballotsWon = 1;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    c[3].ballotsWon = 1;
    c[3].eliminated = false;
    ASSERT_TRUE(!areE(c,4));
    for(int i = 0; i< 4; i++){
	ASSERT_TRUE(!c[i].isWinner);
	}
}

TEST(Voting, voting_areE_3) {
    struct cand c[20];
    init(c);
    c[0].ballotsWon = 2; 
    c[0].eliminated = false;
    c[1].ballotsWon = 2;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    c[3].ballotsWon = 1;
    c[3].eliminated = false;
    ASSERT_TRUE(!areE(c,4));
    for(int i = 0; i< 4; i++){
	ASSERT_TRUE(!c[i].isWinner);
	}
}

// -----------
// isMajority
// -----------

TEST(Voting, voting_isMajority) {
    struct cand c[20];
    init(c);
    c[0].ballotsWon = 4; 
    c[0].eliminated = false;
    c[1].ballotsWon = 1;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    c[3].ballotsWon = 1;
    c[3].eliminated = false;
    ASSERT_TRUE(isMajority(7,c,4));
    ASSERT_TRUE(c[0].isWinner);
    ASSERT_TRUE(!c[1].isWinner);
    ASSERT_TRUE(!c[2].isWinner);
    ASSERT_TRUE(!c[3].isWinner);
}

TEST(Voting, voting_isMajority_2) {
     struct cand c[20];
    init(c);
    c[0].ballotsWon = 2; 
    c[0].eliminated = false;
    c[1].ballotsWon = 1;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    c[3].ballotsWon = 1;
    c[3].eliminated = false;
    ASSERT_TRUE(!isMajority(5,c,4));
    ASSERT_TRUE(!c[0].isWinner);
    ASSERT_TRUE(!c[1].isWinner);
    ASSERT_TRUE(!c[2].isWinner);
    ASSERT_TRUE(!c[3].isWinner);
} 


TEST(Voting, voting_isMajority_3) {
  struct cand c[20];
    init(c);
    c[0].ballotsWon = 2; 
    c[0].eliminated = false;
    c[1].ballotsWon = 2;
    c[1].eliminated = false; 
    c[2].ballotsWon = 2;
    c[2].eliminated = false;
    c[3].ballotsWon = 2;
    c[3].eliminated = false;
    ASSERT_TRUE(!isMajority(8,c,4));
    ASSERT_TRUE(!c[0].isWinner);
    ASSERT_TRUE(!c[1].isWinner);
    ASSERT_TRUE(!c[2].isWinner);
    ASSERT_TRUE(!c[3].isWinner);
}

// -----------
// reassignBallots
// -----------

TEST(Voting, voting_reassignBallots) {
  int matrix_eval[5][3] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++){
	for (int j = 0; j<3; j++){
	matrix[i][j] = matrix_eval[i][j];
		}
	}
    struct cand c[20];
    init(c);
    c[0].ballotsWon = 2; 
    c[0].eliminated = false;
    c[1].ballotsWon = 2;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    
    reassignBallots(matrix, c, 3);
    ASSERT_TRUE(!c[0].eliminated);
    ASSERT_TRUE(!c[1].eliminated);
    ASSERT_TRUE(c[2].eliminated);

}

TEST(Voting, voting_reassignBallots_2) {
  int matrix_eval[5][4] = {{3, 1, 2, 4}, {2, 3, 1, 4}, {2, 3, 1, 4}, {1, 2, 3, 4}, {1, 3, 2, 4}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++)
	for (int j = 0; j<4; j++)
	    matrix[i][j] = matrix_eval[i][j];
    struct cand c[20];
    init(c);
    c[0].ballotsWon = 2; 
    c[0].eliminated = false;
    c[1].ballotsWon = 2;
    c[1].eliminated = false; 
    c[2].ballotsWon = 1;
    c[2].eliminated = false;
    c[3].ballotsWon = 0;
    c[3].eliminated = false;
 
    reassignBallots(matrix, c, 4);
    ASSERT_TRUE(!c[0].eliminated);
    ASSERT_TRUE(!c[1].eliminated);
    ASSERT_TRUE(c[2].eliminated);
    ASSERT_TRUE(c[3].eliminated);
}

// -----------
// voting_eval
// -----------

TEST(Voting, voting_eval) {
    int matrix_eval[5][3] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++){
	for (int j = 0; j<3; j++){
	matrix[i][j] = matrix_eval[i][j];
		}
	}
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    bool expected_winners[20] = {false};
    expected_winners[0] = true;
    voting_eval(matrix, c, 3, 5);
    for(int i = 0; i<20; i++){
        ASSERT_TRUE(c[i].isWinner == expected_winners[i]);
	}
}

TEST(Voting, voting_eval_2) {
    //reverse ordering of ballots
    int matrix_eval[5][3] = {{3, 1, 2}, {2, 3, 1}, {2, 3, 1}, {1, 2, 3}, {1, 3, 2}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++){
	for (int j = 0; j<3; j++){
	matrix[i][j] = matrix_eval[i][j];
		}
	}
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    bool expected_winners[20] = {false};
    expected_winners[0] = true;
    voting_eval(matrix, c, 3, 5);
    for(int i = 0; i<20; i++){
        ASSERT_TRUE(c[i].isWinner == expected_winners[i]);
	}
}

TEST(Voting, voting_eval_3) {
    //First place is loser
    int matrix_eval[5][3] = {{1, 3, 2}, {2, 3, 1}, {2, 3, 1}, {3, 2, 1}, {3, 3, 1}};
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 5; i++){
	for (int j = 0; j<3; j++){
	matrix[i][j] = matrix_eval[i][j];
		}
	}
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    bool expected_winners[20] = {false};
    expected_winners[2] = true;
    voting_eval(matrix, c, 3, 5);
    for(int i = 0; i<20; i++){
        ASSERT_TRUE(c[i].isWinner == expected_winners[i]);
	}
}

TEST(Voting, voting_eval_4) {
    //First and second are winners
    int matrix_eval[6][3] = {{1, 2, 3}, {2, 1, 3}, {2, 3, 1}, {1, 2, 3}, {3, 1, 2}, {2, 3, 1}};  //3rd elim, 1st and 2nd have same num
    int matrix[1000][20] = {{0}};
    for (int i = 0; i < 6; i++){
	for (int j = 0; j<3; j++){
	matrix[i][j] = matrix_eval[i][j];
		}
	}
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].eliminated = false;
    c[1].name = "Jane Smith";
    c[1].eliminated = false;
    c[2].name = "Sirhan Sirhan";
    c[2].eliminated = false;
    bool expected_winners[20] = {false};
    expected_winners[0] = true;
    expected_winners[1] = true;
    voting_eval(matrix, c, 3, 6);
    for(int i = 0; i<20; i++){
        ASSERT_TRUE(c[i].isWinner == expected_winners[i]);
	}
}
// ------------
// voting_print
// ------------

TEST(Voting, voting_print) {
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].isWinner = true;
    c[1].name = "Jane Smith";
    c[2].name = "Sirhan Sirhan";
    std::ostringstream w;
    voting_print(w, c, 3);
    ASSERT_TRUE(w.str() == "John Doe\n");}
 TEST(Voting, voting_print_2) {
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].isWinner = true;
    c[1].name = "Jane Smith";
    c[1].isWinner = true;
    c[2].name = "Sirhan Sirhan";
    std::ostringstream w;
    voting_print(w, c, 3);
    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\n");}
  TEST(Voting, voting_print_3) {
    struct cand c[20];
    init(c);
    c[0].name = "John Doe"; 
    c[0].isWinner = true;
    c[1].name = "Jane Smith";
    c[1].isWinner = true;
    c[2].name = "Sirhan Sirhan";
    c[2].isWinner = true;
    std::ostringstream w;
    voting_print(w, c, 3);
    ASSERT_TRUE(w.str() == "John Doe\nJane Smith\nSirhan Sirhan\n");}
    
// ------------
// voting_solve
// ------------

TEST(Voting, voting_solve) {
    std::istringstream r("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nThom York\nFlea\nJoe Satch\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n2 3 1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n\nThom York\nFlea\n");
   } 
   
TEST(Voting, voting_solve_2) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
   }
   
TEST(Voting, voting_solve_3) {
    std::istringstream r("1\n\n1\nJohn Doe\n1\n1\n1\n1\n1");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_TRUE(w.str() == "John Doe\n");
   } 


