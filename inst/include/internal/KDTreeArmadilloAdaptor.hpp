#pragma once

//[[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include "nanoflann.hpp"
using namespace arma;
using namespace nanoflann;

namespace Rnanoflann
{
    // Define an Armadillo KDTreeAdaptor class
    template <class MatrixType, class Distance, int DIM = -1>
    struct KDTreeArmadilloAdaptor
    {
        using self_t = KDTreeArmadilloAdaptor<MatrixType, Distance, DIM>;
        using num_t = typename MatrixType::elem_type;
        using IndexType = uword;

        using metric_t = typename Distance::template traits<num_t, self_t>::distance_t; // You can change the distance metric as needed.

        using index_t = nanoflann::KDTreeSingleIndexAdaptor<metric_t, self_t, DIM, IndexType>;

        index_t *index_;

        const std::reference_wrapper<const MatrixType> m_data_matrix;

        explicit KDTreeArmadilloAdaptor(const uword dimensionality, const std::reference_wrapper<const MatrixType> &mat, const uword leafs = 10)
            : m_data_matrix(mat)
        {
            const auto dims = mat.get().n_rows; // Assumes column-major Armadillo matrix
            if (static_cast<uword>(dims) != dimensionality)
                throw std::runtime_error("Error: 'dimensionality' must match the column count in the data matrix");
            if (DIM > 0 && static_cast<int>(dims) != DIM)
                throw std::runtime_error("Data set dimensionality does not match the 'DIM' template argument");
            index_ = new index_t(dims, *this /* adaptor */, nanoflann::KDTreeSingleIndexAdaptorParams(leafs));
            index_->buildIndex();
        }

        ~KDTreeArmadilloAdaptor() { delete index_; }

        const self_t &derived() const { return *this; }
        self_t &derived() { return *this; }

        uword kdtree_get_point_count() const
        {
            return m_data_matrix.get().n_cols;
        }

        num_t kdtree_get_pt(uword idx, size_t dim) const
        {
            return m_data_matrix.get()(dim, idx);
        }

        colvec col(uword idx) const
        {
            return m_data_matrix.get().col(idx);
        }

        template <class BBOX>
        bool kdtree_get_bbox(BBOX &bb) const
        {
            return false; // Optional bounding-box computation (not used in this example)
        }
    };

    // Define an Armadillo KDTreeAdaptor class
    template <class MatrixType, class Distance, bool Square, int DIM = -1>
    struct KDTreeArmadilloAdaptor2
    {
        using self_t = KDTreeArmadilloAdaptor2<MatrixType, Distance, Square, DIM>;
        using num_t = typename MatrixType::elem_type;
        using IndexType = uword;

        using metric_t = typename Distance::template traits<num_t, self_t, Square>::distance_t; // You can change the distance metric as needed.

        using index_t = nanoflann::KDTreeSingleIndexAdaptor<metric_t, self_t, DIM, IndexType>;

        index_t *index_;

        const std::reference_wrapper<const MatrixType> m_data_matrix;

        explicit KDTreeArmadilloAdaptor2(const uword dimensionality, const std::reference_wrapper<const MatrixType> &mat, const uword leafs = 10)
            : m_data_matrix(mat)
        {
            const auto dims = mat.get().n_rows; // Assumes column-major Armadillo matrix
            if (static_cast<uword>(dims) != dimensionality)
                throw std::runtime_error("Error: 'dimensionality' must match the column count in the data matrix");
            if (DIM > 0 && static_cast<int>(dims) != DIM)
                throw std::runtime_error("Data set dimensionality does not match the 'DIM' template argument");
            index_ = new index_t(dims, *this /* adaptor */, nanoflann::KDTreeSingleIndexAdaptorParams(leafs));
            index_->buildIndex();
        }

        ~KDTreeArmadilloAdaptor2() { delete index_; }

        const self_t &derived() const { return *this; }
        self_t &derived() { return *this; }

        uword kdtree_get_point_count() const
        {
            return m_data_matrix.get().n_cols;
        }

        colvec col(uword idx) const
        {
            return m_data_matrix.get().col(idx);
        }

        num_t kdtree_get_pt(uword idx, size_t dim) const
        {
            return m_data_matrix.get()(dim, idx);
        }

        template <class BBOX>
        bool kdtree_get_bbox(BBOX &bb) const
        {
            return false; // Optional bounding-box computation (not used in this example)
        }
    };

    template <class MatrixType, class Distance, int DIM = -1>
    struct KDTreeArmadilloAdaptor3
    {
        using self_t = KDTreeArmadilloAdaptor3<MatrixType, Distance, DIM>;
        using num_t = typename MatrixType::elem_type;
        using IndexType = uword;

        using metric_t = typename Distance::template traits<num_t, self_t>::distance_t; // You can change the distance metric as needed.

        using index_t = nanoflann::KDTreeSingleIndexAdaptor<metric_t, self_t, DIM, IndexType>;

        index_t *index_;

        const double p;
        const double p_1;

        const std::reference_wrapper<const MatrixType> m_data_matrix;

        explicit KDTreeArmadilloAdaptor3(const uword dimensionality, const std::reference_wrapper<const MatrixType> &mat, const double p, const uword leafs = 10)
            : p(p), p_1(1.0 / p), m_data_matrix(mat)
        {
            const auto dims = mat.get().n_rows; // Assumes column-major Armadillo matrix
            if (static_cast<uword>(dims) != dimensionality)
                throw std::runtime_error("Error: 'dimensionality' must match the column count in the data matrix");
            if (DIM > 0 && static_cast<int>(dims) != DIM)
                throw std::runtime_error("Data set dimensionality does not match the 'DIM' template argument");
            index_ = new index_t(dims, *this /* adaptor */, nanoflann::KDTreeSingleIndexAdaptorParams(leafs));
            index_->buildIndex();
        }

        ~KDTreeArmadilloAdaptor3() { delete index_; }

        const self_t &derived() const { return *this; }
        self_t &derived() { return *this; }

        uword kdtree_get_point_count() const
        {
            return m_data_matrix.get().n_cols;
        }

        num_t kdtree_get_pt(uword idx, size_t dim) const
        {
            return m_data_matrix.get()(dim, idx);
        }

        colvec col(uword idx) const
        {
            return m_data_matrix.get().col(idx);
        }

        const double getP() const
        {
            return p;
        }

        const double getP_1() const
        {
            return p_1;
        }

        template <class BBOX>
        bool kdtree_get_bbox(BBOX &bb) const
        {
            return false; // Optional bounding-box computation (not used in this example)
        }
    };

    // Define an Armadillo KDTreeAdaptor class
    template <class MatrixType, class Distance, int DIM = -1>
    struct KDTreeArmadilloAdaptor4
    {
        using self_t = KDTreeArmadilloAdaptor4<MatrixType, Distance, DIM>;
        using num_t = typename MatrixType::elem_type;
        using IndexType = uword;

        using metric_t = typename Distance::template traits<num_t, self_t>::distance_t; // You can change the distance metric as needed.

        using index_t = nanoflann::KDTreeSingleIndexAdaptor<metric_t, self_t, DIM, IndexType>;

        index_t *index_;

        const std::reference_wrapper<const MatrixType> m_data_matrix;
        const MatrixType xlogx, ylogy;
        const num_t *begin_points;

        explicit KDTreeArmadilloAdaptor4(const uword dimensionality, const std::reference_wrapper<const MatrixType> &mat, const MatrixType &points, const uword leafs = 10)
            : m_data_matrix(mat), xlogx(mat.get() % arma::log(mat.get())), ylogy(points % arma::log(points)), begin_points(points.memptr())
        {
            const auto dims = mat.get().n_rows; // Assumes column-major Armadillo matrix
            if (static_cast<uword>(dims) != dimensionality)
                throw std::runtime_error("Error: 'dimensionality' must match the column count in the data matrix");
            if (DIM > 0 && static_cast<int>(dims) != DIM)
                throw std::runtime_error("Data set dimensionality does not match the 'DIM' template argument");
            index_ = new index_t(dims, *this /* adaptor */, nanoflann::KDTreeSingleIndexAdaptorParams(leafs));
            index_->buildIndex();
        }

        ~KDTreeArmadilloAdaptor4() { delete index_; }

        const self_t &derived() const { return *this; }
        self_t &derived() { return *this; }

        uword kdtree_get_point_count() const
        {
            return m_data_matrix.get().n_cols;
        }

        num_t kdtree_get_pt(uword idx, size_t dim) const
        {
            return m_data_matrix.get()(dim, idx);
        }

        colvec col(uword idx) const
        {
            return m_data_matrix.get().col(idx);
        }

        colvec col_xlogx(uword idx) const
        {
            return xlogx.col(idx);
        }

        colvec col_ylogy(const num_t *a) const
        {
            auto index = std::floor((a - begin_points) / ylogy.n_rows);
            return ylogy.col(index);
        }

        double log0_5() const
        {
            return std::log(0.5);
        }

        template <class BBOX>
        bool kdtree_get_bbox(BBOX &bb) const
        {
            return false; // Optional bounding-box computation (not used in this example)
        }
    };
};
