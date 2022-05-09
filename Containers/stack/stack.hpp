/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:47:45 by swquinc           #+#    #+#             */
/*   Updated: 2021/08/14 19:47:47 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "../../Other/type_traits.hpp"
# include "../../Other/iterator.hpp"
# include "../../Other/algorithm.hpp"
# include "../../Other/utility.hpp"
# include <deque>

namespace ft {
	template<typename T, typename Container = std::deque<T> >
	class stack {
	protected:
		Container c;	
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;
		//// constructor
		explicit stack(const container_type& cntr = container_type())
		: c(cntr){
		}
		/// methods
		bool empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}

		value_type& top() {
			return(c.back());
		}

		const value_type& top() const {
			return(c.back());
		}

		void push(const value_type& val) {
			c.push_back(val);
		}

		void pop() {
			c.pop_back();
		}

	private:
		friend bool operator==(const stack& lhs, const stack& rhs) {
			return (lhs.c == rhs.c);
		}

		friend bool operator!=(const stack& lhs, const stack& rhs) {
			return (lhs.c != rhs.c);
		}

		friend bool operator<(const stack& lhs, const stack& rhs) {
			return (lhs.c < rhs.c);
		}

		friend bool operator<=(const stack& lhs, const stack& rhs) {
			return (lhs.c <= rhs.c);
		}

		friend bool operator>(const stack& lhs, const stack& rhs) {
			return (lhs.c > rhs.c);
		}
		friend bool operator>=(const stack& lhs, const stack& rhs) {
			return (lhs.c >= rhs.c);
		}
	};
}
#endif
