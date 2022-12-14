/* phyLS: powerful heightened yielded Logic Synthesis
 * Copyright (C) 2022 */

/**
 * @file aig_balancing.hpp
 *
 * @brief transforms the current network into a well-balanced AIG
 *
 * @author Homyoung
 * @since  2022/12/14
 */

#ifndef BALANCE_HPP
#define BALANCE_HPP

#include <algorithm>
#include <mockturtle/algorithms/aig_balancing.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/views/depth_view.hpp>
#include <vector>

#include "../core/misc.hpp"

using namespace std;

namespace alice {

class balance_command : public command {
 public:
  explicit balance_command(const environment::ptr& env)
      : command(env,
                "transforms the current network into a well-balanced AIG") {
    add_flag("--strash, -s", "Balance AND finding structural hashing");
    add_flag("--verbose, -v", "print the information");
  }

 protected:
  void execute() {
    clock_t begin, end;
    double totalTime;

    if (store<aig_network>().size() == 0u)
      std::cerr << "Error: Empty AIG network\n";
    else {
      auto aig = store<aig_network>().current();
      if (is_set("strash")) {
        begin = clock();
        aig_balancing_params ps;
        ps.minimize_levels = false;
        aig_balance(aig, ps);
        end = clock();
        totalTime = (double)(end - begin) / CLOCKS_PER_SEC;
      } else {
        begin = clock();
        aig_balance(aig);
        end = clock();
        totalTime = (double)(end - begin) / CLOCKS_PER_SEC;
      }
      phyLS::print_stats(aig);

      store<aig_network>().extend();
      store<aig_network>().current() = aig;
    }

    cout.setf(ios::fixed);
    cout << "[CPU time]   " << setprecision(2) << totalTime << " s" << endl;
  }

 private:
};

ALICE_ADD_COMMAND(balance, "Logic synthesis")

}  // namespace alice

#endif