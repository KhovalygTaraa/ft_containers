/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:47:11 by swquinc           #+#    #+#             */
/*   Updated: 2021/08/14 19:47:12 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../vector/vector.hpp"
#include "set.hpp"
#include <map>
#include <set>

void print(std::string str) {
	std::string boundary(6 + str.length(), '=');

	std::cout << "\e[1;92m" << boundary << "\e[0m" << std::endl;
	std::cout << "\e[1;92m==\e[0m\e[1;94m " << str << " \e[0m\e[1;92m==\e[0m" << std::endl;
	std::cout << "\e[1;92m" << boundary << "\e[0m" << std::endl;
}

std::string ftrue() {
	return ("\e[0;92mtrue\e[0m");
}

std::string ffalse() {
	return ("\e[0;91mfalse\e[0m");
}

int main() {
	{
		ft::set<int> m;
		ft::set<int>::iterator it;

		m.insert(55);
		m.insert(22);
		m.insert(12);
		m.insert(1);
		m.insert( 11);
		m.insert(7);
		m.insert(3);
		m.insert(33);
		m.insert(8);
		m.insert(26);
		m.insert(155);
		m.insert(122);
		m.insert(112);
		m.insert(111);
		m.insert(17);
		m.insert(13);
		m.insert(133);
		m.insert(18);
		m.insert(126);

		print("insert");
		it = m.begin();

		while (it != m.end()) {
			std::cout << *it << std::endl;
			it++;
		}

		print("find");
		std::cout << *m.find(122) << std::endl;
		it = m.find(55);
		std::cout << *it << std::endl;
		it++;
		std::cout << *it << std::endl;
		it--;
		it--;
		std::cout << *it << std::endl;

		print("count");

		std::cout << "1000 is exist? - " << (m.count(1000) ? ftrue() : ffalse()) << std::endl;
		std::cout << "1    is exist? - " << (m.count(1) ? ftrue() : ffalse()) << std::endl;
		std::cout << "0    is exist? - " << (m.count(0) ? ftrue() : ffalse()) << std::endl;
		std::cout << "155  is exist? - " << (m.count(155) ? ftrue() : ffalse()) << std::endl;
		std::cout << "26   is exist? - " << (m.count(26) ? ftrue() : ffalse()) << std::endl;

		print("equal_range");

		ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> er;

		er = m.equal_range(133);
		std::cout << *er.first << std::endl;
		std::cout << *er.second << std::endl;

		print("upper_bound");

		std::cout << *m.upper_bound(133) << std::endl;
		std::cout << *m.upper_bound(1) << std::endl;
		std::cout << *m.upper_bound(2) << std::endl;

		print("lower_bound");

		std::cout << *m.lower_bound(133) << std::endl;
		std::cout << *m.lower_bound(1) << std::endl;
		std::cout << *m.lower_bound(2) << std::endl;

		print("empty");

		std::cout << m.empty() << std::endl;

		print("clear");

		m.clear();
		it = m.begin();
		std::cout << m.empty() << std::endl;

		while (it != m.end()) {
			std::cout << *it << std::endl;
			it++;
		}
		std::cout << std::endl;
		std::cout << "new test" << std::endl;

		{
			ft::set<int> m;
			ft::set<int>::iterator it;

			m.insert(55);
			m.insert(22);
			m.insert(12);
			m.insert(1);
			m.insert(11);
			m.insert(7);
			m.insert(3);
			m.insert(33);

			print("erase testing");
			print("before erase");
			it = m.begin();

			while (it != m.end()) {
				std::cout << *it << std::endl;
				it++;
			}

			print("after erase");

			m.erase(m.begin());
			m.erase(--m.end());

			it = m.begin();

			while (it != m.end()) {
				std::cout << *it << std::endl;
				it++;
			}
			print("size");

			std::cout << m.size() << std::endl;
			m.insert(323);
			std::cout << m.size() << std::endl;
			m.erase(12);
			std::cout << m.size() << std::endl;

			print("full erase");

			m.erase(m.begin(), m.end());
			it = m.begin();

			while (it != m.end()) {
				std::cout << *it << std::endl;
				it++;
			}
		}


		std::cout << std::endl;
		std::cout << "new test" << std::endl;
		{
			ft::set<int> m;
			ft::set<int>::iterator it;

			m.insert(55);
			m.insert(22);
			m.insert(12);
			m.insert(1);
			m.insert(11);
			m.insert(7);
			m.insert(3);
			m.insert(33);
		}
	}
}
