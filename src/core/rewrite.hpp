#pragma once

#include <mockturtle/algorithms/cut_rewriting.hpp>
#include <mockturtle/algorithms/node_resynthesis/akers.hpp>
#include <mockturtle/algorithms/node_resynthesis/exact.hpp>
#include <mockturtle/networks/aig.hpp>
#include <mockturtle/properties/mccost.hpp>
#include <mockturtle/traits.hpp>
#include <mockturtle/utils/cost_functions.hpp>
#include <mockturtle/views/fanout_view.hpp>
#include <mockturtle/algorithms/node_resynthesis/xag_npn.hpp>


using namespace percy;
using namespace mockturtle;

namespace phyLS
{
template <class Ntk>
void aig_rewrite(Ntk& ntk) {
  // please learn the algorithm of "mockturtle/algorithms/cut_rewriting.hpp"

  /* Code Block 1
   * If you want to use rewriting with compatibility graph
   * Please uncomment Code Block 1 and comment Code Block 2
  */
  // cut_rewriting_params ps;
  // ps.cut_enumeration_ps.cut_size = 4;
  // ps.progress = true;
  // xag_npn_resynthesis<aig_network> resyn;
  // cut_rewriting_with_compatibility_graph(ntk, resyn, ps);


  /* Code Block 2
   * If you want to use general rewriting algorithm
   * Please uncomment Code Block 2 and comment Code Block 1
  */
  cut_rewriting_params ps;
  ps.cut_enumeration_ps.cut_size = 4;
  ps.progress = true;
  xag_npn_resynthesis<aig_network> resyn;
  cut_rewriting(ntk, resyn, ps);
  
}
}