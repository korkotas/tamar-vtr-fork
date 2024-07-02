#pragma once

#include <string>
#include <limits>
#include "vtr_ndmatrix.h"
#include "router_lookahead.h"
#include "router_lookahead_dynamic_utils.h"

class DynamicLookahead : public RouterLookahead {
    public:
        explicit DynamicLookahead() const;
    private:
        int Kmax;
        float alpha_decay;
    protected:
        float get_expected_cost() const override;
        void compute() override;
        void read() override;
        void write() override;
}