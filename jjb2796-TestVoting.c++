#include <iostream>
#include <sstream>
#include <string>
#include "gtest/gtest.h"

#include "Voting.h"

// -----------
// TestVoting
// -----------

// -----------
// voting_read
// -----------


TEST(voting_read, eval_1) {
	int num_can = 0;
	std::string can_names[2] = {""};
	int ballots[1000][20] = {{0}};
	std::istringstream r("2\nBilly Bob\nTimmy Time\n1 2\n1 2\n\n");
	voting_read(r, num_can, can_names, ballots);
	ASSERT_TRUE(num_can == 2);
	ASSERT_TRUE(can_names[0] == "Billy Bob");
	ASSERT_TRUE(can_names[1] == "Timmy Time");
	ASSERT_TRUE(ballots[0][0] == 1);
	ASSERT_TRUE(ballots[0][1] == 2);
	ASSERT_TRUE(ballots[1][0] == 1);
	ASSERT_TRUE(ballots[1][1] == 2);
}

TEST(voting_read, eval_2) {
	int num_can = 0;
	std::string can_names[1] = {""};
	int ballots[1000][20] = {{0}};
	std::istringstream r("1\nTaylor B\n1\n\n");
	voting_read(r, num_can, can_names, ballots);
	ASSERT_TRUE(num_can == 1);
	ASSERT_TRUE(can_names[0] == "Taylor B");
	ASSERT_TRUE(ballots[0][0] == 1);
}

TEST(voting_read, eval_3) {
	int num_can = 0;
	std::string can_names[3] = {""};
	int ballots[1000][20] = {{0}};
	std::istringstream r("");
	voting_read(r, num_can, can_names, ballots);
	ASSERT_TRUE(num_can == 0);
	ASSERT_TRUE(can_names[0] == "");
	ASSERT_TRUE(ballots[0][0] == 0);
}

//add one more voting_read test case

// --------------
//  voting_print
// --------------

TEST(voting_print, print_test1) {
	std::ostringstream w;
	std::string can_names[20] = {""};
	can_names[0] = "Billy";
	can_names[1] = "Yllib";
	voting_print(w, 0, can_names);
	ASSERT_TRUE(w.str() == "Billy\n");

}

TEST(voting_print, print_test2) {
	std::ostringstream w;
	std::string can_names[20] = {""};
	can_names[0] = "Billy";
	can_names[1] = "Yllib";
	voting_print(w, 1, can_names);
	ASSERT_TRUE(w.str() == "Yllib\n");

}

TEST(voting_print, print_test_spaces) {
	std::ostringstream w;
	std::string can_names[20] = {""};
	can_names[0] = "Billy";
	can_names[1] = "Yllib";
	can_names[2] = "James Smith the 3rd";
	voting_print(w, 2, can_names);
	ASSERT_TRUE(w.str() == "James Smith the 3rd\n");

}


// ---------------
//  find_win_loss
// ---------------

TEST(find_win_loss, f_w_l_test_winner) {
	int low = 0;
	int high = 0;
	int votes[20] = {0};
	votes[1] = 100;
	int num_can = 20;
	int vote_count = 100;
	find_win_loss(low, high, votes, num_can, vote_count);
	ASSERT_TRUE(high == low);
	ASSERT_TRUE(high == 2);
}

TEST(find_win_loss, f_w_l_test_tie) {
	int low = 0;
	int high = 0;
	int votes[20] = {0};
	votes[0] = 100;
	votes[1] = 100;
	int num_can = 2;
	int vote_count = 200;
	find_win_loss(low, high, votes, num_can, vote_count);
	ASSERT_TRUE(high == low);
	ASSERT_TRUE(high == 3);
}

TEST(find_win_loss, f_w_l_test_loser) {
	int low = 0;
	int high = 0;
	int votes[20] = {0};
	votes[0] = 10;
	votes[1] = 100;
	votes[2] = 90;
	int num_can = 3;
	int vote_count = 200;
	find_win_loss(low, high, votes, num_can, vote_count);
	ASSERT_TRUE(high != low);
	ASSERT_TRUE(high == 2);
	ASSERT_TRUE(low == 1);
}

// ---------------
//  ballot_shift
// ---------------


TEST(ballot_shift, ballot_shift_test1) {
	int ballots[20][1000][20] = {{{0}}};
	int index1 = 0;
	int index2 = 0;
	int num_can = 2;
	ballots[index1][index2][0] = 1;
	ballots[index1][index2][1] = 2;
	ballot_shift(ballots, index1, index2, num_can);
	ASSERT_TRUE(ballots[index1][index2][0] == 2);
	ASSERT_TRUE(ballots[index1][index2][1] == -1);
}

TEST(ballot_shift, ballot_shift_test2) {
	int ballots[20][1000][20] = {{{0}}};
	int index1 = 10;
	int index2 = 700;
	int num_can = 5;
	ballots[index1][index2][0] = 1;
	ballots[index1][index2][1] = 2;
	ballots[index1][index2][2] = 3;
	ballots[index1][index2][3] = 4;
	ballots[index1][index2][4] = 5;
	ballot_shift(ballots, index1, index2, num_can);
	ASSERT_TRUE(ballots[index1][index2][0] == 2);
	ASSERT_TRUE(ballots[index1][index2][1] == 3);
	ASSERT_TRUE(ballots[index1][index2][2] == 4);
	ASSERT_TRUE(ballots[index1][index2][3] == 5);
	ASSERT_TRUE(ballots[index1][index2][4] == -1);
}

TEST(ballot_shift, ballot_shift_test3) {
	int ballots[20][1000][20] = {{{0}}};
	int index1 = 19;
	int index2 = 999;
	int num_can = 20;
	ballots[index1][index2][0] = 1;
	ballots[index1][index2][1] = 2;
	ballots[index1][index2][2] = 3;
	ballots[index1][index2][3] = 4;
	ballots[index1][index2][4] = 5;
	ballots[index1][index2][5] = 6;
	ballots[index1][index2][6] = 7;
	ballots[index1][index2][7] = 8;
	ballots[index1][index2][8] = 9;
	ballots[index1][index2][9] = 10;
	ballots[index1][index2][10] = 11;
	ballots[index1][index2][11] = 12;
	ballots[index1][index2][12] = 13;
	ballots[index1][index2][13] = 14;
	ballots[index1][index2][14] = 15;
	ballots[index1][index2][15] = 16;
	ballots[index1][index2][16] = 17;
	ballots[index1][index2][17] = 18;
	ballots[index1][index2][18] = 19;
	ballots[index1][index2][19] = 20;
	ballot_shift(ballots, index1, index2, num_can);
	ASSERT_TRUE(ballots[index1][index2][0] == 2);
	ASSERT_TRUE(ballots[index1][index2][1] == 3);
	ASSERT_TRUE(ballots[index1][index2][2] == 4);
	ASSERT_TRUE(ballots[index1][index2][3] == 5);
	ASSERT_TRUE(ballots[index1][index2][4] == 6);
	ASSERT_TRUE(ballots[index1][index2][5] == 7);
	ASSERT_TRUE(ballots[index1][index2][6] == 8);
	ASSERT_TRUE(ballots[index1][index2][7] == 9);
	ASSERT_TRUE(ballots[index1][index2][8] == 10);
	ASSERT_TRUE(ballots[index1][index2][9] == 11);
	ASSERT_TRUE(ballots[index1][index2][10] == 12);
	ASSERT_TRUE(ballots[index1][index2][11] == 13);
	ASSERT_TRUE(ballots[index1][index2][12] == 14);
	ASSERT_TRUE(ballots[index1][index2][13] == 15);
	ASSERT_TRUE(ballots[index1][index2][14] == 16);
	ASSERT_TRUE(ballots[index1][index2][15] == 17);
	ASSERT_TRUE(ballots[index1][index2][16] == 18);
	ASSERT_TRUE(ballots[index1][index2][17] == 19);
	ASSERT_TRUE(ballots[index1][index2][18] == 20);
	ASSERT_TRUE(ballots[index1][index2][19] == -1);
}

// ---------------
//  ballot_move
// ---------------

TEST(ballot_move, ballot_move_test1) {
	int ballots[20][1000][20] = {{{0}}};
	int first_can = 0;
	int second_can = 1;
	int ballot_index = 0;
	ballots[first_can][ballot_index][0] = 1;
	ballots[first_can][ballot_index][1] = 2;
	ballots[first_can][ballot_index][2] = 3;
	ballots[first_can][ballot_index][3] = 4;
	ballots[first_can][ballot_index][4] = 5;
	ballots[second_can][0][0] = 2;
	ballots[second_can][0][1] = 1;
	ballots[second_can][0][2] = 3;
	ballots[second_can][0][3] = 4;
	ballots[second_can][0][4] = 5;
	ballot_move(ballots, first_can, second_can, ballot_index);
	ASSERT_TRUE(ballots[second_can][1][0] == 1);
	ASSERT_TRUE(ballots[second_can][1][1] == 2);	
	ASSERT_TRUE(ballots[second_can][1][2] == 3);	
	ASSERT_TRUE(ballots[second_can][1][3] == 4);
	ASSERT_TRUE(ballots[second_can][1][4] == 5);	
	ASSERT_TRUE(ballots[first_can][0][0] == 0);	
	ASSERT_TRUE(ballots[first_can][0][1] == 0);
	ASSERT_TRUE(ballots[first_can][0][2] == 0);
	ASSERT_TRUE(ballots[first_can][0][3] == 0);
	ASSERT_TRUE(ballots[first_can][0][4] == 0);	
}

TEST(ballot_move, ballot_move_test2) {
	int ballots[20][1000][20] = {{{0}}};
	int first_can = 1;
	int second_can = 19;
	int ballot_index = 30;
	ballots[first_can][ballot_index][0] = 1;
	ballots[first_can][ballot_index][1] = 2;
	ballots[first_can][ballot_index][2] = 3;
	ballots[first_can][ballot_index][3] = 4;
	ballots[first_can][ballot_index][4] = 5;
	ballots[second_can][0][0] = 2;
	ballots[second_can][0][1] = 1;
	ballots[second_can][0][2] = 3;
	ballots[second_can][0][3] = 4;
	ballots[second_can][0][4] = 5;
	ballot_move(ballots, first_can, second_can, ballot_index);
	ASSERT_TRUE(ballots[second_can][1][0] == 1);
	ASSERT_TRUE(ballots[second_can][1][1] == 2);	
	ASSERT_TRUE(ballots[second_can][1][2] == 3);	
	ASSERT_TRUE(ballots[second_can][1][3] == 4);
	ASSERT_TRUE(ballots[second_can][1][4] == 5);
	ASSERT_TRUE(ballots[first_can][ballot_index][0] == 0);	
	ASSERT_TRUE(ballots[first_can][ballot_index][1] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][2] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][3] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][4] == 0);			
}

TEST(ballot_move, ballot_move_test3) {
	int ballots[20][1000][20] = {{{0}}};
	int first_can = 0;
	int second_can = 15;
	int ballot_index = 30;
	ballots[first_can][ballot_index][0] = 1;
	ballots[first_can][ballot_index][1] = 2;
	ballots[first_can][ballot_index][2] = 3;
	ballots[first_can][ballot_index][3] = 4;
	ballots[first_can][ballot_index][4] = 5;
	ballots[second_can][0][0] = 2;
	ballots[second_can][0][1] = 1;
	ballots[second_can][0][2] = 3;
	ballots[second_can][0][3] = 4;
	ballots[second_can][0][4] = 5;
	ballot_move(ballots, first_can, second_can, ballot_index);
	ASSERT_TRUE(ballots[second_can][1][0] == 1);
	ASSERT_TRUE(ballots[second_can][1][1] == 2);	
	ASSERT_TRUE(ballots[second_can][1][2] == 3);	
	ASSERT_TRUE(ballots[second_can][1][3] == 4);
	ASSERT_TRUE(ballots[second_can][1][4] == 5);
	ASSERT_TRUE(ballots[first_can][ballot_index][0] == 0);	
	ASSERT_TRUE(ballots[first_can][ballot_index][1] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][2] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][3] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][4] == 0);	

	//Move a ballot to cand 16 and move it back to cand 1

	first_can = 15;
	second_can = 0;
	ballot_index = 1;
	ballot_move(ballots, first_can, second_can, ballot_index);
	ASSERT_TRUE(ballots[second_can][0][0] == 1);
	ASSERT_TRUE(ballots[second_can][0][1] == 2);	
	ASSERT_TRUE(ballots[second_can][0][2] == 3);	
	ASSERT_TRUE(ballots[second_can][0][3] == 4);
	ASSERT_TRUE(ballots[second_can][0][4] == 5);
	ASSERT_TRUE(ballots[first_can][ballot_index][0] == 0);	
	ASSERT_TRUE(ballots[first_can][ballot_index][1] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][2] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][3] == 0);
	ASSERT_TRUE(ballots[first_can][ballot_index][4] == 0);		
}

// ---------------
//  vote_reassign
// ---------------

TEST(vote_reassign, vote_reassign_test1) {
	int votes[20] = {0};
	int ballots[20][1000][20] = {{{0}}};
	int low = 1;
	int num_can = 3;
	votes[0] = 10;
	votes[1] = 11;
	votes[2] = 13;
	ballots[0][0][0] = 1;
	ballots[0][0][1] = 2;
	ballots[0][0][2] = 3;
	ballots[1][0][0] = 2;
	ballots[1][0][1] = 1;
	ballots[1][0][2] = 3;
	ballots[2][0][0] = 3;
	ballots[2][0][1] = 1;
	ballots[2][0][2] = 2;
	vote_reassign(votes, ballots, low, num_can);
	ASSERT_TRUE(votes[0] == -1);
	ASSERT_TRUE(votes[1] == 12);
	ASSERT_TRUE(votes[2] == 13);
}

TEST(vote_reassign, vote_reassign_test2) {
	int votes[20] = {0};
	int ballots[20][1000][20] = {{{0}}};
	int low = 3;
	int num_can = 3;
	votes[0] = 10;
	votes[1] = 10;
	votes[2] = 13;
	ballots[0][0][0] = 1;
	ballots[0][0][1] = 2;
	ballots[0][0][2] = 3;
	ballots[1][0][0] = 2;
	ballots[1][0][1] = 1;
	ballots[1][0][2] = 3;
	ballots[2][0][0] = 3;
	ballots[2][0][1] = 1;
	ballots[2][0][2] = 2;
	vote_reassign(votes, ballots, low, num_can);
	ASSERT_TRUE(votes[0] == -1);
	ASSERT_TRUE(votes[1] == -1);
	ASSERT_TRUE(votes[2] == 15);
}

TEST(vote_reassign, vote_reassign_test3) {
	int votes[20] = {0};
	int ballots[20][1000][20] = {{{0}}};
	int low = 9;
	int num_can = 4;
	votes[0] = 10;
	votes[1] = 15;
	votes[2] = 15;
	votes[3] = 10;

	ballots[0][0][0] = 1;
	ballots[0][0][1] = 2;
	ballots[0][0][2] = 3;
	ballots[0][0][3] = 4;

	ballots[1][0][0] = 2;
	ballots[1][0][1] = 4;
	ballots[1][0][2] = 1;
	ballots[1][0][3] = 3;

	ballots[2][0][0] = 3;
	ballots[2][0][1] = 1;
	ballots[2][0][2] = 2;
	ballots[2][0][3] = 2;

	ballots[3][0][0] = 4;
	ballots[3][0][1] = 3;
	ballots[3][0][2] = 2;
	ballots[3][0][3] = 3;

	vote_reassign(votes, ballots, low, num_can);
	ASSERT_TRUE(votes[0] == -1);
	ASSERT_TRUE(votes[1] == 16);
	ASSERT_TRUE(votes[2] == 16);
	ASSERT_TRUE(votes[3] == -1);
}

// ---------------
//  voting_eval
// ---------------

TEST(voting_eval, vote_eval_test1) {
	std::ostringstream w;
	int num_can = 2;
	std::string can_names[20] = {""};
	int ballots[1000][20] = {{0}};
	can_names[0] = "Dr. Poop";
	can_names[1] = "Mr. Fart";
	ballots[0][0] = 1;
	ballots[0][1] = 2;
	ballots[1][0] = 1;
	ballots[1][1] = 2;
	ballots[2][0] = 2;
	ballots[2][1] = 1;
	voting_eval(w, num_can, can_names, ballots);
	ASSERT_TRUE(w.str() == "Dr. Poop\n");
}

TEST(voting_eval, vote_eval_test2) {
	std::ostringstream w;
	int num_can = 7;
	std::string can_names[20] = {""};
	int ballots[1000][20] = {{0}};
	can_names[0] = "I'm";
	can_names[1] = "12";
	can_names[2] = "and";
	can_names[3] = "what";
	can_names[4] = "is";
	can_names[5] = "this";
	can_names[6] = "?";
	
	voting_eval(w, num_can, can_names, ballots);
	ASSERT_TRUE(w.str() == "I'm\n12\nand\nwhat\nis\nthis\n?\n");
}


TEST(voting_eval, vote_eval_test3) {
	std::ostringstream w;
	int num_can = 3;
	std::string can_names[20] = {""};
	int ballots[1000][20] = {{0}};
	can_names[0] = "Winner1";
	can_names[1] = "Winner2";
	can_names[2] = "Loser :(";

	ballots[0][0] = 1;
	ballots[0][1] = 2;
	ballots[0][2] = 3;
	
	ballots[1][0] = 1;
	ballots[1][1] = 2;
	ballots[1][2] = 3;
	
	ballots[2][0] = 2; 
	ballots[2][1] = 1;
	ballots[2][2] = 3;
	
	ballots[3][0] = 2; 
	ballots[3][1] = 1;
	ballots[3][2] = 3;
	
	ballots[4][0] = 3;
	ballots[4][1] = 1;
	ballots[4][2] = 2;

	ballots[5][0] = 1;  
	ballots[5][1] = 2;
	ballots[5][2] = 3;

	ballots[6][0] = 2; 
	ballots[6][1] = 1;
	ballots[6][2] = 3;

	ballots[7][0] = 3; 
	ballots[7][1] = 2;
	ballots[7][2] = 1;

	voting_eval(w, num_can, can_names, ballots);
	ASSERT_TRUE(w.str() == "Winner1\nWinner2\n");
}