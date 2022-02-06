//
// Created by Oran on 06.02.22.
//
#pragma once
#include <vector>
#include <numeric>
#include <functional>

class ndarray
{
public:
    ndarray(const std::vector<int>& shape)
            : m_nelem(std::accumulate(shape.begin(), shape.end(),
                                      1, std::multiplies<int>()))
            , m_ndim(shape.size())
            , m_shape(shape)
    {
        compute_strides();
        m_data.resize(m_nelem, 0.0);
    }
    ndarray()
    {
    }
    ~ndarray()
    {
    }

    const unsigned char& operator[](int i) const
    {
        return m_data.at(i);
    }

    unsigned char& operator[](int i)
    {
        return m_data.at(i);
    }

    const unsigned char& operator[](const std::vector<int>& indices) const
    {
        auto flat_index = std::inner_product(
                indices.begin(), indices.end(),
                m_strides.begin(), 0);
        return m_data.at(flat_index);
    }

    unsigned char& operator[](const std::vector<int>& indices)
    {
        auto flat_index = std::inner_product(
                indices.begin(), indices.end(),
                m_strides.begin(), 0);
        return m_data.at(flat_index);
    }

    void reshape(const std::vector<int>& new_shape)
    {
        auto new_nelem = std::accumulate(
                new_shape.begin(), new_shape.end(),
                1, std::multiplies<int>());
        if (new_nelem != m_nelem) {
            throw std::invalid_argument("dynamic_array::reshape(): "
                                        "number of elements must not change.");
        }
        m_nelem = new_nelem;
        m_ndim = new_shape.size();
        m_shape = new_shape;
        compute_strides();
    }

    const std::vector<int>& shape() const
    {
        return m_shape;
    }

    const std::vector<int>& strides() const
    {
        return m_strides;
    }

    int ndim() const
    {
        return m_ndim;
    }

    int nelem() const
    {
        return m_nelem;
    }

private:
    int m_ndim;
    int m_nelem;
    std::vector<int> m_shape;
    std::vector<int> m_strides;
    std::vector<unsigned char> m_data;

    void compute_strides()
    {
        m_strides.resize(m_ndim);
        m_strides.at(m_ndim - 1) = 1;
        std::partial_sum(m_shape.rbegin(),
                         m_shape.rend() - 1,
                         m_strides.rbegin() + 1,
                         std::multiplies<int>());
    }
};
