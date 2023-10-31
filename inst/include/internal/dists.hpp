#pragma once

#include "nanoflann.hpp"
using namespace nanoflann;


namespace Rnanoflann {
    template <
        class T, class DataSource, bool Square = false, typename _DistanceType = T,
        typename IndexType = uint32_t>
    struct euclidean_adaptor
    {
        using ElementType  = T;
        using DistanceType = _DistanceType;

        const DataSource& data_source;

        euclidean_adaptor(const DataSource& _data_source)
            : data_source(_data_source)
        {
        }

        DistanceType evalMetric(
            const T* a, const IndexType b_idx, size_t size) const
        {
            DistanceType result = DistanceType();
            for (size_t i = 0; i < size; ++i)
            {
                const DistanceType diff =
                    a[i] - data_source.kdtree_get_pt(b_idx, i);
                result += diff * diff;
            }
            return result;
        }

        template <typename U, typename V>
        DistanceType accum_dist(const U a, const V b, const size_t) const
        {
            return Square ? (a - b) : std::sqrt(a - b);
        }
    };



    /** Metaprogramming helper traits class for the L2 (Euclidean) **squared**
     * distance metric */
    struct euclidean : public Metric
    {
        template <class T, class DataSource, bool Square, typename IndexType = uint32_t>
        struct traits
        {
            using distance_t = euclidean_adaptor<T, DataSource, Square, T, IndexType>;
        };
    };
};
