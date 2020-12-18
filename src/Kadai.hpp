#ifndef KADAI_HPP
#define KADAI_HPP

#include <memory>
#include <vector>

#include "Strategy.hpp"
#include "Metrics.hpp"

void run_kadai
(
 Strategy &sim,
 const std::vector<std::shared_ptr<Metric>> &additional_metrics
 );

#endif
