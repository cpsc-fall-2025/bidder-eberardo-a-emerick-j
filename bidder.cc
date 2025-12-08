#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>


// ============================================================================
// INSTRUCTIONS
// ============================================================================
// 1. Implement the three functions below.
// 2. You may use the main() function at the bottom to test your code locally.
// 3. Do not change the function signatures.
// ============================================================================

// TODO: Implement this function to return a vector of strings
// containing the names of everyone on your team.
std::vector<std::string> GetTeamMembers() {
  return {"Eberardo Aristeo", "Emerick Juarez"};
}

// TODO: Implement this function to return a string that describes
// the strategy your logic uses to bid (e.g., "We bid high early on").
std::string GetStrategy() {
  // Your code here
  return "";
}

// TODO: Implement the bidding logic.
// parameters:
//   rounds: The total number of rounds in the game.
//   budget: The total points available to spend across all rounds.
//   output_filename: The name of the file where the bids should be written.
//
// Logic:
//   1. Calculate how much to bid in each round.
//   2. Open 'output_filename' for writing.
//   3. Write the bid for each round on a new line in the file.
//
// Constraints:
//   - You must write exactly 'rounds' number of lines.
//   - The sum of all bids must not exceed 'budget'.
//   - Bids must be non-negative integers.

// int randomNum(int min, int max) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dist(min, max);
//     return dist(gen);
// }
int seed3{0};

bool cond() {

  seed3++;

    if (seed3 <= 2) {
      return true;
    } else {
      seed3 = 0;
      return false;
    }

  return false;
}
int seed3B{0}; //Refers to when seed is equal to 3 and how this is meant for Budget
int seed3CB{0}; //Refers to when seed is equal to 3 and saves the current Bidded per round

int perRound(int rounds, int budget, int bids, int curr) {
  int startPoint{5}; //Start at 10% the budget

  int res{0};
  if (curr >= 1) {
    seed3B++;
    startPoint = 0;

    if (seed3B <= 2) {
      seed3CB += budget/10; //Increase by 10%
    } else {
      seed3B = 0;
      seed3CB = 0;

      return budget/5; //Increase by 20%

    }
    //std::cout << seed3B << "  |  " << seed3CB << " - " << curr << " - " << rounds << std::endl;
 }

  //Result conditons
  if (seed3CB + bids > budget) {
    res = budget - bids + seed3CB;
  } else if (curr >= rounds) {
    res = budget;
  } else {
    res = seed3CB + startPoint;
   }

  //std::cout << "\n" << res << "\n" << bids << std::endl;
  return res; //Return the startPoint added with the current round
}

// int bids{0};
// int Updater{0};

// void UpdateFile(int Bid, std::string output_filename) {
//   output << Bid << "\n";
// }

// int BidPerRound(int budget, bool BigLeap) {
//   if (BigLeap) {
//     return budget/10;
//   } else { return budget/20; }
// }

// void ExecuteSeedPath(int curr, int rounds, int budget, std::string output_filename) {
//   int RoundBid{0};
//   Updater++;

//     if (Updater <= 2) {
//       RoundBid = BidPerRound(budget, false);
//     } else {
//       RoundBid = BidPerRound(budget, true);
//       Updater = 0;
//     }


//   if (bids >= budget) {
//     RoundBid = 0;
//     bids = budget;
//   } else if (curr >= rounds) {
//     RoundBid = budget - bids;
//   }

//   bids += RoundBid;

//   UpdateFile(RoundBid, output_filename);
// }

void GenerateBids(int rounds, int budget, std::string output_filename) {

  std::ofstream output(output_filename);

  // for (int i = 0; i <= rounds; i++){
  //   ExecuteSeedPath(i, rounds, budget, output_filename);
  // }

  int seed{3};
  int bids{0};
  int bid_round{perRound(rounds, budget, bids, -1)};



  for (int i = 1; i < rounds + 1; i++) {
    if (bids > budget) {
      output << "\n";
    } else if (cond()) {
      if (seed == 3){
        bids += bid_round;
        bid_round = perRound(rounds, budget, bids, i);
      } else{
        bids += bid_round;
      }

      output << bid_round << "\n";
    } else {
      output << 0 << "\n";
    }
  }


}

// ============================================================================
// MAIN FUNCTION
// Use this to test your code.
// This function will be ignored by the "make test" command.
// ============================================================================
int main() {
  // You can write code here to call your functions and see if they work.
  // Example:
  GenerateBids(10, 100, "test_output.txt");

  return 0;
}