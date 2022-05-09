/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:40:28 by swquinc           #+#    #+#             */
/*   Updated: 2021/07/27 18:40:30 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP
# include "type_traits.hpp"

namespace ft {

	template<typename T1, typename T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair(): first(), second() {};

		template<typename U, typename V>
		pair(const pair<U, V> &pr)
		:first(pr.first), second(pr.second) {

		};

		pair(const first_type &a, const second_type &b)
		:first(a), second(b){
		};

		pair& operator=(const pair &pr) {
			first = pr.first;
			second = pr.second;
			return (*this);
		};

	};


	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 a, T2 b) {
		pair<T1, T2> tmp(a, b);
		return (tmp);
	}

	template<typename U, typename V>
	bool operator==(const pair<U, V> &lhs, const pair<U, V> &rhs) {
		return (lhs.first == rhs.first && rhs.second == rhs.second);
	}

	template<typename first_type, typename second_type>
	bool operator!=(const pair<first_type, second_type> &lhs, const pair<first_type, second_type> &rhs) {
		return (!operator==(lhs, rhs));
	}

	template<typename first_type, typename second_type>
	bool operator<(const pair<first_type, second_type> &lhs, const pair<first_type, second_type> &rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template<typename first_type, typename second_type>
	bool operator>(const pair<first_type, second_type> &lhs, const pair<first_type, second_type> &rhs) {
		return (rhs < lhs);
	}
	template<typename first_type, typename second_type>
	bool operator<=(const pair<first_type, second_type> &lhs, const pair<first_type, second_type> &rhs) {
		return (!(lhs > rhs));
	}

	template<typename first_type, typename second_type>
	bool operator>=(const pair<first_type, second_type> &lhs, const pair<first_type, second_type> &rhs) {
		return (!(lhs < rhs));
	}
}

#endif
