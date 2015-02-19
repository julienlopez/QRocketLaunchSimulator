#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cassert>
#include <numeric>
#include <cmath>

namespace utils
{

	template <class T, std::size_t DIM> class point
	{
	public:
		using value_type = T;
		using value_squared_type = decltype(T() * T());

		point()
		{
			std::fill(m_values.begin(), m_values.end(), T{});
		}

		point(typename std::initializer_list<T> values)
		{
			if(values.size() == 1)
			{
				std::fill(m_values.begin(), m_values.end(), *values.begin());
			}
			else
			{
				assert(values.size() == DIM
					   && "wrong number of arguments passed to construct point");
				std::size_t pos = 0;
				for(auto it = values.begin(); it != values.end(); ++it, pos++)
				{
					m_values[pos] = *it;
				}
			}
		}

		point(const point&) = default;
		point(point&&) = default;

		point& operator=(const point&) = default;
		point& operator=(point&&) = default;

		const T& x() const
		{
			static_assert(DIM > 0, "");
			return m_values[0];
		}

		const T& y() const
		{
			static_assert(DIM > 1, "");
			return m_values[1];
		}

		const T& z() const
		{
			static_assert(DIM > 2, "");
			return m_values[2];
		}

		const T& operator[](std::size_t i) const
		{
			assert(i < DIM);
			return m_values[i];
		}

		T& operator[](std::size_t i)
		{
			assert(i < DIM);
			return m_values[i];
		}

		value_squared_type norm2() const
		{
			return std::inner_product(m_values.cbegin(), m_values.cend(), m_values.cbegin(),
									  value_squared_type{});
		}

		T norm() const
		{
			return sqrt(norm2());
		}

		point& operator+=(const point& p)
		{
			for(std::size_t i = 0; i < m_values.size(); ++i)
				m_values[i] += p.m_values[i];
			return *this;
		}

		point& operator-=(const point& p)
		{
			for(std::size_t i = 0; i < m_values.size(); ++i)
				m_values[i] -= p.m_values[i];
			return *this;
		}

		/**
		 * \brief multiplication by a scalar
		 */
		template <class U> point<decltype(T() * U()), DIM> operator*(U u) const
		{
			point<decltype(T() * U()), DIM> res;
			for(std::size_t i = 0; i < DIM; ++i)
				res[i] = m_values[i] * u;
			return res;
		}

		/**
		 * \brief division by a scalar
		 */
		template <class U> point<decltype(T() / U()), DIM> operator/(U u) const
		{
			point<decltype(T() / U()), DIM> res;
			for(std::size_t i = 0; i < DIM; ++i)
				res[i] = m_values[i] / u;
			return res;
		}

	private:
		using container_t = std::array<T, DIM>;

		container_t m_values;
	};

	template <class T, std::size_t DIM>
	point<T, DIM> operator+(point<T, DIM> p1, const point<T, DIM>& p2)
	{
		p1 += p2;
		return p1;
	}

	template <class T, std::size_t DIM>
	point<T, DIM> operator-(point<T, DIM> p1, const point<T, DIM>& p2)
	{
		p1 -= p2;
		return p1;
	}

	template <class T, class U, std::size_t DIM>
	point<decltype(T() * U()), DIM> operator*(U scalar, const point<T, DIM>& p)
	{
		return p * scalar;
	}

	template <class T> using point3d = point<T, 3>;
}

#endif // POINT_HPP
