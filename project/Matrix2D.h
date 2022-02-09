//
// Created by Oran on 06.02.22.
//
#pragma once
#include <vector>
#include <numeric>
#include <functional>
#include <valarray>
#include <array>
#include <iostream>

typedef std::array<int, 4> Slice;

class Matrix2D
{
public:
    Matrix2D(const std::vector<int>& shape)
            : m_nelem(std::accumulate(shape.begin(), shape.end(),
                                      1, std::multiplies<int>()))
            , m_ndim(shape.size())
            , m_shape(shape)
    {
        compute_strides();
        m_data.resize(m_nelem, 0.0);
    }
    Matrix2D()
    {
    }
    ~Matrix2D()
    {
    }

    const double& operator[](int i) const
    {
        return m_data.at(i);
    }

    double& operator[](int i)
    {
        return m_data.at(i);
    }

    const double& operator[](const std::vector<int>& indices) const
    {
        auto flat_index = std::inner_product(
                indices.begin(), indices.end(),
                m_strides.begin(), 0);
        return m_data.at(flat_index);
    }

    double& operator[](const std::vector<int>& indices)
    {
        auto flat_index = std::inner_product(
                indices.begin(), indices.end(),
                m_strides.begin(), 0);
        return m_data.at(flat_index);
    }

    /*
     * Returns a flat std::vector of the slice in row major
     * Does not check for violations of memory access
     * Returns value so the local slice isn't lost
     */
    const std::vector<double> operator[](Slice& indices) const
    {
        int startRow = indices[0];
        int endRow = indices[1];
        int startCol = indices[2];
        int endCol = indices[3];
        std::vector<double> slice;
        for (int i=startRow;i<endRow;++i)
        {
            for (int j=startCol;i<endCol;i++)
            {
                std::cout << m_data.at(j+m_strides.at(0)*i) <<std::endl;
                slice.push_back(m_data.at(i+m_strides.at(0)*j));
            }
        }
        return slice;
    }

    std::vector<double> operator[](Slice& indices)
    {
        int startRow = indices[0];
        int endRow = indices[1];
        int startCol = indices[2];
        int endCol = indices[3];
        std::vector<double> slice;

        for (int i=startRow;i<endRow;++i)
        {
            for (int j=startCol;i<endCol;i++)
            {
                std::cout << m_data.at(j+m_strides.at(0)*i) <<std::endl;
                slice.push_back(m_data.at(i+m_strides.at(0)*j));
            }
        }
        return slice;
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
    struct Iterator
    {
       using iterator_category = std::forward_iterator_tag;
       using difference_type = std::ptrdiff_t;
       using value_type = double;
       using pointer = double*;
       using reference = double&;
       Iterator(pointer ptr) : m_ptr(ptr) {}

       reference operator*() const {return *m_ptr;}
       pointer operator->() {return m_ptr;}
       Iterator& operator++() {m_ptr++; return *this;}
       Iterator operator++(int) {Iterator tmp = *this; ++(*this); return tmp;}

       friend bool operator== (const Iterator& a, const Iterator& b) {return a.m_ptr == b.m_ptr;}
       friend bool operator!= (const Iterator& a, const Iterator& b) {return a.m_ptr != b.m_ptr;}
    private:
        pointer m_ptr;
    };
    Iterator begin() {return Iterator(&m_data[0]);}
    Iterator end() {return Iterator(&m_data[m_nelem]);}
private:
    int m_ndim;
    int m_nelem;
    std::vector<int> m_shape;
    std::vector<int> m_strides;
    std::vector<double> m_data;

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
